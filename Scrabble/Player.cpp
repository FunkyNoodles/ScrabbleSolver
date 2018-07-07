#include "Player.h"
#include "EnumUtils.h"
#include <unordered_set>
#include <queue>
#include <functional>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <string>


Player::Player(Board * board)
{
	this->board = board;
}

Player::~Player()
{
}

Placement Player::solve(TrieTracker& tracker, PlacementStrategy strategy)
{
	std::vector<Placement> results;
	std::string curWord;
	std::string curLetters;
	SeenTrie::SeenTrie * seen = new SeenTrie::SeenTrie();

	auto placementCmp = [](const Placement& lhs, const Placement& rhs) {
		return lhs.getScore() < rhs.getScore();
	};
	std::priority_queue<Placement, std::vector<Placement>,
		std::function<int(const Placement& x, const Placement&  y)> > solutions(placementCmp);

	auto searchSpace = buildSearchSpace();
	tracker.resetState();

	if (board->empty()) {
		seen->reset();
		for (std::pair<int, int> p : searchSpace) {
			int r = p.first;
			int c = p.second;
			seen->reset();
			solve(tracker, seen, r, c, r, c, PlacementType::DOWN, results, curWord, curLetters, true, 1, 0, 0);
		}
		
	}
	else {
		int lastSize = 0;
		for (int i = 0; i < Board::HEIGHT; ++i) {
			for (int j = 0; j < Board::WIDTH; ++j) {
				auto begin = std::chrono::steady_clock::now();
				if (board->getLetter(i - 1, j) == 0) {
					tracker.resetState();
					seen->reset();
					solve(tracker, seen, i, j, i, j, PlacementType::DOWN, results, curWord, curLetters, false, 1, 0, 0);
				}

				if (board->getLetter(i, j - 1) == 0) {
					tracker.resetState();
					seen->reset();
					solve(tracker, seen, i, j, i, j, PlacementType::CROSS, results, curWord, curLetters, false, 1, 0, 0);
				}
				auto end = std::chrono::steady_clock::now();
				//std::cout << i << "\t" << j << "\t" << results.size() - lastSize << std::endl;
				//std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0 << "ms" << std::endl;
				lastSize = results.size();
			}
		}
		//solve(tracker, seen, 0, 8, 0, 8, PlacementType::CROSS, results, curWord, curLetters, false, 1, 0, 0);
	}
	delete seen;

	for (auto r : results) {
		solutions.push(r);
	}
	Placement finalSolution;
	switch (strategy)
	{
	case PlacementStrategy::GREEDY:
		if (solutions.empty()) {
			finalSolution = Placement();
		}
		else {
			finalSolution = solutions.top();
		}
		break;
	default:
		break;
	}
	return finalSolution;
}

void Player::draw(LetterBag & bag)
{
	while (letters.size() < 7 && !bag.empty()) {
		letters.push_back(bag.getNext());
	}
}

void Player::removeAfterPlacement(Placement placement)
{
	std::string s = placement.getLetters();
	int numberOfFreeTiles = std::count_if(s.begin(), s.end(), [](const char c) {return std::islower(c);});
	auto itr = std::remove_if(letters.begin(), letters.end(),
		[&](const Letter & l) {
			if (l.getLetter() == ' ') {
				if (numberOfFreeTiles > 0) {
					--numberOfFreeTiles;
					return true;
				}
			}
			else {
				int exists = std::count(s.begin(), s.end(), l.getLetter());
				if (exists > 0) {
					int loc = s.find_first_of(l.getLetter());
					s.erase(loc, 1);
					return true;
				}
			}
			return false;
		}
	);
	letters.erase(itr, letters.end());
}

void Player::populateLetters(std::string initialLetters)
{
	for (char c : initialLetters) {
		letters.push_back(Letter(c, board->getLetterScore(c)));
	}
}

void Player::writeLetters(std::ostream & os)
{
	for (Letter l : letters) {
		os << l.getLetter() << " ";
	}
	os << std::endl;
}

bool Player::done() const
{
	return letters.empty();
}

int Player::tallyRemainingLetters() const
{
	int tally = 0;
	for (Letter l : letters) {
		tally += l.getValue();
	}
	return tally;
}

void Player::solve(TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
	const PlacementType type, std::vector<Placement> & results, std::string & curWord,
	std::string & curLetters, bool legalPlacement, int multiplier, int perpendicularWordScores, int score)
{
	int rinc, cinc;
	EnumUtils::setIncrements(type, rinc, cinc);
	
	if (tracker.isCurStateWord() && legalPlacement && board->getLetter(r, c) == 0 && curLetters.size() != 0) {
		int realScore = score * multiplier + perpendicularWordScores;
		if (curLetters.size() == 7) {
			// Bingo
			realScore += 50;
		}
		results.push_back(Placement(rStart, cStart, type, curLetters, realScore));
	}
	if (r >= Board::WIDTH || c >= Board::HEIGHT || r < 0 || c < 0) {
		// Out of bound, base case
		tracker.prev();
		return;
	}
	char curChar = board->getLetter(r, c);
	if (!letters.empty() && curChar == 0) {
		// Current location empty and have letters to use
		int size = letters.size();
		for (int i = 0; i < size; ++i) {
			Letter newLetter = letters.front();
			letters.pop_front();
			char newChar = newLetter.getLetter();
			if (newChar == ' ') {
				// Explore wild card tile substitutions
				for (char spaceSub = 'a'; spaceSub <= 'z'; ++spaceSub) {
					explore(tracker, seen, r, c, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
						multiplier, perpendicularWordScores, score, rinc, cinc, Letter(spaceSub, board->getLetterScore(' ')));
				}
			}
			else {
				explore(tracker, seen, r, c, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
					multiplier, perpendicularWordScores, score, rinc, cinc, newLetter);
			}
				
			letters.push_back(newLetter);
		}
	}
	else if (letters.empty() && curChar == 0) {
		// Current location empty and no more letters to use
		// Search for this location and orientation is done.
		// Carry on
	}
	else {
		// Current location not empty, needs to keep searching
		if (tracker.next(std::toupper(curChar))) {
			int scoreToAdd = board->getLetterScore(curChar);
			curWord.push_back(curChar);
			solve(tracker, seen, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, true,
				multiplier, perpendicularWordScores, score + scoreToAdd);
			curWord.pop_back();
		}
	}
	tracker.prev();
	return;
}

int Player::scorePlacedTile(TrieTracker & tracker, const int r, const int c, const PlacementType type, Letter tile)
{
	int rStart, cStart, rinc, cinc;
	EnumUtils::setIncrements(type, rinc, cinc);
	findStartIndices(r, c, rStart, cStart, type);
	int score = 0;
	int multiplier = 1;
	int rCur = rStart, cCur = cStart;
	int curCharScore = 0;
	char curChar = board->getLetter(rCur, cCur);
	int count = 0;
	// Create a fresh tracker to search if the perpendicular word is valid
	TrieTracker * perpendicularTracker = new TrieTracker(tracker, true);
	while (1) {
		
		if (rCur == r && cCur == c) {
			// At the location of intersection
			curChar = tile.getLetter();
			curCharScore = board->getTileScore(tile, r, c, multiplier);
		}
		else {
			// Not at the location of intersection
			curChar = board->getLetter(rCur, cCur);
			curCharScore = board->getLetterScore(curChar);
		}
		if (curChar == 0) {
			// If reached end or out of bound
			break;
		}
		++count;
		if (!perpendicularTracker->next(std::toupper(curChar))) {
			// Perpendicular word not valid
			return -1;
		}
		score += curCharScore;
		rCur += rinc;
		cCur += cinc;
	}
	if (count == 1) {
		// There is no valid intersecting words already placed.
		return 0;
	}
	int perpendicularScore = perpendicularTracker->isCurStateWord() ? score * multiplier : -1;
	delete perpendicularTracker;

	return perpendicularScore;
}

void Player::findStartIndices(const int r, const int c, int & rStart, int & cStart, const PlacementType type)
{
	int rdec, cdec;
	EnumUtils::setDecrements(type, rdec, cdec);
	int rCur = r, cCur = c;
	while (board->getLetter(rCur + rdec, cCur + cdec) != 0) {
		rCur += rdec;
		cCur += cdec;
	}
	rStart = rCur;
	cStart = cCur;
}

void Player::explore(TrieTracker & tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
	const PlacementType type, std::vector<Placement>& results, std::string & curWord, std::string & curLetters,
	bool legalPlacement, int multiplier, int perpendicularWordScores, int score, int rinc, int cinc, Letter newLetter)
{
	char newChar = newLetter.getLetter();
	// Score the newly placed tile
	int perpendicularWordScore = scorePlacedTile(tracker, r, c, EnumUtils::getOther(type), newLetter);
	if (perpendicularWordScore < 0) {
		return;
	}
	else if (perpendicularWordScore > 0) {
		legalPlacement = true;
	}
	// Check for premium spots
	int newMultiplier = multiplier;
	int scoreToAdd = board->getTileScore(newLetter, r, c, newMultiplier);

	curWord.push_back(newChar);
	curLetters.push_back(newChar);
	bool hasNext = seen->hasNext(newChar);
	if (hasNext == false && tracker.next(std::toupper(newChar))) {
	//if (tracker.next(newChar)) {
		seen->insert(newChar);
		seen->next(newChar);
		solve(tracker, seen, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
			newMultiplier, perpendicularWordScores + perpendicularWordScore, score + scoreToAdd);
		seen->prev();
	}
	curLetters.pop_back();
	curWord.pop_back();
}

std::list<std::pair<int, int>> Player::buildSearchSpace()
{
	std::list<std::pair<int, int>> searchSpace;

	if (board->empty()) {
		for (int i = 1; i < 8; ++i) {
			searchSpace.push_back(std::make_pair(i, Board::HEIGHT / 2));
		}
	}

	return searchSpace;
}

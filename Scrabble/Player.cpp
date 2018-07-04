#include "Player.h"
#include "EnumUtils.h"
#include <unordered_set>
#include <queue>
#include <functional>
#include <chrono>
#include <cctype>
#include <algorithm>
#include <string>


Player::Player()
{
}

Player::~Player()
{
}

Placement Player::solve(Board& board, TrieTracker& tracker, PlacementStrategy strategy)
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


	/*letters.push_back(Letter('S', board.getLetterScore('S')));
	letters.push_back(Letter('O', board.getLetterScore('O')));
	letters.push_back(Letter('B', board.getLetterScore('B')));
	letters.push_back(Letter('I', board.getLetterScore('I')));
	letters.push_back(Letter('A', board.getLetterScore('A')));
	letters.push_back(Letter(' ', board.getLetterScore(' ')));
	letters.push_back(Letter(' ', board.getLetterScore(' ')));*/

	/*letters.push_back(Letter('I', board.getLetterScore('I')));
	letters.push_back(Letter('A', board.getLetterScore('A')));
	letters.push_back(Letter('B', board.getLetterScore('B')));
	letters.push_back(Letter('O', board.getLetterScore('O')));
	letters.push_back(Letter('S', board.getLetterScore('S')));
	letters.push_back(Letter('O', board.getLetterScore('O')));
	letters.push_back(Letter('N', board.getLetterScore('N')));*/

	if (board.empty()) {
		seen->reset();
		solve(board, tracker, seen, board.WIDTH / 2, board.HEIGHT / 2, board.WIDTH / 2, board.HEIGHT / 2,
			PlacementType::CROSS, results, curWord, curLetters, true, 1, 0, 0);
	}
	else {
		int lastSize = 0;
		for (int i = 0; i < board.HEIGHT; ++i) {
			for (int j = 0; j < board.WIDTH; ++j) {
				auto begin = std::chrono::steady_clock::now();
				if (board.getLetter(i - 1, j) == 0) {
					tracker.resetState();
					seen->reset();
					solve(board, tracker, seen, i, j, i, j, PlacementType::DOWN, results, curWord, curLetters, false, 1, 0, 0);
				}

				if (board.getLetter(i, j - 1) == 0) {
					tracker.resetState();
					seen->reset();
					solve(board, tracker, seen, i, j, i, j, PlacementType::CROSS, results, curWord, curLetters, false, 1, 0, 0);
				}
				auto end = std::chrono::steady_clock::now();
				//std::cout << i << "\t" << j << "\t" << results.size() - lastSize << std::endl;
				//std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0 << "ms" << std::endl;
				lastSize = results.size();
			}
		}
		//tracker.resetState();
		//solve(board, tracker, seen, 2, 10, 2, 10, PlacementType::DOWN, results, curWord, curLetters, false, 1, 0, 0);
	}
	delete seen;

	for (auto r : results) {
		solutions.push(r);
	}
	/*int c0 = 0;
	while (c0 < 25 && !solutions.empty())
	{
		std::cout << solutions.top() << std::endl;
		solutions.pop();
		c0++;
	}*/
	Placement finalSolution;
	switch (strategy)
	{
	case PlacementStrategy::BEST:
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

void Player::solve(Board& board, TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
	const PlacementType type, std::vector<Placement> & results, std::string & curWord,
	std::string & curLetters, bool legalPlacement, int multiplier, int perpendicularWordScores, int score)
{
	int rinc, cinc;
	EnumUtils::setIncrements(type, rinc, cinc);
	
	if (tracker.isCurStateWord() && legalPlacement && board.getLetter(r, c) == 0) {
		int realScore = score * multiplier + perpendicularWordScores;
		if (letters.empty()) {
			// Bingo
			realScore += 50;
		}
		results.push_back(Placement(rStart, cStart, type, curLetters, realScore));
		//std::cout << curWord << "\t" << realScore << std::endl;
	}
	if (r >= board.WIDTH || c >= board.HEIGHT || r < 0 || c < 0) {
		tracker.prev();
		return;
	}
	if (!letters.empty()) {
		char curChar = std::toupper(board.getLetter(r, c));
		if (curChar == 0) {
			// Current location empty

			int size = letters.size();
			for (int i = 0; i < size; ++i) {
				Letter newLetter = letters.front();
				letters.pop_front();
				char newChar = newLetter.getLetter();
				if (newChar == ' ') {
					for (char spaceSub = 'a'; spaceSub <= 'z'; ++spaceSub) {
						explore(board, tracker, seen, r, c, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
							multiplier, perpendicularWordScores, score, rinc, cinc, Letter(spaceSub, board.getLetterScore(' ')));
					}
				}
				else {
					explore(board, tracker, seen, r, c, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
						multiplier, perpendicularWordScores, score, rinc, cinc, newLetter);
				}
				
				letters.push_back(newLetter);
			}

		}
		else {
			if (tracker.next(curChar)) {
				int scoreToAdd = board.getLetterScore(curChar);
				curWord.push_back(curChar);
				solve(board, tracker, seen, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, true,
					multiplier, perpendicularWordScores, score + scoreToAdd);
				curWord.pop_back();
			}
		}
	}
	tracker.prev();
	return;
}

int Player::scorePlacedTile(Board & board, TrieTracker & tracker, const int r, const int c, const PlacementType type, Letter tile)
{
	int rStart, cStart, rinc, cinc;
	EnumUtils::setIncrements(type, rinc, cinc);
	findStartIndices(board, r, c, rStart, cStart, type);
	int score = 0;
	int multiplier = 1;
	int rCur = rStart, cCur = cStart;
	int curCharScore = 0;
	char curChar = board.getLetter(rCur, cCur);
	char nextChar;
	int count = 0;
	while (1) {
		nextChar = board.getLetter(rCur + rinc, cCur + cinc);
		
		if (rCur == r && cCur == c) {
			curChar = std::toupper(tile.getLetter());
			curCharScore = board.getTileScore(tile, r, c, multiplier);
		}
		else {
			curChar = std::toupper(board.getLetter(rCur, cCur));
			curCharScore = board.getLetterScore(curChar);
		}
		if (curChar == 0) {
			break;
		}
		++count;
		if (!tracker.next(curChar)) {
			return -1;
		}
		score += curCharScore;
		rCur += rinc;
		cCur += cinc;
	}
	if (count == 1) {
		return 0;
	}
	return tracker.isCurStateWord() ? score * multiplier : -1;
}

void Player::findStartIndices(Board & board, const int r, const int c, int & rStart, int & cStart, const PlacementType type)
{
	int rdec, cdec;
	EnumUtils::setDecrements(type, rdec, cdec);
	int rCur = r, cCur = c;
	while (board.getLetter(rCur + rdec, cCur + cdec) != 0) {
		rCur += rdec;
		cCur += cdec;
	}
	rStart = rCur;
	cStart = cCur;
}

void Player::explore(Board & board, TrieTracker & tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
	const PlacementType type, std::vector<Placement>& results, std::string & curWord, std::string & curLetters,
	bool legalPlacement, int multiplier, int perpendicularWordScores, int score, int rinc, int cinc, Letter newLetter)
{
	char newChar = newLetter.getLetter();
	// Score the newly placed tile
	TrieTracker * perpendicularTracker = new TrieTracker(tracker);
	perpendicularTracker->resetState();
	int perpendicularWordScore = scorePlacedTile(board, *perpendicularTracker, r, c,
		EnumUtils::getOther(type), newLetter);
	delete perpendicularTracker;
	if (perpendicularWordScore < 0) {
		return;
	}
	else if (perpendicularWordScore > 0) {
		legalPlacement = true;
	}
	// Check for premium spots
	int newMultiplier = multiplier;
	int scoreToAdd = board.getTileScore(newLetter, r, c, newMultiplier);

	curWord.push_back(newChar);
	curLetters.push_back(newChar);
	bool hasNext = seen->hasNext(newChar);
	if (hasNext == false && tracker.next(std::toupper(newChar))) {
	//if (tracker.next(newChar)) {
		seen->insert(newChar);
		seen->next(newChar);
		solve(board, tracker, seen, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
			newMultiplier, perpendicularWordScores + perpendicularWordScore, score + scoreToAdd);
		seen->prev();
	}
	curLetters.pop_back();
	curWord.pop_back();
}

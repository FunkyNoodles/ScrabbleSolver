#include "Player.h"
#include "EnumUtils.h"
#include <iostream>
#include <unordered_set>
#include <queue>
#include <functional>


Player::Player()
{
	letters.push_back('S');
	letters.push_back('O');
	letters.push_back('B');
	letters.push_back('I');
	letters.push_back('A');
	letters.push_back('O');
	letters.push_back('N');
	/*letters.push_back('I');
	letters.push_back('N');
	letters.push_back('E');
	letters.push_back('Z');
	letters.push_back('R');
	letters.push_back('I');
	letters.push_back('U');*/
}

Player::~Player()
{
}

Placement Player::solve(Board& board, TrieTracker& tracker)
{
	std::vector<Placement> results;
	std::string curWord;
	std::string curLetters;

	auto placementCmp = [](const Placement& lhs, const Placement& rhs) {
		return lhs.getScore() < rhs.getScore();
	};
	std::priority_queue<Placement, std::vector<Placement>,
		std::function<int(const Placement& x, const Placement&  y)> > solutions(placementCmp);

	if (board.empty()) {
		solve(board, tracker, board.WIDTH / 2, board.HEIGHT / 2, board.WIDTH / 2, board.HEIGHT / 2, 
			PlacementType::CROSS, results, curWord, curLetters, true, 1, 0, 0);
	}
	else {
		for (int i = 0; i < board.HEIGHT / 2; ++i) {
			for (int j = 0; j < board.WIDTH; ++j) {
				tracker.resetState();
				solve(board, tracker, i, j, i, j, PlacementType::DOWN, results, curWord, curLetters, false, 1, 0, 0);
				tracker.resetState();
				solve(board, tracker, i, j, i, j, PlacementType::CROSS, results, curWord, curLetters, false, 1, 0, 0);
			}
		}
		//tracker.resetState();
		//solve(board, tracker, 6, 6, 6, 6, PlacementType::CROSS, results, curWord, curLetters, false, 1, 0, 0);
	}
	for (auto r : results) {
		solutions.push(r);
	}
	int c0 = 0;
	while (c0 < 25 && !solutions.empty())
	{
		std::cout << solutions.top() << std::endl;
		solutions.pop();
		c0++;
	}
	return Placement();
}

void Player::solve(Board& board, TrieTracker& tracker, const int r, const int c, const int rStart, const int cStart,
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
		results.push_back(Placement(rStart, cStart, type, curWord, realScore));
		//std::cout << curWord << "\t" << realScore << std::endl;
	}
	if (r >= board.WIDTH || c >= board.HEIGHT || r < 0 || c < 0) {
		tracker.prev();
		return;
	}
	if (!letters.empty()) {
		char curChar = board.getLetter(r, c);
		if (curChar == 0) {
			// Current location empty
			std::unordered_set<std::string> seen;

			int size = letters.size();
			for (int i = 0; i < size; ++i) {
				char newChar = letters.front();

				// Score the newly placed tile
				TrieTracker * perpendicularTracker = new TrieTracker(tracker);
				perpendicularTracker->resetState();
				int perpendicularWordScore = scorePlacedTile(board, *perpendicularTracker, r, c,
					EnumUtils::getOther(type), newChar);
				delete perpendicularTracker;
				if (perpendicularWordScore < 0) {
					// Cannot place this new tile
					letters.pop_front();
					letters.push_back(newChar);
					continue;
				}
				else if (perpendicularWordScore > 0) {
					legalPlacement = true;
				}
				// Check for premium spots
				int newMultiplier = multiplier;
				int scoreToAdd = board.getTileScore(newChar, r, c, newMultiplier);

				letters.pop_front();
				curWord.push_back(newChar);
				curLetters.push_back(newChar);
				if (seen.find(curLetters) == seen.end() && tracker.next(newChar)) {
				//if (tracker.next(newChar)) {
					solve(board, tracker, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, legalPlacement,
						newMultiplier, perpendicularWordScores + perpendicularWordScore, score + scoreToAdd);
				}
				seen.insert(curLetters);
				curLetters.pop_back();
				curWord.pop_back();
				letters.push_back(newChar);
			}
		}
		else {
			if (tracker.next(curChar)) {
				int scoreToAdd = board.getLetterScore(curChar);
				curWord.push_back(curChar);
				solve(board, tracker, r + rinc, c + cinc, rStart, cStart, type, results, curWord, curLetters, true,
					multiplier, perpendicularWordScores, score + scoreToAdd);
				curWord.pop_back();
			}
		}
	}
	tracker.prev();
	return;
}

int Player::scorePlacedTile(Board & board, TrieTracker & tracker, const int r, const int c, const PlacementType type, char tile)
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
			curChar = tile;
			curCharScore = board.getTileScore(tile, r, c, multiplier);
		}
		else {
			curChar = board.getLetter(rCur, cCur);
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

#include "Player.h"
#include "EnumUtils.h"
#include <iostream>


Player::Player()
{
	letters.push_back('I');
	letters.push_back('A');
	letters.push_back('B');
	letters.push_back('O');
	letters.push_back('S');
	letters.push_back('O');
	letters.push_back('N');
}

Player::~Player()
{
}

Placement Player::solve(Board& board, TrieTracker& tracker)
{
	std::vector<Placement> results;
	std::string curWord;
	if (board.empty()) {
		solve(board, tracker, board.WIDTH / 2, board.HEIGHT / 2, PlacementType::CROSS, results, curWord, true);
	}
	else {
		std::cout << scorePlacedTile(board, tracker, 6, 10, PlacementType::DOWN, 'E') << std::endl;
		tracker.resetState();
		solve(board, tracker, 2, 10, PlacementType::DOWN, results, curWord, false);
	}
	return Placement();
}

Placement Player::solve(Board& board, TrieTracker& tracker, const int r, const int c,
	const PlacementType type, std::vector<Placement> & results, std::string & curWord,
	bool legalPlacement)
{
	if (r > board.WIDTH || c > board.HEIGHT || r < 0 || c < 0) {
		return Placement();
	}
	int rinc, cinc;
	EnumUtils::setIncrements(type, rinc, cinc);
	
	if (tracker.isCurStateWord() && legalPlacement && board.getLetter(r, c) == 0) {
		if (curWord == "AIO") {
			std::cout << std::endl;
		}
		std::cout << curWord << std::endl;
	}
	if (!letters.empty()) {
		char curChar = board.getLetter(r, c);
		if (curChar == 0) {
			// Current location empty
			int size = letters.size();
			for (int i = 0; i < size; ++i) {
				char newChar = letters.front();

				letters.pop_front();
				curWord.push_back(newChar);
				if (tracker.next(newChar)) {
					solve(board, tracker, r + rinc, c + cinc, type, results, curWord, legalPlacement);
				}
				curWord.pop_back();
				letters.push_back(newChar);
			}
		}
		else {
			if (tracker.next(curChar)) {
				solve(board, tracker, r + rinc, c + cinc, type, results, curWord, true);
			}
		}
	}
	tracker.prev();
	return Placement();
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

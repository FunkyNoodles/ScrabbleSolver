#include "Player.h"
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
		solve(board, tracker, board.WIDTH / 2, board.HEIGHT / 2, PlacementType::CROSS, results, curWord);
	}
	else {
		solve(board, tracker, 2, 10, PlacementType::DOWN, results, curWord);
	}
	return Placement();
}

Placement Player::solve(Board& board, TrieTracker& tracker, const int r, const int c,
	const PlacementType type, std::vector<Placement> & results, std::string & curWord)
{
	int rinc, cinc;
	if (type == PlacementType::CROSS) {
		rinc = 0;
		cinc = 1;
	}
	else {
		rinc = 1;
		cinc = 0;
	}
	if (tracker.isCurStateWord()) {
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
					solve(board, tracker, r + rinc, c + cinc, type, results, curWord);
				}
				curWord.pop_back();
				letters.push_back(newChar);
			}
		}
		else {
			if (tracker.next(curChar)) {
				solve(board, tracker, r + rinc, c + cinc, type, results, curWord);
			}
		}
	}
	tracker.prev();
	return Placement();
}

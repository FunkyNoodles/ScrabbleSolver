#include "Player.h"
#include <iostream>


Player::Player()
{
	letters.push_back('T');
	letters.push_back('A');
	letters.push_back('B');
	//letters.push_back("E");
	//letters.push_back("W");
	//letters.push_back("O");
	//letters.push_back("P");
}

Player::~Player()
{
}

Placement Player::solve(const Board board)
{
	solve(board, 0, 0, PlacementType::CROSS, "");
	return Placement();
}

Placement Player::solve(const Board board, const int r, const int c, const PlacementType type, std::string curWord)
{
	if (letters.empty()) {
		std::cout << curWord << std::endl;
	}
	else {
		int size = letters.size();
		for (int i = 0; i < size; ++i) {
			char newChar = letters.front();
			letters.pop_front();
			curWord.push_back(newChar);
			solve(board, r, c, type, curWord);
			curWord.pop_back();
			letters.push_back(newChar);
		}
	}
	return Placement();
}

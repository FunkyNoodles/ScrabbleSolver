#include "Player.h"
#include <iostream>


Player::Player()
{
	letters.push_back('T');
	letters.push_back('A');
	letters.push_back('B');
	letters.push_back('E');
	letters.push_back('W');
	letters.push_back('O');
	letters.push_back('P');
}

Player::~Player()
{
}

Placement Player::solve(Board& board, Trie& trie)
{
	std::vector<Placement> results;
	std::string curWord;
	if (board.empty()) {
		solve(board, trie, board.WIDTH / 2, board.HEIGHT / 2, PlacementType::CROSS, results, curWord);
	}
	else {
		solve(board, trie, 0, 0, PlacementType::CROSS, results, curWord);
	}
	return Placement();
}

Placement Player::solve(Board& board, Trie& trie, const int r, const int c,
	const PlacementType type, std::vector<Placement> & results, std::string & curWord)
{
	if (trie.isCurStateWord()) {
		std::cout << curWord << std::endl;
	}
	if (letters.empty()) {
		//std::cout << curWord << std::endl;
	}
	else {
		int size = letters.size();
		for (int i = 0; i < size; ++i) {
			char newChar = letters.front();
			
			letters.pop_front();
			curWord.push_back(newChar);
			if (trie.next(newChar)) {
				solve(board, trie, r, c, type, results, curWord);
			}
			curWord.pop_back();
			letters.push_back(newChar);
		}
	}
	trie.prev();
	return Placement();
}

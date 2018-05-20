#pragma once
#include <list>
#include <vector>
#include <string>
#include "Board.h"
#include "Trie.h"
#include "Placement.h"

class Player
{
public:
	Player();
	~Player();

	Placement solve(Board& board, Trie& trie);
	Placement solve(Board& board, Trie& trie, const int r, const int c,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord);

private:
	std::list<char> letters;

};


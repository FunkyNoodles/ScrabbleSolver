#pragma once
#include <list>
#include <vector>
#include <string>
#include "Board.h"
#include "Trie.h"
#include "Placement.h"
#include "TrieTracker.h"

class Player
{
public:
	Player();
	~Player();

	Placement solve(Board& board, TrieTracker& trie);
	Placement solve(Board& board, TrieTracker& trie, const int r, const int c,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord);

private:
	std::list<char> letters;

};


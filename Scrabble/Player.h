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

	Placement solve(Board& board, TrieTracker& tracker);
	Placement solve(Board& board, TrieTracker& tracker, const int r, const int c,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord,
		bool legalPlacement);

private:
	std::list<char> letters;
	int scorePlacedTile(Board& board, TrieTracker& tracker, const int r, const int c,
		const PlacementType type, char tile);
	void findStartIndices(Board& board, const int r, const int c, int& rStart, int & cStart,
		const PlacementType type);
};


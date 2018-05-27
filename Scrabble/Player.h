#pragma once
#include <list>
#include <vector>
#include <string>
#include "Board.h"
#include "Trie.h"
#include "Placement.h"
#include "SeenTrie.h"
#include "TrieTracker.h"

class Player
{
public:
	Player();
	~Player();

	Placement solve(Board& board, TrieTracker& tracker);
	void solve(Board& board, TrieTracker& tracker, SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord, std::string & curLetters,
		bool legalPlacement, int multiplier, int perpendicularWordScores, int score);

private:
	std::list<char> letters;
	int scorePlacedTile(Board& board, TrieTracker& tracker, const int r, const int c,
		const PlacementType type, char tile);
	void findStartIndices(Board& board, const int r, const int c, int& rStart, int & cStart,
		const PlacementType type);
};


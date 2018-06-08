#pragma once
#include <list>
#include <vector>
#include <string>
#include "Board.h"
#include "Letter.h"
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
	void solve(Board& board, TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord, std::string & curLetters,
		bool legalPlacement, int multiplier, int perpendicularWordScores, int score);

private:
	std::list<Letter> letters;
	int scorePlacedTile(Board& board, TrieTracker& tracker, const int r, const int c,
		const PlacementType type, Letter tile);
	void findStartIndices(Board& board, const int r, const int c, int& rStart, int & cStart,
		const PlacementType type);

	void explore(Board& board, TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
		const PlacementType type, std::vector<Placement> & results, std::string & curWord, std::string & curLetters,
		bool legalPlacement, int multiplier, int perpendicularWordScores, int score, int rinc, int cinc, Letter newLetter);
};


#pragma once
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include "Board.h"
#include "Letter.h"
#include "Trie.h"
#include "Placement.h"
#include "SeenTrie.h"
#include "PlacementStrategy.h"
#include "TrieTracker.h"
#include "LetterBag.h"
#include "ThreadSafeVector.cpp"


class Player
{
public:
	Player(Board * board);
	~Player();

	Placement solve(Trie & trie, PlacementStrategy strategy);
	void draw(LetterBag & bag);
	void removeAfterPlacement(Placement placement);
	void populateLetters(std::string initialLetters);
	void writeLetters(std::ostream& os);
	bool done() const;
	int tallyRemainingLetters() const;

private:
	std::list<Letter> letters;
	Board * board;

	void multithreadedSolve(int id, Trie & trie, const int r, const int c,
		ThreadSafeVector<Placement> & results, PlacementType placementType);
	void solve(TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
		const PlacementType type, ThreadSafeVector<Placement> & results, std::list<Letter> & letters, std::string & curWord,
		std::string & curLetters, bool legalPlacement, int multiplier, int perpendicularWordScores, int score);
	int scorePlacedTile(TrieTracker& tracker, const int r, const int c,
		const PlacementType type, Letter tile);
	void findStartIndices(const int r, const int c, int& rStart, int & cStart,
		const PlacementType type);
	void explore(TrieTracker& tracker, SeenTrie::SeenTrie * seen, const int r, const int c, const int rStart, const int cStart,
		const PlacementType type, ThreadSafeVector<Placement> & results, std::list<Letter> & letters, std::string & curWord,
		std::string & curLetters, bool legalPlacement, int multiplier, int perpendicularWordScores, int score, int rinc, int cinc, Letter newLetter);
	std::list<std::pair<int, int> > buildSearchSpace();
};


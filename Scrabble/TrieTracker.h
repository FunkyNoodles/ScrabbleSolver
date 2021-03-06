#pragma once
#include "Trie.h"

class TrieTracker
{
public:
	TrieTracker(Trie & trie);
	TrieTracker(const TrieTracker& tracker, bool reset);
	~TrieTracker();

	void resetState();
	bool next(char nextChar);
	void prev();
	bool isCurStateWord();
private:
	TrieNode * root;
	TrieNode * curState;
};


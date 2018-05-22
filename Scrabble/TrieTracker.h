#pragma once
#include "Trie.h"

class TrieTracker
{
public:
	TrieTracker(Trie * trie);
	~TrieTracker();

	void resetState();
	bool next(char nextChar);
	void prev();
	bool isCurStateWord();
private:
	TrieNode * root;
	TrieNode * curState;
};

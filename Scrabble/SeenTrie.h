#pragma once
#include "Trie.h"

class SeenTrie
{
public:
	SeenTrie();
	~SeenTrie();


	void reset();
	void insert(char c);
	bool hasNext(char nextChar);
	bool next(char nextChar);
	void prev();
private:
	TrieNode * root;
	TrieNode * curState;
	void deleteNodes(TrieNode * root);
};


#pragma once
#include <string>

const int SIZE = 26;
const int OFFSET = 65;

class TrieNode {
public:
	TrieNode * * children = nullptr;
	bool isWord = false;

	TrieNode() {
		children = new TrieNode*[SIZE];
		for (int i = 0; i < SIZE; ++i) {
			children[i] = nullptr;
		}
	}

	~TrieNode() {
		delete[] children;
		children = nullptr;
	}
};

class Trie
{
public:
	Trie();
	~Trie();

	bool buildTrie(std::string file);
	void insert(std::string str);
	bool find(std::string str);
private:
	TrieNode * root;
	void deleteNodes(TrieNode * root);
};


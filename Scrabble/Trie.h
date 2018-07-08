#pragma once
#include <string>

const int ALPHABET_SIZE = 26;
const int OFFSET = 65;

class TrieNode {
public:
	TrieNode * * children = nullptr;
	TrieNode * parent;
	bool isWord = false;

	TrieNode(TrieNode * parent) {
		children = new TrieNode*[ALPHABET_SIZE];
		this->parent = parent;
		for (int i = 0; i < ALPHABET_SIZE; ++i) {
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

	TrieNode * getRoot();
private:
	TrieNode * root;
	void deleteNodes(TrieNode * root);
};


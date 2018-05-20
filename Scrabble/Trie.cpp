#include "Trie.h"
#include <fstream>
#include <cctype>
#include <stdexcept>


Trie::Trie()
{
	root = new TrieNode(nullptr);
	curState = root;
}

Trie::~Trie()
{
	deleteNodes(root);
}

bool Trie::buildTrie(std::string file)
{
	std::ifstream dictionaryFile(file);
	if (!dictionaryFile.is_open()) {
		return false;
	}
	std::string line;
	while (std::getline(dictionaryFile, line))
	{
		insert(line);
	}
	dictionaryFile.close();
	return false;
}

void Trie::insert(std::string str)
{
	TrieNode * cur = root;
	for (char& c : str) {
		if (!std::isupper(c)) {
			throw std::out_of_range("Letters in words must be upper cases");
		}

		if (cur->children[c - OFFSET] == nullptr) {
			cur->children[c - OFFSET] = new TrieNode(cur);
		}
		cur = cur->children[c - OFFSET];
	}
	cur->isWord = true;
}

bool Trie::find(std::string str)
{
	TrieNode * cur = root;
	for (char& c : str) {
		if (cur->children[c - OFFSET] == nullptr) {
			return false;
		}
		cur = cur->children[c - OFFSET];
	}
	return cur->isWord;
}

void Trie::resetState()
{
	curState = root;
}

bool Trie::next(char nextChar)
{
	TrieNode * nextState = curState->children[nextChar - OFFSET];
	if (nextState != nullptr) {
		curState = nextState;
		return true;
	}
	return false;
}

void Trie::prev()
{
	if (curState != root) {
		curState = curState->parent;
	}
}

bool Trie::isCurStateWord()
{
	return curState->isWord;
}

void Trie::deleteNodes(TrieNode * root)
{
	if (root == nullptr) {
		return;
	}
	for (int i = 0; i < SIZE; ++i) {
		deleteNodes(root->children[i]);
	}
	delete root;
}

#include "SeenTrie.h"



SeenTrie::SeenTrie::SeenTrie()
{
	root = new SeenTrieNode(nullptr);
	curState = root;
}

SeenTrie::SeenTrie::~SeenTrie()
{
	deleteNodes(root);
}

void SeenTrie::SeenTrie::reset()
{
	deleteNodes(root);
	root = new SeenTrieNode(nullptr);
	curState = root;
}

void SeenTrie::SeenTrie::insert(char c)
{
	if (curState->children[charToIndex(c)] == nullptr) {
		curState->children[charToIndex(c)] = new SeenTrieNode(curState);
	}
}

bool SeenTrie::SeenTrie::hasNext(char nextChar)
{
	SeenTrieNode * nextState = curState->children[charToIndex(nextChar)];
	if (nextState != nullptr) {
		return true;
	}
	return false;
}

bool SeenTrie::SeenTrie::next(char nextChar)
{
	SeenTrieNode * nextState = curState->children[charToIndex(nextChar)];
	if (nextState != nullptr) {
		curState = nextState;
		return true;
	}
	return false;
}

void SeenTrie::SeenTrie::prev()
{
	if (curState != root) {
		curState = curState->parent;
	}
}

void SeenTrie::SeenTrie::deleteNodes(SeenTrieNode * root)
{
	if (root == nullptr) {
		return;
	}
	for (int i = 0; i < SIZE; ++i) {
		deleteNodes(root->children[i]);
	}
	delete root;
}

int SeenTrie::SeenTrie::charToIndex(char c)
{
	int i = c - UPPER_OFFSET;
	if (i > 25) {
		i = c - LOWER_OFFSET + 26;
	}
	return i;
}

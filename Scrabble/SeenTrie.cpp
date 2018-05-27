#include "SeenTrie.h"



SeenTrie::SeenTrie()
{
	root = new TrieNode(nullptr);
	curState = root;
}

SeenTrie::~SeenTrie()
{
	deleteNodes(root);
}

void SeenTrie::reset()
{
	deleteNodes(root);
	root = new TrieNode(nullptr);
	curState = root;
}

void SeenTrie::insert(char c)
{
	if (curState->children[c - OFFSET] == nullptr) {
		curState->children[c - OFFSET] = new TrieNode(curState);
	}
}

bool SeenTrie::hasNext(char nextChar)
{
	TrieNode * nextState = curState->children[nextChar - OFFSET];
	if (nextState != nullptr) {
		return true;
	}
	return false;
}

bool SeenTrie::next(char nextChar)
{
	TrieNode * nextState = curState->children[nextChar - OFFSET];
	if (nextState != nullptr) {
		curState = nextState;
		return true;
	}
	return false;
}

void SeenTrie::prev()
{
	if (curState != root) {
		curState = curState->parent;
	}
}

void SeenTrie::deleteNodes(TrieNode * root)
{
	if (root == nullptr) {
		return;
	}
	for (int i = 0; i < SIZE; ++i) {
		deleteNodes(root->children[i]);
	}
	delete root;
}

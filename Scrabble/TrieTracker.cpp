#include "TrieTracker.h"



TrieTracker::TrieTracker(Trie * trie)
{
	root = trie->getRoot();
	curState = root;
}

TrieTracker::TrieTracker(const TrieTracker & tracker, bool reset)
{
	root = tracker.root;
	curState = tracker.curState;
	if (reset) {
		resetState();
	}
}

TrieTracker::~TrieTracker()
{
}

void TrieTracker::resetState()
{
	curState = root;
}

bool TrieTracker::next(char nextChar)
{
	TrieNode * nextState = curState->children[nextChar - OFFSET];
	if (nextState != nullptr) {
		curState = nextState;
		return true;
	}
	return false;
}

void TrieTracker::prev()
{
	if (curState != root) {
		curState = curState->parent;
	}
}

bool TrieTracker::isCurStateWord()
{
	return curState->isWord;
}

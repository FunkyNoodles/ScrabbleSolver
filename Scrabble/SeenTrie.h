#pragma once

namespace SeenTrie
{
	const int SIZE = 26 * 2;
	const int UPPER_OFFSET = 65;
	const int LOWER_OFFSET = 97;
	class SeenTrieNode {
	public:
		SeenTrieNode * * children = nullptr;
		SeenTrieNode * parent;
		bool isWord = false;

		

		SeenTrieNode(SeenTrieNode * parent) {
			children = new SeenTrieNode*[SIZE];
			this->parent = parent;
			for (int i = 0; i < SIZE; ++i) {
				children[i] = nullptr;
			}
		}

		~SeenTrieNode() {
			delete[] children;
			children = nullptr;
		}
	};

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
		SeenTrieNode * root;
		SeenTrieNode * curState;

		void deleteNodes(SeenTrieNode * root);
		int charToIndex(char c);
	};
}

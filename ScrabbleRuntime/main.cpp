#include "../Scrabble/LetterBag.h"
#include "../Scrabble/Dictionary.h"
#include "../Scrabble/Trie.h"

#include <vld.h>
#include <iostream>

int main() {
	LetterBag letterBag;
	//Dictionary dictionary;
	Trie trie;
	trie.buildTrie("dictionary.txt");

	std::cout << trie.find("POD") << "\t" << trie.find("VEAL") << "\t" << trie.find("DUC") << std::endl;
	return 0;
}

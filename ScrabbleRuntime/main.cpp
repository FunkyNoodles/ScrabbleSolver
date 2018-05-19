#include "../Scrabble/LetterBag.h"
#include "../Scrabble/Dictionary.h"
#include "../Scrabble/Trie.h"
#include "../Scrabble/Player.h"
#include "../Scrabble/Board.h"

#include <vld.h>
#include <iostream>
#include <chrono>
#include <string>

int main() {
	LetterBag letterBag;
	//Dictionary dictionary;
	//Trie trie;
	//trie.buildTrie("dictionary.txt");

	//std::cout << trie.find("POD") << "\t" << trie.find("VEAL") << "\t" << trie.find("DUC") << std::endl;

	Player player;
	Board b;
	player.solve(b);
	std::cout << "Done" << std::endl;
	while(1){}
	return 0;
}

#include "../Scrabble/LetterBag.h"
#include "../Scrabble/Dictionary.h"
#include "../Scrabble/Trie.h"
#include "../Scrabble/Player.h"
#include "../Scrabble/Board.h"
#include "../Scrabble/Placement.h"
#include "../Scrabble/TrieTracker.h"

#include <vld.h>
#include <iostream>
#include <chrono>
#include <string>

int main() {
	LetterBag letterBag;
	//Dictionary dictionary;
	Trie trie;
	std::cout << "Loading dictionary..." << std::endl;
	auto begin = std::chrono::steady_clock::now();
	trie.buildTrie("dictionary.txt");
	auto end = std::chrono::steady_clock::now();
	std::cout << "Dictionary loaded, took " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000.0 << " s"<< std::endl;
	TrieTracker tracker(&trie);


	Player player;
	Board b;

	Placement p0(7, 7, PlacementType::CROSS, "WEPT", 18);
	//Placement p1(5, 10, PlacementType::DOWN, "LI", 3);
	Placement p1(7, 9, PlacementType::DOWN, "I", 3);
	b.place(p0);
	b.place(p1);
	std::cout << b << std::endl;

	begin = std::chrono::steady_clock::now();
	player.solve(b, tracker);
	end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << std::endl;
	std::cout << b;
	std::cout << "Done" << std::endl;
	while(1){}
	return 0;
}

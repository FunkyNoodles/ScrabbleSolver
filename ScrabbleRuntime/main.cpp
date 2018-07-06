#include "../Scrabble/LetterBag.h"
#include "../Scrabble/Dictionary.h"
#include "../Scrabble/Trie.h"
#include "../Scrabble/Player.h"
#include "../Scrabble/Board.h"
#include "../Scrabble/Placement.h"
#include "../Scrabble/TrieTracker.h"
#include "../Scrabble/PlacementStrategy.h"

#include <vld.h>
#include <iostream>
#include <chrono>
#include <string>
#include <fstream>

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


	Player player1, player2;
	bool player1Pass = false, player2Pass = false;
	int player1Score = 0, player2Score = 0;
	TrieTracker tracker1(&trie);
	TrieTracker tracker2(&trie);
	Board b;

	/*std::ifstream inputTestBoard;
	inputTestBoard.open("InputTestBoard.txt");
	if (inputTestBoard.is_open()) {
		inputTestBoard >> b;
	}
	inputTestBoard.close();*/

	std::cout << b << std::endl;

	player1.draw(letterBag);
	player2.draw(letterBag);

	std::ofstream testBoardLog;
	testBoardLog.open("TestBoardLog.log");
	while (!(player1Pass && player2Pass)) {
		player1Pass = false;
		player2Pass = false;

		tracker1.resetState();
		Placement sol1 = player1.solve(b, tracker1, PlacementStrategy::BEST);
		player1.writeLetters(std::cout);
		player1.writeLetters(testBoardLog);
		std::cout << sol1.getScore() << std::endl;
		player1.removeAfterPlacement(sol1);
		player1.draw(letterBag);
		if (sol1.getScore() >= 0) {
			b.place(sol1);
			player1Score += sol1.getScore();
			if (player1.done() && letterBag.empty()) {
				break;
			}
		}
		else {
			player1Pass = true;
		}
		testBoardLog << b;
		std::cout << b;
		//std::cin.get();

		tracker2.resetState();
		Placement sol2 = player2.solve(b, tracker2, PlacementStrategy::BEST);
		player2.writeLetters(std::cout);
		player2.writeLetters(testBoardLog);
		std::cout << sol2.getScore() << std::endl;
		player2.removeAfterPlacement(sol2);
		player2.draw(letterBag);
		if (sol2.getScore() >= 0) {
			b.place(sol2);
			player2Score += sol2.getScore();
			if (player2.done() && letterBag.empty()) {
				break;
			}
		}
		else {
			player2Pass = true;
		}
		std::cout << player1Score << ' ' << player2Score << std::endl;

		testBoardLog << b;
		std::cout << b;
		/*std::cin.get();*/
	}
	testBoardLog.close();
	std::cout << player1Score << ' ' << player2Score << std::endl;
	player1Score += player2.tallyRemainingLetters();
	player2Score += player1.tallyRemainingLetters();
	std::cout << player1Score << ' ' << player2Score << std::endl;

	/*begin = std::chrono::steady_clock::now();
	Placement ps = player1.solve(b, tracker1, PlacementStrategy::BEST);
	end = std::chrono::steady_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000.0 << std::endl;
	b.place(ps);*/
	std::cout << b;
	std::cout << "Done" << std::endl;
	return 0;
}

#include "gtest/gtest.h"
#include "../Scrabble/LetterBag.h"
#include "../Scrabble/Dictionary.h"
#include "../Scrabble/Trie.h"
#include "../Scrabble/Player.h"
#include "../Scrabble/Board.h"
#include "../Scrabble/Placement.h"
#include "../Scrabble/TrieTracker.h"
#include "../Scrabble/PlacementStrategy.h"

#include <fstream>
#include <chrono>
#include <string>

class PlayerBenchmark : public ::testing::Test {
protected:

	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(PlayerBenchmark, solveCorrect) {

	Trie trie;
	trie.buildTrie("../../ScrabbleRuntime/dictionary.txt");
	LetterBag letterBag(0);

	int numberOfTestBoards = 3;
	int iterations = 10;
	std::ifstream inputTestBoard;
	std::ofstream benchmarkResults("BenchmarkResults.txt");

	for (int i = 0; i < numberOfTestBoards; ++i) {
		long long timeSum = 0;
		for (int j = 0; j < iterations; ++j) {
			Board board(&letterBag);
			Player player(&board);

			std::string fileName = "../../ScrabbleTests/PlayerBenchmark/Board" + std::to_string(i) + ".txt";
			std::string initialLetters, expectedScoreString;
			int expectedScore;
			inputTestBoard.open(fileName);
			if (inputTestBoard.is_open()) {
				std::getline(inputTestBoard, initialLetters);
				std::getline(inputTestBoard, expectedScoreString);
				expectedScore = std::stoi(expectedScoreString);
				inputTestBoard >> board;
				inputTestBoard.close();
			}
			else {
				continue;
			}

			player.populateLetters(initialLetters);
			TrieTracker tracker(&trie);
			auto begin = std::chrono::steady_clock::now();
			Placement result = player.solve(tracker, PlacementStrategy::GREEDY);
			auto end = std::chrono::steady_clock::now();
			timeSum += std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
			if (result.getScore() == 40) {
				std::cout << "wrong" << std::endl;
			}
			EXPECT_EQ(result.getScore(), expectedScore);
		}
		benchmarkResults << "Test " << i << " took " << timeSum / 1000.0 / iterations << " ms" << std::endl;
	}
	benchmarkResults.close();
}
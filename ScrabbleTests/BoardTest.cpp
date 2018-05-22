#include "gtest/gtest.h"
#include "../Scrabble/Board.h"
#include <fstream>

class BoardTest : public ::testing::Test {
protected:
	virtual void setUp() {
	}

	virtual void tearDown() {
	}
};

TEST_F(BoardTest, getBoardTypeCorrect) {
	Board board;
	EXPECT_EQ(board.getBoardType(7, 7), BoardType::DOUBLE_WORD);
	EXPECT_EQ(board.getBoardType(9, 7), BoardType::NONE);
	EXPECT_EQ(board.getBoardType(12, 12), BoardType::DOUBLE_WORD);
	EXPECT_EQ(board.getBoardType(14, 0), BoardType::TRIPLE_WORD);
	EXPECT_EQ(board.getBoardType(5, 13), BoardType::TRIPLE_LETTER);
}

TEST_F(BoardTest, ioCorrect) {
	Placement p0(0, 0, PlacementType::CROSS, "WEPT", 0);
	Placement p1(0, 3, PlacementType::DOWN, "AP", 0);
	Board board;
	board.place(p0);
	board.place(p1);
	std::ofstream oFile;
	oFile.open("test.txt");
	oFile << board;
	oFile.close();
	std::ifstream iFile;
	iFile.open("test.txt");
	Board boardIn;
	iFile >> boardIn;
	iFile.close();
	EXPECT_EQ(board, boardIn);
}
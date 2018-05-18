#include "gtest/gtest.h"
#include "../Scrabble/Board.h"

class BoardTest : public ::testing::Test {
protected:
	virtual void setUp() {
	}

	virtual void tearDown() {
	}
};

TEST(GetBoardType, correct) {
	Board board;
	EXPECT_EQ(board.getBoardType(7, 7), BoardType::DOUBLE_WORD);
	EXPECT_EQ(board.getBoardType(9, 7), BoardType::NONE);
	EXPECT_EQ(board.getBoardType(12, 12), BoardType::DOUBLE_WORD);
	EXPECT_EQ(board.getBoardType(14, 0), BoardType::TRIPLE_WORD);
	EXPECT_EQ(board.getBoardType(5, 13), BoardType::TRIPLE_LETTER);
}
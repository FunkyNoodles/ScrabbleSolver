#include "Board.h"
#include <utility>


Board::Board()
{
	populateQuarterBoardTypes();
	board = new Letter *[HEIGHT];
	for (int i = 0; i < HEIGHT; ++i) {
		board[i] = new Letter[WIDTH];
	}
}

Board::Board(const Board & b)
{
	board = new Letter *[HEIGHT];
	for (int i = 0; i < HEIGHT; ++i) {
		board[i] = new Letter[WIDTH];
	}
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			board[i][j] = b.board[i][j];
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < HEIGHT; ++i) {
		delete[] board[i];
	}
	delete[] board;
}

BoardType Board::getBoardType(const int r, const int c)
{
	int reducedR = reduceIndex(r);
	int reducedC = reduceIndex(c);
	auto it = quarterBoardTypes.find(std::make_pair(reducedR, reducedC));
	if (it == quarterBoardTypes.end()) {
		return BoardType::NONE;
	}
	return it->second;
}

void Board::populateQuarterBoardTypes()
{
	// Triple word
	quarterBoardTypes[std::make_pair(0, 0)] = BoardType::TRIPLE_WORD;
	quarterBoardTypes[std::make_pair(0, 7)] = BoardType::TRIPLE_WORD;
	quarterBoardTypes[std::make_pair(7, 0)] = BoardType::TRIPLE_WORD;

	// Double word
	quarterBoardTypes[std::make_pair(1, 1)] = BoardType::DOUBLE_WORD;
	quarterBoardTypes[std::make_pair(2, 2)] = BoardType::DOUBLE_WORD;
	quarterBoardTypes[std::make_pair(3, 3)] = BoardType::DOUBLE_WORD;
	quarterBoardTypes[std::make_pair(4, 4)] = BoardType::DOUBLE_WORD;
	quarterBoardTypes[std::make_pair(7, 7)] = BoardType::DOUBLE_WORD;

	// Triple letter
	quarterBoardTypes[std::make_pair(1, 5)] = BoardType::TRIPLE_LETTER;
	quarterBoardTypes[std::make_pair(5, 5)] = BoardType::TRIPLE_LETTER;
	quarterBoardTypes[std::make_pair(5, 1)] = BoardType::TRIPLE_LETTER;

	// Double letter
	quarterBoardTypes[std::make_pair(0, 3)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(0, 3)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(2, 6)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(6, 2)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(7, 3)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(3, 7)] = BoardType::DOUBLE_LETTER;

}

int Board::reduceIndex(const int i)
{
	if (i <= WIDTH / 2) {
		return i;
	}
	else {
		return WIDTH / 2 - (i - WIDTH / 2);
	}
}



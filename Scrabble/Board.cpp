#include "Board.h"
#include "EnumUtils.h"
#include <utility>


Board::Board()
{
	letterBag = new LetterBag();
	populateQuarterBoardTypes();
	board = new char *[HEIGHT];
	for (int i = 0; i < HEIGHT; ++i) {
		board[i] = new char[WIDTH];
	}
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < WIDTH; ++j) {
			board[i][j] = 0;
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < HEIGHT; ++i) {
		delete[] board[i];
	}
	delete[] board;
	delete letterBag;
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

char Board::getLetter(const int r, const int c) const
{
	if (r >= WIDTH || c >= HEIGHT || r < 0 || c < 0) {
		return 0;
	}
	return board[r][c];
}

void Board::setLetter(const int r, const int c, const char ch)
{
	if (r > WIDTH || c > HEIGHT || r < 0 || c < 0) {
		throw std::out_of_range("Board index out of range");
	}
	board[r][c] = ch;
}

bool Board::place(Placement placement)
{
	isEmpty = false;
	int r = placement.getX();
	int c = placement.getY();
	int rinc, cinc;
	EnumUtils::setIncrements(placement.getPlacementType(), rinc, cinc);

	int i = 0;
	while (i < placement.getLetters().size()) {
		const char & ch = placement.getLetters()[i];
		if (board[r][c] == 0) {
			board[r][c] = ch;
			++i;
		}
		r += rinc;
		c += cinc;
	}
	return false;
}

int Board::getLetterScore(char tile)
{
	return letterBag->getLetterScore(tile);
}

int Board::getTileScore(Letter letter, const int r, const int c, int & multiplier)
{
	int letterScore = letter.getValue();
	switch (getBoardType(r, c)) {
	case BoardType::TRIPLE_WORD:
		multiplier *= 3;
		break;
	case BoardType::DOUBLE_WORD:
		multiplier *= 2;
		break;
	case BoardType::TRIPLE_LETTER:
		letterScore *= 3;
		break;
	case BoardType::DOUBLE_LETTER:
		letterScore *= 2;
		break;
	default:;
	}
	return letterScore;
}

bool Board::operator==(const Board & other) const
{
	for (int i = 0; i < WIDTH; ++i) {
		for (int j = 0; j < HEIGHT; ++j) {
			if (board[i][j] != other.getLetter(i, j)) {
				return false;
			}
		}
	}
	return true;
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
	quarterBoardTypes[std::make_pair(3, 0)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(2, 6)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(6, 2)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(7, 3)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(3, 7)] = BoardType::DOUBLE_LETTER;
	quarterBoardTypes[std::make_pair(6, 6)] = BoardType::DOUBLE_LETTER;

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

std::ostream & operator<<(std::ostream & os, const Board & board)
{
	for (int i = 0; i < board.WIDTH; ++i) {
		for (int j = 0; j < board.HEIGHT; ++j) {
			char c = board.getLetter(i, j);
			if (c == 0) {
				os << '.';
			}
			else {
				os << c;
			}
		}
		os << std::endl;
	}
	return os;
}

std::istream & operator>>(std::istream & is, Board & board)
{
	char c;
	for (int i = 0; i < board.WIDTH; ++i) {
		for (int j = 0; j < board.HEIGHT; ++j) {
			is >> c;
			c = (c == '.') ? 0 : c;
			board.setLetter(i, j, c);
		}
	}
	return is;
}

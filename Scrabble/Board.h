#pragma once
#include "Letter.h"

#include <map>
#include <unordered_map>
#include <vector>
#include <boost/container_hash/hash.hpp>

enum class BoardType
{
	TRIPLE_WORD,
	DOUBLE_WORD,
	TRIPLE_LETTER,
	DOUBLE_LETTER,
	NONE
};

class Board
{
public:
	const int WIDTH = 15, HEIGHT = 15;

	Board();
	Board(const Board & b);
	~Board();

	BoardType getBoardType(const int r, const int c);

private:
	Letter * * board;
	std::unordered_map<std::pair<int, int>, BoardType, boost::hash<std::pair<int, int>>> quarterBoardTypes;

	void populateQuarterBoardTypes();
	int reduceIndex(const int i);
	
};


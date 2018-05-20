#pragma once
#include "Letter.h"
#include "Placement.h"

#include <map>
#include <unordered_map>
#include <vector>
#include <boost/container_hash/hash.hpp>
#include <iostream>

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
	const static int WIDTH = 15, HEIGHT = 15;

	Board();
	Board(const Board & b);
	~Board();

	BoardType getBoardType(const int r, const int c);
	char getLetter(const int r, const int c) const;
	bool place(Placement placement);
	bool empty() const { return isEmpty; }

	friend std::ostream& operator<<(std::ostream& os, const Board& board);

private:
	char * * board;
	bool isEmpty = true;
	std::unordered_map<std::pair<int, int>, BoardType, boost::hash<std::pair<int, int>>> quarterBoardTypes;

	void populateQuarterBoardTypes();
	int reduceIndex(const int i);
	
};


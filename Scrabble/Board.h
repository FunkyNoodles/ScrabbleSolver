#pragma once
#include "Letter.h"
#include "Placement.h"
#include "LetterBag.h"

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
	~Board();

	BoardType getBoardType(const int r, const int c);
	char getLetter(const int r, const int c) const;
	void setLetter(const int r, const int c, const char ch);
	bool place(Placement placement);
	bool empty() const { return isEmpty; }
	int getLetterScore(char tile);
	int getTileScore(Letter letter, const int r, const int c, int& multiplier);

	friend std::ostream& operator<<(std::ostream& os, const Board& board);
	friend std::istream& operator>>(std::istream& is, Board& board);
	bool operator==(const Board& other) const;

private:
	char * * board;
	bool isEmpty = true;
	std::unordered_map<std::pair<int, int>, BoardType, boost::hash<std::pair<int, int>>> quarterBoardTypes;
	LetterBag * letterBag;

	void populateQuarterBoardTypes();
	int reduceIndex(const int i);
	
};


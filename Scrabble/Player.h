#pragma once
#include <list>
#include <string>
#include "Board.h"
#include "Placement.h"

class Player
{
public:
	std::list<char> letters;

	Player();
	~Player();

	Placement solve(const Board board);
	Placement solve(const Board board, const int r, const int c, const PlacementType type, std::string curWord);
};


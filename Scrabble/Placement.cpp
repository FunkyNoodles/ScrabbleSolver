#include "Placement.h"



Placement::Placement()
{
}

Placement::Placement(const int x, const int y, const PlacementType type, const std::string letters, const int score)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->letters = letters;
	this->score = score;
}

Placement::~Placement()
{
}

int Placement::getX() const
{
	return x;
}

int Placement::getY() const
{
	return y;
}

int Placement::getScore() const
{
	return score;
}

const PlacementType & Placement::getPlacementType() const
{
	return type;
}

const std::string & Placement::getLetters() const
{
	return letters;
}

#include "Placement.h"



Placement::Placement()
{
}

Placement::Placement(const int x, const int y, const PlacementType type, const std::string word, const int score)
{
	this->x = x;
	this->y = y;
	this->type = type;
	this->word = word;
	this->score = score;
}

Placement::~Placement()
{
}

const int & Placement::getX() const
{
	return x;
}

const int & Placement::getY() const
{
	return y;
}

const int & Placement::getScore() const
{
	return score;
}

const PlacementType & Placement::getPlacementType() const
{
	return type;
}

const std::string & Placement::getWord() const
{
	return word;
}

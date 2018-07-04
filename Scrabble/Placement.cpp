#include "Placement.h"



Placement::Placement()
{
	this->score = -1;
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

std::ostream & operator<<(std::ostream & os, const Placement & p)
{
	std::string typeStr = (p.getPlacementType() == PlacementType::DOWN) ? "DOWN" : "CROSS";
	os << p.getX() << "\t" << p.getY() << "\t" << typeStr << "\t" << p.getLetters() << "\t" << p.getScore();
	return os;
}

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

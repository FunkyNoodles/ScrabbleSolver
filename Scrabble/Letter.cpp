#include "Letter.h"

Letter::Letter(char letter, int value)
{
	this->letter = letter;
	this->value = value;
}

Letter::~Letter()
{
}

char Letter::getLetter() const
{
	return this->letter;
}

int Letter::getValue() const
{
	return this->value;
}

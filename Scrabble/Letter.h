#pragma once
class Letter
{
public:
	Letter(char letter, int value);
	~Letter();

	char getLetter();
	int getValue();

private:
	char letter;
	int value;
};


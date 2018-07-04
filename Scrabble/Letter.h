#pragma once
class Letter
{
public:
	Letter(char letter, int value);
	~Letter();

	char getLetter() const;
	int getValue() const;

private:
	char letter;
	int value;
};


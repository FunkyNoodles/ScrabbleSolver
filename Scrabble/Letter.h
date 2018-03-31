#pragma once
class Letter
{
public:
	Letter();
	Letter(char letter, int value);
	~Letter();

private:
	char letter;
	int value;
};


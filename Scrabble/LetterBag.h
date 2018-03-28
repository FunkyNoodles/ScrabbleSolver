#pragma once
#include <map>
class LetterBag
{
public:
	LetterBag();
	~LetterBag();

private:
	std::map<char, int> letterCounts;
	std::map<char, int> letterScores;

	void initResources();
};


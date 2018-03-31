#pragma once
#include <map>
#include <vector>
#include "Letter.h"
class LetterBag
{
public:
	LetterBag();
	~LetterBag();

	int remaining();
	Letter getNext();

private:
	std::map<char, int> letterCounts;
	std::map<char, int> letterScores;

	std::vector<char> bag;

	void initResources();
	void populateBag();
};


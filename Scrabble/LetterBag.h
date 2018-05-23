#pragma once
#include <unordered_map>
#include <vector>
#include "Letter.h"
class LetterBag
{
public:
	LetterBag();
	~LetterBag();

	int remaining();
	Letter getNext();

	int getLetterScore(char tile);

private:
	std::unordered_map<char, int> letterCounts;
	std::unordered_map<char, int> letterScores;

	std::vector<char> bag;

	void initResources();
	void populateBag();
};


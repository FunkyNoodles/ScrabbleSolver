#pragma once
#include <unordered_map>
#include <vector>
#include "Letter.h"
class LetterBag
{
public:
	LetterBag(unsigned int seed);
	~LetterBag();

	int remaining();
	bool empty() const;
	Letter getNext();

	int getLetterScore(char tile);

private:
	std::unordered_map<char, int> letterCounts;
	std::unordered_map<char, int> letterScores;

	std::vector<char> bag;

	unsigned int seed;
	const int SHUFFLE_TIMES = 10;

	void initResources();
	void populateBag();
};


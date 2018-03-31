#pragma once
#include <map>
#include <vector>
class LetterBag
{
public:
	LetterBag();
	~LetterBag();

private:
	std::map<char, int> letterCounts;
	std::map<char, int> letterScores;

	std::vector<char> bag;

	void initResources();
	void populateBag();
};


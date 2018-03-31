#pragma once
#include <string>
#include <unordered_set>

class Dictionary
{
public:
	Dictionary();
	~Dictionary();

	bool find(std::string word);

private:
	std::unordered_set<std::string> dictionary;
};

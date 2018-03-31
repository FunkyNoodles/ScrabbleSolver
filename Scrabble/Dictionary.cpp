#include "Dictionary.h"
#include <fstream>
#include <sstream>


Dictionary::Dictionary()
{
	std::ifstream dictionaryFile("dictionary.txt");
	std::string line;
	while (std::getline(dictionaryFile, line))
	{
		dictionary.insert(line);
	}
	dictionaryFile.close();
}

Dictionary::~Dictionary()
{
}

bool Dictionary::find(std::string word)
{
	auto got = dictionary.find(word);
	if (got == dictionary.end()) {
		return false;
	}
	return true;
}

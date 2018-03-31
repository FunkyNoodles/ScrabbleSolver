#include "LetterBag.h"
#include "Dictionary.h"
#include <iostream>

int main() {
	LetterBag letterBag;
	Dictionary dictionary;
	std::cout << dictionary.find("HELLO") << '\t' << dictionary.find("DUC") << std::endl;
	return 0;
}

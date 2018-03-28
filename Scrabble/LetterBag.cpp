#include "LetterBag.h"


LetterBag::LetterBag()
{
	initResources();
}


LetterBag::~LetterBag()
{
}

void LetterBag::initResources()
{
	letterCounts[' '] = 2;
	letterCounts['E'] = 12;
	letterCounts['A'] = 9;
	letterCounts['I'] = 9;
	letterCounts['O'] = 8;
	letterCounts['N'] = 6;
	letterCounts['R'] = 6;
	letterCounts['T'] = 6;
	letterCounts['L'] = 4;
	letterCounts['S'] = 4;
	letterCounts['U'] = 4;
	letterCounts['D'] = 4;
	letterCounts['G'] = 3;
	letterCounts['B'] = 2;
	letterCounts['C'] = 2;
	letterCounts['M'] = 2;
	letterCounts['P'] = 2;
	letterCounts['F'] = 2;
	letterCounts['H'] = 2;
	letterCounts['V'] = 2;
	letterCounts['W'] = 2;
	letterCounts['Y'] = 2;
	letterCounts['K'] = 1;
	letterCounts['J'] = 1;
	letterCounts['X'] = 1;
	letterCounts['Q'] = 1;
	letterCounts['Z'] = 1;

	letterScores[' '] = 0;
	letterScores['E'] = 1;
	letterScores['A'] = 1;
	letterScores['I'] = 1;
	letterScores['O'] = 1;
	letterScores['N'] = 1;
	letterScores['R'] = 1;
	letterScores['T'] = 1;
	letterScores['L'] = 1;
	letterScores['S'] = 1;
	letterScores['U'] = 1;
	letterScores['D'] = 2;
	letterScores['G'] = 2;
	letterScores['B'] = 3;
	letterScores['C'] = 3;
	letterScores['M'] = 3;
	letterScores['P'] = 3;
	letterScores['F'] = 4;
	letterScores['H'] = 4;
	letterScores['V'] = 4;
	letterScores['W'] = 4;
	letterScores['Y'] = 4;
	letterScores['K'] = 5;
	letterScores['J'] = 8;
	letterScores['X'] = 8;
	letterScores['Q'] = 10;
	letterScores['Z'] = 10;
}

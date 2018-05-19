#pragma once
#include <string>

enum class PlacementType {
	CROSS,
	DOWN
};

class Placement
{
public:
	Placement();
	Placement(const int x, const int y, const PlacementType type, const std::string word, const int score);
	~Placement();
private:
	int x, y, score;
	PlacementType type;
	std::string word;
};


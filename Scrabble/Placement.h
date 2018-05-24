#pragma once
#include <iostream>
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

	int getX() const;
	int getY() const;
	int getScore() const;
	const PlacementType & getPlacementType() const;
	const std::string & getLetters() const;

	friend std::ostream& operator<<(std::ostream& os, const Placement& p);
private:
	int x, y, score;
	PlacementType type;
	std::string letters;
};


#pragma once
#include "Position.h"
#include "Direction.h"
#include <vector>
using std::vector;

typedef vector<char> VisitedSteps;

class Movement
{
public:
	virtual Direction::eDirection GetMove(char* board[], int ghostInd, Position& destination, Position* source) = 0;
};


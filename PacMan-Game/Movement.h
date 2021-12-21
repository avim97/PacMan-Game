#pragma once
#include "Position.h"
#include "Direction.h"
#include <vector>
using std::vector;

typedef vector<vector<char>> VisitedSteps;
typedef vector<vector<char>> GameBoard;

class Movement
{
public:
	virtual Direction::eDirection GetMove(GameBoard board, int ghostInd, const Position& destination, const Position& source) = 0;
};


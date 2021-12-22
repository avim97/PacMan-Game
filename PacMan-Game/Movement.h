#pragma once
#include "Position.h"
#include "Direction.h"
#include <vector>
using std::vector;

typedef vector<vector<char>> VisitedSteps;
typedef vector<vector<char>> GameBoard;
typedef vector<Position> PositionsVector;

class Movement
{
public:
	virtual Direction::eDirection GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& fruitMoves) = 0;
};


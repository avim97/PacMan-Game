#pragma once
#include "Movement.h"

class GoodMovement: public Movement
{
public:
	Direction::eDirection GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions)  override;
};


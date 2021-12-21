#pragma once
#include "Movement.h"

class GoodMovement: public Movement
{
public:
	Direction::eDirection GetMove(GameBoard board, int ghostInd, const Position& destination, const Position& source)  override;
};


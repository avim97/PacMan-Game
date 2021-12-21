#pragma once
#include "Movement.h"

class NoviceMovement: public Movement
{
public:
	Direction::eDirection GetMove(GameBoard board, int ghostInd, const Position& destination, const Position& source) override;

};


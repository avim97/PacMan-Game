#pragma once
#include "Movement.h"

class NoviceMovement : public Movement
{
public:
	Direction::eDirection GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves) override;

};


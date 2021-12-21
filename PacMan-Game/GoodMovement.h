#pragma once
#include "Movement.h"

class GoodMovement: public Movement
{
public:
	Direction::eDirection GetMove(char* board[], int ghostInd, Position& destination, Position* source)  override;
};


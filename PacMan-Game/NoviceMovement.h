#pragma once
#include "Movement.h"

class NoviceMovement: public Movement
{
public:
	Direction::eDirection GetMove(char* board[], int ghostInd, Position& destination, Position* source) override;

};


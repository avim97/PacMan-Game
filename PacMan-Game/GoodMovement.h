#pragma once
#include "Movement.h"

class GoodMovement: public Movement
{
public:
	void Move(int ghostInd)  override;
};


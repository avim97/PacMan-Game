#pragma once
#include "eGameMode.h"
#include "NoviceMovement.h"
#include "GoodMovement.h"
#include "BestMovement.h"

class MovementFactory
{
public:
	const Movement* Create(GameMode gameMode);
};


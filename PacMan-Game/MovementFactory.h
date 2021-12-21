#pragma once
#include "GoodMovement.h"
#include "NoviceMovement.h"
#include "BestMovement.h"
#include "eGameMode.h"





class MovementFactory
{
public:
	Movement* Create(GameMode gameMode, int _height, int _width);
};


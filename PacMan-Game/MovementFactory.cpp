#include "MovementFactory.h"

const Movement* MovementFactory::Create(GameMode gameMode)
{
	Movement* movement = nullptr;
	switch (gameMode)
	{
	case GameMode::NOVICE:
		movement = new NoviceMovement;
		break;

	case GameMode::GOOD:
		movement = new GoodMovement;
		break;

	default:
		movement = new BestMovement;
		break;



	}

	return movement;
}
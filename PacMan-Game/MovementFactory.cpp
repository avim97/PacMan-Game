#include "MovementFactory.h"

Movement* MovementFactory::Create(GameMode gameMode, int _height, int _width)
{

	switch (gameMode)
	{
	case GameMode::NOVICE:
		return new NoviceMovement;


	case GameMode::GOOD:
		return new GoodMovement;


	default: // meaning "BEST" game mode was chosen
		return new BestMovement(_height, _width);

	}
}
#include "Pacman.h"


void Pacman::Move(char nextDir)
{
	Direction::eDirection direction = Direction::Convert(nextDir);
	// here we need to check if there's a ghost in the next step, or not and then check if there's food or space
	switch (direction)
	{
	case Direction::UP:
		//fill
	case Direction::DOWN:
		//fill
	case Direction::LEFT:
		//fill
	case Direction::RIGHT:
		//fill
	case Direction::STAY:
		//fill
	default:


	}
}


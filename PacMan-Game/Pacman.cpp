#include "Pacman.h"



void Pacman::Move(char nextDir)
{
	Direction::eDirection direction = Direction::Convert(nextDir);
	int newYcoord = m_position.getYcoord();
	int newXcoord = m_position.getXcoord();
	// here we need to check if there's a ghost in the next step, or not and then check if there's food or space
	switch (direction)
	{
	case Direction::UP:
		Game::PacmanStepCheck(newYcoord - 1, newXcoord);
		break;

	case Direction::DOWN:
		Game::PacmanStepCheck(newYcoord + 1, newXcoord);
		break;

	case Direction::LEFT:
		Game::PacmanStepCheck(newYcoord, newXcoord - 1);
		break;

	case Direction::RIGHT:
		Game::PacmanStepCheck(newYcoord, newXcoord + 1);
		break;

	case Direction::STAY:
		setPosition(newXcoord, newYcoord);
		break;
		//check if other cases occur

	default:
		setPosition(newXcoord, newYcoord);
		//check if other cases occur
	}
}




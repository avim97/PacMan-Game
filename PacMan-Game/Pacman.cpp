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
		stepCheck(newYcoord-1,newXcoord);
		break;

	case Direction::DOWN:
		stepCheck(newYcoord + 1, newXcoord);
		break;

	case Direction::LEFT:
		stepCheck(newYcoord, newXcoord - 1);
		break;
		
	case Direction::RIGHT:
		stepCheck(newYcoord, newXcoord + 1);
		break;

	case Direction::STAY:
		setPosition(newXcoord, newYcoord);
		break;

	default:
		setPosition(newXcoord, newYcoord);
		//check if other cases occur
	}
}




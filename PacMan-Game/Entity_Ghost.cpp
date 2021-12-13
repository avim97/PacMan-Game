#include "Entity_Ghost.h"

void Move(char nextDir)
{

	Direction::eDirection ghostDir = Direction::getRandDir();
	int yCoord = Entity::getycoord();
	int xCoord = Entity::getXcoord();

	switch (ghostDir)
	{
	case Direction::eDirection::UP:
		GhostStepCheck(yCoord - 1, xCoord, ghost);

		break;

	case Direction::eDirection::DOWN:
		GhostStepCheck(yCoord + 1, xCoord, ghost);
		break;

	case Direction::eDirection::LEFT:
		GhostStepCheck(yCoord, xCoord - 1, ghost);
		break;

	case Direction::eDirection::RIGHT:
		GhostStepCheck(yCoord, xCoord + 1, ghost);
		break;

	default:
		break;
	}



}
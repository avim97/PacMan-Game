#include "Direction.h"


Direction::eDirection Direction::Convert(char key)
{
	{
		key = toupper(key);
		Direction::eDirection value = Direction::eDirection::UNDEFINED;

		switch (key)
		{
		case 'W':
			value = Direction::eDirection::UP;
			break;

		case 'X':
			value = Direction::eDirection::DOWN;
			break;

		case 'A':
			value = Direction::eDirection::LEFT;
			break;

		case 'D':
			value = Direction::eDirection::RIGHT;
			break;

		case 'S':
			value = Direction::eDirection::STAY;
			break;

		default:
			break;
		}

		return value;
	}
}

Direction::eDirection Direction::getRandDir()
{
	int dir = 1 + rand() % 4;

	switch (dir)
	{
	case 1:
		return eDirection::LEFT;

	case 2:
		return eDirection::RIGHT;
		
	case 3:
		return eDirection::UP;

	default:
		return eDirection::DOWN;

	}
}

bool Direction::isValidDirection(char nextDirection)
{
	eDirection direction = Convert(nextDirection);
	if (direction != eDirection::UNDEFINED)
		return true;

	else
		return false;
}
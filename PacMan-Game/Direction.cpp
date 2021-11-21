#include "Direction.h"


Direction::eDirection Direction::Convert(char c)
{
	{
		c = toupper(c);
		Direction::eDirection value = Direction::eDirection::UNDEFINED;

		switch (c)
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
		return Direction::eDirection::LEFT;

	case 2:
		return Direction::eDirection::RIGHT;
		
	case 3:
		return Direction::eDirection::UP;

	default:
		return Direction::eDirection::DOWN;

	}
}
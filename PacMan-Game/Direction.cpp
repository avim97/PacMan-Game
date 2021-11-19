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


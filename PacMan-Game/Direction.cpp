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

string Direction::ConvertToString(char _direction)
{
	_direction = toupper(_direction);
	string direction;

	switch (_direction)
	{
	case 'W':
		direction = "UP";
		break;

	case 'X':
		direction = "DOWN";
		break;

	case 'A':
		direction = "LEFT";
		break;

	case 'D':
		direction = "RIGHT";
		break;

	case 'S':
		direction = "STAY";
		break;

	default:
		break;
	}

	return direction;
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

Direction::eDirection Direction::GetDirection(int move)
{
	eDirection direction;

	switch (move)
	{
	case 1:
		direction = eDirection::UP;
		break;

	case 2:
		direction = eDirection::DOWN;
		break;

	case 3:
		direction = eDirection::LEFT;
		break;

	case 4:
		direction = eDirection::RIGHT;
		break;

	default:
		direction = eDirection::UNDEFINED;
		break;
	}

	return direction;
}
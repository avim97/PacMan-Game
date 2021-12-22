#include "GoodMovement.h"

Direction::eDirection GoodMovement::GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves)
{
	Direction::eDirection direction;
	AvailablePaths m_Paths = GetPaths();
	if (ghostsMoves % m_SwitchNumber == 0)
	{
		if (m_SwitchCounter == 5)
		{
			direction = Direction::getRandDir();
			m_SwitchCounter = 0;
		}
		else
		{
			direction = Direction::eDirection::UNDEFINED;
			m_SwitchCounter++;
		}
	}
	else
	{
		Direction::eDirection shortestDirection = Direction::eDirection::UNDEFINED;
		Position nextPosition;
		int shortestPath = m_Paths.size() * 100;
		int currentPath = NOT_FOUND;
		int xCoord = source.getXcoord();
		int yCoord = source.getYcoord();
		size_t height = m_Paths.size() - 1;
		size_t width = m_Paths[0].size();

		for (int i = 1; i <= TOTAL_MOVES; i++)
		{
			int nextX = xCoord;
			int nextY = yCoord;
			Direction::eDirection currentDirection = Direction::GetDirection(i);

			if (currentDirection == Direction::eDirection::UP &&
				nextY > 0 &&
				board[nextY - 1][nextX] != static_cast<char>(BoardObjects::WALL) &&
				board[nextY - 1][nextX] != '%' &&
				board[nextY - 1][nextX] != 'L')
			{
				nextY--;
			}
			else if (currentDirection == Direction::eDirection::DOWN &&
				nextY < height - 1 &&
				board[nextY + 1][nextX] != static_cast<char>(BoardObjects::WALL) &&
				board[nextY + 1][nextX] != '%' &&
				board[nextY + 1][nextX] != 'L')
			{
				nextY++;
			}

			else if (currentDirection == Direction::eDirection::LEFT &&
				nextX > 0 &&
				board[nextY][nextX - 1] != static_cast<char>(BoardObjects::WALL) &&
				board[nextY][nextX - 1] != '%' &&
				board[nextY][nextX - 1] != 'L')
			{
				nextX--;
			}

			else if (nextX < width - 1 &&
				board[nextY][nextX + 1] != static_cast<char>(BoardObjects::WALL) &&
				board[nextY][nextX + 1] != '%' &&
				board[nextY][nextX + 1] != 'L')
			{
				nextX++;
			}



			nextPosition.setPosition(nextX, nextY);
			currentPath = GetMinDistance(board, destination, nextPosition, otherGhostsPositions);

			if (shortestDirection == Direction::eDirection::UNDEFINED || currentPath <= shortestPath)
			{
				shortestDirection = currentDirection;
				shortestPath = currentPath;
			}

		}

		return shortestDirection;
	}

	return direction;
}
#include "BestMovement.h"

void BestMovement::InitializeVisitedPaths(GameBoard board, const Position& destination, const Position& source, PositionsVector otherGhostsPositions)
{
	int rows = m_Paths.size();
	int cols = m_Paths[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (board[i][j] != static_cast<char>(BoardObjects::WALL) &&
				board[i][j] != 'L' &&
				board[i][j] != '%' &&
				IsValidPosition({j,i}, otherGhostsPositions)) 
				m_Paths[i][j] = TRAVELABLE;

			else
				m_Paths[i][j] = NOT_TRAVELABLE;
		}
	}

	SetSource(source);
	SetDestination(destination);

} // check if needed to add another check value
void BestMovement::SetSource(const Position& sourcePos)
{
	int xCoord = sourcePos.getXcoord();
	int yCoord = sourcePos.getYcoord();

	m_Paths[yCoord][xCoord] = SOURCE;
}
void BestMovement::SetDestination(const Position& destPos)
{
	int xCoord = destPos.getXcoord();
	int yCoord = destPos.getYcoord();
	m_Paths[yCoord][xCoord] = DESTINATION;
}
Direction::eDirection BestMovement::GetMove(GameBoard board, int ghostInd, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves)
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
			board[nextY - 1][nextX] != 'L' &&
			IsValidPosition({ nextX ,nextY - 1 }, otherGhostsPositions))
		{
			nextY--;
		}
		else if (currentDirection == Direction::eDirection::DOWN &&
			nextY < height - 1 &&
			board[nextY + 1][nextX] != static_cast<char>(BoardObjects::WALL) &&
			board[nextY + 1][nextX] != '%' &&
			board[nextY + 1][nextX] != 'L' &&
			IsValidPosition({ nextX,nextY + 1 }, otherGhostsPositions))
		{
			nextY++;
		}

		else if (currentDirection == Direction::eDirection::LEFT &&
			nextX > 0 &&
			board[nextY][nextX - 1] != static_cast<char>(BoardObjects::WALL) &&
			board[nextY][nextX - 1] != '%' &&
			board[nextY][nextX - 1] != 'L' &&
			IsValidPosition({ nextX -1,nextY }, otherGhostsPositions))
		{
			nextX--;
		}

		else if (nextX < width - 1 &&
			board[nextY][nextX + 1] != static_cast<char>(BoardObjects::WALL) &&
			board[nextY][nextX + 1] != '%' &&
			board[nextY][nextX + 1] != 'L' &&
			IsValidPosition({ nextX + 1,nextY }, otherGhostsPositions))
		{
			nextX++;
		}

		else
			continue;

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
int BestMovement::GetMinDistance(GameBoard board, const Position& destination, const Position& source, PositionsVector otherGhostsPositions)
{

	QItem qsource;
	Queue nextPositions;
	size_t rows = m_Paths.size();
	size_t cols = m_Paths[0].size();

	InitializeVisitedPaths(board, destination, source, otherGhostsPositions);

	qsource.setPosition(source.getXcoord(), source.getYcoord());
	nextPositions.push(qsource);

	m_Paths[qsource.getYcoord()][qsource.getXcoord()] = NOT_TRAVELABLE;

	while (!nextPositions.empty())
	{

		QItem nextPosition = nextPositions.front();
		nextPositions.pop();

		if (m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord()] == DESTINATION)
			return nextPosition.GetDistance();

		// moving UP
		if (nextPosition.getYcoord() - 1 >= 0 &&
			m_Paths[nextPosition.getYcoord() - 1][nextPosition.getXcoord()] != NOT_TRAVELABLE)
		{
			QItem newPos(nextPosition.getXcoord(), nextPosition.getYcoord() - 1, nextPosition.GetDistance() + 1);
			nextPositions.push(newPos);
			if (m_Paths[nextPosition.getYcoord() - 1][nextPosition.getXcoord()] == TRAVELABLE)
				m_Paths[nextPosition.getYcoord() - 1][nextPosition.getXcoord()] = NOT_TRAVELABLE;

			//BestMovmentPrintDEBUG(rows, cols);
		}

		// moving DOWN
		if (nextPosition.getYcoord() + 1 < rows &&
			m_Paths[nextPosition.getYcoord() + 1][nextPosition.getXcoord()] != NOT_TRAVELABLE)
		{
			QItem newPos(nextPosition.getXcoord(), nextPosition.getYcoord() + 1, nextPosition.GetDistance() + 1);
			nextPositions.push(newPos);

			if (m_Paths[nextPosition.getYcoord() + 1][nextPosition.getXcoord()] == TRAVELABLE)
				m_Paths[nextPosition.getYcoord() + 1][nextPosition.getXcoord()] = NOT_TRAVELABLE;

			//BestMovmentPrintDEBUG(rows, cols);
		}

		// moving LEFT
		if (nextPosition.getXcoord() - 1 >= 0 &&
			m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() - 1] != NOT_TRAVELABLE)
		{
			QItem newPos(nextPosition.getXcoord() - 1, nextPosition.getYcoord(), nextPosition.GetDistance() + 1);
			nextPositions.push(newPos);
			if (m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() - 1] == TRAVELABLE)
				m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() - 1] = NOT_TRAVELABLE;

			//BestMovmentPrintDEBUG(rows, cols);
		}

		//moving RIGHT
		if (nextPosition.getXcoord() + 1 < cols &&
			m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() + 1] != NOT_TRAVELABLE)
		{
			QItem newPos(nextPosition.getXcoord() + 1, nextPosition.getYcoord(), nextPosition.GetDistance() + 1);
			nextPositions.push(newPos);

			if (m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() + 1] == TRAVELABLE)
				m_Paths[nextPosition.getYcoord()][nextPosition.getXcoord() + 1] = NOT_TRAVELABLE;

			//BestMovmentPrintDEBUG(rows, cols);
		}
	}

	return NOT_FOUND;

}
bool BestMovement::IsValidPosition(Position position, int rows, int cols)
{
	if ((position.getXcoord() < cols && position.getYcoord() < rows) &&
		(position.getXcoord() >= 0 && position.getYcoord() >= 0))
		return true;

	else
		return false;
}
bool BestMovement::IsValidPosition(const Position& currentPosition, PositionsVector otherGhostsPositions)
{
	size_t otherGhosts = otherGhostsPositions.size();
	for (size_t i = 0; i < otherGhosts; i++)
		if (currentPosition == otherGhostsPositions[i])
			return false;

	return true;
}


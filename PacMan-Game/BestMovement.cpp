#include "BestMovement.h"

void BestMovement::InitializeVisitedPaths(GameBoard board, const Position& destination, const Position& source)
{
	size_t rows = m_Paths.size();
	size_t cols = m_Paths[0].size();

	for (size_t i = 0; i < rows ; i++)
	{
		for (size_t j = 0; j < cols ; j++)
		{
			if (board[i][j] != static_cast<char>(BoardObjects::WALL))
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
Direction::eDirection BestMovement::GetMove(GameBoard board, int ghostInd, const Position& destination, const Position& source)
{
	Direction::eDirection shortestMove = Direction::eDirection::UP;
	Position nextPosition;
	int shortestPath = NOT_FOUND;
	int currentPath;
	int xCoord = source.getXcoord();
	int yCoord = source.getYcoord();
	size_t height = m_Paths.size() - 1;
	size_t width = m_Paths[0].size();
	for (int i = 1; i <= TOTAL_MOVES; i++)
	{
		int nextX = xCoord;
		int nextY = yCoord;
		Direction::eDirection currentDirection = Direction::GetDirection(i);

		if (currentDirection == Direction::eDirection::UP && nextY > 1)
		{
			nextY--;
		}
		else if (currentDirection == Direction::eDirection::DOWN && nextY < height - 2)
		{
			nextY++;
		}

		else if (currentDirection == Direction::eDirection::LEFT && nextX > 1)
		{
			nextX--;
		}

		else if (nextX < width - 2)
		{
			nextX++;
		}
		
		nextPosition.setPosition(nextX, nextY);
		currentPath = GetMinDistance(board, destination, nextPosition);
		if (shortestMove == Direction::eDirection::UNDEFINED || currentPath >= shortestPath)
		{
			shortestMove = currentDirection;
			shortestPath = currentPath;
		}
	}

	return shortestMove;
}
int BestMovement::GetMinDistance(GameBoard board, const Position& destination, const Position& source)
{
	QItem qsource;
	Queue queue;
	size_t rows = m_Paths.size();
	size_t cols = m_Paths[0].size();
	VisitedPaths visited(rows,vector<bool>(cols));

	InitializeVisitedPaths(board, destination, source);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (m_Paths[i][j] == NOT_TRAVELABLE)
				visited[i][j] = true;
			else
				visited[i][j] = false;

			if (m_Paths[i][j] == SOURCE)
				qsource.setPosition(j, i);
		}
	}


	queue.push(qsource);
	visited[qsource.getYcoord() - 1][qsource.getXcoord() - 1] = true;

	while (!queue.empty())
	{
		QItem pos = queue.front();
		queue.pop();

		if (m_Paths[pos.getYcoord() - 1][pos.getXcoord() - 1] == DESTINATION)
			return pos.GetDistance();

		if (pos.getYcoord() - 2 >= 0 && 
			visited[pos.getYcoord() - 2][pos.getXcoord() - 1] == false)
		{
			QItem newPos(pos.getXcoord() - 1, pos.getYcoord() - 2, pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getYcoord() - 1][pos.getXcoord() - 2] = true;

		}

		

		if (pos.getYcoord() < rows &&
			visited[pos.getYcoord()][pos.getXcoord() - 1] == false) 
		{
			QItem newPos(pos.getXcoord() , pos.getYcoord(), pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getYcoord()][pos.getXcoord() - 1] = true;
		}

		if (pos.getXcoord() - 2 >= 0 &&
			visited[pos.getYcoord() - 1][pos.getXcoord() - 2] == false) 
		{
			QItem newPos(pos.getXcoord() - 2, pos.getYcoord() - 1, pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getYcoord() - 1][pos.getXcoord() - 2] = true;
		}

		if (pos.getXcoord()  < cols &&
			visited[pos.getYcoord() - 1][pos.getXcoord()] == false) 
		{
			QItem newPos(pos.getXcoord(), pos.getYcoord() - 1, pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getYcoord() - 1][pos.getXcoord()] = true;
		}
	}
	return NOT_FOUND;
}
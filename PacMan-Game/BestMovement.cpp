#include "BestMovement.h"

void BestMovement::InitializeVisitedPaths(char* board[], Position& destination, const Position& source)
{
	size_t rows = m_Paths.size();
	size_t cols = m_Paths[0].size();

	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; i < cols; i++)
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
	m_Paths[xCoord][yCoord] = DESTINATION;
}
void BestMovement::SetDestination(const Position& destPos)
{
	int xCoord = destPos.getXcoord();
	int yCoord = destPos.getYcoord();
	m_Paths[xCoord][yCoord] = SOURCE;
}
Direction::eDirection BestMovement::GetMove(char* board[], int ghostInd, Position& destination, Position* source)
{
	Direction::eDirection shortestMove = Direction::eDirection::UNDEFINED;
	int shortestPath = NOT_FOUND;
	int currentPath;
	int xCoord = source->getXcoord();
	int yCoord = source->getYcoord();
	for (int i = 1; i <= TOTAL_MOVES; i++)
	{
		int nextX = xCoord;
		int nextY = yCoord;
		Direction::eDirection currentDirection = Direction::GetDirection(i);

		if (currentDirection == Direction::eDirection::UP)
		{
			nextY--;
		}
		else if (currentDirection == Direction::eDirection::DOWN)
		{
			nextY++;
		}

		else if (currentDirection == Direction::eDirection::LEFT)
		{
			nextX--;
		}

		else
		{
			nextX++;
		}

		currentPath = GetMinDistance(board, destination, {xCoord, yCoord - 1});
		if (shortestMove == Direction::eDirection::UNDEFINED || currentPath >= shortestPath)
		{
			shortestMove = currentDirection;
			shortestPath = currentPath;
		}
	}

	return shortestMove;
}
int BestMovement::GetMinDistance(char* board[], Position& destination, const Position& source)
{
	QItem qsource;
	Queue queue;
	size_t rows = m_Paths.size();
	size_t cols = m_Paths[0].size();
	VisitedPaths visited(rows,vector<bool>(cols));

	InitializeVisitedPaths(board, destination, source);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; i < cols; i++)
		{
			if (m_Paths[i][j] == NOT_TRAVELABLE)
				visited[i][j] = true;
			else
				visited[i][j] = false;

			if (m_Paths[i][j] == SOURCE)
				qsource.setPosition(rows, cols);
		}
	}


	queue.push(qsource);
	visited[qsource.getXcoord()][qsource.getYcoord()] = true;

	while (!queue.empty())
	{
		QItem pos = queue.front();
		queue.pop();

		if (m_Paths[pos.getXcoord()][pos.getYcoord()] == DESTINATION)
			return pos.GetDistance();

		if (pos.getXcoord() - 1 >= 0 &&
			visited[pos.getXcoord() - 1][pos.getYcoord()] == false)
		{
			QItem newPos(pos.getXcoord() - 1, pos.getYcoord(), pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getXcoord() - 1][pos.getYcoord()] = true;
		}

		if (pos.getXcoord() + 1 < rows &&
			visited[pos.getXcoord() + 1][pos.getYcoord()] == false) 
		{
			QItem newPos(pos.getXcoord() + 1, pos.getYcoord(), pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getXcoord() + 1][pos.getYcoord()] = true;
		}

		if (pos.getYcoord() - 1 >= 0 &&
			visited[pos.getXcoord()][pos.getYcoord() - 1] == false) 
		{
			QItem newPos(pos.getXcoord(), pos.getYcoord() - 1, pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getXcoord()][pos.getYcoord() - 1] = true;
		}

		if (pos.getYcoord() + 1 < cols &&
			visited[pos.getXcoord()][pos.getYcoord() + 1] == false) 
		{
			QItem newPos(pos.getXcoord(), pos.getYcoord() + 1, pos.GetDistance() + 1);
			queue.push(newPos);
			visited[pos.getXcoord()][pos.getYcoord() + 1] = true;
		}
	}
	return NOT_FOUND;
}
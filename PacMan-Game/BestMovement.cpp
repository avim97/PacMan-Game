#include "BestMovement.h"

void BestMovement::InitializeVisitedPaths(char* board[])
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
}
void BestMovement::SetSource(Position& sourcePos)
{
	int xCoord = sourcePos.getXcoord();
	int yCoord = sourcePos.getYcoord();
	m_Paths[xCoord][yCoord] = DESTANATION;
}
void BestMovement::SetDestanation(Position& destPos)
{
	int xCoord = destPos.getXcoord();
	int yCoord = destPos.getYcoord();
	m_Paths[xCoord][yCoord] = SOURCE;
}
void BestMovement::Move(int ghostInd)
{

}
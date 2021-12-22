#include "NoviceMovement.h"

Direction::eDirection NoviceMovement::GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves)
{
	if (ghostsMoves % 20 == 0)
	{
		return Direction::getRandDir();
	}
	else
	{
		return Direction::eDirection::UNDEFINED;
	}
}
#pragma once
#include "BestMovement.h"

class GoodMovement : public BestMovement
{
private:
	enum { TRAVELABLE = '*', NOT_TRAVELABLE = '0', DESTINATION = 'D', SOURCE = 'S', NOT_FOUND = -1, TOTAL_MOVES = 4 };
	int m_SwitchNumber;
	int m_SwitchCounter;
	bool m_IsSmart;

public:
	GoodMovement(int _height, int _width) :
		BestMovement(_height, _width),
		m_IsSmart(true)
	{
		GetRandomCounter();
	};

	void GetRandomCounter() { m_SwitchNumber = 1 + (rand() % 20); };
	Direction::eDirection GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves)  override;
	void ActivateSmartMovement() { m_IsSmart = true; };
	void DeActivateSmartMovement() { m_IsSmart = false; m_SwitchCounter = 0; };
};


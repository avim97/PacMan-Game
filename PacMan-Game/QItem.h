#pragma once
#include "Position.h"

class QItem : public Position
{
private:
	int m_Distance;

public:
	QItem() :
		Position(),
		m_Distance(0)
	{};

	QItem(int xCoord, int yCoord, int _distance) :
		Position(xCoord, yCoord),
		m_Distance(_distance)
	{};

	int GetDistance() const { return m_Distance; };

};


#pragma once
#include "io_utils.h"
#include "Color.h"


using std::cout;

class Legend
{
private:
	const int m_MaxHeight = 3;
	const int m_MaxWidth = 20;
	Color m_LivesColor;
	Color m_ScoreColor;
	Position m_Position;
	const char heart[2] = { '<','3'};

public:
	Legend(Position& boardPos) :
		m_LivesColor(Color::eColor::RED),
		m_ScoreColor(Color::eColor::YELLOW),
		m_Position(boardPos)
	{};
	bool checkIfWithinLegendRange(Position& position)const;
	bool checkIfWithinRange(int start, int end, int value)const;
	void printLegend(int& lives, int& score,bool& m_isColorful) const;
};

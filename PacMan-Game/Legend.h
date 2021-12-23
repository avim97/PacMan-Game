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
	const char heart[2] = { '<','3' };

public:
	Legend() :
		m_LivesColor(Color::eColor::RED),
		m_ScoreColor(Color::eColor::YELLOW) {};

	bool checkIfWithinLegendRange(const Position& position)const;
	bool checkIfWithinRange(const int& start, const int& end, const int& value)const;
	void printLegend(const int& lives, const  int& score, const bool& m_isColorful) const;
	void SetPosition(const Position& position) { m_Position = position; };
	Position& GetPosition() { return m_Position; };
	void SetLivesColor(Color::eColor color) { m_LivesColor.setColor(color); };
	void SetScoreColor(Color::eColor color) { m_ScoreColor.setColor(color); };
};

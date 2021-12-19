#include "Legend.h"



bool Legend::checkIfWithinLegendRange(const Position&  position) const
{
	if (!checkIfWithinRange(m_Position.getXcoord(), m_Position.getXcoord() + 2, position.getXcoord()) || !checkIfWithinRange(m_Position.getYcoord(), m_Position.getYcoord() + 19, position.getYcoord()))
		return false;
	else
		return true;
}
bool Legend::checkIfWithinRange(const int &start, const int& end, const int& value)const
{
	if (value >= start && value <= end)
		return true;
	else
		return false;
}
void Legend::printLegend(int& lives, int& score,bool& m_isColorful)const {
	int x = m_Position.getXcoord();
	int y = m_Position.getYcoord();
	gotoxy(x,y);
	
	if (m_LivesColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
		Color::resetOutputColor();
	cout << "Current score: ";

	if (m_LivesColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
		Color::applyOutputColor(Color::getColorValue(Color::eColor::BOLD_GREEN));
	cout << score;
	if (m_LivesColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
		Color::resetOutputColor();
	gotoxy(x+1, y);
	cout << "Lives Left:";
	if (m_LivesColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
		Color::applyOutputColor(Color::getColorValue(Color::eColor::RED));

	for (int i=0;i<lives;i++)
	{
		if (lives > 0)
		{
			cout << heart;
			lives--;
		}
		else
			cout << "   ";

	}
}


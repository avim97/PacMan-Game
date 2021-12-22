#include "Legend.h"



bool Legend::checkIfWithinLegendRange(const Position& position) const
{
	if (!checkIfWithinRange(m_Position.getXcoord(), m_Position.getXcoord() + 2, position.getXcoord()) || !checkIfWithinRange(m_Position.getYcoord(), m_Position.getYcoord() + 19, position.getYcoord()))
		return false;
	else
		return true;
}
bool Legend::checkIfWithinRange(const int& start, const int& end, const int& value)const
{
	if (value >= start && value <= end)
		return true;
	else
		return false;
}
void Legend::printLegend(const int& lives, const  int& score, const bool& m_isColorful)const {
	int y = m_Position.getXcoord();
	int x = m_Position.getYcoord();
	bool isColorful = (m_LivesColor.getColor() != static_cast<int>(Color::eColor::DEFAULT));

	gotoxy(x, y);

	if (isColorful)
		Color::resetOutputColor();
	cout << "Current score: ";

	if (isColorful)
		Color::applyOutputColor(Color::getColorValue(Color::eColor::BOLD_GREEN));
	cout << score;

	if (isColorful)
		Color::resetOutputColor();

	gotoxy(x, y + 1);

	cout << "Lives Left: ";
	if (isColorful)
		Color::applyOutputColor(Color::getColorValue(Color::eColor::RED));
	
	for (int i = 0; i < lives; i++)
	{
			cout << heart<< " ";
	}

	if (isColorful)
		Color::resetOutputColor();

}


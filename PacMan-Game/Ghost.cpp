#include "Ghost.h"

void Ghost::Erase(const int yCoord, const int xCoord, Board& board) const
{

	int color;

	gotoxy(xCoord, yCoord); //there is a problem here it prints no on the right location

	if (board.getCellValue(xCoord, yCoord) == static_cast<char>(BoardObjects::FOOD))
	{
		color = board.getBreadcrumbColor().getColor();
		if (color != static_cast<int>(Color::eColor::DEFAULT))
		{
			Color::applyOutputColor(color);
			cout << static_cast<char>(BoardObjects::FOOD);
			Color::resetOutputColor();
		}
		else
			cout << static_cast<char>(BoardObjects::FOOD);

	}
	else // there was a space before
	{
		cout << static_cast<char>(BoardObjects::SPACE);
	}
}

#include "Ghost.h"

void Ghost::Erase(const int yCoord, const int xCoord, Board& board) const
{

	int color;

	gotoxy(xCoord, yCoord);

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
	else 
	{
		cout << static_cast<char>(BoardObjects::SPACE);
	}
}

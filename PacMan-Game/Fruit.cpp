#include "Fruit.h"

char Fruit::GetFruitFigure(int value) const
{
	char figure;

	if (value >= 5 && value <= 7)
		figure = value + '0';

	else if (value == 8)
		figure = '8';

	else
		figure = '9';

	return figure;
}
void Fruit::Erase(const int yCoord, const int xCoord, Board& board) const
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
void Fruit::SetActivationMode(bool activate)
{
	m_IsActive = activate;
}
void Fruit::ActivateFruit(Position position)
{
	int scoreValue;

	SetActivationMode(true);
	SetActivationChangeFlag(true);
	scoreValue = GetRandomScoreValue();
	SetFigure(GetFruitFigure(scoreValue));
	SetPosition(position);
	SetInitialPosition(position);
}
void Fruit::ActivateFruit(Position position, int value)
{
	SetActivationMode(true);
	SetActivationChangeFlag(true);
	SetScoreValue(value);
	SetFigure(GetFruitFigure(value));
	SetPosition(position);
	SetInitialPosition(position);
}
void Fruit::DeActivateFruit(Board& board)
{
	Position currentPosition = GetPosition();
	SetActivationMode(false);
	SetActivationChangeFlag(true);
	Erase(currentPosition.getYcoord(), currentPosition.getXcoord(), board);
}
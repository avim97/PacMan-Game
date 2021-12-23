#include "GameCreature.h"

void GameCreature::Move() const
{
	int xCoord = this->GetXcoord();
	int yCoord = this->GetYcoord();

	gotoxy(xCoord, yCoord);

	int color = this->GetColor().getColor();

	if (color != static_cast<int>(Color::eColor::DEFAULT))
	{
		Color::applyOutputColor(color);
		this->Draw();
		Color::resetOutputColor();
	}
	else
		this->Draw();

}
void GameCreature::Move(const Position _position) const
{
	int xCoord = _position.getXcoord();
	int yCoord = _position.getYcoord();

	gotoxy(xCoord, yCoord);

	int color = this->GetColor().getColor(); ;

	if (color != static_cast<int>(Color::eColor::DEFAULT))
	{
		Color::applyOutputColor(color);
		this->Draw();
		Color::resetOutputColor();
	}

	else
		this->Draw();

}
void GameCreature::EraseFood(int yCoord, int xCoord, Board& board)
{
	board.setChar(xCoord, yCoord, static_cast<char>(BoardObjects::SPACE));
}
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
void GameCreature::Move(const Position _Position) const
{
	int xCoord = _Position.getXcoord();
	int yCoord = _Position.getYcoord();

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
void GameCreature::EraseFood(const int yCoord, const int xCoord, Board& board)
{
	board.setChar(xCoord, yCoord, static_cast<char>(BoardObjects::SPACE));
}
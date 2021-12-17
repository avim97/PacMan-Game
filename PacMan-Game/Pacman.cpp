#include "Pacman.h"

void Pacman::UpdateLife()
{
	m_life--;
}

bool Pacman::UpdateScore(Board& board)
{
	m_score++;

	if (m_score == board.getMaxScore())
		return false;

	return true;
}

bool Pacman::IsAlive() const
{
	if (m_life == 0)
		return false;
	else
		return true;
}

void Pacman::Erase(const int yCoord, const int xCoord, Board& board) const
{
	gotoxy(xCoord, yCoord);
	cout << static_cast<char>(BoardObjects::SPACE);
}

//void Pacman::Erase(const Position& position, Board& board) const
//{
//	//gotoxy(position);
//	cout << static_cast<char>(BoardObjects::SPACE);
//}

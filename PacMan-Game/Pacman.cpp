#include "Pacman.h"

void Pacman::UpdateLife()
{
	m_Lives--;
}
void Pacman::UpdateLife(int lives)
{
	m_Lives = lives;
}

bool Pacman::UpdateBreadcrumbScore(Board& board)
{
	m_BreadcrumbsScore++;

	if (m_BreadcrumbsScore == board.getMaxScore())
		return false;

	return true;
}

bool Pacman::IsAlive() const
{
	if (m_Lives == 0)
		return false;
	else
		return true;
}

void Pacman::Erase(const int yCoord, const int xCoord, Board& board) const
{
	gotoxy(xCoord, yCoord);
	cout << static_cast<char>(BoardObjects::SPACE);
}



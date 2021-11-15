#include "Game.h"
void Game::initView()
{
	int xCoord, yCoord;
	char lastPos;
	gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	cout << (char)BoardObjects::FOOD;
	xCoord = m_Pacman.initialPos.getXcoord();
	yCoord = m_Pacman.initialPos.getYcoord();
	gotoxy(xCoord, yCoord);
	cout << m_Pacman.getFigure();
	m_Pacman.setPosition(xCoord, yCoord);

	lastPos = m_Board.getPosition(m_Bashful.getXcoord(), m_Bashful.getYcoord());
	switch (lastPos)
	{
	case (char)BoardObjects::FOOD:
		cout << (char)BoardObjects::FOOD;
		break;

	case (char)BoardObjects::SPACE:
		cout << (char)BoardObjects::SPACE;
		break;

	default:
		break;
	}
	xCoord = m_Bashful.initialPos.getXcoord();
	yCoord = m_Bashful.initialPos.getYcoord();
	gotoxy(xCoord, yCoord);
	cout << m_Bashful.getFigure();
	m_Bashful.setPosition(xCoord, yCoord);

	lastPos = m_Board.getPosition(m_Speedy.getXcoord(), m_Speedy.getYcoord());
	switch (lastPos)
	{
	case (char)BoardObjects::FOOD:
		cout << (char)BoardObjects::FOOD;
		break;

	case (char)BoardObjects::SPACE:
		cout << (char)BoardObjects::SPACE;
		break;

	default:
		break;
	}
	xCoord = m_Speedy.initialPos.getXcoord();
	yCoord = m_Speedy.initialPos.getYcoord();
	gotoxy(xCoord, yCoord);
	cout << m_Speedy.getFigure();
	m_Speedy.setPosition(xCoord, yCoord);

	// make a function that does that in a modular way
}
void Game::stepCheck(const int Ycoord, const int Xcoord)
{
	const char nextPos=m_Board.getPosition(Xcoord, Ycoord);
	switch (nextPos) {
//wall
	case 35:
		break;
//empty space - check if tunnel
	case 32:
		break;
//ghost
	case 234:
		break;
//food - check if tunnel
	case 249:
		break;
	default:
		//check other possible cases
	}

}

bool Game::updateLife()
{
	m_life--;

	if (m_life == 0)
		return false; //meaining Pacman now has 0 lives, the user lost

	else
		return true; //lives are not zero, can continue to play
}

void Game::updateScore()
{
	m_score++;
}

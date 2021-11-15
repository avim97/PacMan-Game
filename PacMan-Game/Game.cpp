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
void Game::PacmanStepCheck(const int Ycoord, const int Xcoord)
{
	const char nextPos = m_Board.getPosition(Xcoord, Ycoord);
	switch (nextPos) {
		//wall
	case 35:
		break;//stay

		//empty space - check if tunnel
	case 32:
		checkTunnel(Ycoord, Xcoord); break;//nothing to change

			//ghost
	case 234:
		break;

		//food - check if tunnel & score++
	case 249:
		break;
	default:
		//out of board borders - ignore (stay)
	}

}
void Game::checkTunnel(const int Ycoord, const int Xcoord)
{
	if (Xcoord > 34 && Xcoord < 39 && Ycoord == 0)//checking if within top tunnel
		m_Pacman.setPosition(Xcoord, m_Board.getHeight() - 1);//if in tunnel - pacman is sent to the other side
	else if (Xcoord > 34 && Xcoord < 39 && Ycoord == m_Board.getHeight() - 1)//check if within botoom tunnel
		m_Pacman.setPosition(Xcoord, 0);

	else if (Ycoord > 10 && Ycoord < 15 && Xcoord == 0)//same test for width tunnel
		m_Pacman.setPosition(m_Board.getWidth() - 1, Ycoord);
	else if (Ycoord > 10 && Ycoord < 15 && Xcoord == m_Board.getWidth() - 1)
		m_Pacman.setPosition(0, Ycoord);

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

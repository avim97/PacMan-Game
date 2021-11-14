#include "Game.h"
void Game::initView()
{
	int xCoord, yCoord;
	char lastPos;
	gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	cout << (char)SPACE;
	xCoord = m_Pacman.initialPos.getXcoord();
	yCoord = m_Pacman.initialPos.getYcoord();
	gotoxy(xCoord, yCoord);
	cout << m_Pacman.getFigure();
	m_Pacman.setPosition(xCoord, yCoord);

	lastPos = m_Board.getPosition(m_Bashful.getXcoord(), m_Bashful.getYcoord());
	switch (lastPos)
	{
	case FOOD:
		cout << (char)FOOD;
		break;

	case SPACE:
		cout << (char)SPACE;
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
	case FOOD:
		cout << (char)FOOD;
		break;

	case SPACE:
		cout << (char)SPACE;
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

void Game::calcMaxScore()
{
	int Height = m_Board.getHeight();
	int Width = m_Board.getWidth();

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (m_Board.getPosition(i,j) == FOOD)
			{
				m_maxScore++;
			}

		}
	}

}
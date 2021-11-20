#include "Game.h"


void Game::initView()
{
	int xCoord, yCoord;
	char lastPos;
	gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	cout << (char)BoardObjects::FOOD;
	xCoord = m_Pacman.initialPos.getXcoord();
	yCoord = m_Pacman.initialPos.getYcoord();
	printPacman(yCoord, xCoord);
	m_Pacman.setPosition(xCoord, yCoord);

	lastPos = m_Board.getPosition(m_Ghost[0].getXcoord(), m_Ghost[0].getYcoord());
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
	xCoord = m_Ghost[0].initialPos.getXcoord();
	yCoord = m_Ghost[0].initialPos.getYcoord();
	printGhost(yCoord, xCoord, 0);
	m_Ghost[0].setPosition(xCoord, yCoord);

	lastPos = m_Board.getPosition(m_Ghost[1].getXcoord(), m_Ghost[1].getYcoord());
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
	xCoord = m_Ghost[1].initialPos.getXcoord();
	yCoord = m_Ghost[1].initialPos.getYcoord();
	printGhost(yCoord, xCoord, 1);
	m_Ghost[1].setPosition(xCoord, yCoord);

	// make a function that does that in a modular way
}
void Game::moveObject(char nextDir)
{
	Direction::eDirection direction = Direction::Convert(nextDir);
	int yCoord = m_Pacman.getYcoord();
	int xCoord = m_Pacman.getXcoord();
	
	switch (direction)
	{
	case Direction::eDirection::UP:
		if (PacmanStepCheck(yCoord - 1, xCoord))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}
		
		else
		{
			if (m_life == 0)
				gameOn = false;
		}
		break;

	case Direction::eDirection::DOWN:
		if (PacmanStepCheck(yCoord + 1, xCoord))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				gameOn = false;
		}
		break;

	case Direction::eDirection::LEFT:
		if (PacmanStepCheck(yCoord, xCoord - 1))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				gameOn = false;
		}
		break;

	case Direction::eDirection::RIGHT:
		if (PacmanStepCheck(yCoord, xCoord + 1))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				gameOn = false;
		}
		break;

	default: //User pressed STAY or an UNDEFINED key
		break;
	}
}
void Game::moveObject(int ghost)
{

	Direction::eDirection ghostDir = Direction::getRandDir();
	int yCoord = m_Ghost[ghost].getYcoord();
	int xCoord = m_Ghost[ghost].getXcoord();
	// here we need to check if there's a ghost in the next step, or not and then check if there's food or space
	switch (ghostDir)
	{
	case Direction::eDirection::UP:
		GhostStepCheck(yCoord - 1, xCoord, ghost);
		//print ghost and erase ghost
		break;

	case Direction::eDirection::DOWN:
		GhostStepCheck(yCoord + 1, xCoord, ghost);
		break;

	case Direction::eDirection::LEFT:
		GhostStepCheck(yCoord, xCoord - 1, ghost);
		break;

	case Direction::eDirection::RIGHT:
		GhostStepCheck(yCoord, xCoord + 1, ghost);
		break;

	default: 
		break;
	}

	
	
}
void Game::crossTunnel(const int yCoord, const int xCoord)
{
	if (xCoord == 0)
	{
		m_Pacman.setPosition(m_Board.getHeight() - 1, yCoord);
	}

	else if (xCoord == m_Board.getHeight() - 1)
	{
		m_Pacman.setPosition(0, yCoord);
	}

	if (yCoord == 0)
	{
		m_Pacman.setPosition(xCoord, m_Board.getWidth() -1);
	}

	else if (yCoord == m_Board.getWidth() - 1)
	{
		m_Pacman.setPosition(xCoord, 0);
	}
}
void Game::GhostStepCheck(const int yCoord, const int xCoord, int ghost)
{
	int moved = true;
	const char nextPos = m_Board.getPosition(xCoord, yCoord);
	switch (nextPos) {
	case (char)BoardObjects::WALL:
		moveObject(ghost);
		break;

	case (char)BoardObjects::SPACE:
		if (!checkTunnel(yCoord, xCoord))
			m_Ghost[ghost].setPosition(xCoord, yCoord);
		else
		{
			moveObject(ghost);
		}
		break;

	case (char)BoardObjects::GHOST:
		moveObject(ghost);
		break;

	case (char)BoardObjects::PACMAN:
		if (!updateLife())
		{
			gameOn = false;
		}
		else {
			initView(); //going back to the initial view
		}
		break;


	default:
		break;

	}
}
bool Game::PacmanStepCheck(const int yCoord, const int xCoord)
{
	bool moved = true;
	const char nextPos = m_Board.getPosition(xCoord, yCoord);
	switch (nextPos) 
	{

	case (char)BoardObjects::WALL:
		moved = false;
		break;

		
	case (char)BoardObjects::SPACE:
		if (!checkTunnel(yCoord, xCoord))
			m_Pacman.setPosition(xCoord, yCoord);
		else
			crossTunnel(yCoord, xCoord);
		moved = true;
		break;

		
	case (char)BoardObjects::GHOST:
		if (!updateLife())
		{
			moved = false;
			gameOn = false;
		}
		else {
			initView(); //check the cases he loses
		}

		break;

		
	case (char)BoardObjects::FOOD:
		if (updateScore())
		{
			moved = true;
			eraseFood(yCoord, xCoord);
		}
			
		else
			gameOn = false; //pacman ate all of the breadcrums - the user won
		break;

	default:
		break;
	}

	return moved;

}
bool Game::checkTunnel(const int yCoord, const int xCoord)
{
	if ((xCoord == 0 || xCoord == m_Board.getWidth() - 1) && m_Board.getPosition(0, yCoord) != (char)BoardObjects::WALL)
		return true;

	else if ((yCoord == 0 || yCoord == m_Board.getHeight() - 1) && m_Board.getPosition(xCoord, 0) != (char)BoardObjects::WALL)
		return true;

	else
		return false;
	

	//if (xCoord >= 34 && xCoord <= 39 && yCoord == 0 || yCoord == 1) {//checking if within top tunnel
	//	//m_Pacman.setPosition(xCoord, m_Board.getHeight() - 1);//if in tunnel - pacman is sent to the other side
	//	return true;
	//}
	//else if (xCoord >= 34 && xCoord <= 39 && yCoord == m_Board.getHeight() - 1)//check if within botoom tunnel
	//{
	//	//m_Pacman.setPosition(xCoord, 0);
	//	return true;
	//}

	//else if (yCoord == 11 || yCoord == 12 || yCoord == 16 || yCoord == 17 && xCoord == 1) {//same test for width tunnel
	//	//m_Pacman.setPosition(m_Board.getWidth() - 1, yCoord);
	//	return true;
	//}
	//else if (yCoord > 10 && yCoord < 15 && xCoord == m_Board.getWidth() - 1)
	//{
	//	//m_Pacman.setPosition(0, yCoord);
	//	return true;
	//}
	//return false;

}
bool Game::updateLife()
{
	m_life--;

	if (m_life == 0)
		return false; //meaining Pacman now has 0 lives, the user lost

	else
		return true; //lives are not zero, can continue to play
}
bool Game::updateScore()
{
	m_score++;

	if (m_score == m_Board.getMaxScore())
		return false;

	return true;
}
void Game::eraseFood(const int yCoord, const int xCoord)
{
	m_Board.setChar(xCoord, yCoord, (char)BoardObjects::SPACE);
}
void Game::printPacman(const int yCoord, const int xCoord)
{
	gotoxy(xCoord, yCoord);
	cout << "\033[33m" << m_Pacman.getFigure();
}
void Game::eraseGhost(const int yCoord, const int xCoord)
{
	gotoxy(yCoord, xCoord);
	cout << m_Board.getPosition(xCoord, yCoord);
}
void Game::printGhost(const int yCoord, const int xCoord, int ghost)
{
	gotoxy(yCoord, xCoord);
	cout << m_Ghost[ghost].getFigure();
}
void Game::erasePacman(const int yCoord, const int xCoord)
{
	gotoxy(yCoord, xCoord);
	cout << (char)BoardObjects::SPACE; 
}
#include "Game.h"


void Game::initView()
{
	int xCoord, yCoord;
	char lastPos;
	gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	cout << m_Board.getPosition(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	xCoord = m_Pacman.initialPos.getXcoord();
	yCoord = m_Pacman.initialPos.getYcoord();
	printPacman(yCoord, xCoord);
	m_Pacman.setPosition(xCoord, yCoord);

	/*lastPos = m_Board.getPosition(m_Ghost[0].getXcoord(), m_Ghost[0].getYcoord());*/
	/*switch (lastPos)
	{
	case (char)BoardObjects::FOOD:
		cout << (char)BoardObjects::FOOD;
		break;

	case (char)BoardObjects::SPACE:
		cout << (char)BoardObjects::SPACE;
		break;

	default:
		break;
	}*/
	gotoxy(m_Ghost[0].getXcoord(), m_Ghost[0].getYcoord());
	cout << m_Board.getPosition(m_Ghost[0].getXcoord(), m_Ghost[0].getYcoord());
	xCoord = m_Ghost[0].initialPos.getXcoord();
	yCoord = m_Ghost[0].initialPos.getYcoord();
	printGhost(yCoord, xCoord, 0);
	m_Ghost[0].setPosition(xCoord, yCoord);

	//lastPos = m_Board.getPosition(m_Ghost[1].getXcoord(), m_Ghost[1].getYcoord());
	//switch (lastPos)
	//{
	//case (char)BoardObjects::FOOD:
	//	cout << (char)BoardObjects::FOOD;
	//	break;

	//case (char)BoardObjects::SPACE:
	//	cout << (char)BoardObjects::SPACE;
	//	break;

	//default:
	//	break;
	//}
	gotoxy(m_Ghost[1].getXcoord(), m_Ghost[1].getYcoord());
	cout << m_Board.getPosition(m_Ghost[1].getXcoord(), m_Ghost[1].getYcoord());
	xCoord = m_Ghost[1].initialPos.getXcoord();
	yCoord = m_Ghost[1].initialPos.getYcoord();
	printGhost(yCoord, xCoord, 1);
	m_Ghost[1].setPosition(xCoord, yCoord);

	// make a function that does that in a modular way
}
void Game::movePacman(char nextDir)
{
	int yCoord = m_Pacman.getYcoord();
	int xCoord = m_Pacman.getXcoord();


	if (isValidMove(nextDir)) { m_Pacman.setDirection(nextDir); }

	else { nextDir = m_Pacman.getDirection(); };

	switch (toupper(nextDir))
	{
	case (char)Direction::eDirection::UP:
		if (PacmanStepCheck(yCoord - 1, xCoord))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				m_gameStatus = eGameStatus::LOST;
		}
		break;

	case (char)Direction::eDirection::DOWN:
		if (PacmanStepCheck(yCoord + 1, xCoord))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				m_gameStatus = eGameStatus::LOST;
		}
		break;

	case (char)Direction::eDirection::LEFT:
		if (PacmanStepCheck(yCoord, xCoord - 1))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				m_gameStatus = eGameStatus::LOST;
		}
		break;

	case (char)Direction::eDirection::RIGHT:
		if (PacmanStepCheck(yCoord, xCoord + 1))
		{
			erasePacman(yCoord, xCoord);
			printPacman(m_Pacman.getYcoord(), m_Pacman.getXcoord());
		}

		else
		{
			if (m_life == 0)
				m_gameStatus = eGameStatus::LOST;
		}
		break;

	default: // pressed STAY - the pacman stops
		break;
	}
}
void Game::moveGhost(int ghost)
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
	if (xCoord == 0) //left tunnel
	{
		m_Pacman.setPosition(m_Board.getWidth() - 1, yCoord);
	}

	else if (xCoord == m_Board.getWidth() - 1) //right tunnel
	{
		m_Pacman.setPosition(0, yCoord);
	}

	else if (yCoord == 0) // top tunnel
	{
		m_Pacman.setPosition(xCoord, m_Board.getHeight() - 1);
	}

	else if (yCoord == m_Board.getHeight() - 1) // bottom tunnel
	{
		m_Pacman.setPosition(xCoord, 0);
	}
}
void Game::GhostStepCheck(const int yCoord, const int xCoord, int ghost)
{

	if (checkGhostIntersection())
	{
		if (!updateLife())
		{
			m_gameStatus = eGameStatus::LOST;
		}
		else
		{
			initView(); //check the cases he loses
		}
	}

	else
	{
		char nextPos = m_Board.getPosition(xCoord, yCoord);
		switch (nextPos) {
		case (char)BoardObjects::WALL:
			moveGhost(ghost);
			break;

		case (char)BoardObjects::SPACE:
			eraseGhost(m_Ghost[ghost].getYcoord(), m_Ghost[ghost].getXcoord());
			m_Ghost[ghost].setPosition(xCoord, yCoord);
			printGhost(yCoord, xCoord, ghost);
			break;

		case (char)BoardObjects::FOOD:
			if (!checkTunnel(yCoord, xCoord))
			{
				eraseGhost(m_Ghost[ghost].getYcoord(), m_Ghost[ghost].getXcoord());
				m_Ghost[ghost].setPosition(xCoord, yCoord);
				printGhost(yCoord, xCoord, ghost);
			}

			else
			{
				moveGhost(ghost);
			}
			break;

		case (char)BoardObjects::GHOST:
			moveGhost(ghost);
			break;

		case (char)BoardObjects::PACMAN:
			if (!updateLife())
			{
				m_gameStatus = eGameStatus::LOST;
			}
			else {
				initView(); //going back to the initial view
			}
			break;


		default:
			break;

		}
	}

}
bool Game::PacmanStepCheck(const int yCoord, const int xCoord)
{
	bool moved = true;

	if (checkGhostIntersection())
	{

		if (!updateLife())
		{
			moved = false;
			m_gameStatus = eGameStatus::LOST;
		}
		else
		{

			initView(); //check the cases he loses
		}
	}

	else
	{
		char nextPos = m_Board.getPosition(xCoord, yCoord);

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

		case (char)BoardObjects::FOOD:
			if (updateScore())
			{
				m_Pacman.setPosition(xCoord, yCoord);
				moved = true;
				eraseFood(yCoord, xCoord);
			}

			else
				m_gameStatus = eGameStatus::WON;
			//pacman ate all of the breadcrums - the user won
			break;

		default:
			break;
		}

	}



	return moved;

}
bool Game::checkGhostIntersection()
{
	bool isIntersecting = false;

	if (m_Pacman.getXcoord() == m_Ghost[0].getXcoord() && m_Pacman.getYcoord() == m_Ghost[0].getYcoord() || m_Pacman.getXcoord() == m_Ghost[1].getXcoord() && m_Pacman.getYcoord() == m_Ghost[1].getYcoord())
	{
		isIntersecting = true;

	}

	return isIntersecting;
}
bool Game::checkTunnel(const int yCoord, const int xCoord)
{
	if ((xCoord == 0 || xCoord == m_Board.getWidth() - 1) && m_Board.getPosition(xCoord, yCoord) != (char)BoardObjects::WALL) //left or right tunnels
		return true;

	else if ((yCoord == 0 || yCoord == m_Board.getHeight() - 1) && m_Board.getPosition(xCoord, yCoord) != (char)BoardObjects::WALL) //top or bottom tunnels
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
	gotoxy(xCoord, yCoord);
	cout << m_Board.getPosition(xCoord, yCoord);
}
void Game::printGhost(const int yCoord, const int xCoord, int ghost)
{
	gotoxy(xCoord, yCoord);
	cout << m_Ghost[ghost].getFigure();
}
void Game::erasePacman(const int yCoord, const int xCoord)
{
	gotoxy(xCoord, yCoord);
	cout << (char)BoardObjects::SPACE;
}
bool Game::isValidMove(char move)
{
	Direction::eDirection direction = Direction::Convert(move);
	if (direction != Direction::eDirection::UNDEFINED)
		return true;

	else
		return false;
}
void Game::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, ghostsMoves = 0;

	hideCursor();

	do
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 27)
			{
				PauseGame();
			}

			movePacman(key);
		}
		else
			movePacman(m_Pacman.getDirection());
		pacmanMoves++;
		if (pacmanMoves % 2 == 0)
		{
			moveGhost(0);
			moveGhost(1);
		}
		Sleep(300);
		showPlayerStatus();
	} while (m_gameStatus == eGameStatus::RUNNING);

	if (m_gameStatus == eGameStatus::WON)
		userWon();
	else
		userLost();

}
void Game::PauseGame()
{
	do {
		gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
		cout << "\033[37m" << " Game Paused, press ESC to continue.";

	} while (!_kbhit || _getch() != 27);
	gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
	cout << "                                       " << endl;
}
void Game::showPlayerStatus()
{
	int lives = getLives();
	int score = getScore();
	gotoxy(0, this->m_Board.getHeight() + 1);
	cout << "Current score: " << "\033[36m" << ("%d ", score);
	gotoxy(this->m_Board.getWidth() - 20, this->m_Board.getHeight() + 1);
	cout << "Lives Left:";
	for (int i = 0; i < 3; i++)
	{
		if (lives > 0)
		{
			cout << "\033[31m" << " <3";
			lives--;
		}
		else
			cout << "   ";
	}


}
void Game::userWon()
{
	clrscr();
	gotoxy(15, 15);
	cout << "You're a Winner!" << endl;
	gotoxy(15, 16);
	cout << "Press any key to go back to the main menu..." << endl;
	while (!_kbhit()) {};
	clrscr();
}
void Game::userLost()
{
	clrscr();
	gotoxy(15, 15);
	cout << "You're a Loser!" << endl;
	gotoxy(15, 16);
	cout << "Press any key to go back to the main menu..." << endl;
	while (!_kbhit()) {};
	clrscr();
}
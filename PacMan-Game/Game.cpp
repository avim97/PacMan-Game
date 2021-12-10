#include "Game.h"



void Game::initView()
{
	initialPacmanPos();
	for (int i = 0; i < sizeof(m_Ghost) / sizeof(m_Ghost[0]); i++)
		initialGhostPos(i);
}
void Game::initialGhostPos(int ghostInd)
{
	int xCoord, yCoord;
	gotoxy(m_Ghost[ghostInd].getXcoord(), m_Ghost[ghostInd].getYcoord());
	cout << m_Board.getPosition(m_Ghost[ghostInd].getXcoord(), m_Ghost[ghostInd].getYcoord());
	xCoord = m_Ghost[ghostInd].initialPos.getXcoord();
	yCoord = m_Ghost[ghostInd].initialPos.getYcoord();
	printGhost(yCoord, xCoord, ghostInd);
	m_Ghost[ghostInd].setPosition(xCoord, yCoord);
}
void Game::initialPacmanPos()
{
	int xCoord, yCoord;
	gotoxy(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	cout << m_Board.getPosition(m_Pacman.getXcoord(), m_Pacman.getYcoord());
	xCoord = m_Pacman.initialPos.getXcoord();
	yCoord = m_Pacman.initialPos.getYcoord();
	printPacman(yCoord, xCoord);
	m_Pacman.setPosition(xCoord, yCoord);
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

	default:
		break;
	}
}
void Game::moveGhost(int ghost)
{

	Direction::eDirection ghostDir = Direction::getRandDir();
	int yCoord = m_Ghost[ghost].getYcoord();
	int xCoord = m_Ghost[ghost].getXcoord();

	switch (ghostDir)
	{
	case Direction::eDirection::UP:
		GhostStepCheck(yCoord - 1, xCoord, ghost);

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
		m_Pacman.setPosition(m_Board.getWidth() - 1, yCoord);
	}

	else if (xCoord == m_Board.getWidth() - 1)
	{
		m_Pacman.setPosition(0, yCoord);
	}

	else if (yCoord == 0)
	{
		m_Pacman.setPosition(xCoord, m_Board.getHeight() - 1);
	}

	else if (yCoord == m_Board.getHeight() - 1)
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
			initView();
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
				initView();
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

			initView();
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
	if ((xCoord == 0 || xCoord == m_Board.getWidth() - 1) && m_Board.getPosition(xCoord, yCoord) != (char)BoardObjects::WALL)
		return true;

	else if ((yCoord == 0 || yCoord == m_Board.getHeight() - 1) && m_Board.getPosition(xCoord, yCoord) != (char)BoardObjects::WALL)
		return true;

	else
		return false;

}
bool Game::updateLife()
{
	m_life--;

	if (m_life == 0)
		return false;

	else
		return true;
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
	int color;

	color = m_Pacman.getColor().getColor();
	Color::applyOutputColor(color);
	cout << m_Pacman.getFigure();
	Color::resetOutputColor();




}
void Game::eraseGhost(const int yCoord, const int xCoord)
{
	gotoxy(xCoord, yCoord);
	int color;
	if (m_Board.getPosition(xCoord, yCoord) == (char)BoardObjects::FOOD)
	{
		color = m_Board.getBreadcrumbColor().getColor();
		Color::applyOutputColor(color);
		cout << (char)BoardObjects::FOOD ;
		Color::resetOutputColor();
	}
	else // there was a space before
	{
		cout << (char)BoardObjects::SPACE;
	}

	
}
void Game::printGhost(const int yCoord, const int xCoord, int ghost)
{
	gotoxy(xCoord, yCoord);

	int color;

	color = m_Ghost[ghost].getColor().getColor();
	Color::applyOutputColor(color);
	cout << m_Ghost[ghost].getFigure();
	Color::resetOutputColor();
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

	if (!getColorStyle())
		setDefaultColor();

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

	} while (!_kbhit() || _getch() != 27);
	gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
	cout << "                                       " << endl;
}
void Game::showPlayerStatus()
{
	int lives = getLives();
	int score = getScore();

	gotoxy(0, this->m_Board.getHeight() + 1);
	Color::resetOutputColor();
	cout << "Current score: "; 
	Color::applyOutputColor(Color::getColorValue(Color::eColor::BOLD_GREEN));
	cout << score ;
	Color::resetOutputColor();
	gotoxy(this->m_Board.getWidth() - 20, this->m_Board.getHeight() + 1);
	cout << "Lives Left:";
	Color::applyOutputColor(Color::getColorValue(Color::eColor::RED));
	for (int i = 0; i < 3; i++)
	{
		if (lives > 0)
		{
			cout << " <3";
			lives--;
		}
		else
			cout << "   ";
	}
	Color::resetOutputColor();
}
void Game::userWon()
{
	clrscr();
	cout << R"(
 __     __          __          __         _ 
 \ \   / /          \ \        / /        | |
  \ \_/ /__  _   _   \ \  /\  / /__  _ __ | |
   \   / _ \| | | |   \ \/  \/ / _ \| '_ \| |
    | | (_) | |_| |    \  /\  / (_) | | | |_|
    |_|\___/ \__,_|     \/  \/ \___/|_| |_(_)
                                             
                                             
)";
	cout << "Press any key to go back to the main menu..." << endl;
	while (!_kbhit()) {};
	clrscr();
}
void Game::userLost()
{
	clrscr();
	cout<< R"(
 __     __           _               _   _ 
 \ \   / /          | |             | | | |
  \ \_/ /__  _   _  | |     ___  ___| |_| |
   \   / _ \| | | | | |    / _ \/ __| __| |
    | | (_) | |_| | | |___| (_) \__ \ |_|_|
    |_|\___/ \__,_| |______\___/|___/\__(_)
                                           
                                           
)";

	cout << endl <<  "  Press any key to go back to the main menu..." << endl;
	while (!_kbhit()) {};
	clrscr();
}
void Game::setDefaultColor() //this function sets the default color (white) to all of the game and board objects.
{
	m_Board.setBreadcrumColor(Color::eColor::DEFAULT);
	m_Board.setWallColor(Color::eColor::DEFAULT);
	m_Pacman.setColor(Color::eColor::DEFAULT);
	m_Ghost[0].setColor(Color::eColor::DEFAULT);
	m_Ghost[1].setColor(Color::eColor::DEFAULT);
}
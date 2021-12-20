#include "Game.h"


void Game::initView()
{
	initialPacmanPos();
	initialGhostPos();
	InitialFruitPosition();
	
}
void Game::initialGhostPos()
{
	size_t ghostsNumber = m_Ghosts.size();
	int xCoord, yCoord;
	Position CurrentPosition;
	Position InitialPosition;

	for (int i = 0; i < ghostsNumber; i++)
	{
		CurrentPosition = this->m_Ghosts[i].GetPosition();
		InitialPosition = this->m_Ghosts[i].GetInitialPosition();

		xCoord = CurrentPosition.getXcoord();
		yCoord = CurrentPosition.getYcoord();

		gotoxy(xCoord, yCoord);
		m_Ghosts[i].ResetCurrentPosition();
		m_Ghosts[i].Erase(yCoord, xCoord, m_Board);
		m_Ghosts[i].Move();
	}
}
void Game::initialPacmanPos()
{
	Position CurrentPosition = this->m_Pacman.GetPosition();
	Position InitialPosition = this->m_Pacman.GetInitialPosition();

	int xCoord, yCoord;

	xCoord = CurrentPosition.getXcoord();
	yCoord = CurrentPosition.getYcoord();

	gotoxy(xCoord, yCoord);
	cout << m_Board.getCellValue(CurrentPosition);

	m_Pacman.ResetCurrentPosition();

	m_Pacman.Move();

}
void Game::InitialFruitPosition()
{
	
	m_Fruit.ActivateFruit(m_Board.GetRandomPosition());
}
void Game::InitializeGhosts(const int& ghostsNumber)
{
	for (int i = 0; i < ghostsNumber; i++)
	{
		Ghost _Ghost(Color::getColor(i), { 38, 14 + i }, 1);
		m_Ghosts.push_back(_Ghost);
	}
}
void Game::crossTunnel(const int yCoord, const int xCoord)
{
	if (xCoord == 0)
	{
		m_Pacman.SetPosition(m_Board.getWidth() - 1, yCoord);
	}

	else if (xCoord == m_Board.getWidth() - 1)
	{
		m_Pacman.SetPosition(0, yCoord);
	}

	else if (yCoord == 0)
	{
		m_Pacman.SetPosition(xCoord, m_Board.getHeight() - 1);
	}

	else if (yCoord == m_Board.getHeight() - 1)
	{
		m_Pacman.SetPosition(xCoord, 0);
	}
}

//Move Functions
void Game::MovePacman(char nextDir)
{
	int yCoord = m_Pacman.GetYcoord();
	int xCoord = m_Pacman.GetXcoord();


	if (Direction::isValidDirection(nextDir)) { m_Pacman.SetDirection(nextDir); }

	else { nextDir = m_Pacman.GetCurrentDirection(); };

	switch (toupper(nextDir))
	{
	case static_cast<char>(Direction::eDirection::UP):
		if (PacmanStepCheck(yCoord - 1, xCoord))
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::DOWN):
		if (PacmanStepCheck(yCoord + 1, xCoord))
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::LEFT):
		if (PacmanStepCheck(yCoord, xCoord - 1))
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::RIGHT):
		if (PacmanStepCheck(yCoord, xCoord + 1))
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	default:
		break;
	}
}
void Game::MoveGhost(int ghost)
{
	char Moved = false;


	int yCoord = m_Ghosts[ghost].GetYcoord();
	int xCoord = m_Ghosts[ghost].GetXcoord();

	while (!Moved)
	{
		Direction::eDirection ghostDir = Direction::getRandDir();
		switch (ghostDir)
		{
		case Direction::eDirection::UP:
			Moved = GhostStepCheck(yCoord - 1, xCoord, ghost);
			break;

		case Direction::eDirection::DOWN:
			Moved = GhostStepCheck(yCoord + 1, xCoord, ghost);
			break;

		case Direction::eDirection::LEFT:
			Moved = GhostStepCheck(yCoord, xCoord - 1, ghost);
			break;

		case Direction::eDirection::RIGHT:
			Moved = GhostStepCheck(yCoord, xCoord + 1, ghost);
			break;

		default:
			break;
		}

	}

}
void Game::MoveFruit()
{

	char Moved = false;
	Direction::eDirection fruitDirection;
	int yCoord = m_Fruit.GetYcoord();
	int xCoord = m_Fruit.GetXcoord();
	bool activeFruit = rand() % 2;

	if (activeFruit && !m_Fruit.IsActive())
	{
		m_Fruit.ActivateFruit(m_Board.GetRandomPosition());
	}

	while (!Moved && m_Fruit.IsActive())
	{
		fruitDirection = Direction::getRandDir();
		switch (fruitDirection)
		{
		case Direction::eDirection::UP:
			if (FruitStepCheck(yCoord - 1, xCoord))
			{
				m_Fruit.Erase(yCoord, xCoord, m_Board);
				m_Fruit.Move();
				Moved = true;
			}
			break;

		case Direction::eDirection::DOWN:
			if (FruitStepCheck(yCoord + 1, xCoord))
			{
				m_Fruit.Erase(yCoord, xCoord, m_Board);
				m_Fruit.Move();
				Moved = true;
			}
			break;

		case Direction::eDirection::LEFT:
			if (FruitStepCheck(yCoord, xCoord - 1))
			{
				m_Fruit.Erase(yCoord, xCoord, m_Board);
				m_Fruit.Move();
				Moved = true;
			}
			break;

		case Direction::eDirection::RIGHT:
			if (FruitStepCheck(yCoord, xCoord + 1))
			{
				m_Fruit.Erase(yCoord, xCoord, m_Board);
				m_Fruit.Move();
				Moved = true;
			}
			break;

		default:
			break;
		}

	}
}

//StepChecks Functions
bool Game::PacmanStepCheck(const int yCoord, const int xCoord)
{

	bool Moved = true;
	Position nextPosition(xCoord, yCoord);
	if (CheckPacmanIntersection(yCoord, xCoord))
	{
		m_Pacman.UpdateLife();
		Moved = false;
		if (!m_Pacman.IsAlive())
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
		char nextPos = m_Board.getCellValue(xCoord, yCoord);

		if (nextPosition == m_Fruit.GetPosition())
		{
			m_Pacman.UpdateFruitScore(m_Fruit.GetScoreValue());
			m_Fruit.DeActivateFruit(m_Board);
		}


		switch (nextPos)
		{

		case static_cast<char>(BoardObjects::WALL):
			Moved = false;
			break;


		case static_cast<char>(BoardObjects::SPACE):
			if (!checkTunnel(yCoord, xCoord))
				m_Pacman.SetPosition(xCoord, yCoord);
			else
				crossTunnel(yCoord, xCoord);
			break;

		case static_cast<char>(BoardObjects::FOOD):
			if (m_Pacman.UpdateBreadcrumbScore(m_Board))
			{
				m_Pacman.SetPosition(xCoord, yCoord);
				eraseFood(yCoord, xCoord);
			}

			else
				m_gameStatus = eGameStatus::WON;
			break;

		default:
			break;
		}

	}



	return Moved;

}
bool Game::GhostStepCheck(const int yCoord, const int xCoord, int ghost)
{
	bool IsValidStep = true;

	if (CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::PACMAN))
	{
		m_Pacman.UpdateLife();
		if (m_Pacman.IsAlive())
		{
			initView();
		}
		else
		{
			m_gameStatus = eGameStatus::LOST;
		}
	}


	else if (CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::GHOST))
	{
		IsValidStep = false;
	}

	else //there is not pacman or ghost in the next direction
	{
		int CurrentXCoord = m_Ghosts[ghost].GetXcoord();
		int CurrentYCoord = m_Ghosts[ghost].GetYcoord();
		char nextPos = m_Board.getCellValue(xCoord, yCoord);

		CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::FRUIT);
		switch (nextPos) {
		case static_cast<char>(BoardObjects::WALL):
			IsValidStep = false;
			break;

		case static_cast<char>(BoardObjects::SPACE):
			m_Ghosts[ghost].Erase(CurrentYCoord, CurrentXCoord, m_Board);
			m_Ghosts[ghost].SetPosition(xCoord, yCoord);
			m_Ghosts[ghost].Move();
			break;

		case static_cast<char>(BoardObjects::FOOD):
			if (!checkTunnel(yCoord, xCoord))
			{
				m_Ghosts[ghost].Erase(CurrentYCoord, CurrentXCoord, m_Board);
				m_Ghosts[ghost].SetPosition(xCoord, yCoord);
				m_Ghosts[ghost].Move();
			}

			else
			{
				IsValidStep = false;
			}

			break;

		default:
			break;

		}
	}

	return IsValidStep;

}
bool Game::FruitStepCheck(const int yCoord, const int xCoord)
{
	bool isValidStep = true;
	char cellValue = m_Board.getCellValue(xCoord, yCoord);

	if (!CheckFruitIntersection({ yCoord, xCoord }, BoardObjects::PACMAN) && !CheckFruitIntersection({ yCoord, xCoord }, BoardObjects::GHOST))
	{
		if (cellValue == static_cast<char>(BoardObjects::WALL))
			isValidStep = false;

		else if (cellValue == static_cast<char>(BoardObjects::FOOD) || cellValue == static_cast<char>(BoardObjects::SPACE))
		{
			if (!checkTunnel(yCoord, xCoord))
			{
				m_Fruit.SetPosition(xCoord, yCoord);
			}

			else
				isValidStep = false;
		}
	}
	else
		
		isValidStep = false;

	return isValidStep;

}
bool Game::CheckFruitIntersection(Position nextPosition, BoardObjects gameObject)
{
	char Intersected = false;
	switch (gameObject)
	{
	case BoardObjects::PACMAN:
		if (nextPosition == m_Pacman.GetPosition())
		{
			m_Pacman.UpdateFruitScore(m_Fruit.GetScoreValue());
			m_Fruit.DeActivateFruit(m_Board);
			Intersected = true;
		}
		break;


	case BoardObjects::GHOST:
		size_t ghostsNumber = m_Ghosts.size();
		for (int i = 0; i < ghostsNumber && !Intersected; i++)
		{
			if (nextPosition == m_Ghosts[i].GetPosition())
			{
				m_Fruit.DeActivateFruit(m_Board);
				Intersected = true;
			}
		}
		break;
	}

	return Intersected;
}
bool Game::CheckPacmanIntersection(const int yCoord, const int xCoord)
{
	bool IsIntersecting = false;
	size_t ghostsNumber = m_Ghosts.size();
	const Position& NextPosition = { xCoord, yCoord };
	for (int i = 0; i < ghostsNumber && !IsIntersecting; i++)
	{
		if (NextPosition == m_Ghosts[i].GetPosition())
			IsIntersecting = true;
	}


	return IsIntersecting;
}
bool Game::CheckGhostIntersection(int ghostInd, int yCoord, int xCoord, BoardObjects gameObject)
{
	bool isIntersecting = false;
	Position nextPosition = { xCoord, yCoord };

	switch (gameObject)
	{
	case BoardObjects::GHOST:

		for (int i = 0; i < m_Ghosts.size() && !isIntersecting; i++)
		{
			if (i != ghostInd)
			{
				if (nextPosition == m_Ghosts[i].GetPosition())
				{
					isIntersecting = true;
				}
			}
		}
		break;

	case BoardObjects::PACMAN:

		if (nextPosition == m_Pacman.GetPosition())
			isIntersecting = true;
		break;

	case BoardObjects::FRUIT:
		if (nextPosition == m_Fruit.GetPosition())
		{
			m_Fruit.DeActivateFruit(m_Board);

		}
		break;
	}

	return isIntersecting;

}
bool Game::checkTunnel(const int yCoord, const int xCoord)
{
	if ((xCoord == 0 || xCoord == m_Board.getWidth() - 1) && m_Board.getCellValue(xCoord, yCoord) != (char)BoardObjects::WALL)
		return true;

	else if ((yCoord == 0 || yCoord == m_Board.getHeight() - 1) && m_Board.getCellValue(xCoord, yCoord) != (char)BoardObjects::WALL)
		return true;

	else
		return false;

}
void Game::eraseFood(const int yCoord, const int xCoord)
{
	m_Board.setChar(xCoord, yCoord, static_cast<char>(BoardObjects::SPACE));
}
void Game::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0,  fruitMoves =0;

	if (!getColorStyle())
		setDefaultColor();

	hideCursor();

	while (m_gameStatus == eGameStatus::RUNNING)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 27)
			{
				PauseGame();
			}

			MovePacman(key);
		}
		else
			MovePacman(m_Pacman.GetCurrentDirection());

		pacmanMoves++;

		if (pacmanMoves % 2 == 0)
		{
			for (int i = 0; i < m_Ghosts.size(); i++)
			{
				MoveGhost(i);
			}
		}

		else if (pacmanMoves % 5 == 0)
		{
			MoveFruit();
			fruitMoves++;
		}

		else if (fruitMoves % 10 == 0)
		{
			m_Fruit.DeActivateFruit(m_Board);
		}

		Sleep(300);
		ShowPlayerStatus();
	}

	if (m_gameStatus == eGameStatus::WON)
		userWon();
	else
		userLost();

}
void Game::PauseGame()
{
	do {
		gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
		if (this->m_IsColorful)
			Color::resetOutputColor();
		cout << " Game Paused, press ESC to continue.";

	} while (!_kbhit() || _getch() != 27);
	gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
	cout << "                                       " << endl;

}
void Game::ShowPlayerStatus()
{
	int lives = m_Pacman.GetCurrentLives();
	int score = m_Pacman.GetCurrentScore();

	gotoxy(0, this->m_Board.getHeight() + 1);

	if (this->m_IsColorful)
		Color::resetOutputColor();

	cout << "Current score: ";

	if (this->m_IsColorful)
		Color::applyOutputColor(Color::getColorValue(Color::eColor::BOLD_GREEN));
	cout << score;

	if (this->m_IsColorful)
		Color::resetOutputColor();

	gotoxy(this->m_Board.getWidth() - 20, this->m_Board.getHeight() + 1);

	cout << "Lives Left:";

	if (this->m_IsColorful)
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
	if (this->m_IsColorful)
		Color::resetOutputColor();
}
void Game::userWon()
{
	clrscr();
	if (this->m_IsColorful)
		Color::resetOutputColor();
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
	if (this->m_IsColorful)
		Color::resetOutputColor();
	cout << R"(
 __     __           _               _   _ 
 \ \   / /          | |             | | | |
  \ \_/ /__  _   _  | |     ___  ___| |_| |
   \   / _ \| | | | | |    / _ \/ __| __| |
    | | (_) | |_| | | |___| (_) \__ \ |_|_|
    |_|\___/ \__,_| |______\___/|___/\__(_)
                                           
                                           
)";

	cout << endl << "  Press any key to go back to the main menu..." << endl;
	while (!_kbhit()) {};
	clrscr();
}
void Game::setColorStyle(bool isColorful)
{
	if (!isColorful)
		setDefaultColor();
	m_IsColorful = isColorful;
}
void Game::setDefaultColor() //this function sets the default color (white) to all of the game and board objects.
{
	size_t ghostsNumber = m_Ghosts.size();
	m_Board.setBreadcrumColor(Color::eColor::DEFAULT);
	m_Board.setWallColor(Color::eColor::DEFAULT);
	m_Pacman.SetColor(Color::eColor::DEFAULT);
	for (int i = 0; i < ghostsNumber; i++)
	{
		m_Ghosts[i].SetColor(Color::eColor::DEFAULT);
	}

}

//Updated functions for inheritence
//bool Game::updateLife()
//{
//	m_Lives--;
//
//	if (m_Lives == 0)
//		return false;
//
//	else
//		return true;
//}
//bool Game::updateScore()
//{
//	m_BreadcrumbsScore++;
//
//	if (m_BreadcrumbsScore == m_Board.getMaxScore())
//		return false;
//
//	return true;
//}
//void Game::MoveCreature(char nextDir, BoardObjects object)
//{
//
//}
//void Game::printPacman(const int yCoord, const int xCoord)
//{
//	gotoxy(xCoord, yCoord);
//	int color;
//	if (this->m_isColorful)
//	{
//		color = m_Pacman.getColor().getColor();
//		Color::applyOutputColor(color);
//	}
//	cout << m_Pacman.getFigure();
//} 
//void Game::eraseGhost(const int yCoord, const int xCoord)
//{
//	gotoxy(xCoord, yCoord);
//	int color;
//	if (m_Board.getCellValue(xCoord, yCoord) == (char)BoardObjects::FOOD)
//	{
//		color = m_Board.getBreadcrumbColor().getColor();
//		if (this->m_isColorful)
//		{
//			Color::applyOutputColor(color);
//		}
//		cout << static_cast<char>(BoardObjects::FOOD);
//
//	}
//	else // there was a space before
//	{
//		cout << static_cast<char>(BoardObjects::SPACE);
//	}
//
//	
//}
//void Game::printGhost(const int yCoord, const int xCoord, int ghost)
//{
//	gotoxy(xCoord, yCoord);
//
//	int color;
//
//	if (this->m_isColorful)
//	{
//		color = m_Ghost[ghost].getColor().getColor();
//		Color::applyOutputColor(color);
//	}
//	cout << m_Ghost[ghost].getFigure();
//
//}
//void Game::erasePacman(const int yCoord, const int xCoord)
//{
//	gotoxy(xCoord, yCoord);
//	cout << static_cast<char>(BoardObjects::SPACE);
//}
//bool Game::isValidMove(char move)
//{
//	Direction::eDirection direction = Direction::Convert(move);
//	if (direction != Direction::eDirection::UNDEFINED)
//		return true;
//
//	else
//		return false;
//}
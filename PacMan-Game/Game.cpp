#include "Game.h"

Game::~Game()
{
	size_t totalGhosts = m_Ghosts.size();
	for (size_t i = 0; i < totalGhosts; i++)
	{
		delete m_Ghosts[i];
	}
}
void Game::initView()
{
	initialPacmanPos();
	initialGhostPos();
	InitializeFruitPosition();

}
void Game::initialGhostPos()
{
	size_t ghostsNumber = m_Ghosts.size();
	int xCoord, yCoord;
	Position CurrentPosition;
	Position InitialPosition;

	for (int i = 0; i < ghostsNumber; i++)
	{
		CurrentPosition = this->m_Ghosts[i]->GetPosition();
		InitialPosition = this->m_Ghosts[i]->GetInitialPosition();

		xCoord = CurrentPosition.getXcoord();
		yCoord = CurrentPosition.getYcoord();

		gotoxy(xCoord, yCoord);
		m_Ghosts[i]->ResetCurrentPosition();
		m_Ghosts[i]->Erase(yCoord, xCoord, m_Board);
		m_Ghosts[i]->Move();
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
void Game::InitializeFruitPosition()
{
	m_Fruit.DeActivateFruit(m_Board);
	m_Fruit.ActivateFruit(m_Board.GetRandomPosition());
}
void Game::InitializeGhostsVector(const vector<Position>& ghostsMoves)
{
	Position initialPosition;
	size_t totalGhosts = ghostsMoves.size();
	size_t _height = m_Board.getHeight();
	size_t _width = m_Board.getWidth();

	m_Ghosts.reserve(totalGhosts);
	for (int i = 0; i < totalGhosts; i++)
	{
		initialPosition = ghostsMoves[i];
		Ghost* _Ghost = new Ghost(Color::getColor(i), initialPosition, m_GameMode, _height, _width);
		m_Ghosts.push_back(_Ghost);
	}
}
void Game::CrossTunnel(const int yCoord, const int xCoord)
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
void Game::MoveGhost(int ghost, int& ghostsMoves)
{
	Direction::eDirection nextDirection, lastDirection = Direction::eDirection::VALID;
	char Moved = false;
	int yCoord = m_Ghosts[ghost]->GetYcoord();
	int xCoord = m_Ghosts[ghost]->GetXcoord();
	PositionsVector ghostsCurrentPositions;

	LoadGhostsPositions(ghostsCurrentPositions, m_Ghosts, ghost);

	while (!Moved)
	{
		if (DirectionValidator(lastDirection, ghost, ghostsMoves) == true)
		{
			nextDirection = m_Ghosts[ghost]->GetMovement(m_Board.GetBoard(), ghost, m_Pacman.GetPosition(), m_Ghosts[ghost]->GetPosition(), ghostsCurrentPositions, ghostsMoves);

			switch (nextDirection)
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

			if (Moved) { m_Ghosts[ghost]->SetDirection(static_cast<char>(nextDirection)); }
			else { lastDirection = Direction::eDirection::UNDEFINED; }

		}
	}

}
void Game::MoveFruit()
{

	char Moved = false;
	Direction::eDirection fruitDirection;
	int yCoord;
	int xCoord;
	bool activeFruit = rand() % 2;

	if (activeFruit && !m_Fruit.IsActive())
	{

		m_Fruit.ActivateFruit(m_Board.GetRandomPosition());
	}

	yCoord = m_Fruit.GetYcoord();
	xCoord = m_Fruit.GetXcoord();

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
		if (CheckTunnel(yCoord, xCoord))
		{
			CrossTunnel(yCoord, xCoord);
			Moved = true;
		}
		else if (CheckBoardEdge(xCoord, yCoord))
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
				m_Pacman.SetPosition(xCoord, yCoord);
				break;

			case static_cast<char>(BoardObjects::FOOD):
				if (m_Pacman.UpdateBreadcrumbScore(m_Board))
				{
					m_Pacman.SetPosition(xCoord, yCoord);
					EraseFood(yCoord, xCoord);
				}
				else
					m_gameStatus = eGameStatus::WON;

				break;

			default:
				break;
			}
		}
		else { Moved = false; }

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



	else 
	{
		if (CheckBoardEdge(xCoord, yCoord)) {
			int CurrentXCoord = m_Ghosts[ghost]->GetXcoord();
			int CurrentYCoord = m_Ghosts[ghost]->GetYcoord();

			char nextPos = m_Board.getCellValue(xCoord, yCoord);

			CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::FRUIT);

			switch (nextPos) {
			case static_cast<char>(BoardObjects::WALL) || '%' || 'L':
				IsValidStep = false;
				break;

			case static_cast<char>(BoardObjects::SPACE):
				m_Ghosts[ghost]->Erase(CurrentYCoord, CurrentXCoord, m_Board);
				m_Ghosts[ghost]->SetPosition(xCoord, yCoord);
				m_Ghosts[ghost]->Move();
				break;

			case static_cast<char>(BoardObjects::FOOD):
				if (!CheckTunnel(yCoord, xCoord))
				{
					m_Ghosts[ghost]->Erase(CurrentYCoord, CurrentXCoord, m_Board);
					m_Ghosts[ghost]->SetPosition(xCoord, yCoord);
					m_Ghosts[ghost]->Move();
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
		else IsValidStep = false;
	}

	return IsValidStep;

}
bool Game::FruitStepCheck(const int yCoord, const int xCoord)
{
	bool isValidStep = true;
	if (CheckBoardEdge(xCoord, yCoord))
	{


		char cellValue = m_Board.getCellValue(xCoord, yCoord);

		if (!CheckFruitIntersection({ yCoord, xCoord }, BoardObjects::PACMAN) &&
			!CheckFruitIntersection({ yCoord, xCoord }, BoardObjects::GHOST))
		{
			if (cellValue == static_cast<char>(BoardObjects::WALL))
				isValidStep = false;

			else if (cellValue == static_cast<char>(BoardObjects::FOOD) ||
					cellValue == static_cast<char>(BoardObjects::SPACE) ||
					cellValue == static_cast<char>(BoardObjects::LEGEND))
			{
				if (!CheckTunnel(yCoord, xCoord))
				{
					m_Fruit.SetPosition(xCoord, yCoord);
				}

				else
					isValidStep = false;
			}
		}
		else

			isValidStep = false;
	}
	else isValidStep = false;

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
			if (nextPosition == m_Ghosts[i]->GetPosition())
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
		if (NextPosition == m_Ghosts[i]->GetPosition())
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
				if (nextPosition == m_Ghosts[i]->GetPosition())
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
bool Game::CheckTunnel(const int yCoord, const int xCoord)
{
	int boardWidth = m_Board.getWidth() - 1;
	int boardHeight = m_Board.getHeight() - 1;
	int otherSide;

	if (xCoord == 0 || xCoord == boardWidth)//side tunnel
	{
		otherSide = abs(boardWidth - xCoord);
		if (m_Board.getCellValue(otherSide, yCoord) != static_cast<char>(BoardObjects::WALL) && m_Board.getCellValue(xCoord, yCoord) != static_cast<char>(BoardObjects::WALL))
		{
			return true;
		}
		return false;
	}
	else if (yCoord == 0 || yCoord == boardHeight)//top tunnel
	{
		otherSide = abs(boardHeight - yCoord);
		if (m_Board.getCellValue(xCoord, otherSide) != static_cast<char>(BoardObjects::WALL) && m_Board.getCellValue(xCoord, yCoord) != static_cast<char>(BoardObjects::WALL))
		{
			return true;
		}

		return false;
	}
	else
		return false;

}
void Game::EraseFood(const int yCoord, const int xCoord)
{
	m_Board.setChar(xCoord, yCoord, static_cast<char>(BoardObjects::SPACE));
}
void Game::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0;

	if (!GetColorStyle())
		SetDefaultColor();

	hideCursor();

	while (m_gameStatus == eGameStatus::RUNNING)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 27)
			{
				m_gameStatus = eGameStatus::ESC_PRESSED;

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
				MoveGhost(i, ghostsMoves);
			}
			ghostsMoves++;

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
		m_TotalScore = GetTotalScore();
		m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), m_TotalScore, m_IsColorful);
	}



}
void Game::userWon(bool color)
{
	clrscr();
	if (color)
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
void Game::userLost(bool color)
{
	clrscr();
	if (color)
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
void Game::SetColorStyle(bool isColorful)
{
	if (!isColorful)
		SetDefaultColor();
	m_IsColorful = isColorful;
}
void Game::SetDefaultColor() //this function sets the default color (white) to all of the game and board objects.
{
	size_t ghostsNumber = m_Ghosts.size();
	m_Board.ResetColors();
	m_Pacman.SetColor(Color::eColor::DEFAULT);
	m_Fruit.SetColor(Color::eColor::DEFAULT);
	for (int i = 0; i < ghostsNumber; i++)
	{
		m_Ghosts[i]->SetColor(Color::eColor::DEFAULT);
	}

}
bool Game::CheckBoardEdge(int xCoord, int yCoord)
{
	if (yCoord >= m_Board.getHeight() || yCoord < 0)
		return false;

	else if (xCoord >= m_Board.getWidth() || xCoord < 0)
		return false;
	else
		return true;
}
void Game::LoadGhostsPositions(PositionsVector& positions, GhostsVector ghosts, int currentGhost)
{
	size_t totalGhosts = ghosts.size();
	for (size_t i = 0; i < totalGhosts; i++)
	{
		if (i != currentGhost)
			positions.push_back(ghosts[i]->GetPosition());
	}

}
bool Game::DirectionValidator(Direction::eDirection& lastDirection, int ghost, int& ghostMoves)
{


	if (lastDirection == Direction::eDirection::UNDEFINED)
	{
		switch (m_GameMode)
		{
		case GameMode::NOVICE:
			lastDirection = static_cast<Direction::eDirection>(m_Ghosts[ghost]->GetCurrentDirection());
			break;

		default:
			lastDirection = Direction::getRandDir();
			break;
		}
		ghostMoves++;

	}

	return true;
}
int Game::GetTotalScore()
{
	m_TotalScore = m_Pacman.GetFruitScore() + m_Pacman.GetBreadcrumbScore();
	return m_TotalScore;
}
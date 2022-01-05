#include "LoadedGame.h"

void LoadedGame::PlayGame()
{
	char nextDirection = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0;

	m_GameFiles.OpenRecordingFiles();

	if (m_GameType != GameType::eType::SILENT_LOAD)
	{
		GetColorStatus();
		if (!GetColorStyle()) { SetDefaultColor(); }
		hideCursor();
	}



	while (getGameStatus() == eGameStatus::RUNNING)
	{
		stringstream currentGameFrame; 
		currentGameFrame << m_GameFiles.GetStepsFileLine();

		//nextDirection = GetPacmanNextDirection(currentGameFrame);
			MovePacman(nextDirection);

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

		if (m_GameType != GameType::eType::SILENT_LOAD)
		{
			Sleep(100);
			m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), GetTotalScore(), GetColorStyle());
		}

	}

	m_GameFiles.CloseFiles();
}

void LoadedGame::initialGhostPos()
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
		m_Ghosts[i]->ResetCurrentPosition();

		if (m_GameType != GameType::eType::SILENT_LOAD)
		{
			gotoxy(xCoord, yCoord);
			m_Ghosts[i]->Erase(yCoord, xCoord, m_Board);
			m_Ghosts[i]->Move();
		}
	}
}

void LoadedGame::initialPacmanPos()
{
	Position CurrentPosition = this->m_Pacman.GetPosition();
	Position InitialPosition = this->m_Pacman.GetInitialPosition();

	int xCoord, yCoord;

	xCoord = CurrentPosition.getXcoord();
	yCoord = CurrentPosition.getYcoord();
	m_Pacman.ResetCurrentPosition();

	if (m_GameType != GameType::eType::SILENT_LOAD)
	{
		gotoxy(xCoord, yCoord);
		cout << m_Board.getCellValue(CurrentPosition);
		m_Pacman.Move();
	}
}

void LoadedGame::MovePacman(char nextDir)
{
	int yCoord = m_Pacman.GetYcoord();
	int xCoord = m_Pacman.GetXcoord();
	bool isSilentLoad = (m_GameType == GameType::eType::SILENT_LOAD);

	if (Direction::isValidDirection(nextDir)) { m_Pacman.SetDirection(nextDir); }

	else { nextDir = m_Pacman.GetCurrentDirection(); };

	switch (toupper(nextDir))
	{
	case static_cast<char>(Direction::eDirection::UP):
		if (PacmanStepCheck(yCoord - 1, xCoord) &&
			!isSilentLoad)
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::DOWN):
		if (PacmanStepCheck(yCoord + 1, xCoord) &&
			!isSilentLoad)
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::LEFT):
		if (PacmanStepCheck(yCoord, xCoord - 1) &&
			!isSilentLoad)
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	case static_cast<char>(Direction::eDirection::RIGHT):
		if (PacmanStepCheck(yCoord, xCoord + 1) &&
			!isSilentLoad)
		{
			m_Pacman.Erase(yCoord, xCoord, m_Board);
			m_Pacman.Move();
		}
		break;

	default:
		break;
	}
}

bool LoadedGame::PacmanStepCheck(const int yCoord, const int xCoord)
{

	bool Moved = true;
	bool isSilentLoad = (m_GameType == GameType::eType::SILENT_LOAD);
	Position nextPosition(xCoord, yCoord);
	if (CheckPacmanIntersection(yCoord, xCoord))
	{
		m_Pacman.UpdateLife();
		Moved = false;
		if (!m_Pacman.IsAlive())
		{
			SetGameStatus(eGameStatus::LOST);
		}

		else if (!isSilentLoad)
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
				m_Fruit.SetActivationMode(false);
				if (!isSilentLoad)
					m_Fruit.Erase(nextPosition.getYcoord(), nextPosition.getXcoord(), m_Board);
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
					if (!isSilentLoad) { EraseFood(yCoord, xCoord); }
				}
				else
					SetGameStatus(eGameStatus::WON);
				break;

			default:
				break;
			}
		}
		else { Moved = false; }

	}



	return Moved;
}

void LoadedGame::InitializeFruitPosition()
{
	//Position& nextPosition = GetFruitNextPosition();
	//int scoreValue = GetNextFruitValue(); //TODO!!!

	if (m_GameType != GameType::eType::SILENT_LOAD)
	{
		Position currentPosition = m_Fruit.GetPosition();
		m_Fruit.Erase(currentPosition.getYcoord(), currentPosition.getXcoord(), m_Board);
	}
	//m_Fruit.SetActivationMode(false);
	//m_Fruit.SetScoreValue(scoreValue);
	//m_Fruit.SetFigure(m_Fruit.GetFruitFigure(scoreValue));
	//m_Fruit.SetPosition(nextPosition);
	//m_Fruit.SetInitialPosition(nextPosition);


}

void LoadedGame::MoveGhost(int ghost, int& ghostsMoves)
{
	Direction::eDirection nextDirection = Direction::eDirection::VALID, lastDirection = Direction::eDirection::VALID;
	char Moved = false;

	int yCoord = m_Ghosts[ghost]->GetYcoord();
	int xCoord = m_Ghosts[ghost]->GetXcoord();

	PositionsVector ghostsCurrentPositions;

	LoadGhostsPositions(ghostsCurrentPositions, m_Ghosts, ghost);

	while (!Moved)
	{
		//if (DirectionValidator(lastDirection, ghost, ghostsMoves) == true)
		//{
			//nextDirection = GetGhostNextMove(ghost); THIS METHOD WILL GET NEXT GHOST'S (BY INDEX) DIRECTION

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

		/*}*/
	}
}

bool LoadedGame::GhostStepCheck(const int yCoord, const int xCoord, int ghost)
{
	bool IsValidStep = true, isSilentLoad = m_GameType == GameType::eType::SILENT_LOAD;

	if (CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::PACMAN))
	{
		m_Pacman.UpdateLife();
		if (m_Pacman.IsAlive())
		{
			initView();
		}
		else
		{
			SetGameStatus(eGameStatus::LOST);
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
				if (!isSilentLoad) m_Ghosts[ghost]->Move();
				break;

			case static_cast<char>(BoardObjects::FOOD):
				if (!CheckTunnel(yCoord, xCoord))
				{
					m_Ghosts[ghost]->Erase(CurrentYCoord, CurrentXCoord, m_Board);
					m_Ghosts[ghost]->SetPosition(xCoord, yCoord);

					if (!isSilentLoad) m_Ghosts[ghost]->Move();
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

		else
			IsValidStep = false;
	}

	return IsValidStep;
}

void LoadedGame::MoveFruit()
{
	bool Moved = false, isSilentLoad = (m_GameType == GameType::eType::SILENT_LOAD);
	Direction::eDirection fruitDirection;
	int yCoord;
	int xCoord;
	//Position& nextPosition = GetFruitNextPosition(); // MAKE THIS METHOD

	/*if (!m_Fruit.IsActive())
	{

		m_Fruit.ActivateFruit(nextPosition);
	}*/

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
				if (!isSilentLoad)
				{
					m_Fruit.Erase(yCoord, xCoord, m_Board);
					m_Fruit.Move();
				}

				Moved = true;
			}
			break;

		case Direction::eDirection::DOWN:
			if (FruitStepCheck(yCoord + 1, xCoord))
			{
				if (!isSilentLoad)
				{
					m_Fruit.Erase(yCoord, xCoord, m_Board);
					m_Fruit.Move();
				}
				Moved = true;
			}
			break;

		case Direction::eDirection::LEFT:
			if (FruitStepCheck(yCoord, xCoord - 1))
			{
				if (!isSilentLoad)
				{
					m_Fruit.Erase(yCoord, xCoord, m_Board);
					m_Fruit.Move();
				}
				Moved = true;
			}
			break;

		case Direction::eDirection::RIGHT:
			if (FruitStepCheck(yCoord, xCoord + 1))
			{
				if (!isSilentLoad)
				{
					m_Fruit.Erase(yCoord, xCoord, m_Board);
					m_Fruit.Move();
				}
				Moved = true;
			}
			break;

		default:
			break;
		}

	}
}

bool LoadedGame::FruitStepCheck(const int yCoord, const int xCoord)
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

bool LoadedGame::CheckFruitIntersection(Position nextPosition, BoardObjects gameObject)
{
	char Intersected = false;
	switch (gameObject)
	{
	case BoardObjects::PACMAN:
		if (nextPosition == m_Pacman.GetPosition())
		{
			m_Pacman.UpdateFruitScore(m_Fruit.GetScoreValue());
			if (m_GameType != GameType::eType::SILENT_LOAD)
			{
				Position currentPosition = m_Fruit.GetPosition();
				m_Fruit.Erase(currentPosition.getYcoord(), currentPosition.getXcoord(), m_Board);
			}
			m_Fruit.SetActivationMode(false);
			Intersected = true;
		}
		break;


	case BoardObjects::GHOST:
		size_t ghostsNumber = m_Ghosts.size();
		for (int i = 0; i < ghostsNumber && !Intersected; i++)
		{
			if (nextPosition == m_Ghosts[i]->GetPosition())
			{
				if (m_GameType != GameType::eType::SILENT_LOAD)
				{
					Position currentPosition = m_Fruit.GetPosition();
					m_Fruit.Erase(currentPosition.getYcoord(), currentPosition.getXcoord(), m_Board);
				}
				m_Fruit.SetActivationMode(false);
				Intersected = true;
			}
		}
		break;
	}

	return Intersected;
}

void LoadedGame::GetColorStatus()
{

	if (m_GameFiles.GetStepsFileLine().compare("COLORFUL GAME") == 0)
		SetColorStyle(true);

	else
		SetColorStyle(false);
}

char LoadedGame::GetNextStep(stringstream& CurrentFrame)
{
	char nextStep;
	string gameCreature, nextStep, temp;
	getline(CurrentFrame, temp, '|');

	
}
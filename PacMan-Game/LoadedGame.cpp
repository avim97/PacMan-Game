#include "LoadedGame.h"

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

		else if(!isSilentLoad)
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

			if (nextPosition == m_Fruit.GetPosition() &&
				!isSilentLoad)
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
				if (m_Pacman.UpdateBreadcrumbScore(m_Board) &&
					!isSilentLoad)
				{
					m_Pacman.SetPosition(xCoord, yCoord);
					EraseFood(yCoord, xCoord);
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
		if (ValidateDirection(lastDirection, ghost, ghostsMoves) == true)
		{
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

		}
	}
}
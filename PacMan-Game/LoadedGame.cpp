#include "LoadedGame.h"

void LoadedGame::PlayGame()
{
	bool loadSucceded = true;
	char nextDirection = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0;

	m_GameFiles.OpenRecordingFiles();


	GetColorStatus();
	if (!GetColorStyle()) { SetDefaultColor(); }
	hideCursor();

	while (getGameStatus() == eGameStatus::RUNNING &&
		loadSucceded && m_GameFiles.IsStepsFileGood())
	{
		stringstream currentGameFrame;
		currentGameFrame << m_GameFiles.GetStepsFileLine();

		ApplyGameFrame(currentGameFrame, loadSucceded);

		if (!loadSucceded)
			this->m_GameLoadSucceded = false;

		if (m_GameType != GameType::eType::SILENT_LOAD &&
			getGameStatus() == eGameStatus::RUNNING)
		{
			Sleep(100);
			m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), GetTotalScore(), GetColorStyle());
		}

	}

	VerifyGameResult();
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

	m_Pacman.SetDirection(nextDir);

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
		m_GameResult = IntersectionResult;
		VerifyGameResult();

		if (!m_Pacman.IsAlive())
		{
			SetGameStatus(eGameStatus::LOST);
			m_GameResult = LostResult;
			VerifyGameResult();
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
				m_Fruit.SetActivationChangeFlag(true);

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
				{
					SetGameStatus(eGameStatus::WON);
					m_GameResult = BoardFinishedResult;
				}
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

void LoadedGame::MoveGhost(int ghost, char nextDir)
{
	Direction::eDirection direction = Direction::Convert(nextDir);
	int yCoord = m_Ghosts[ghost]->GetYcoord();
	int xCoord = m_Ghosts[ghost]->GetXcoord();

	PositionsVector ghostsCurrentPositions;

	LoadGhostsPositions(ghostsCurrentPositions, m_Ghosts, ghost);

	switch (direction)
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

bool LoadedGame::GhostStepCheck(const int yCoord, const int xCoord, int ghost)
{
	bool IsValidStep = true, isSilentLoad = m_GameType == GameType::eType::SILENT_LOAD;

	if (CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::PACMAN))
	{
		m_Pacman.UpdateLife();
		m_GameResult = IntersectionResult;
		VerifyGameResult(); //EXCEPTION

		if (!m_Pacman.IsAlive())
		{
			SetGameStatus(eGameStatus::LOST);
			m_GameResult = LostResult;
			VerifyGameResult(); //EXCEPTION
			initView();
		}
	}


	else if (CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::GHOST))
	{
		IsValidStep = false;
	}



	else
	{
		if (CheckBoardEdge(xCoord, yCoord)) 
		{
			int CurrentXCoord = m_Ghosts[ghost]->GetXcoord();
			int CurrentYCoord = m_Ghosts[ghost]->GetYcoord();
			char nextPos = m_Board.getCellValue(xCoord, yCoord);

			CheckGhostIntersection(ghost, yCoord, xCoord, BoardObjects::FRUIT);

			switch (nextPos) {
			case static_cast<char>(BoardObjects::WALL) || static_cast<char>(BoardObjects::NOT_FOOD) 
			|| static_cast<char>(BoardObjects::LEGEND) :
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

void LoadedGame::MoveFruit(char nextDir)
{
	bool isSilentLoad = (m_GameType == GameType::eType::SILENT_LOAD);
	Direction::eDirection fruitDirection = Direction::Convert(nextDir);
	int yCoord;
	int xCoord;

	yCoord = m_Fruit.GetYcoord();
	xCoord = m_Fruit.GetXcoord();


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
		}
		break;

	default:
		break;
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
			m_Fruit.SetActivationChangeFlag(true);
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
				m_Fruit.SetActivationChangeFlag(true);
				Intersected = true;
			}
		}
		break;
	}

	return Intersected;
}

void LoadedGame::GetColorStatus()
{

	if (m_GameFiles.GetStepsFileLine().compare("COLORFUL GAME\n") == 0)
		SetColorStyle(true);

	else
		SetColorStyle(false);
}

void LoadedGame::ApplyGameFrame(stringstream& currentFrame, bool& loadSucceded)
{

	string creatureData, nextAction;
	BoardObjects  creature;

	while (currentFrame.good() && currentFrame.peek() != endline) // ?? There is a problem here when i get to the end of the stringstream it reads ' ' and doensnt notify EOF
	{
		creature = GetCreature(creatureData, currentFrame);

		if (creature != BoardObjects::UNDEFINED)
		{
			if (GetAction(creature, creatureData, nextAction, currentFrame))
			{
				ExecuteAction(creature, creatureData, nextAction);
				m_TimePoint++;
			}

			else
			{
				loadSucceded = false;
			}

		}

		else { loadSucceded = false; }
	}

	//if (!loadSucceded)
	//	throw LoadException; implement later
}

BoardObjects LoadedGame::GetCreature(string& creature, stringstream& currentFrame) const
{
	BoardObjects game_creature;


	getline(currentFrame, creature, hyphen);

	GameCreatureValidator(game_creature, creature);

	switch (game_creature)
	{

	case BoardObjects::GHOST:
		if (!GetGhostNumber(creature, currentFrame))
			game_creature = BoardObjects::UNDEFINED;
		break;

	default:
		break;
	}

	return game_creature;
}

void LoadedGame::GameCreatureValidator(BoardObjects& creature, string& readCreature) const
{
	if (readCreature == pacman)
	{
		creature = BoardObjects::PACMAN;
	}

	else if (readCreature == ghost)
	{
		creature = BoardObjects::GHOST;
	}

	else if (readCreature == fruit)
	{
		creature = BoardObjects::FRUIT;
	}

	else
	{
		creature = BoardObjects::UNDEFINED;
	}

}

bool LoadedGame::GetGhostNumber(string& creature, stringstream& currentFrame) const
{
	string ghost_number;
	getline(currentFrame, ghost_number, hyphen);
	return GhostNumberValidator(ghost_number, creature);
}

bool LoadedGame::GhostNumberValidator(string& inputIndex, string& currentGhost) const
{
	using std::stoi;
	int index = stoi(inputIndex);
	bool isValidGhost;

	if (index >= MIN_INDEX && index <= MAX_INDEX)
	{
		currentGhost.clear();
		currentGhost.push_back(index + '0');
		isValidGhost = true;
	}

	else
	{
		isValidGhost = false;
	}
	return isValidGhost;
}

bool LoadedGame::GetAction(BoardObjects& game_creature, string& creature_data, string& nextAction, stringstream& currentFrame) const
{
	bool isValidAction = true;

	switch (game_creature)
	{
	case BoardObjects::PACMAN:
		GetDirection(game_creature, creature_data, nextAction, currentFrame);
		break;

	case BoardObjects::GHOST:
		GetDirection(game_creature, creature_data, nextAction, currentFrame);
		break;

	case BoardObjects::FRUIT:
		GetFruitAction(creature_data, nextAction, currentFrame);
		break;
	}

	if (nextAction == invalid_action)
		isValidAction = false;

	return isValidAction;
}

void LoadedGame::GetDirection(BoardObjects& creature, string& creature_data, string& nextAction, stringstream& currentFrame) const
{
	getline(currentFrame, nextAction, separator);

	if (nextAction != move_down && nextAction != move_up && nextAction != move_left &&
		(creature == BoardObjects::PACMAN && nextAction != move_stay) &&
		!ValidateNextDirection(creature, creature_data, nextAction))
	{
		nextAction = invalid_action;
	}
}

bool LoadedGame::ValidateNextDirection(BoardObjects& creature, string& creature_data, string& nextAction) const
{
	int xCoord, yCoord;

	switch (creature)
	{
	case BoardObjects::PACMAN:
		xCoord = m_Pacman.GetXcoord();
		yCoord = m_Pacman.GetYcoord();
		break;

	case BoardObjects::GHOST:

		xCoord = m_Ghosts[num_char_to_int(creature_data.front())]->GetXcoord();
		yCoord = m_Ghosts[num_char_to_int(creature_data.front())]->GetXcoord();
		break;

	case BoardObjects::FRUIT:
		xCoord = m_Fruit.GetXcoord();
		yCoord = m_Fruit.GetYcoord();
		break;
	}

	return DirectionValidator(xCoord, yCoord, nextAction);
}

void LoadedGame::GetFruitAction(string& creature_data, string& nextAction, stringstream& currentFrame) const
{
	stringstream action;

	getline(currentFrame, nextAction, separator);

	if (!VerifyFruitDirection(nextAction) && !VerifyFruitDeActivation(nextAction) && !VerifyFruitInitialization(creature_data, nextAction))
	{
		nextAction = invalid_action;
	}
}

bool LoadedGame::VerifyFruitDirection(string& nextAction) const
{
	bool isDirection = true;

	if (nextAction != move_down && nextAction != move_up && nextAction != move_left)
	{
		isDirection = false;
	}

	return isDirection;
}

bool LoadedGame::VerifyFruitDeActivation(string& nextAction) const
{
	bool isDeActivation = false;
	if (nextAction == action_deActivation)
		isDeActivation = true;
	return isDeActivation;
}

bool LoadedGame::VerifyFruitInitialization(string& creatureData, string& nextAction) const
{
	bool isInitialization = true;
	stringstream actionData;
	string data;
	Position initial_position;

	actionData << nextAction;

	getline(actionData, data, colon);

	if (data == action_initialization)
	{
		nextAction = action_initialization;

		getline(actionData, data, left_bracket);

		if (VerifyFruitValue(data))
		{

			creatureData = data + separator;

		}

		if (data != invalid_action)
		{
			getline(actionData, data, right_bracket);

			if (VerifyInitialPosition(data))
			{
				creatureData += data;
			}
		}

		else
			isInitialization = false;
	}

	else
		isInitialization = false;




	return isInitialization;
}

bool LoadedGame::VerifyFruitValue(string& actionData) const
{
	bool isValidValue = true;
	int value;
	stringstream ss_value;

	ss_value << actionData;
	ss_value >> value;

	if (value < 5 || value > 9)
	{
		isValidValue = false;
		actionData = invalid_action;
	}

	return isValidValue;
}

bool LoadedGame::VerifyInitialPosition(string& actionData) const
{
	bool isValidInitialPosition = true;
	stringstream ss_position;
	string xValue, yValue;

	ss_position << actionData;

	getline(ss_position, xValue, comma);
	getline(ss_position, yValue);

	if (!PositionValidator(xValue, yValue))
	{
		isValidInitialPosition = false;
		actionData = invalid_action;
	}

	return isValidInitialPosition;
}

bool LoadedGame::PositionValidator(string& xCoord, string& yCoord)const
{
	bool isValidPosition = true;
	int xValue, yValue;
	stringstream ss_xCoord, ss_yCoord;

	ss_xCoord << xCoord;
	ss_xCoord >> xValue;
	ss_yCoord << yCoord;
	ss_yCoord >> yValue;

	if (!CheckBoardEdge(xValue, yValue) || m_Board.getCellValue(xValue, yValue) == static_cast<char>(BoardObjects::WALL))
	{
		isValidPosition = false;
	}

	return isValidPosition;
}

bool LoadedGame::DirectionValidator(int& xCoord, int& yCoord, string& nextDirection) const
{
	Direction::eDirection direction = Direction::Convert(nextDirection);
	bool isValidDirection = true;

	switch (direction)
	{
	case Direction::eDirection::UP:
		isValidDirection = CheckBoardEdge(xCoord, yCoord - 1);
		break;

	case Direction::eDirection::DOWN:
		isValidDirection = CheckBoardEdge(xCoord, yCoord + 1);
		break;

	case Direction::eDirection::LEFT:
		isValidDirection = CheckBoardEdge(xCoord - 1, yCoord);
		break;

	case Direction::eDirection::RIGHT:
		isValidDirection = CheckBoardEdge(xCoord + 1, yCoord);
		break;

	default:
		break;
	}

	return isValidDirection;
}

void LoadedGame::ExecuteAction(BoardObjects& creatue, string& creatureData, string& action)
{
	
	switch (creatue)
	{
	case BoardObjects::PACMAN:
		MovePacman(Direction::ConvertToChar(action));
		break;

	case BoardObjects::GHOST:

		MoveGhost(num_char_to_int(creatureData.front()), Direction::ConvertToChar(action));
		break;

	case BoardObjects::FRUIT:
		ExecuteFruitAction(action, creatureData);
		break;
	}
}

void LoadedGame::ExecuteFruitAction(string& action, string& actionData)
{
	if (action == action_deActivation)
	{
		DeactivateFruit();
	}

	else if (action == action_initialization)
	{
		ActivateFruit(actionData);
	}

	else
	{
		MoveFruit(Direction::ConvertToChar(actionData));
	}

}

void LoadedGame::DeactivateFruit()
{
	int xCoord, yCoord;
	xCoord = m_Fruit.GetXcoord();
	yCoord = m_Fruit.GetYcoord();

	m_Fruit.SetActivationMode(false);
	m_Fruit.SetActivationChangeFlag(true); //?

	if (m_GameType != GameType::eType::SILENT_LOAD)
	{
		m_Fruit.Erase(yCoord, xCoord, m_Board);
	}
}
void LoadedGame::ActivateFruit(string& activation_data)
{
	using std::stoi;

	stringstream data;
	string value, xCoord, yCoord;
	Position initial_position;

	data << activation_data;
	getline(data, value, separator);
	getline(data, xCoord, comma);
	getline(data, yCoord);

	initial_position.setPosition(stoi(xCoord), stoi(yCoord));
	m_Fruit.ActivateFruit(initial_position, stoi(value));

	if (m_GameType != GameType::eType::SILENT_LOAD)
	{
		m_Fruit.Move();
	}

}
void LoadedGame::VerifyGameResult()
{
	string file_result = m_GameFiles.GetResultFileLine();
	string time;
	stringstream ss_timepoint;
	ss_timepoint << m_TimePoint;
	ss_timepoint >> time;

	if (m_GameResult + time == file_result)
	{
		m_GameLoadSucceded = false;
	}
}

void LoadedGame::VerifyGameResult(string& result)
{
	string file_result = m_GameFiles.GetResultFileLine();
	string time;
	stringstream ss_timepoint;
	ss_timepoint << m_TimePoint;
	ss_timepoint >> time;

	if (result + time == file_result)
	{
		m_GameLoadSucceded = false;
	}
}

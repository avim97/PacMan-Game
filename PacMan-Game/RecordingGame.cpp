#include "RecordingGame.h"

void RecordingGame::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0, currLives = m_Pacman.GetCurrentLives();
	bool fruitMoved = false, ghostsMoved = false;

	if (!GetColorStyle())
		SetDefaultColor();

	OpenRecordingFiles();
	m_GameFiles.InsertGameColorToFile(GetColorStyle());

	hideCursor();

	while (m_gameStatus == eGameStatus::RUNNING)
	{
		fruitMoved = false;
		ghostsMoved = false;

		if (_kbhit())
		{
			key = _getch();

			if (key == ESC)
			{
				PauseRecording();
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
			ghostsMoved = true;
		}

		if (pacmanMoves % 5 == 0)
		{
			MoveFruit();
			fruitMoves++;
			fruitMoved = m_Fruit.IsActive();
		}

		else if (fruitMoves % 10 == 0 && m_Fruit.IsActive())
		{
			m_Fruit.DeActivateFruit(m_Board);
		}

		Sleep(300);

		m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), GetTotalScore(), GetColorStyle());

		RecordSteps(ghostsMoved, fruitMoved);

		if (currLives != m_Pacman.GetCurrentLives())
		{
			currLives = m_Pacman.GetCurrentLives();
			UpdateResultFile(pacmanMoves, eGameStatus::INTERSECTION);
		}

		UpdateResultFile(pacmanMoves);

	}

	CloseRecordingFiles();
}
void RecordingGame::RecordSteps(bool& ghostsMoved, bool& fruitMoved)
{
	using file_consts::ghost;
	using file_consts::pacman;
	using file_consts::fruit;
	string currGameFrame;
	stringstream outputString;

	outputString << pacman << hyphen << space
		<< Direction::ConvertToString(m_Pacman.GetCurrentDirection()) << space << separator;

	if (m_Fruit.GetActivationChangeStatus())
	{
		if (m_Fruit.IsActive())
		{
			outputString << fruit << hyphen << action_initialization << colon << m_Fruit.GetScoreValue()
				<< left_bracket << m_Fruit.GetXcoord() << comma << m_Fruit.GetYcoord() << right_bracket << space << separator;
		}

		else
		{
			outputString << fruit << hyphen << action_deActivation << separator;
		}

		m_Fruit.SetActivationChangeFlag(false);
	}

	else if (fruitMoved && m_Fruit.GetCurrentDirection() != static_cast<char>(Direction::eDirection::STAY))
	{
		outputString << fruit << hyphen << space
			<< Direction::ConvertToString(m_Fruit.GetCurrentDirection()) << space << separator;
	}


	if (ghostsMoved)
	{
		for (int i = 0; i < m_Ghosts.size(); i++)
		{
			outputString << ghost << hyphen << space << i << space << hyphen << space
				<< Direction::ConvertToString(m_Ghosts[i]->GetCurrentDirection()) << space << separator;
		}
	}
	m_GameFiles.InsertStringToStepsFile(outputString);


}
void RecordingGame::UpdateResultFile(int& frameNumber)
{

	using file_consts::LostResult;
	using file_consts::BoardFinishedResult;
	using file_consts::ExitResult;
	using file_consts::IntersectionResult;

	stringstream result;

	switch (m_gameStatus)
	{
	case eGameStatus::WON:
		result << BoardFinishedResult << frameNumber;
		m_GameFiles.InsertStringToResultFile(result);
		break;

	case eGameStatus::LOST:
		result << LostResult << frameNumber;
		m_GameFiles.InsertStringToResultFile(result);
		break;

	case eGameStatus::EXIT:
		result << ExitResult << frameNumber;
		m_GameFiles.InsertStringToResultFile(result);
		break;

	default:
		break;
	}



}
void RecordingGame::UpdateResultFile(int& frameNumber, eGameStatus result)
{
	using file_consts::LostResult;
	using file_consts::BoardFinishedResult;
	using file_consts::ExitResult;
	using file_consts::IntersectionResult;

	stringstream ss_result;

	switch (result)
	{
	case eGameStatus::WON:
		ss_result << BoardFinishedResult << frameNumber;
		break;

	case eGameStatus::LOST:
		ss_result << LostResult << frameNumber;
		break;

	case eGameStatus::INTERSECTION:
		ss_result << IntersectionResult << frameNumber;
		break;

	case eGameStatus::RUNNING:
		ss_result << IntersectionResult << frameNumber;
		break;

	case eGameStatus::EXIT:
		ss_result << ExitResult << frameNumber;
		break;

	}

	m_GameFiles.InsertStringToResultFile(ss_result);
}
void RecordingGame::PauseRecording()
{
	bool isValidChoice = false;
	char inputChoice;

	clrscr();
	cout << " ---------------------------------------------------" << endl;
	cout << " | Recording paused, press ESC to continue recording" << endl;
	cout << " ---------------------------------------------------" << endl << endl;

	while (!isValidChoice)
	{
		inputChoice = _getch();


		if (inputChoice == ESC)
		{
			clrscr();
			this->PrintBoard(true);
			isValidChoice = true;
		}

		else
		{
			cout << "Wrong choice, press any key and try again." << endl;
			isValidChoice = false;
		}
	}



}
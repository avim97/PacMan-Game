#include "RecordingGame.h"

void RecordingGame::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0, currLives = m_Pacman.GetCurrentLives();
	bool fruitMoved = false, ghostsMoved = false;

	if (!GetColorStyle())
		SetDefaultColor();

	m_GameFiles.CreateRecordingFiles();
	m_GameFiles.InsertGameColorToFile(GetColorStyle());

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
			ghostsMoved = true;
		}


		if (pacmanMoves % 5 == 0)
		{
			MoveFruit();
			fruitMoves++;
			fruitMoved = m_Fruit.IsActive();
		}

		else if (fruitMoves % 10 == 0)
		{
			m_Fruit.DeActivateFruit(m_Board);
		}

		Sleep(300);

		m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), GetTotalScore(), GetColorStyle());

		RecordSteps(ghostsMoved, fruitMoved);

		if (currLives != m_Pacman.GetCurrentLives())
		{
			currLives = m_Pacman.GetCurrentLives();
			UpdateResultFile(pacmanMoves);
		}
	}


	m_GameFiles.CloseFiles();

}
void RecordingGame::RecordSteps(bool& ghostsMoved, bool& fruitMoved)
{
	string currGameFrame;
	stringstream outputString;

	outputString << "Pacman " << Direction::ConvertToString(m_Pacman.GetCurrentDirection()) << ' ' << '|';

	if (ghostsMoved)
	{
		for (int i = 0; i < m_Ghosts.size(); i++)
		{
			outputString << " Ghost" << '[' << i << ']' << ' ' << Direction::ConvertToString(m_Ghosts[i]->GetCurrentDirection()) << ' ';
		}
		outputString << '|';
	}

	//fruit
	if (m_Fruit.IsActive() && m_Fruit.GetReactivated())
	{
		outputString << " Fruit " << m_Fruit.GetXcoord() << ' ' << m_Fruit.GetYcoord();
		outputString << '|';

	}

	else if (!m_Fruit.IsActive() && m_Fruit.GetReactivated())
	{
		outputString << " Fruit X";
		outputString << '|';
	}

	else if (fruitMoved)
	{
		outputString << " Fruit " << Direction::ConvertToString(m_Fruit.GetCurrentDirection()) << ' ';
		outputString << '|';
	}

	ghostsMoved = false;
	fruitMoved = false;

	m_Fruit.SetReActivationFlag(false);
	m_GameFiles.InsertStringToStepsFile(outputString);


}
void RecordingGame::UpdateResultFile(int& frameNumber)
{

	stringstream result;
	switch (m_gameStatus)
	{
	case eGameStatus::WON:
	{
		result << "BOARD_FINISHED" << ' ' << frameNumber;
		break;
	}
	case eGameStatus::LOST:
	{

		result <<  "LOST" << ' ' << frameNumber;
		break;
	}
	case eGameStatus::NEXT_BOARD:
	{
		result << "NEXT_BOARD" << ' ' << frameNumber;
		break;
	}
	case eGameStatus::RUNNING:
	{
		result << "INTERSECTION" << ' ' << frameNumber;
		break;
	}
	case eGameStatus::EXIT:
	{
		result << "EXIT" << ' ' << frameNumber;
		break;
	}
	}
	m_GameFiles.InsertStringToResultFile(result);

}

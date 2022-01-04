#include "RecordingGame.h"

void RecordingGame::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0, currLives = m_Pacman.GetCurrentLives();
	bool fruitMoved = false, ghostsMoved = false;

	if (!GetColorStyle())
		SetDefaultColor();

	m_GameFiles.CreateRecordingFiles();

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
			fruitMoved = true;
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
	}m_GameFiles.CloseFiles();

}
void RecordingGame::RecordSteps(bool& ghostsMoved, bool& fruitMoved)
{
	string currGameFrame;
	//pacman
	currGameFrame = "Pacman " + ("%s", m_Pacman.GetCurrentDirection()) + ' ';
	//ghosts
	if (ghostsMoved)
	{
		currGameFrame += '|';
		for (int i = 0; i < m_Ghosts.size(); i++)
		{
			currGameFrame += ("Ghost[%d] ", i) + ("%s,", m_Ghosts[i]->GetCurrentDirection()) + ' ';
		}
		currGameFrame += '|';
	}
	//fruit
	if (m_Fruit.IsActive() && m_Fruit.GetReactivated())//fruit is active and status was changed
		currGameFrame += ("Fruit %d %d ", m_Fruit.GetXcoord(), m_Fruit.GetYcoord());

	else if (!m_Fruit.IsActive() && m_Fruit.GetReactivated())
		currGameFrame += "Fruit X ";

	else if (fruitMoved)
		currGameFrame += ("Fruit %s ", m_Fruit.GetCurrentDirection());

	ghostsMoved = false;
	fruitMoved = false;
	m_Fruit.SetReactivated(false);
	m_GameFiles.InsertStringToStepsFile(currGameFrame);

}

void RecordingGame::UpdateResultFile(int& frameNumber)
{
	string Result;
	switch (m_gameStatus)
	{
	case eGameStatus::WON:
	{
		Result += ("%d Board_Finished", frameNumber);
		break;
	}
	case eGameStatus::LOST:
	{
		Result += ("%d LOST", frameNumber);
		break;
	}
	case eGameStatus::NEXT_BOARD:
	{
		Result += ("%d Board_Finished", frameNumber);
		break;
	}
	case eGameStatus::RUNNING:
	{
		Result += ("%d Intersection", frameNumber);
		break;
	}
	}
	m_GameFiles.InsertStringToResultFile(Result);

}

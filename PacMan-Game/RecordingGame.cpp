#include "RecordingGame.h"

void RecordingGame::PlayGame()
{
	char key = 'S';
	int pacmanMoves = 0, fruitMoves = 0, ghostsMoves = 0;
	bool fruitMoved = false, ghostsMoved = false;

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


		if (pacmanMoves % 5 == 0)
		{
			MoveFruit();
			fruitMoves++;
		}

		else if (fruitMoves % 10 == 0)
		{
			m_Fruit.DeActivateFruit(m_Board);
		}

		Sleep(300);
		
		m_Board.GetLegend().printLegend(m_Pacman.GetCurrentLives(), GetTotalScore(), GetColorStyle());

	}
}
void RecordingGame::RecordSteps(bool ghostsMoved, bool fruitMoved)
 {
	string currGameFrame;
	//pacman
	currGameFrame += "Pacman " + ("%s", m_Pacman.GetCurrentDirection()) + ' ';
	//ghosts
	if (ghostsMoved)
		for (int i = 0; i < m_Ghosts.size(); i++)
		{
			currGameFrame += ("Ghost[%d] ", i) + ("%s", m_Ghosts[i]->GetCurrentDirection()) + ' ';

		}
	//fruit
	if (m_Fruit.IsActive()&&m_Fruit.GetReactivated())//fruit is active and status was changed
	{
		currGameFrame += "Fruit %d %d ";
		m_Fruit.SetReactivated(false);
		
	}
	//else if ()
	//{

	//}

}
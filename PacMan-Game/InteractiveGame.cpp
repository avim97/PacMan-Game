#include "InteractiveGame.h"

void InteractiveGame::PauseGame()
{
	do {
		gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
		if (GetColorStyle())
			Color::resetOutputColor();
		cout << " Game Paused, press ESC to continue.";

	} while (!_kbhit() || _getch() != 27);
	gotoxy(this->m_Board.getWidth() / 4, this->m_Board.getHeight() + 2);
	cout << "                                       " << endl;
}
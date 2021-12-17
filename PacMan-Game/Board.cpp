
#include "Board.h"
#include <iostream>


void Board::initBoard(Position &pacmanInitialPos, vector<Position>& ghostInitialPos, Position& fruitInitialPos)
{
for (int i=0;i<HEIGHT;i++)
	for(int j=0;j<WIDTH;j++)
		{
			switch (board[i][j])
			{
			case '@':
				pacmanInitialPos = { i,j };
				break;
			case '$':
				ghostInitialPos.push_back({ i,j });
				break;
			case '#':
				break;
			case '%':
				break;
			case '&':
				break;
			}
		}

}

void Board::printBoard()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == static_cast<char>(BoardObjects::FOOD))
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_breadcrumbColor.applyOutputColor(m_breadcrumbColor.getColor());
				std::cout << board[i][j];
				//m_breadcrumbColor.resetOutputColor();
			}

			else
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_wallColor.resetOutputColor();
				std::cout << board[i][j];

			}

		}
		std::cout << '\n';
	}
}
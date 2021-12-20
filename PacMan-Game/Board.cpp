
#include "Board.h"
#include <iostream>


void Board::initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos)
{
	
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			switch (board[i][j])
			{
			case '@':
				pacmanInitialPos = { i,j };
				break;
			case '$':
				ghostInitialPos.push_back({ i,j });
				board[i][j] = ' ';
				break;
			case '#':
				break;
			case '%':
				board[i][j] = ' ';
				break;
			case '&':
				legend.SetPosition({ i,j });
				ChangeLegendCells();
				break;
			case 'L':
				break;
			default:
					board[i][j] = static_cast<char>(249);
					this->totalBreadcrumbs++;
			}
		}
}
void Board::ChangeLegendCells()
{
	int startX = legend.GetPosition().getXcoord();
	int startY = legend.GetPosition().getYcoord();

	for(int i=0; i<3; i++)
		for (int j = 0; j < 20; j++)
		{
			board[startX + i][startY + j] = 'L';
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
Position Board::GetRandomPosition()
{

	int randomX = 1 + (rand() % WIDTH);
	int randomY = 1 + (rand() % HEIGHT);
	while (board[randomX][randomY] == static_cast<char>(BoardObjects::WALL))
	{
		 randomX = 1 + (rand() % WIDTH);
		 randomY = 1 + (rand() % HEIGHT);
	}
	return { randomY,randomX };
}
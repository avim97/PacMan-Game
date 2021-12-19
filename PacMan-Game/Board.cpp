
#include "Board.h"
#include <iostream>


void Board::initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos)
{
	Position legendLocation;
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			bool IsLegend
			if()

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
				legendLocation = { i,j };
				break;
			default:
				board[i][j] = static_cast<char>(249);

				this->totalBreadcrumbs++;
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
Position Board::getPacmanInitPos()const
{
	return m_PacmanInitialPos;
}

vector<Position> Board::getGhostInitPos() const
{
	return m_GhostInitialPos;
}

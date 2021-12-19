
#include "Board.h"
#include <iostream>


Legend& Board::initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos)
{
	
	Position *LegendPos = new Position;
	LegendPos = nullptr;
	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			if(LegendPos !=nullptr)
			{ 

			}
			else {
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
					*LegendPos = { i,j };
					Legend Legend(*LegendPos);
					break;
				default:
					if (Legend.checkIfWithinLegendRange({ i,j }))
						board[i][j] = 'L';
					else
					{
						board[i][j] = static_cast<char>(249);
						this->totalBreadcrumbs++;
					}


			else if (((j > 26 && j < 34 || j>39 && j < 47) && i > 9 && i < 13) || ((j > 26 && j < 34 || j>39 && j < 47) && i > 15 && i < 19) || (i < 16 && i>12 && (j < 34 || j>39)))
				board[i][j] = static_cast<char>(BoardObjects::WALL);


			else if (j <= 1 || j >= WIDTH - 2)
				board[i][j] = static_cast<char>(BoardObjects::WALL);


			else if (((i < 7 || i>18) && j > 10 && j < 18) || ((i < 7 || i>18) && j < 63 && j>55))
				board[i][j] = static_cast<char>(BoardObjects::WALL);


			else 

			{
				board[i][j] = static_cast<char>(BoardObjects::FOOD);
				totalBreadcrumbs++;
			}
		}
	}
	createTopTunnel();
	createBottomTunnel();


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


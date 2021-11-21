
#include "Board.h"
#include <iostream>
using namespace std;


//Board::Board()
//{
//
//	//Dont forget to insert SPACE in the pacman's initial positing in the matrix !!
//	for (int i = 0; i < HEIGHT; i++)
//	{
//		for (int j = 0; j < WIDTH; j++)
//		{
//			//top and bottom tunnels & top & bottom walls - tunnel is between cols 29 - 34
//			if ((i == 1 || i == HEIGHT - 2) && ((j < 34 && j>29) || (j > 39 && j < 44)) || ((i == 0 || i == HEIGHT - 1) && (j < 34 || j>39)))
//				board[i][j] = (char)BoardObjects::WALL;
//
//
//			//central wall
//			else if (((j > 26 && j < 34 || j>39 && j < 47) && i > 9 && i < 13) || ((j > 26 && j < 34 || j>39 && j < 47) && i > 15 && i < 19) || (i < 16 && i>12 && (j < 34 || j>39)))
//				board[i][j] = (char)BoardObjects::WALL;
//
//			//external walls & side tunnel - tunnel is between 10-15 rows
//			else if (j <= 1 || j >= WIDTH - 2)
//				board[i][j] = (char)BoardObjects::WALL;
//
//			//finger walls
//			else if (((i < 7 || i>18) && j > 10 && j < 18) || ((i < 7 || i>18) && j < 63 && j>55))
//				board[i][j] = (char)BoardObjects::WALL;
//
//			//the rest are breadcrumbs
//			else
//
//			{
//				board[i][j] = (char)BoardObjects::FOOD;
//				totalBreadcrumbs++;
//			}
//		}
//	}
//
//}

void Board::initBoard()
{
	//Dont forget to insert SPACE in the pacman's initial positing in the matrix !!
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//top and bottom tunnels & top & bottom walls - tunnel is between cols 29 - 34
			if ((i == 1 || i == HEIGHT - 2) && ((j < 34 && j>29) || (j > 39 && j < 44)) || ((i == 0 || i == HEIGHT - 1) && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;


			//central wall
			else if (((j > 26 && j < 34 || j>39 && j < 47) && i > 9 && i < 13) || ((j > 26 && j < 34 || j>39 && j < 47) && i > 15 && i < 19) || (i < 16 && i>12 && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;

			//external walls & side tunnel - tunnel is between 10-15 rows
			else if (j <= 1 || j >= WIDTH - 2)
				board[i][j] = (char)BoardObjects::WALL;

			//finger walls
			else if (((i < 7 || i>18) && j > 10 && j < 18) || ((i < 7 || i>18) && j < 63 && j>55))
				board[i][j] = (char)BoardObjects::WALL;

			//the rest are breadcrumbs
			else

			{
				board[i][j] = (char)BoardObjects::FOOD;
				totalBreadcrumbs++;
			}
		}
	}
}

void Board::printBoard() //tranfer to function here that gets a char (a board object) and print the specific object with the specific color
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == (char)BoardObjects::FOOD)
			{
				cout << m_breadcrumbColor.getColorCode(m_breadcrumbColor.getColor()) << board[i][j];
			}

			else
			{
				cout << m_wallColor.getColorCode(m_wallColor.getColor()) << board[i][j];
			}
			
		}
		cout << '\n';
	}
}
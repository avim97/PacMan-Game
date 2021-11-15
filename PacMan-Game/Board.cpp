#include "Board.h"
#include <iostream>
using namespace std;

Board::Board()
{
	//boarders
	//breadcrumbs
	//fruits
	//tunnels - might be a seperate function to handle

	//Dont forget to insert SPACE in the pacman's initial positing in the matrix !!
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//tunnel + top & bottom walls
			if ((i == 1 || i == HEIGHT - 2) && ((j < 34 && j>29) || (j > 39 && j < 44)) || ((i == 0 || i == HEIGHT - 1) && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;


			//central wall
			else if (((j > 26 && j < 34 || j>39 && j < 47) && i > 9 && i < 13) || ((j > 26 && j < 34 || j>39 && j < 47) && i > 15 && i < 19) || (i < 16 && i>12 && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;

			//external walls & side tunnel
			else if ((j <= 1 || j >= WIDTH - 2) &&i<10||i>15)
				board[i][j] = (char)BoardObjects::WALL;

			//finger walls
			else if (((i < 7 || i>18) && j > 10 && j < 18) || ((i < 7 || i>18) && j < 63 && j>55))
				board[i][j] = (char)BoardObjects::WALL;

			//the rest are breadcrumbs
			else
			{
				board[i][j] = (char)BoardObjects::FOOD;

			}

		}
	}
}

void Board::printBoard()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			cout << board[i][j];
		}
		cout << '\n';
	}
}

#include "Board.h"
#include <iostream>
using namespace std;


Board::Board()
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			
			if ((i == 1 || i == HEIGHT - 2) && ((j < 34 && j>29) || (j > 39 && j < 44)) || ((i == 0 || i == HEIGHT - 1) && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;


			
			else if (((j > 26 && j < 34 || j>39 && j < 47) && i > 9 && i < 13) || ((j > 26 && j < 34 || j>39 && j < 47) && i > 15 && i < 19) || (i < 16 && i>12 && (j < 34 || j>39)))
				board[i][j] = (char)BoardObjects::WALL;

			
			else if (j <= 1 || j >= WIDTH - 2)
				board[i][j] = (char)BoardObjects::WALL;

			
			else if (((i < 7 || i>18) && j > 10 && j < 18) || ((i < 7 || i>18) && j < 63 && j>55))
				board[i][j] = (char)BoardObjects::WALL;

			
			else

			{
				board[i][j] = (char)BoardObjects::FOOD;
				totalBreadcrumbs++;
			}
		}
	}

	board[11][0] = board[11][1] = board[12][0] = board[12][1] = board[16][0] = board[16][1] = board[17][0] = board[17][1] = (char)BoardObjects::SPACE;
	board[11][WIDTH - 2] = board[11][WIDTH - 1] = board[12][WIDTH - 2] = board[12][WIDTH - 1] = board[16][WIDTH - 2] = board[16][WIDTH - 1] = board[17][WIDTH - 2] = board[17][WIDTH - 1] = (char)BoardObjects::SPACE;
	// two lines above create width tunnel

	board[0][34] = board[0][35] = board[0][36] = board[0][37] = board[0][38] = board[0][39] = (char)BoardObjects::SPACE;
	board[1][34] = board[1][35] = board[1][36] = board[1][37] = board[1][38] = board[1][39] = (char)BoardObjects::SPACE;
	board[HEIGHT - 1][34] = board[HEIGHT - 1][35] = board[HEIGHT - 1][36] = board[HEIGHT - 1][37] = board[HEIGHT - 1][38] = board[HEIGHT - 1][39] = (char)BoardObjects::SPACE;
	board[HEIGHT - 2][34] = board[HEIGHT - 2][35] = board[HEIGHT - 2][36] = board[HEIGHT - 2][37] = board[HEIGHT - 2][38] = board[HEIGHT - 2][39] = (char)BoardObjects::SPACE;
	//four lines above create length tunnel

	//make two methods for creating tunnels (width and height)

}

void Board::printBoard() 
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == (char)BoardObjects::FOOD)
			{
				cout << "\033[35m" << board[i][j];
			}

			else
			{
				cout << "\033[37m" << board[i][j];
			}
			
		}
		cout << '\n';
	}
}
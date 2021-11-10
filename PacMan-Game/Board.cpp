#include "Board.h"
#include <iostream>
using namespace std;

Board::Board()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HIGHT; j++)
		{
			if (i == 0 || i == (HIGHT - 1))
				cout << "#  ";
			else if (j == 0 || j == WIDTH - 1)
				cout << '#';
			else
				cout << "   ";
		}
		cout << endl << endl;
	}
}
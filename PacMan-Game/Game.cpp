#include "Game.h"

//board print
void boardCreate() {

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (i == 0 || i == (HEIGHT - 1))
				cout << "#  ";
			else if (j == 0 || j == WIDTH - 1)
				cout << '#';
			else
				cout << "   ";
		}
		cout << endl<<endl;
	}
}

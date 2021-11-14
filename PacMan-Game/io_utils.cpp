#include "io_utils.h"
#include "eColor.h"

using namespace std;

//#ifndef WINDOWS
//void gotoxy(int x, int y) {}
//int _getch(void) { return 0; }
//int _kbhit(void) { return 0; }
//void Sleep(unsigned long) {}
//void setTextColor(eColor color) {}
//void hideCursor() {}
//void clear_screen() {}
//#else
//void gotoxy(int x, int y)
//{
//	HANDLE hConsoleOutput;
//	COORD dwCursorPosition;
//	cout << flush;
//	dwCursorPosition.X = x;
//	dwCursorPosition.Y = y;
//	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
//}
//
//void setTextColor(Color colorToSet) {
//	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
//}
//
//void hideCursor()
//{
//	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
//	CONSOLE_CURSOR_INFO CURSOR;
//	CURSOR.dwSize = 1;
//	CURSOR.bVisible = FALSE;
//	SetConsoleCursorInfo(myconsole, &CURSOR);//second argument need pointer
//}





using namespace std;

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void clrscr()
{
	system("cls");
}



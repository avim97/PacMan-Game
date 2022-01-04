#pragma once


#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <vector>
#include <filesystem>
#include "Position.h"



void hideCursor();
void gotoxy(const int x, const int y);
void clrscr();
void ClearInputBuffer();

//class IO_UTILS
//{
//public:
//	static void hideCursor();
//	static void gotoxy(const int x, const int y);
//	static void clrscr();
//	static void ClearInputBuffer();
//}; //think later about transferring this to class
#include "Color.h"

void Color::applyOutputColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void Color::resetOutputColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), static_cast<int>(eColor::DEFAULT));
	hideCursor();
}



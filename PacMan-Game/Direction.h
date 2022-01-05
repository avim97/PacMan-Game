#pragma once

#include <cctype>
#include <stdlib.h>
#include <time.h>
#include <string>

using std::string;

class Direction
{
public:
	enum class  eDirection { UP = 'W', DOWN = 'X', LEFT = 'A', RIGHT = 'D', STAY = 'S', UNDEFINED, VALID };
	static  eDirection Convert(char key);
	static string ConvertToString(char _direction);
	static eDirection getRandDir();
	static bool isValidDirection(char nextDirection);
	static eDirection GetDirection(int move);
};


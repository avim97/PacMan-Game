#ifndef Direction_h
#define Direction_h
#include <cctype>
#include <stdlib.h>
#include <time.h>

class Direction
{
public:
	enum class eDirection { UP = 'W', DOWN = 'X', LEFT = 'A', RIGHT = 'D', STAY = 'S', UNDEFINED };
	static  eDirection Convert(char c);
	static eDirection getRandDir();
};

#endif // !Directions_h

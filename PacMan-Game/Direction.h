#ifndef Direction_h
#define Direction_h
#include <cctype>

class Direction
{
public:
	enum eDirection { UP = 'W', DOWN = 'X', LEFT = 'A', RIGHT = 'D', STAY = 'S', UNDEFINED };
	static eDirection Convert(char c);
};


#endif // !Directions_h

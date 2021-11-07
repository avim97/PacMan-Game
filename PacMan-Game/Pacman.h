#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>
using namespace std;
#include "Position.h"

class Pacman
{
private:
	int lives = 3;
	enum color{WHITE, YELLOW, BROWN, RED, BLUE}; // check later if should convert to enum class in a seperate header
	const char figure = '@';
	position position;
public:
	void initPosition(); //check
	void setColor(); //check
	bool updateLife(); 

};




#endif /* PACMAN_H */

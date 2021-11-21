#pragma once

enum class BoardObjects
{
	FOOD = 249, SPACE = 32, WALL = 178, GHOST = 234, PACMAN = 64
	
};

/*
* class BoardObject
* {
* public:
*   enum eBoardObject {FOOD = 249, SPACE = 32, WALL = 178, GHOST = 234, PACMAN = 64}
*   static void printObject(char obj)
*   {
*     switch(obj):
*     case FOOD:
*     cout << "\033[1m\033[37m" << (char)FOOD;
*     break;
*   
*     case WALL:
*     cout <<  << (char)WALL;
*     break;
* 
*     case GHOST: 
*     //seperate to red and blue ....
*     break;
* 
*     case PACMAN:
*     cout << "\033[1m\033[33m" << (char)PACMAN;
      break;


    }
  }
*/

//think about adding here funcion for printing food (with "cout << "THE CODE FOR THE SPECIFIC COLOR" << FOOD) e.g - meaning turning BoardOBjects into class
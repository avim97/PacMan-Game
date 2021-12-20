#pragma once
#include "Position.h"
#include <vector>
using std::vector;

typedef vector<char> VisitedSteps;

class Movement
{
private:
	
public:
	virtual void Move(int ghostInd) = 0;
};


#pragma once
#include "Movement.h"
#include "eBoardObjects.h"
#include <iostream>
#include <vector>
#include <queue>
using std::queue;
using std::vector;
typedef vector<vector<char>> VisitedPaths;

class BestMovement : public Movement
{
private:
	enum { TRAVELABLE = '*',NOT_TRAVELABLE = '0', DESTANATION = 'D', SOURCE = 'S' };
	VisitedPaths m_Paths;
	int m_ShortestPath;
	queue<Position> m_QPosition;
public:
	BestMovement(int _height, int _width) :
		m_ShortestPath(0)
	{ m_Paths.resize(_height, vector<char>(_width)); };
	void InitializeVisitedPaths(char* board[]);
	void SetSource(Position& sourcePos);
	void SetDestanation(Position& destPos);
	void Move(int ghostInd) override;
};


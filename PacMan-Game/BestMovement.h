#pragma once
#include "Movement.h"
#include "eBoardObjects.h"
#include "QItem.h"
#include <iostream>
#include <vector>
#include <queue>

using std::queue;
using std::vector;
typedef vector<vector<char>> AvailablePaths;
typedef vector<vector<char>> GameBoard;
typedef queue<QItem> Queue;


class BestMovement : public Movement
{
private:
	enum { TRAVELABLE = '*', NOT_TRAVELABLE = '0', DESTINATION = 'D', SOURCE = 'S', NOT_FOUND = -1, TOTAL_MOVES = 4 };
	AvailablePaths m_Paths;
	int m_ShortestPath;
public:

	BestMovement() :
		m_ShortestPath(0)
	{};

	BestMovement(int _height, int _width) :
		m_ShortestPath(0)
	{
		m_Paths.resize(_height, vector<char>(_width));
	};

	void InitializeVisitedPaths(GameBoard board, const Position& destination, const Position& source, PositionsVector otherGhostsPositions);
	void SetSource(const Position& sourcePos);
	void SetDestination(const Position& destPos);
	Direction::eDirection GetMove(GameBoard board, int currentGhost, const Position& destination, const Position& source, PositionsVector otherGhostsPositions, int& ghostsMoves) override;
	int GetMinDistance(GameBoard board, const Position& destination, const Position& source, PositionsVector otherGhostsPositions);
	bool IsValidPosition(Position position, int rows, int cols);
	bool IsValidPosition(const Position& currentPosition, PositionsVector otherGhostsPositions);
	AvailablePaths GetPaths() { return m_Paths; };


};


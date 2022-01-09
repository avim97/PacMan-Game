#pragma once
#include "eBoardObjects.h"
#include "Color.h"
#include "Position.h"
#include "BoardFiles.h"
#include <vector>
#include "Legend.h"

using std::vector;
typedef vector<vector<char>> GameBoard;


class Board
{
private:
	bool m_isValidBoard = true;
	int HEIGHT;
	int WIDTH;
	unsigned int totalBreadcrumbs = 0;
	Position m_PacmanInitialPos = { 0,0 };
	Position m_FruitInitialPos = { 0,0 };
	Color m_wallColor;
	Color m_breadcrumbColor;
	vector<Position> m_GhostInitialPos = {};
	Legend m_Legend;
	GameBoard board;

	



public:
	Board(string& fileName) :m_wallColor(Color::eColor::DEFAULT), m_breadcrumbColor(Color::eColor::BOLD_GREEN) {
		BoardFiles::UpdateBoardFromFile(fileName, board, HEIGHT, WIDTH);
		InitializeBoard(m_PacmanInitialPos, m_GhostInitialPos);
	};

	void InitializeBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos);
	void PrintBoard();
	void PrintBoard(bool wasPaused);
	void ChangeLegendCells();
	int getWidth() const { return WIDTH; };
	int getHeight()const { return HEIGHT; };
	int getMaxScore() const { return totalBreadcrumbs; };
	Color getWallColor() const { return m_wallColor; };
	Color getBreadcrumbColor()const { return m_breadcrumbColor; };
	char getCellValue(const int x, const int y) const { return board[y][x]; };
	char getCellValue(const Position& position) const { return board[position.getYcoord()][position.getXcoord()]; }; //check
	void setChar(const int xCoord, const int yCoord, char ch) { board[yCoord][xCoord] = ch; };
	void setWallColor(Color::eColor color) { m_wallColor.setColor(color); };
	void setBreadcrumColor(Color::eColor color) { m_breadcrumbColor.setColor(color); };
	void ResetColors();
	Position GetRandomPosition();
	const Position& getPacmanInitPos() const { return m_PacmanInitialPos; }
	const vector<Position>& getGhostInitPos() const { return m_GhostInitialPos; };
	GameBoard GetBoard() const { return board; };
	Legend GetLegend() const { return m_Legend; };
	void CheckLegendSpace();
	bool CheckWithinBoardRange(const int& x,const int& y)const;
	
};



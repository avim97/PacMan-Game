#pragma once
#include "eBoardObjects.h"
#include "Color.h"
#include "Position.h"
#include "FileActions.h"
#include <vector>
#include "Legend.h"

using std::vector;
typedef vector<vector<char>> GameBoard;


class Board
{
private:
	int HEIGHT;
	int WIDTH;
	unsigned int totalBreadcrumbs = 0;
	Position m_PacmanInitialPos = { 0,0 };
	Position m_FruitInitialPos = { 0,0 };
	vector<Position> m_GhostInitialPos = {};
	Legend legend;

	GameBoard board;
	Color m_wallColor;
	Color m_breadcrumbColor;



public:
	Board(string& fileName) :m_wallColor(Color::eColor::DEFAULT), m_breadcrumbColor(Color::eColor::BOLD_GREEN) {
		FileActions::updateBoardFromFile(fileName, board, HEIGHT, WIDTH);

		initBoard(m_PacmanInitialPos, m_GhostInitialPos);

	};
	void initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos);
	void createLegend(Position& legendLocation);
	void printBoard();
	void ChangeLegendCells();

	int getWidth() { return WIDTH; };
	int getHeight() { return HEIGHT; };
	int getMaxScore() { return totalBreadcrumbs; };
	Color  getWallColor() { return m_wallColor; };
	Color  getBreadcrumbColor() { return m_breadcrumbColor; };
	char getCellValue(const int x, const int y) const { return board[y][x]; };
	char getCellValue(const Position& position) const { return board[position.getYcoord()][position.getXcoord()]; }; //check
	void setChar(const int xCoord, const int yCoord, char ch) { board[yCoord][xCoord] = ch; };
	void setWallColor(Color::eColor color) { m_wallColor.setColor(color); };
	void setBreadcrumColor(Color::eColor color) { m_breadcrumbColor.setColor(color); };
	Position GetRandomPosition();
	const Position& getPacmanInitPos() const { return m_PacmanInitialPos; }
	const vector<Position>& getGhostInitPos() const { return m_GhostInitialPos; };
	void ChangeBoard(Board& board);
	GameBoard GetBoard() { return board; };
	Legend GetLegend() { return legend; };
};




#include "Board.h"
#include <iostream>


void Board::initBoard(Position& pacmanInitialPos, vector<Position>& ghostInitialPos)
{

	for (int i = 0; i < HEIGHT; i++)
		for (int j = 0; j < WIDTH; j++)
		{
			switch (board[i][j])
			{
			case '@':
				pacmanInitialPos = { j,i };
				break;
			case '$':
				ghostInitialPos.push_back({ j,i });
				board[i][j] = static_cast<char>(BoardObjects::FOOD);
				break;
			case '#':
				board[i][j] = static_cast<char>(BoardObjects::WALL);
				break;
			case '%':
				board[i][j] = static_cast<char>(BoardObjects::SPACE);
				break;
			case '&':
				legend.SetPosition({ i,j });
				break;
			case 'L':
				break;
			default:
				board[i][j] = static_cast<char>(BoardObjects::FOOD);
				this->totalBreadcrumbs++;
			}
		}
	CheckLegendSpace();
	ChangeLegendCells();

}
void Board::CheckLegendSpace()
{

	int y = (legend.GetPosition().getXcoord());
	int x = (legend.GetPosition().getYcoord());
	int maxHeight = HEIGHT;
	int expectedRows = y + 2 + 1;
	int expectedCols = x + 19 + 1;
	if (expectedRows - HEIGHT > 0)
	{
		maxHeight = expectedRows;
		for (int i = 0; i < expectedRows - HEIGHT; i++)
		{
			vector<char> temp;
			for (int j = 0; j < WIDTH; j++)
				temp.push_back(static_cast<char>(BoardObjects::SPACE));
			board.push_back(temp);
		}
	}
	if (expectedCols - WIDTH > 0)
	{
		for (int i = 0; i < maxHeight; i++)
			for (int j = 0; j < expectedCols - WIDTH; j++)
				board[i].push_back(static_cast<char>(BoardObjects::SPACE));
	}

}
void Board::ChangeLegendCells()
{
	int startX = legend.GetPosition().getXcoord();
	int startY = legend.GetPosition().getYcoord();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 20; j++)
		{
			board[startX + i][startY + j] = static_cast<char>(BoardObjects::SPACE);
		}
}

void Board::printBoard()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == static_cast<char>(BoardObjects::FOOD))
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_breadcrumbColor.applyOutputColor(m_breadcrumbColor.getColor());
				if (board[i][j] == 'L')
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];
			}

			else
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_wallColor.resetOutputColor();
				if (board[i][j] == 'L')
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];

			}

		}
		std::cout << '\n';
	}
}
Position Board::GetRandomPosition()
{

	int randomX = 1 + (rand() % WIDTH - 1);
	int randomY = 1 + (rand() % HEIGHT - 1);
	Position randomPosition;
	while (board[randomY][randomX] == static_cast<char>(BoardObjects::WALL))
	{
		randomX = 1 + (rand() % WIDTH - 1);
		randomY = 1 + (rand() % HEIGHT - 1);
	}
	randomPosition.setYcoord(randomY);
	randomPosition.setXcoord(randomX);

	return randomPosition;
}
bool Board::CheckWithinBoardRange(int& x, int& y)
{
	if (x >= 0 && x < WIDTH)
		if (y >= 0 && y < HEIGHT)
			return true;
		else return false;
}
void Board::printBoard(bool wasPaused) {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (board[i][j] == static_cast<char>(BoardObjects::FOOD))
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_breadcrumbColor.applyOutputColor(m_breadcrumbColor.getColor());
				if (board[i][j] == 'L')
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];
			}
			else if (board[i][j] == static_cast<char>(BoardObjects::PACMAN))
			{
				std::cout << static_cast<char>(BoardObjects::SPACE);
			}
			else
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_wallColor.resetOutputColor();
				if (board[i][j] == 'L')
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];

			}

		}
		std::cout << '\n';


	}
}
//void Board::ChangeBoard(Board& newBoard)
//{
//	this->board = newBoard.GetBoard();
//	this->HEIGHT = newBoard.HEIGHT;
//	this->WIDTH = newBoard.WIDTH;
//	this->totalBreadcrumbs = newBoard.totalBreadcrumbs;
//	this->m_FruitInitialPos = newBoard.m_FruitInitialPos;
//	this->m_GhostInitialPos = newBoard.m_GhostInitialPos;
//	this->m_PacmanInitialPos = newBoard.m_PacmanInitialPos;
//	this->legend.SetPosition(newBoard.legend.GetPosition());
//	delete &newBoard;


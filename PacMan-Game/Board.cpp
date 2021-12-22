
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
				board[i][j] = static_cast<char>(BoardObjects::SPACE);
				break;

			case '$':
				ghostInitialPos.push_back({ j,i });
				board[i][j] = static_cast<char>(BoardObjects::SPACE);
				break;
			case '#':
				board[i][j] = static_cast<char>(BoardObjects::WALL);
				break;
			case '%':
				//board[i][j] = static_cast<char>(BoardObjects::SPACE);
				break;
			case '&':
				legend.SetPosition({ i,j });
				ChangeLegendCells();
				break;

			case 'L':
				break;

			default:
				board[i][j] = static_cast<char>(BoardObjects::FOOD);
				this->totalBreadcrumbs++;
			}
		}
}
void Board::ChangeLegendCells()
{
	int startX = legend.GetPosition().getXcoord();
	int startY = legend.GetPosition().getYcoord();

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 20; j++)
		{
			board[startX + i][startY + j] = 'L';
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

				if (board[i][j] == 'L' || board[i][j] == '%')										// ADD THESE CHARS TO AN ENUM LATER
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];
			}

			else
			{
				if (this->m_breadcrumbColor.getColor() != static_cast<int>(Color::eColor::DEFAULT))
					m_wallColor.resetOutputColor();

				if (board[i][j] == 'L' || board[i][j] == '%')
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

	int randomX = rand() % WIDTH;
	int randomY = rand() % HEIGHT;
	Position randomPosition;
	while (board[randomY][randomX] == static_cast<char>(BoardObjects::WALL))
	{
		randomX = rand() % WIDTH;
		randomY = rand() % HEIGHT;
	}
	randomPosition.setYcoord(randomY);
	randomPosition.setXcoord(randomX);

	return randomPosition;
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


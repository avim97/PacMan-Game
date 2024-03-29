
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
				board[i][j] = static_cast<char>(BoardObjects::FOOD);
				break;
			case '#':
				board[i][j] = static_cast<char>(BoardObjects::WALL);
				break;
			case '%':
				break;
			case '&':
				m_Legend.SetPosition({ i,j });
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

	int y = (m_Legend.GetPosition().getXcoord());
	int x = (m_Legend.GetPosition().getYcoord());
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
	int startX = m_Legend.GetPosition().getXcoord();
	int startY = m_Legend.GetPosition().getYcoord();

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

				if (board[i][j] == 'L' || board[i][j] == '%')										
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

				if (board[i][j] == 'L' || board[i][j] == '%')
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
				if (board[i][j] == 'L' || board[i][j] == '%')
					std::cout << static_cast<char>(BoardObjects::SPACE);
				else
					std::cout << board[i][j];

			}

		}
		std::cout << '\n';


	}
}
void Board::ResetColors()
{
	m_wallColor.setColor(Color::eColor::DEFAULT);
	m_breadcrumbColor.setColor(Color::eColor::DEFAULT);
	m_Legend.SetLivesColor(Color::eColor::DEFAULT);
	m_Legend.SetScoreColor(Color::eColor::DEFAULT);
}

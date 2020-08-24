#include "Board.h"

Board::Board()
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			this->squares[row][column] = 0;
		}
	}
}

Board::Board(const Board& other)
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			this->squares[row][column] = other.squares[row][column];
		}
	}
}

void Board::operator=(const Board& other)
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			this->squares[row][column] = other.squares[row][column];
		}
	}
}

void Board::changeSquare(int row, int column, int newValue)
{
	this->squares[row][column] = newValue;
}

int Board::getValue(int row, int column)
{
	return this->squares[row][column];
}

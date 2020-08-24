#pragma once

// This is a class where I keep the numbers from sudoku
// 0 means that square of table doesn't have a value
// Any value different from 1 to 9 isn't allowed in table

class Board
{
private:
	int squares[10][10];
public:
	Board();
	Board(const Board& other);
	void operator=(const Board& other);
	~Board() {}
	// this function changes value from the square of specified row and column
	void changeSquare(int row, int column, int newValue);
	// this function returns the value from the specified square with row and column
	int getValue(int row, int column);
};
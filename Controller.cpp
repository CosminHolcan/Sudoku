#include "Controller.h"
#include <vector>
#include <random>
#include <chrono>

std::vector<int> values{ 1,2,3,4,5,6,7,8,9 };

// this function verifies if the table is full completed or not
// if yes, then returns false, otherwise, returns true
// ( to be more specific, function is looking for a zero)
bool findZero(Board& board, int& row, int& column)
{
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			if (board.getValue(row, column) == 0)
				return true;
		}
	}
	return false;
}

// this function checks if a value can be added to a square, from the point of view of the row
// if possible, then return yes, otherwise false
bool checkRow(Board& board, int row,int column, int value)
{
	for (int j = 0; j < 9; j++)
	{
		if (board.getValue(row, j) == value && column!=j)
			return false;
	}
	return true;
}

// this function checks if a value can be added to a square, from the point of view of the column
// if possible, then return yes, otherwise false
bool checkColumn(Board& board,int row, int column, int value)
{
	for (int i = 0; i < 9; i++)
	{
		if (board.getValue(i, column) == value && i!= row)
			return false;
	}
	return true;
}

// this function checks if a value can be added to a square, from the point of view of the 3x3 box where square is
// if possible, then return yes, otherwise false
bool checkBox(Board& board, int row, int column, int value)
{
	int rowOfInterest = row / 3 * 3;
	int columnOfInterest = column / 3 * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board.getValue(rowOfInterest + i, columnOfInterest + j) == value && (rowOfInterest+i != row || columnOfInterest+j != column ))
				return false;
		}
	}
	return true;
}

// this function checks if a value can be added to a square, from any point of view (row, column and box)
// if possible, then return yes, otherwise false
bool isGoodMove(Board& board, int row, int column, int value)
{
	return checkRow(board, row,column, value) && checkColumn(board, row,column, value) && checkBox(board, row, column, value);
}

// this function takes a board as parameter and puts values in board to complete it
// this works fine if the initial board is empty ( for this case this function was made)
bool createSolvedSudoku(Board& board)
{
	int row, column;
	if (findZero(board, row, column) == false)
		return true;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(values.begin(), values.end(), std::default_random_engine(seed));
	for (auto value : values)
	{
		if (isGoodMove(board, row, column, value))
		{
			board.changeSquare(row, column, value);
			if (createSolvedSudoku(board))
				return true;
			board.changeSquare(row, column, 0);
		}
	}
	return false;
}

// this function counts how many solutions can a board have
// because a sudoku should have just one solution, if there are two or more solutions the function will return two
void countingSolutions(Board& board, int& counter)
{
	int row, column;
	if (findZero(board, row, column) == false)
	{
		counter++;
		return;
	}
	for (int value = 1; value < 9; value++)
	{
		if (isGoodMove(board, row, column, value))
		{
			board.changeSquare(row, column, value);
			countingSolutions(board, counter);
			board.changeSquare(row, column, 0);
		}
	}
}

// this function takes as argument a board ( empty one or with elements) and completes it if this is possible
// in that case returns true, otherwise false
bool solveSudoku(Board& board)
{
	int row, column;
	if (findZero(board, row, column) == false)
		return true;
	for (int value = 1; value < 10; value++)
	{
		if (isGoodMove(board, row, column, value))
		{
			board.changeSquare(row, column, value);
			if (solveSudoku(board))
				return true;
			board.changeSquare(row, column, 0);
		}
	}
	return false;
}

// based on how many values we want to eliminate (approximative), this function selects randomly a number equal or a little larger
// of elements to be removed, and will eliminate elements ( I mean, make this squares 0)
// after this, the board will look like an initial sudoku table
void removeValues(Board& board, int difficulty)
{
	std::vector<std::pair<int, int>> pairs;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			pairs.push_back(std::make_pair(i, j));
		}
	if (difficulty == 49)
		difficulty = difficulty + rand() % 4;
	else
		difficulty = difficulty + rand() % 6;
	while (difficulty != 0)
	{
		int random = rand() % (pairs.size());
		int row = pairs[random].first;
		int column = pairs[random].second;
		while (board.getValue(row, column) == 0)
		{
			random = rand() % (pairs.size());
			row = pairs[random].first;
			column = pairs[random].second;
		}
		int value = board.getValue(row, column);
		board.changeSquare(row, column, 0);
		int counter = 0;
		countingSolutions(board, counter);
		if (counter != 1)
		{
			board.changeSquare(row, column, value);
		}
		else
		{
			difficulty--;
			std::pair<int, int> pair(row, column);
			pairs.erase(std::find(pairs.begin(), pairs.end(), pair));
		}
	}
}

// this function returns a board with not so many empty positions, being easy to complete
Board createEasySudoku()
{
	Board board;
	createSolvedSudoku(board);
	removeValues(board, 23);
	return board;
}

// this function returns a board with a medium number of empty positions
Board createMediumSudoku()
{
	Board board;
	createSolvedSudoku(board);
	removeValues(board, 35);
	return board;
}

// this function returns a board with many empty positions, being hard to complete
Board createHardSudoku()
{
	Board board;
	createSolvedSudoku(board);
	removeValues(board, 49);
	return board;
}

// this function takes 2 boards, one initial and one completed ( or trying to be completed)
// for the squares which are empty on initial board, the program will establish if they are correctly completed in final board
// if the value from a square is not correct ( because of row, column or box), its coordinates will be added to a vector
// which will be returned
// the function returns the coordinates of wrong squares through a vector of pairs
std::vector<std::pair<int, int>> findErrors(Board& initialBoard, Board& finishedBoard)
{
	std::vector<std::pair<int, int>> errors;
	int value;
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			if (initialBoard.getValue(row, column) == 0)
			{
				value = finishedBoard.getValue(row, column);
				if (value == 0)
				{
					std::pair<int, int> pair(row, column);
					errors.push_back(pair);
				}
				bool ok = false;
				for (int i = 1; i < 10; i++)
					if (value == i)
						ok = true;
				if (ok == false)
				{
					std::pair<int, int> pair(row, column);
					errors.push_back(pair);
				}
				else
				{
					if (!isGoodMove(finishedBoard, row, column, value))
					{
						std::pair<int, int> pair(row, column);
						errors.push_back(pair);
					}
				}
			}
		}
	}
	return errors;
}


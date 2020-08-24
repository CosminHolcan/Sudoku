#include "Tests.h"
#include <assert.h>

void test_findZero_noZeroes_returnFalse()
{
	Board board;
	int row, column;
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			board.changeSquare(row, column, 1);
		}
	}
	row = 0;
	column = 0;
	assert(findZero(board, row, column) == false);
}

void test_findZero_zeroFound_returnTrueAndPosition()
{
	Board board;
	int row, column;
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			board.changeSquare(row, column, 1);
		}
	}
	row = 0;
	column = 0;
	board.changeSquare(2, 7, 0);
	assert(findZero(board, row, column) == true);
	assert(row == 2);
	assert(column == 7);
}

void test_checkRow_rowOk_returnTrue()
{
	Board board;
	int row, column;
	row = 5;
	column = 0;
	board.changeSquare(row, column, 1);
	for (int j = 1; j < 9; j++)
		board.changeSquare(row, j, j + 1);
	int value = board.getValue(row, column);
	assert(checkRow(board, row, column, value) == true);
}

void test_checkRow_valueOnOtherColumn_returnFalse()
{
	Board board;
	int row, column;
	row = 3;
	column = 5;
	for (int j = 0; j < 9; j++)
		board.changeSquare(row, j, 7);
	int value = board.getValue(row, column);
	assert(checkRow(board, row, column, value) == false);
}

void test_checkColumn_columnOk_returnTrue()
{
	Board board;
	int row, column;
	row = 5;
	column = 0;
	board.changeSquare(row, column, 4);
	for (int i = 1; i < 9; i++)
		board.changeSquare(i, column, i + 1);
	int value = board.getValue(row, column);
	assert(checkColumn(board, row, column, value) == true);
}

void test_checkColumn_valueOnOtherRow_returnFalse()
{
	Board board;
	int row, column;
	row = 3;
	column = 5;
	for (int i = 0; i < 9; i++)
		board.changeSquare(i, column, 6);
	int value = board.getValue(row, column);
	assert(checkColumn(board, row, column, value) == false);
}

void test_checkBox_BoxOk_returnTrue()
{
	Board board;
	int row, column;
	row = 5;
	column = 2;
	int value = 1;
	int newRow = row / 3 * 3;
	int newColumn = column / 3 * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board.changeSquare(newRow + i, newColumn + j, value);
			value++;
		}
	}
	value = board.getValue(row, column);
	assert(checkBox(board, row, column, value) == true);
}

void test_checkBox_valueOnOtherPosition_returnFalse()
{
	Board board;
	int row, column;
	row = 4;
	column = 6;
	int value = 1;
	int newRow = row / 3 * 3;
	int newColumn = column / 3 * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board.changeSquare(newRow + i, newColumn + j, value);
			value++;
		}
	}
	board.changeSquare(row, column, 1);
	value = board.getValue(row, column);
	assert(checkBox(board, row, column, value) == false);
}

void test_isGoodMove_validMove_returnTrue()
{
	Board board;
	int row, column, i, j;
	int value = 1;
	row = 2;
	column = 1;
	for (i = 0; i < 9; i++)
	{
		board.changeSquare(0, i, value);
		value++;
	}
	value = 4;
	for (i = 0; i < 9; i++)
	{
		board.changeSquare(1, i, value);
		value++;
		if (value == 10)
			value = 1;
	}
	board.changeSquare(2, 0, 7);
	board.changeSquare(2, 2, 9);
	value = 1;
	for (i = 3; i < 9; i++)
	{
		board.changeSquare(2, i, value);
		value++;
	}
	assert(isGoodMove(board, 2, 1, 8) == true);
}

void test_createSolvedSudoku()
{
	Board board;
	createSolvedSudoku(board);

}

void testAll()
{
	test_findZero_noZeroes_returnFalse();
	test_findZero_zeroFound_returnTrueAndPosition();
	test_checkRow_rowOk_returnTrue();
	test_checkRow_valueOnOtherColumn_returnFalse();
	test_checkColumn_columnOk_returnTrue();
	test_checkBox_BoxOk_returnTrue();
	test_checkBox_valueOnOtherPosition_returnFalse();
	test_isGoodMove_validMove_returnTrue();

}

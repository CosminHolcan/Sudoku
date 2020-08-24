#pragma once
#include "Board.h"
#include <vector>

bool findZero(Board& board, int& row, int& column);

bool checkRow(Board& board, int row, int column, int value);

bool checkColumn(Board& board, int row,  int column, int value);

bool checkBox(Board& board, int row, int column, int value);

bool isGoodMove(Board& board, int row, int column, int value);

bool createSolvedSudoku(Board& board);

void countingSolutions(Board& board, int& counter);

bool solveSudoku(Board& board);

void removeValues(Board& board, int difficulty);

Board createEasySudoku();

Board createMediumSudoku();

Board createHardSudoku();

std::vector<std::pair<int, int>> findErrors(Board& initialBoard, Board& finishedBoard);
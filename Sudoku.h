#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Sudoku.h"

class Sudoku : public QMainWindow
{
    Q_OBJECT

public:
    Sudoku(QWidget *parent = Q_NULLPTR);

private:
    Ui::SudokuClass ui;
};

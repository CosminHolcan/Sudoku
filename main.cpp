#include "Sudoku.h"
#include <QtWidgets/QApplication>
#include "UserInterface.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
    testAll();
    QApplication a(argc, argv);
    UserInterface ui;
    ui.show();
    return a.exec();
}

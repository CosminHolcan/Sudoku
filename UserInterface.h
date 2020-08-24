#pragma once
#include "Controller.h"

#include <QWidget>
#include "ui_UserInterface.h"


class UserInterface : public QWidget
{
	Q_OBJECT

public:
	UserInterface(QWidget* parent = Q_NULLPTR);
	~UserInterface();
private:
	Ui::UserInterface ui;
	Board usedBoard;
	int speed;
	bool stopComputer;
	void connectSignals();
	void makeEasyBoard();
	void makeMediumBoard();
	void makeHardBoard();
	bool letComputerSolve();
	void drawTable();
	void populateTable();
	void createDelay();
	void createDelayManualSpeed(int usedSpeed);
	void handlerSolver();
	void handlerCheck();
	void handlerSpeed();
};

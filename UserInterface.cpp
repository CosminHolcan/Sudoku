#include "UserInterface.h"
#include "windows.h"
#include <chrono>
#include <thread>
#include <qtimeline.h>
#include <qtimezone.h>
#include <stdlib.h>


UserInterface::UserInterface(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Sudoku");
	this->setFixedHeight(550);
	this->setFixedWidth(700);
	QPixmap bkgnd("Sky-Background.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bkgnd);
	this->setPalette(palette);
	this->speed = 500;
	this->stopComputer = false;
	this->usedBoard = Board();
	this->ui.congratsLabel->setText("");
	this->ui.slideBar->setRange(0, 1000);
	this->ui.slideBar->setValue(500);
	this->connectSignals();
	this->drawTable();
}

UserInterface::~UserInterface()
{
}

void UserInterface::connectSignals()
{
	QObject::connect(this->ui.easyButton, &QPushButton::clicked, this, &UserInterface::makeEasyBoard);
	QObject::connect(this->ui.mediumButton, &QPushButton::clicked, this, &UserInterface::makeMediumBoard);
	QObject::connect(this->ui.hardButton, &QPushButton::clicked, this, &UserInterface::makeHardBoard);
	QObject::connect(this->ui.computerButton, &QPushButton::clicked, this, &UserInterface::handlerSolver);
	QObject::connect(this->ui.checkButton, &QPushButton::clicked, this, &UserInterface::handlerCheck);
	QObject::connect(this->ui.slideBar, &QSlider::valueChanged, this, &UserInterface::handlerSpeed);
}

void UserInterface::makeEasyBoard()
{
	this->ui.tableWidget->clearSelection();
	this->stopComputer = true;
	this->usedBoard = createEasySudoku();
	this->populateTable();
}

void UserInterface::makeMediumBoard()
{
	this->ui.tableWidget->clearSelection();
	this->stopComputer = true;
	this->usedBoard = createMediumSudoku();
	this->populateTable();
}

void UserInterface::makeHardBoard()
{
	this->ui.tableWidget->clearSelection();
	this->stopComputer = true;
	this->usedBoard = createHardSudoku();
	this->populateTable();
}



bool UserInterface::letComputerSolve()
{
	while (!this->stopComputer)
	{
		int row, column;
		if (findZero(this->usedBoard, row, column) == false)
			return true;
		for (int value = 1; value < 10; value++)
		{
			if (isGoodMove(this->usedBoard, row, column, value))
			{
				this->usedBoard.changeSquare(row, column, value);
				this->ui.tableWidget->item(row, column)->setText(QString::number(value));
				this->createDelay();
				if (this->letComputerSolve())
					return true;
				this->usedBoard.changeSquare(row, column, 0);
			}
		}
		return false;
	}
}

void UserInterface::drawTable()
{
	this->ui.tableWidget->setRowCount(9);
	this->ui.tableWidget->setColumnCount(9);
	this->ui.tableWidget->setFixedHeight(312);
	this->ui.tableWidget->setFixedWidth(370);
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			if ((row < 3 && (column <3 || column >=6)) || (row >=3 && row <6 && column >=3 && column <6) || (row >=6 && (column <3 || column >=6)))
			{
				QString qvalue("");
				QVariant oVariant(qvalue);
				QTableWidgetItem* item = new QTableWidgetItem();
				item->setData(Qt::DisplayRole, oVariant);
				item->setBackground(Qt::yellow);
				this->ui.tableWidget->setItem(row, column, item);
			}
			else
			{
				QString qvalue("");
				QVariant oVariant(qvalue);
				QTableWidgetItem* item = new QTableWidgetItem();
				item->setData(Qt::DisplayRole, oVariant);
				item->setBackground(Qt::green);
				this->ui.tableWidget->setItem(row, column, item);
			}
			QFont font = this->ui.tableWidget->item(row, column)->font();
			font.setBold(true);
			this->ui.tableWidget->item(row, column)->setFont(font);
		}
	}
	this->ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void UserInterface::populateTable()
{
	for (int row = 0; row < 9; row++)
	{
		for (int column = 0; column < 9; column++)
		{
			int value = this->usedBoard.getValue(row, column);
			if (value != 0)
			{
				this->ui.tableWidget->item(row, column)->setFlags(this->ui.tableWidget->item(row, column)->flags() & ~Qt::ItemIsEditable);
				QString qvalue = QString::number(value);
				this->ui.tableWidget->item(row, column)->setText(qvalue);
				this->ui.tableWidget->item(row, column)->setTextColor(Qt::black);
			}
			else
			{
				this->ui.tableWidget->item(row, column)->setFlags(this->ui.tableWidget->item(row, column)->flags() | Qt::ItemIsEditable);
				QString qvalue("");
				this->ui.tableWidget->item(row, column)->setText(qvalue);
				this->ui.tableWidget->item(row, column)->setTextColor(Qt::blue);
			}
		}
	}
}

void UserInterface::createDelay()
{
	QTime dieTime = QTime::currentTime().addMSecs(this->speed);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

void UserInterface::createDelayManualSpeed(int usedSpeed)
{
	QTime dieTime = QTime::currentTime().addMSecs(usedSpeed);
	while (QTime::currentTime() < dieTime)
		QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}


void UserInterface::handlerSolver()
{
	this->ui.tableWidget->clearSelection();
	this->stopComputer = false;
	this->letComputerSolve();
}

void UserInterface::handlerCheck()
{
	this->stopComputer = true;
	this->ui.computerButton->setEnabled(false);
	this->ui.easyButton->setEnabled(false);
	this->ui.mediumButton->setEnabled(false);
	this->ui.hardButton->setEnabled(false);
	this->ui.tableWidget->setEnabled(false);
	this->ui.tableWidget->clearSelection();
	int value, row, column;
	Board userBoard;
	for (row = 0; row < 9; row++)
	{
		for (column = 0; column < 9; column++)
		{
			std::string str = this->ui.tableWidget->item(row, column)->text().toStdString();
			try
			{
				value = std::stoi(str);
			}
			catch (...)
			{
				value = 0;
			}
			userBoard.changeSquare(row, column, value);
		}
	}
	std::vector<std::pair<int, int>> errors = findErrors(this->usedBoard, userBoard);
	if (errors.size() == 0)
	{
		this->ui.congratsLabel->setText("Congrats !");
		this->createDelayManualSpeed(1500);
		this->ui.congratsLabel->setText("");
		this->ui.computerButton->setEnabled(true);
		this->ui.easyButton->setEnabled(true);
		this->ui.mediumButton->setEnabled(true);
		this->ui.hardButton->setEnabled(true);
		this->ui.tableWidget->setEnabled(true);
		return;
	}
	for (auto pair : errors)
	{
		row = pair.first;
		column = pair.second;
		if (userBoard.getValue(row, column) == 0)
		{
			this->ui.tableWidget->item(row, column)->setText("?");
			this->ui.tableWidget->item(row, column)->setTextColor(Qt::red);
		}
		else
		{
			this->ui.tableWidget->item(row, column)->setTextColor(Qt::red);
		}
	}
	this->ui.congratsLabel->setText("Try again !");
	this->createDelayManualSpeed(3000);
	for (auto pair : errors)
	{
		row = pair.first;
		column = pair.second;
		this->ui.tableWidget->item(row, column)->setTextColor(Qt::blue);
		this->ui.tableWidget->item(row, column)->setText("");
	}
	this->ui.congratsLabel->setText("");
	this->ui.computerButton->setEnabled(true);
	this->ui.easyButton->setEnabled(true);
	this->ui.mediumButton->setEnabled(true);
	this->ui.hardButton->setEnabled(true);
	this->ui.tableWidget->setEnabled(true);
}

void UserInterface::handlerSpeed()
{
	this->speed = this->ui.slideBar->value();
}

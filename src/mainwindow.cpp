#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow),
	mSolver(),
	mChessboardScene(0),
	mIsSearchingForSolution(false),
	mHasOperationBeenCancelled(false),
	mIsSolutionShowed(false),
	mButtonGroup()
{
	ui->setupUi(this);

	move(QApplication::desktop()->screen()->rect().center()-this->rect().center());   // Center window

	resetChessboard(ui->chessboardSizeSpinBox->value());

	setFocusPolicy(Qt::ClickFocus);

	mButtonGroup.addButton(ui->showSolutionLinesRadioButton);
	mButtonGroup.addButton(ui->showSolutionNumbersRadioButton);

	ui->showSolutionNumbersRadioButton->setChecked(true);
	ui->showSolutionNumbersRadioButton->setEnabled(false);
	ui->showSolutionLinesRadioButton->setEnabled(false);

	QObject::connect(&mSolver, SIGNAL(finished()), this, SLOT(onSolverFinished()));
}

MainWindow::~MainWindow()
{
	QObject::disconnect(&mSolver, SIGNAL(finished()), this, SLOT(onSolverFinished()));

	delete ui;
}

void MainWindow::resetChessboard(int size)
{
	// Delete old chessboard scene (if exists)
	if (mChessboardScene != 0)
	{
		delete mChessboardScene;
		mChessboardScene = 0;
	}

	// Create new chessboard scene
	mChessboardScene = new ChessboardScene(size, mSolver);

	// Connect view to scene
	ui->chessboardView->setScene(mChessboardScene);
	ui->chessboardView->setBackgroundBrush(QBrush(Qt::gray));

	mSolver.setChessboardSize(size);

	mSolver.setStartPosition( Vector2b(0, 0) );
}

void MainWindow::onSearchForSolutionCancelOperationButtonClicked()
{
	// If search for solution button is clicked
	if (!mIsSearchingForSolution)
	{
		mIsSearchingForSolution = true;
		mHasOperationBeenCancelled = false;
		ui->searchForSolutionCancelOperationButton->setText("Cancel operation");
		ui->solutionStackedWidget->setCurrentIndex(0);

		ui->chessboardSizeLabel->setEnabled(false);
		ui->chessboardSizeSpinBox->setEnabled(false);
		mChessboardScene->setIsChessboardInteractive(false);

		// Search for a solution in separate thread
		mSolver.start();
	}
	// Else if cancel operation button is clicked
	else
	{
		mSolver.cancelOperation();   // Request for cancellation of operation
		mHasOperationBeenCancelled = true;
		ui->chessboardSizeLabel->setEnabled(true);
		ui->chessboardSizeSpinBox->setEnabled(true);
		mChessboardScene->setIsChessboardInteractive(true);
	}
}

void MainWindow::onSolverFinished()
{
	mIsSearchingForSolution = false;
	ui->searchForSolutionCancelOperationButton->setText("Search for solution");
	ui->solutionStackedWidget->setCurrentIndex(1);

	// If operation has finished correctly
	if (!mHasOperationBeenCancelled)
	{
		// If a solution has been found
		if (mSolver.hasSolutionBeenFound())
		{
			ui->showSolutionNumbersRadioButton->setEnabled(true);
			ui->showSolutionLinesRadioButton->setEnabled(true);
			ui->backButton->setEnabled(true);
			ui->searchForSolutionCancelOperationButton->setEnabled(false);
			ui->solutionLabel->setText("Solution has been found.");
			mChessboardScene->createSolutionNumbersAndLines(mSolver.solution());
		}
		// Else if a solution does not exist
		else
		{
			ui->solutionLabel->setText("Solution does not exist.");
			ui->chessboardSizeLabel->setEnabled(true);
			ui->chessboardSizeSpinBox->setEnabled(true);
			mChessboardScene->setIsChessboardInteractive(true);
		}
	}
	// Else if operation has been cancelled by user
	else
	{
		ui->solutionLabel->setText("The operation has been cancelled.");
	}

	if (ui->showSolutionNumbersRadioButton->isChecked())
		mChessboardScene->showSolutionNumbers();
	else
		mChessboardScene->showSolutionLines();
}

void MainWindow::onShowSolutionNumbersRadioButtonToggled(bool value)
{
	if (value == true)
	{
		mChessboardScene->showSolutionNumbers();
	}
}

void MainWindow::onShowSolutionLinesRadioButtonToggled(bool value)
{
	if (value == true)
	{
		mChessboardScene->showSolutionLines();
	}
}

void MainWindow::onBackButtonClicked()
{
	ui->showSolutionNumbersRadioButton->setEnabled(false);
	ui->showSolutionLinesRadioButton->setEnabled(false);
	ui->backButton->setEnabled(false);
	ui->searchForSolutionCancelOperationButton->setEnabled(true);
	ui->solutionLabel->setText("");
	ui->chessboardSizeLabel->setEnabled(true);
	ui->chessboardSizeSpinBox->setEnabled(true);

	resetChessboard(ui->chessboardSizeSpinBox->value());
}

void MainWindow::leaveEvent(QEvent *e)
{
	QMainWindow::leaveEvent(e);
	mChessboardScene->hideSelectionGraphicsItem();
}

void MainWindow::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	if (mChessboardScene != 0)
		mChessboardScene->hideSelectionGraphicsItem();
}

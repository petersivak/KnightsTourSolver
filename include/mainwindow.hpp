#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QButtonGroup>

#include "solver.hpp"
#include "chessboardscene.hpp"

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

public slots:
	void resetChessboard(int size);
	void onSearchForSolutionCancelOperationButtonClicked();
	void onSolverFinished();
	void onShowSolutionNumbersRadioButtonToggled(bool value);
	void onShowSolutionLinesRadioButtonToggled(bool value);
	void onBackButtonClicked();

protected:
	void leaveEvent(QEvent *e);
	void changeEvent(QEvent *e);
	
private:
	Ui::MainWindow *ui;

	Solver mSolver;

	ChessboardScene *mChessboardScene;

	bool mIsSearchingForSolution;
	bool mHasOperationBeenCancelled;
	bool mIsSolutionShowed;

	QButtonGroup mButtonGroup;
};

#endif // MAINWINDOW_HPP

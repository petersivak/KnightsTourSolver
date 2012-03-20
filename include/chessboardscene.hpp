#ifndef CHESSBOARDSCENE_HPP
#define CHESSBOARDSCENE_HPP

#include <QGraphicsScene>

#include <QGraphicsSceneHoverEvent>

#include "vector2b.hpp"
#include "solver.hpp"

class ChessboardScene : public QGraphicsScene
{
	Q_OBJECT

private:
	static const int FRAME_SIZE = 18;
	static const int SQUARE_SIZE = 50;

public:
	ChessboardScene(int size, Solver &solver);

	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	void hideSelectionGraphicsItem();

	void createSolutionNumbersAndLines(const QList<Vector2b> &solution);
	void showSolutionNumbers();
	void showSolutionLines();

	void setIsChessboardInteractive(bool value);
	
signals:
	
public slots:

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
	int mSize;
	Solver &mSolver;

	QPixmap mUpleftFrameTexture;
	QPixmap mUprightFrameTexture;
	QPixmap mDownleftFrameTexture;
	QPixmap mDownrightFrameTexture;
	QPixmap mUpFrameTexture;
	QPixmap mDownFrameTexture;
	QPixmap mLeftFrameTexture;
	QPixmap mRightFrameTexture;
	QPixmap mWhiteSquareTexture;
	QPixmap mBlackSquareTexture;
	QPixmap mKnightTexture;

	QGraphicsPixmapItem *mKnightGraphicsItem;
	QGraphicsRectItem *mTranslucentKnightGraphicsItem;
	QGraphicsRectItem *mStartPosGraphicsItem;
	QGraphicsRectItem *mFinishPosGraphicsItem;

	QFont mNumbersLettersFont;

	QList<QGraphicsTextItem *> mSolutionNumbers;
	QList<QGraphicsLineItem *> mSolutionLines;

	bool mIsChessboardInteractive;
};

#endif // CHESSBOARDSCENE_HPP

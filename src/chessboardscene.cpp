#include "chessboardscene.hpp"

#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include "textfunctions.hpp"
#include "squaregraphicsitem.hpp"

ChessboardScene::ChessboardScene(int size, Solver &solver) :
	QGraphicsScene(0),
	mSize(size),
	mSolver(solver),
	mUpleftFrameTexture(":/images/upleft_frame.png"),
	mUprightFrameTexture(":/images/upright_frame.png"),
	mDownleftFrameTexture(":/images/downleft_frame.png"),
	mDownrightFrameTexture(":/images/downright_frame.png"),
	mUpFrameTexture(":/images/up_frame.png"),
	mDownFrameTexture(":/images/down_frame.png"),
	mLeftFrameTexture(":/images/left_frame.png"),
	mRightFrameTexture(":/images/right_frame.png"),
	mWhiteSquareTexture(":/images/white_square.png"),
	mBlackSquareTexture(":/images/black_square.png"),
	mKnightTexture(":/images/knight.png"),
	mKnightGraphicsItem(0),
	mTranslucentKnightGraphicsItem(0),
	mStartPosGraphicsItem(0),
	mFinishPosGraphicsItem(0),
	mNumbersLettersFont("Lato", 10, QFont::Bold, false),
	mSolutionNumbers(),
	mSolutionLines(),
	mIsChessboardInteractive(true)
{
	// Create frame
	addPixmap(mUpleftFrameTexture)->setPos(0, 0);
	addPixmap(mUprightFrameTexture)->setPos(size * SQUARE_SIZE + FRAME_SIZE, 0);
	addPixmap(mDownleftFrameTexture)->setPos(0, size * SQUARE_SIZE + FRAME_SIZE);
	addPixmap(mDownrightFrameTexture)->setPos(size * SQUARE_SIZE + FRAME_SIZE, size * SQUARE_SIZE + FRAME_SIZE);
	for (int i = 0; i < size; ++i)
	{
		addPixmap(mUpFrameTexture)->setPos(i * SQUARE_SIZE + FRAME_SIZE, 0);
		addPixmap(mDownFrameTexture)->setPos(i * SQUARE_SIZE + FRAME_SIZE, size * SQUARE_SIZE + FRAME_SIZE);
		addPixmap(mLeftFrameTexture)->setPos(0, i * SQUARE_SIZE + FRAME_SIZE);
		addPixmap(mRightFrameTexture)->setPos(size * SQUARE_SIZE + FRAME_SIZE, i * SQUARE_SIZE + FRAME_SIZE);
	}

	// Create numbers and letters
	for (int i = 0; i < size; ++i)
	{
		QGraphicsTextItem *leftNumber = addText(QString::number(i + 1));
		leftNumber->setPos( centeredTextPos(QString::number(i + 1), QPointF(0, i * SQUARE_SIZE + FRAME_SIZE),
										QPointF(FRAME_SIZE, SQUARE_SIZE), QFontMetrics(mNumbersLettersFont)) );
		leftNumber->setDefaultTextColor(Qt::white);
		leftNumber->setFont(mNumbersLettersFont);

		QGraphicsTextItem *rightNumber = addText(QString::number(i + 1));
		rightNumber->setPos( centeredTextPos(QString::number(i + 1), QPointF(size * SQUARE_SIZE + FRAME_SIZE,
				i * SQUARE_SIZE + FRAME_SIZE), QPointF(FRAME_SIZE, SQUARE_SIZE), QFontMetrics(mNumbersLettersFont)) );
		rightNumber->setDefaultTextColor(Qt::white);
		rightNumber->setFont(mNumbersLettersFont);

		QGraphicsTextItem *upLetter = addText(QString(65 + i));
		upLetter->setPos( centeredTextPos(QString(65 + i), QPointF(i * SQUARE_SIZE + FRAME_SIZE, 0),
										QPointF(SQUARE_SIZE, FRAME_SIZE), QFontMetrics(mNumbersLettersFont)) );
		upLetter->setDefaultTextColor(Qt::white);
		upLetter->setFont(mNumbersLettersFont);

		QGraphicsTextItem *downLetter = addText(QString(65 + i));
		downLetter->setPos( centeredTextPos(QString(65 + i), QPointF(i * SQUARE_SIZE + FRAME_SIZE,
				size * SQUARE_SIZE + FRAME_SIZE), QPointF(SQUARE_SIZE, FRAME_SIZE), QFontMetrics(mNumbersLettersFont)) );
		downLetter->setDefaultTextColor(Qt::white);
		downLetter->setFont(mNumbersLettersFont);
	}

	// Create squares
	for (int i = 0; i < size * size; ++i)
	{
		QPixmap pixmap;

		if ( ((i / size) % 2) == 0 )
		{
			if ( (i % 2) == 0 )
				pixmap = mWhiteSquareTexture;
			else
				pixmap = mBlackSquareTexture;
		}
		else
		{
			if ( (i % 2) == 0 )
			{
				if ( (size % 2) == 0 )
					pixmap = mBlackSquareTexture;
				else
					pixmap = mWhiteSquareTexture;
			}
			else
			{
				if ( (size % 2) == 0 )
					pixmap = mWhiteSquareTexture;
				else
					pixmap = mBlackSquareTexture;
			}
		}

		SquareGraphicsItem *squareItem = new SquareGraphicsItem(*this);
		squareItem->setPixmap(pixmap);
		squareItem->setPos((i % size) * SQUARE_SIZE + FRAME_SIZE, (i / size) * SQUARE_SIZE + FRAME_SIZE);
		squareItem->setAcceptHoverEvents(true);
		addItem(squareItem);
	}

	// Create knight
	(mKnightGraphicsItem = addPixmap(mKnightTexture))->setPos(FRAME_SIZE, FRAME_SIZE);
	mTranslucentKnightGraphicsItem = addRect(FRAME_SIZE, FRAME_SIZE, SQUARE_SIZE, SQUARE_SIZE, QPen(Qt::NoPen),
											 QBrush(QColor(0, 255, 128, 32)));
	mTranslucentKnightGraphicsItem->setVisible(false);

	// Create start and finish position rectangles
	mStartPosGraphicsItem = addRect(FRAME_SIZE, FRAME_SIZE, SQUARE_SIZE, SQUARE_SIZE, QPen(Qt::NoPen),
											 QBrush(QColor(0, 192, 0, 255)));
	mStartPosGraphicsItem->hide();
	mFinishPosGraphicsItem = addRect(FRAME_SIZE, FRAME_SIZE, SQUARE_SIZE, SQUARE_SIZE, QPen(Qt::NoPen),
											 QBrush(QColor(128, 0, 255, 255)));
	mFinishPosGraphicsItem->hide();
}

void ChessboardScene::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	qreal x = event->scenePos().x();
	qreal y = event->scenePos().y();

	// If user move mouse out of chessboard - hide translucent knight
	if ( (x < FRAME_SIZE) || (x >= mSize * SQUARE_SIZE + FRAME_SIZE) ||
		 (y < FRAME_SIZE) || (y >= mSize * SQUARE_SIZE + FRAME_SIZE) )
	{
		mTranslucentKnightGraphicsItem->hide();
	}
}

void ChessboardScene::hideSelectionGraphicsItem()
{
	mTranslucentKnightGraphicsItem->hide();
}

void ChessboardScene::createSolutionNumbersAndLines(const QList<Vector2b> &solution)
{
	// Remove previous solution numbers
	for (int i = 0; i < mSolutionNumbers.size(); ++i)
	{
		removeItem(mSolutionNumbers[i]);
	}

	// Create solution numbers
	for (int i = 0; i < solution.size(); ++i)
	{
		// Get coordinates of solution number
		qint8 x = solution[solution.size() - 1 - i].x();
		qint8 y = solution[solution.size() - 1 - i].y();

		// Create solution number
		QGraphicsTextItem *solutionNumber = addText(QString::number(i + 1));
		solutionNumber->setPos(centeredTextPos(QString::number(i + 1),
											   QPointF(x * SQUARE_SIZE + FRAME_SIZE, y * SQUARE_SIZE + FRAME_SIZE),
											   QPointF(SQUARE_SIZE, SQUARE_SIZE), QFontMetrics(mNumbersLettersFont)));
		solutionNumber->hide();
		solutionNumber->setDefaultTextColor(Qt::black);
		solutionNumber->setFont(mNumbersLettersFont);

		// Add the number to the list
		mSolutionNumbers.append(solutionNumber);
	}

	// Remove previous solution lines
	for (int i = 0; i < mSolutionLines.size(); ++i)
	{
		removeItem(mSolutionLines[i]);
	}

	// Create solution lines
	for (int i = 0; i < solution.size() - 1; ++i)
	{
		// Get coordinates of solution line
		qint8 x1 = solution[solution.size() - 1 - i].x();
		qint8 y1 = solution[solution.size() - 1 - i].y();
		qint8 x2 = solution[solution.size() - 2 - i].x();
		qint8 y2 = solution[solution.size() - 2 - i].y();

		// Create solution number (hide it for now)
		QPen linePen;
		linePen.setWidth(2);
		QGraphicsLineItem *solutionLine = addLine(x1 * SQUARE_SIZE + FRAME_SIZE + SQUARE_SIZE / 2,
												  y1 * SQUARE_SIZE + FRAME_SIZE + SQUARE_SIZE / 2,
												  x2 * SQUARE_SIZE + FRAME_SIZE + SQUARE_SIZE / 2,
												  y2 * SQUARE_SIZE + FRAME_SIZE + SQUARE_SIZE / 2,
												  linePen);
		solutionLine->hide();

		// Add the line to the list
		mSolutionLines.append(solutionLine);
	}

	// Set start and finish rectangle positions
	mStartPosGraphicsItem->setPos(solution[solution.size() - 1].x() * SQUARE_SIZE,
								  solution[solution.size() - 1].y() * SQUARE_SIZE);
	mStartPosGraphicsItem->show();
	mFinishPosGraphicsItem->setPos(solution[0].x() * SQUARE_SIZE,
								   solution[0].y() * SQUARE_SIZE);
	mFinishPosGraphicsItem->show();
}

void ChessboardScene::showSolutionNumbers()
{
	for (int i = 0; i < mSolutionNumbers.size(); ++i)
	{
		mSolutionNumbers[i]->show();
	}

	for (int i = 0; i < mSolutionLines.size(); ++i)
	{
		mSolutionLines[i]->hide();
	}
	update();
}

void ChessboardScene::showSolutionLines()
{
	for (int i = 0; i < mSolutionLines.size(); ++i)
	{
		mSolutionLines[i]->show();
	}

	for (int i = 0; i < mSolutionNumbers.size(); ++i)
	{
		mSolutionNumbers[i]->hide();
	}
	update();
}

void ChessboardScene::setIsChessboardInteractive(bool value)
{
	mIsChessboardInteractive = value;

	if (value == false)
	{
		mKnightGraphicsItem->hide();
	}
	else
	{
		mKnightGraphicsItem->show();
	}
}

void ChessboardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (!mIsChessboardInteractive)
		return;

	qreal x = event->scenePos().x();
	qreal y = event->scenePos().y();

	// If user clicked out of chessboard - do nothing
	if ( (x < FRAME_SIZE) || (x >= mSize * SQUARE_SIZE + FRAME_SIZE) ||
		 (y < FRAME_SIZE) || (y >= mSize * SQUARE_SIZE + FRAME_SIZE) )
	{
		return;
	}

	mKnightGraphicsItem->setPos( ((int) (x - FRAME_SIZE) / SQUARE_SIZE) * SQUARE_SIZE + FRAME_SIZE,
								 ((int) (y - FRAME_SIZE) / SQUARE_SIZE) * SQUARE_SIZE + FRAME_SIZE );

	mSolver.setStartPosition( Vector2b((int) (x - FRAME_SIZE) / SQUARE_SIZE,
									   (int) (y - FRAME_SIZE) / SQUARE_SIZE) );
}

void ChessboardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (!mIsChessboardInteractive)
		return;

	QGraphicsScene::mouseMoveEvent(event);
	qreal x = event->scenePos().x();
	qreal y = event->scenePos().y();

	// If user move mouse out of chessboard - do nothing
	if ( (x < FRAME_SIZE) || (x >= mSize * SQUARE_SIZE + FRAME_SIZE) ||
		 (y < FRAME_SIZE) || (y >= mSize * SQUARE_SIZE + FRAME_SIZE) )
	{
		return;
	}

	mTranslucentKnightGraphicsItem->setVisible(true);
	mTranslucentKnightGraphicsItem->setPos( ((int) (x - FRAME_SIZE) / SQUARE_SIZE) * SQUARE_SIZE,
								 ((int) (y - FRAME_SIZE) / SQUARE_SIZE) * SQUARE_SIZE );
}

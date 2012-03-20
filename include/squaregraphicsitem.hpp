#ifndef SQUAREGRAPHICSITEM_HPP
#define SQUAREGRAPHICSITEM_HPP

#include <QGraphicsPixmapItem>

#include "chessboardscene.hpp"

class SquareGraphicsItem : public QGraphicsPixmapItem
{
public:
	SquareGraphicsItem(ChessboardScene &scene);

protected:
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
	ChessboardScene &mScene;
};

#endif // SQUAREGRAPHICSITEM_HPP

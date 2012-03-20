#include "squaregraphicsitem.hpp"

SquareGraphicsItem::SquareGraphicsItem(ChessboardScene &scene) :
	mScene(scene)
{
}

void SquareGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	mScene.hoverLeaveEvent(event);
}

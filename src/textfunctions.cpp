#include "textfunctions.hpp"

QPointF centeredTextPos(const QString &text, const QPointF &rectPos, const QPointF &rectSize,
					  const QFontMetrics &fm)
{
	qreal textWidth = fm.width(text);
	qreal textHeight = fm.boundingRect('X').height();
	qreal centeredTextX = rectPos.x() + ((rectSize.x() - textWidth) / 2) - 4;
	qreal centeredTextY = rectPos.y() + ((rectSize.y() - textHeight) / 2) - (textHeight / 2) - 3;

	return QPointF(centeredTextX, centeredTextY);
}

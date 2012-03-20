#ifndef TEXTFUNCTIONS_HPP
#define TEXTFUNCTIONS_HPP

#include <QString>
#include <QFontMetrics>
#include <QPointF>

QPointF centeredTextPos(const QString &text, const QPointF &rectPos, const QPointF &rectSize,
					  const QFontMetrics &fm);

#endif // TEXTFUNCTIONS_HPP

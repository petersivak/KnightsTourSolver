#ifndef POINT_HPP
#define POINT_HPP

#include <QtGlobal>

class Point
{
public:
	Point(qint8 x, qint8 y);

	qint8 x() const;
	qint8 y() const;

private:
	qint8 mX;
	qint8 mY;
};

#endif // POINT_HPP

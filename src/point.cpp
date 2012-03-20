#include "point.hpp"

Point::Point(qint8 x, qint8 y) :
	mX(x),
	mY(y)
{
}

qint8 Point::x() const { return mX; }
qint8 Point::y() const { return mY; }

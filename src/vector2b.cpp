#include "vector2b.hpp"

Vector2b::Vector2b(qint8 x, qint8 y) :
	mX(x),
	mY(y)
{
}

qint8 Vector2b::x() const { return mX; }
qint8 Vector2b::y() const { return mY; }
void Vector2b::setX(qint8 x) { mX = x; }
void Vector2b::setY(qint8 y) { mY = y; }

Vector2b operator+(const Vector2b &first, const Vector2b &second)
{
	return Vector2b(first.x() + second.x(), first.y() + second.y());
}

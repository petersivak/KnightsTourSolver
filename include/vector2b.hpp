#ifndef VECTOR2B_HPP
#define VECTOR2B_HPP

#include <QtGlobal>

class Vector2b
{
public:
	Vector2b(qint8 x, qint8 y);

	friend Vector2b operator+(const Vector2b &first, const Vector2b &second);

	qint8 x() const;
	qint8 y() const;
	void setX(qint8 x);
	void setY(qint8 y);

private:
	qint8 mX;
	qint8 mY;
};

Vector2b operator+(const Vector2b &first, const Vector2b &second);

#endif // VECTOR2B_HPP

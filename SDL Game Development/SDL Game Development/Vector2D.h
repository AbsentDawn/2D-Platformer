#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__

#include<math.h>

class Vector2D
{
public:
	Vector2D(float pX, float pY) : x(pX), y(pY) {}

	float GetX() const { return x; }
	float GetY() const { return y; }

	void SetX(float pX) { x = pX; }
	void SetY(float pY) { y = pY; }

	float Length() { return sqrt(x * x + y * y); }

	Vector2D operator+(const Vector2D& vectorSource) const
	{
		return Vector2D(x + vectorSource.x, y + vectorSource.y);
	}

	friend Vector2D& operator+=(Vector2D& vectorDestination, Vector2D& vectorSource)
	{
		vectorDestination.x += vectorSource.x;
		vectorDestination.y += vectorSource.y;

		return vectorDestination;
	}

	Vector2D operator*(float scalar)
	{
		return Vector2D(x * scalar, y * scalar);
	}

	Vector2D operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2D operator-(const Vector2D &vectorSource) const
	{
		return Vector2D(x - vectorSource.x, y - vectorSource.y);
	}

	friend Vector2D operator-=(Vector2D &vectorDestination, Vector2D &vectorSource)
	{
		vectorDestination.x -= vectorSource.x;
		vectorDestination.y -= vectorSource.y;

		return vectorDestination;
	}

	Vector2D operator/(float scalar)
	{
		return Vector2D(x / scalar, y / scalar);
	}

	Vector2D& operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	void normalize()
	{
		float vectorLength = Length();

		if (vectorLength > 0) {
			(*this) *= 1 / vectorLength;
		}
	}

private:
	float x;
	float y;
};

#endif
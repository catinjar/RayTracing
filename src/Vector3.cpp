#include "Vector3.hpp"

Vector3 &Vector3::operator+=(const Vector3 &other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3 &Vector3::operator-=(const Vector3 &other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const Vector3 &other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3 &Vector3::operator/=(const Vector3 &other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vector3 &Vector3::operator*=(const float value)
{
	x *= value;
	y *= value;
	z *= value;
	return *this;
}

Vector3 &Vector3::operator/=(const float value)
{
	x /= value;
	y /= value;
	z /= value;
	return *this;
}

void Vector3::Normalize()
{
	*this /= Length();
}

Vector3 Vector3::Normalized() const
{
	return *this / Length();
}

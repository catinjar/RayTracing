#pragma once

#include <cmath>
#include <iosfwd>
#include <istream>

struct Vector3
{
	Vector3() = default;
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {} // NOLINT(cppcoreguidelines-pro-type-member-init)
	
	inline Vector3 operator+() const { return *this; }
	inline Vector3 operator-() const { return {-x, -y, -z}; }
	
	inline float operator[](int i) const { return v[i]; }
	inline float& operator[](int i) { return v[i]; }
	
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(const Vector3& other);
	Vector3& operator/=(const Vector3& other);
	
	Vector3& operator*=(float value);
	Vector3& operator/=(float value);
	
	inline float Length() const
	{
		return std::sqrt(SquaredLength());
	}
	
	inline float SquaredLength() const
	{
		return x * x + y * y + z * z;
	}
	
	void Normalize();
	Vector3 Normalized() const;
	
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		struct
		{
			float r;
			float g;
			float b;
		};
		float v[3];
	};
};

inline std::istream& operator>>(std::istream& is, Vector3& vector)
{
	is >> vector.x >> vector.y >> vector.z;
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const Vector3& vector)
{
	os << vector.x << " " << vector.y << " " << vector.z;
	return os;
}

inline Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return { left.x + right.x, left.y + right.y, left.z + right.z };
}

inline Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return { left.x - right.x, left.y - right.y, left.z - right.z };
}

inline Vector3 operator*(const Vector3& left, const Vector3& right)
{
	return { left.x * right.x, left.y * right.y, left.z * right.z };
}

inline Vector3 operator/(const Vector3& left, const Vector3& right)
{
	return { left.x / right.x, left.y / right.y, left.z / right.z };
}

inline Vector3 operator*(float value, const Vector3& vector)
{
	return { value * vector.x, value * vector.y, value * vector.z };
}

inline Vector3 operator*(const Vector3& vector, float value)
{
	return { vector.x * value, vector.y * value, vector.z * value };
}

inline Vector3 operator/(const Vector3& vector, float value)
{
	return { vector.x / value, vector.y / value, vector.z / value };
}

inline float Dot(const Vector3& left, const Vector3& right)
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

inline Vector3 Cross(const Vector3& left, const Vector3& right)
{
	return { left.y * right.z - left.z * right.y,
			 -(left.x * right.z - left.z * right.x),
			 left.x * right.y - left.y * right.x };
}

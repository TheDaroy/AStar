#pragma once
#include <math.h>
struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}
	Vector2& operator +=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator -=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	
	

};

inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) 
{

	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) 
{

	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs) 
{

	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

inline Vector2 operator *(const float& lhs, const Vector2& rhs) 
{

	return Vector2(lhs * rhs.x, lhs * rhs.y);
}
inline Vector2 operator /(const Vector2& lHS, const float& rHS)
{
	return Vector2(lHS.x / rHS, lHS.y / rHS);
}

inline Vector2 operator /(const float& lHS, const Vector2& rHS)
{
	return Vector2(lHS / rHS.x, lHS / rHS.y);
}
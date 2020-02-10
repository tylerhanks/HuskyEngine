#pragma once
#include <cmath>

namespace husky {

	template<typename T>
	struct Vector2D
	{
		Vector2D();
		Vector2D(T x, T y);
		Vector2D(const Vector2D<float>& src);

		// Basic vector operations.
		Vector2D operator+(const Vector2D& rhs) const;
		Vector2D& operator+=(const Vector2D& rhs);
		Vector2D operator-(const Vector2D& rhs) const;
		Vector2D& operator-=(const Vector2D& rhs);
		Vector2D operator*(T rhs) const;
		Vector2D& operator*=(T rhs);

		T dot(const Vector2D& rhs) const;
		T magnitude() const;
		T magnitude_sqr() const;

		Vector2D& Normalize();
		Vector2D GetNormalized() const;

		bool operator==(const Vector2D& rhs) const;
		bool operator!=(const Vector2D& rhs) const;
		
		// Data members.
		T x, y;
	};

	template<typename T>
	inline Vector2D<T>::Vector2D()
		: x((T)0), y((T)0)
	{
	}

	template<typename T>
	inline Vector2D<T>::Vector2D(T x, T y)
		: x(x), y(y)
	{
	}

	template<typename T>
	inline Vector2D<T>::Vector2D(const Vector2D<float>& src)
		: x((T)src.x), y((T)src.y)
	{
	}

	template<typename T>
	inline Vector2D<T> Vector2D<T>::operator+(const Vector2D<T>& rhs) const
	{
		return Vector2D(x + rhs.x, y + rhs.y);
	}

	template<typename T>
	inline Vector2D<T>& Vector2D<T>::operator+=(const Vector2D<T>& rhs)
	{
		return *this = *this + rhs;
	}

	template<typename T>
	inline Vector2D<T> Vector2D<T>::operator-(const Vector2D<T>& rhs) const
	{
		return Vector2D(x - rhs.x, y - rhs.y);
	}

	template<typename T>
	inline Vector2D<T>& Vector2D<T>::operator-=(const Vector2D<T>& rhs)
	{
		return *this = *this - rhs;
	}

	template<typename T>
	inline Vector2D<T> Vector2D<T>::operator*(T rhs) const
	{
		return Vector2D(x * rhs, y * rhs);
	}

	template<typename T>
	inline Vector2D<T>& Vector2D<T>::operator*=(T rhs)
	{
		return *this = *this * rhs;
	}

	template<typename T>
	inline T Vector2D<T>::dot(const Vector2D<T>& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	template<typename T>
	inline T Vector2D<T>::magnitude() const
	{
		return std::sqrtf(magnitude_sqr());
	}

	template<typename T>
	inline T Vector2D<T>::magnitude_sqr() const
	{
		return x * x + y * y;
	}

	template<typename T>
	inline Vector2D<T>& Vector2D<T>::Normalize()
	{
		return *this = GetNormalized();
	}

	template<typename T>
	inline Vector2D<T> Vector2D<T>::GetNormalized() const
	{
		const T len = magnitude();
		if (len != (T)0)
		{
			return *this * ((T)1 / len);
		}
		else
			return *this;
	}

	template<typename T>
	inline bool Vector2D<T>::operator==(const Vector2D<T>& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

	template<typename T>
	inline bool Vector2D<T>::operator!=(const Vector2D<T>& rhs) const
	{
		return !(*this == rhs);
	}

	typedef Vector2D<float> Vec2f;
	typedef Vector2D<int> Vec2i;

}

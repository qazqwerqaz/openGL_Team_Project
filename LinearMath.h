#pragma once
#define EPSILON				0.001f
#include "stdafx.h"
inline float Sign(float x)
{
	return x < 0.0f ? -1.0f : 1.0f;
}


class Vector2
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			
		};
		float v[2];
	};

public:

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	Vector2(Vector2&& other);
	~Vector2();

	Vector2& operator=(const Vector2& other);
	Vector2& operator=(Vector2&& other) noexcept;
	Vector2& operator*(float);
	Vector2 operator -() { return Vector2(-x, -y); }

	void operator += (const Vector2& v)
	{
		x += v.x; y += v.y;
	}

	void operator -= (const Vector2& v)
	{
		x -= v.x; y -= v.y;
	}

	void operator *= (float a)
	{
		x *= a; y *= a;
	}

	void Set(float x, float y);

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();


};

class Vector3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};

public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);
	Vector3(Vector3&& other);
	~Vector3();

	Vector3& operator=(const Vector3& other);
	Vector3& operator=(Vector3&& other) noexcept;
	Vector3& operator*(float);

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();
};

class Vector4
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};

public:
	Vector4();
	Vector4(float x, float y, float z, float w);
	Vector4(const Vector4& other);
	Vector4(Vector4&& other);
	~Vector4();

	Vector4& operator=(const Vector4& other);
	Vector4& operator=(Vector4&& other) noexcept;

	float& operator[](size_t idx);
	float  operator[](size_t idx) const;
	float* operator&();
};

struct Matrix2x2
{
	Matrix2x2() {}
	Matrix2x2(float angle)
	{
		float c = cosf(angle), s = sinf(angle);
		col1.x = c; col2.x = -s;
		col1.y = s; col2.y = c;
	}

	Matrix2x2(const Vector2& col1, const Vector2& col2) : col1(col1), col2(col2) {}

	Matrix2x2 Transpose() const
	{
		return Matrix2x2(Vector2(col1.x, col2.x), Vector2(col1.y, col2.y));
	}

	Matrix2x2 Invert() const
	{
		float a = col1.x, b = col2.x, c = col1.y, d = col2.y;
		Matrix2x2 B;
		float det = a * d - b * c;
		assert(det != 0.0f);
		det = 1.0f / det;
		B.col1.x = det * d;	B.col2.x = -det * b;
		B.col1.y = -det * c;	B.col2.y = det * a;
		return B;
	}

	Vector2 col1, col2;
};

class Matrix4x4
{
public:
	union
	{
		struct
		{
			float m11, m12, m13, m14;
			float m21, m22, m23, m24;
			float m31, m32, m33, m34;
			float m41, m42, m43, m44;
		};
		Vector4 v[4];
	};

public:
	Matrix4x4();
	Matrix4x4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44);

	Matrix4x4(const Matrix4x4& other);
	Matrix4x4(Matrix4x4&& other);
	~Matrix4x4();

	Matrix4x4& operator=(const Matrix4x4& other);
	Matrix4x4& operator=(Matrix4x4&& other) noexcept;

	Vector4& operator[](size_t idx);
	Vector4  operator[](size_t idx) const;
	float *operator&();
};

/* OPERATIONS ------------------------------------------------------------------------------------------------------ */

inline bool isZero(float fNum)
{
	return fabsf(fNum) < EPSILON;
}

inline bool areEqual(float fLhs, float fRhs)
{
	return isZero(fLhs - fRhs);
}

namespace V2
{
	inline Vector2 add(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2
		(
			lhs.x + rhs.x,
			lhs.y + rhs.y
		);
	}

	inline Vector2 subtract(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2
		(
			lhs.x - rhs.x,
			lhs.y - rhs.y
		);
	}

	inline float dot(const Vector2& lhs, const Vector2& rhs)
	{
		return
			(lhs.x * rhs.x) +
			(lhs.y * rhs.y);
	}


	inline float size(const Vector2& v3Vector)
	{
		return sqrtf(V2::dot(v3Vector, v3Vector));
	}

	inline Vector2 normalize(const Vector2& v3Vector)
	{
		Vector2 v3Result;
		float fSize = size(v3Vector);
		v3Result.x = v3Vector.x / fSize;
		v3Result.y = v3Vector.y / fSize;
		return v3Result;
	}
}

namespace V3
{
	inline Vector3 add(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3
		(
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z
		);
	}

	inline Vector3 subtract(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3
		(
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z
		);
	}

	inline float dot(const Vector3& lhs, const Vector3& rhs)
	{
		return
			(lhs.x * rhs.x) +
			(lhs.y * rhs.y) +
			(lhs.z * rhs.z);
	}

	inline Vector3 cross(const Vector3& lhs, const Vector3& rhs)
	{
		Vector3 v3Result;
		v3Result.x = lhs.y * rhs.z - lhs.z * rhs.y;
		v3Result.y = lhs.z * rhs.x - lhs.x * rhs.z;
		v3Result.z = lhs.x * rhs.y - lhs.y * rhs.x;
		return v3Result;
	}

	inline float size(const Vector3& v3Vector)
	{
		return sqrtf(V3::dot(v3Vector, v3Vector));
	}

	inline Vector3 normalize(const Vector3& v3Vector)
	{
		Vector3 v3Result;
		float fSize = size(v3Vector);
		v3Result.x = v3Vector.x / fSize;
		v3Result.y = v3Vector.y / fSize;
		v3Result.z = v3Vector.z / fSize;

		return v3Result;
	}
}

namespace V4
{
	inline Vector4 mult(const Matrix4x4& lMatrix, const Vector4& rColumnVector)
	{
		Vector4 v4Result(0.f, 0.f, 0.f, 0.f);
		for (size_t i = 0; i < 4; ++i)
			for (size_t j = 0; j < 4; ++j)
			{
				float f1 = lMatrix[i][j];
				float f2 = rColumnVector[j];
				v4Result[i] += f1 * f2;
			}

		return v4Result;
	}

	inline Vector4 mult(const Vector4& lhs, const Vector4& rhs)
	{
		Vector4 v4Result;
		v4Result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
		v4Result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
		v4Result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
		v4Result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
		return v4Result;
	}

	inline Vector4 conj(const Vector4& q)
	{
		return Vector4(-q.x, -q.y, -q.z, q.w);
	}
}

inline Vector2 operator * (const Matrix2x2& A, const Vector2& v)
{
	return Vector2(A.col1.x * v.x + A.col2.x * v.y, A.col1.y * v.x + A.col2.y * v.y);
}

inline Vector2 operator + (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x + b.x, a.y + b.y);
}

inline Vector2 operator - (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}


inline Matrix2x2 operator * (const Matrix2x2& A, const Matrix2x2& B)
{
	return Matrix2x2(A * B.col1, A * B.col2);
}

inline Vector2 Abs(const Vector2& a)
{
	return Vector2(fabsf(a.x), fabsf(a.y));
}

inline Matrix2x2 Abs(const Matrix2x2& A)
{
	return Matrix2x2(Abs(A.col1), Abs(A.col2));
}

inline Matrix2x2 operator + (const Matrix2x2& A, const Matrix2x2& B)
{
	return Matrix2x2(A.col1 + B.col1, A.col2 + B.col2);
}

inline float Cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

inline Vector2 Cross(const Vector2& a, float s)
{
	return Vector2(s * a.y, -s * a.x);
}

inline Vector2 Cross(float s, const Vector2& a)
{
	return Vector2(-s * a.y, s * a.x);
}


inline float Min(float a, float b)
{
	return a < b ? a : b;
}

inline float Max(float a, float b)
{
	return a > b ? a : b;
}

inline float Clamp(float a, float low, float high)
{
	return Max(low, Min(a, high));
}
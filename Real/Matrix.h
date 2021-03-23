#pragma once
// column matrix

#include <math.h>
#include <algorithm>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"


using namespace std;

class Matrix2 {
private:
	float m[4];

public:
	Matrix2();
	Matrix2(const float matrix[4]);
	Matrix2(float m0, float m1, float m2, float m3);
	~Matrix2() {};

	inline Matrix2& identity() {
		m[0] = m[3] = 1.0f;
		m[1] = m[2] = 0.0f;
		return *this;
	}

	inline void set(const float src[4]) {
		m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
	}

	inline void set(float m0, float m1, float m2, float m3) {
		m[0] = m0;  m[1] = m1;  m[2] = m2;  m[3] = m3;
	}

	inline float operator[](int index) const {
		return m[index];
	}

	inline Matrix2 operator+(const Matrix2& rhs) const {
		return Matrix2(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3]);
	}

	inline Matrix2 operator-(const Matrix2& rhs) const {
		return Matrix2(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3]);
	}

	inline Vector2 operator*(const Vector2& rhs) const {
		return Vector2(m[0] * rhs.x + m[2] * rhs.y, m[1] * rhs.x + m[3] * rhs.y);
	}

	inline bool operator==(const Matrix2& rhs) const {
		return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]);
	}

	inline Matrix2& transpose() {
		swap(m[1], m[2]);
		return *this;
	}




	Matrix2& invert();
};

class Matrix3 {
private:
	float m[9];

public:
	Matrix3();
	Matrix3(const float matrix[9]);
	Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);
	~Matrix3() {};

	inline Matrix3& identity() {
		m[0] = m[4] = m[8] = 1.0f;
		m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
		return *this;
	}

	inline void set(const float src[9]) {
		m[0] = src[0];  m[1] = src[1];  m[2] = src[2];
		m[3] = src[3];  m[4] = src[4];  m[5] = src[5];
		m[6] = src[6];  m[7] = src[7];  m[8] = src[8];
	}

	inline void set(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) {
		m[0] = m0;  m[1] = m1;  m[2] = m2;
		m[3] = m3;  m[4] = m4;  m[5] = m5;
		m[6] = m6;  m[7] = m6;  m[8] = m8;
	}

	inline float operator[](int index) const {
		return m[index];
	}

	inline Matrix3 operator+(const Matrix3& rhs) const {
		return Matrix3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
			m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
			m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
	}

	inline Matrix3 operator-(const Matrix3& rhs) const {
		return Matrix3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
			m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
			m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
	}

	inline Vector3 operator*(const Vector3& rhs) const {
		return Vector3(m[0] * rhs.x + m[3] * rhs.y + m[6] * rhs.z,
			m[1] * rhs.x + m[4] * rhs.y + m[7] * rhs.z,
			m[2] * rhs.x + m[5] * rhs.y + m[8] * rhs.z);
	}

	inline Matrix3 operator*(const Matrix3& rhs) const
	{
		return Matrix3(m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
			m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
			m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
	}

	inline bool operator==(const Matrix3& rhs) const {
		return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
			(m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
			(m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
	}

	inline Matrix3& transpose() {
		swap(m[1], m[3]);
		swap(m[2], m[6]);
		swap(m[5], m[7]);

		return *this;
	}




	inline friend Matrix3 operator*(float s, const Matrix3& rhs) {
		return Matrix3(s * rhs[0], s * rhs[1], s * rhs[2], s * rhs[3], s * rhs[4], s * rhs[5], s * rhs[6], s * rhs[7], s * rhs[8]);
	}
	inline friend Vector3 operator*(const Vector3& v, const Matrix3& m) {
		return Vector3(v.x * m[0] + v.y * m[1] + v.z * m[2], v.x * m[3] + v.y * m[4] + v.z * m[5], v.x * m[6] + v.y * m[7] + v.z * m[8]);
	}




	Matrix3& invert();
};

class Matrix4 {
private:
	float m[16];

public:
	Matrix4();
	Matrix4(float f);
	Matrix4(const float matrix[16]);
	Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15);
	~Matrix4() {};

	static Matrix4 identity;
	static Matrix4 zero;

	inline void set(const float src[16]){
		m[0] = src[0];		m[1] = src[1];		m[2] = src[2];		m[3] = src[3];
		m[4] = src[4];		m[5] = src[5];		m[6] = src[6];		m[7] = src[7];
		m[8] = src[8];		m[9] = src[9];		m[10] = src[10];	m[11] = src[11];
		m[12] = src[12];	m[13] = src[13];	m[14] = src[14];	m[15] = src[15];
	}

	inline void set(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
		float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15) {
		m[0] = m0;		m[1] = m1;		m[2] = m2;		m[3] = m3;
		m[4] = m4;		m[5] = m5;		m[6] = m6;		m[7] = m7;
		m[8] = m8;		m[9] = m9;		m[10] = m10;	m[11] = m11;
		m[12] = m12;	m[13] = m13;	m[14] = m14;	m[15] = m15;
	}

	inline float operator[](int index) const {
		return m[index];
	}

	inline Matrix4 operator+(const Matrix4& rhs) const{
		return Matrix4(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
			m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
			m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
			m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
	}

	inline Matrix4 operator-(const Matrix4& rhs) const{
		return Matrix4(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
			m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
			m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
			m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
	}

	inline Vector4 operator*(const Vector4& rhs) const{
		return Vector4(m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12] * rhs.w,
			m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13] * rhs.w,
			m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14] * rhs.w,
			m[3] * rhs.x + m[7] * rhs.y + m[11] * rhs.z + m[15] * rhs.w);
	}

	inline Vector3 operator*(const Vector3& rhs) const{
		return Vector3(m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z,
			m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z,
			m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z);
	}

	inline Matrix4 operator*(const Matrix4& n) const{
		return Matrix4(m[0] * n[0] + m[4] * n[1] + m[8] * n[2] + m[12] * n[3], m[1] * n[0] + m[5] * n[1] + m[9] * n[2] + m[13] * n[3], m[2] * n[0] + m[6] * n[1] + m[10] * n[2] + m[14] * n[3], m[3] * n[0] + m[7] * n[1] + m[11] * n[2] + m[15] * n[3],
			m[0] * n[4] + m[4] * n[5] + m[8] * n[6] + m[12] * n[7], m[1] * n[4] + m[5] * n[5] + m[9] * n[6] + m[13] * n[7], m[2] * n[4] + m[6] * n[5] + m[10] * n[6] + m[14] * n[7], m[3] * n[4] + m[7] * n[5] + m[11] * n[6] + m[15] * n[7],
			m[0] * n[8] + m[4] * n[9] + m[8] * n[10] + m[12] * n[11], m[1] * n[8] + m[5] * n[9] + m[9] * n[10] + m[13] * n[11], m[2] * n[8] + m[6] * n[9] + m[10] * n[10] + m[14] * n[11], m[3] * n[8] + m[7] * n[9] + m[11] * n[10] + m[15] * n[11],
			m[0] * n[12] + m[4] * n[13] + m[8] * n[14] + m[12] * n[15], m[1] * n[12] + m[5] * n[13] + m[9] * n[14] + m[13] * n[15], m[2] * n[12] + m[6] * n[13] + m[10] * n[14] + m[14] * n[15], m[3] * n[12] + m[7] * n[13] + m[11] * n[14] + m[15] * n[15]);
	}

	inline bool operator==(const Matrix4& n) const{
		return (m[0] == n[0]) && (m[1] == n[1]) && (m[2] == n[2]) && (m[3] == n[3]) &&
			(m[4] == n[4]) && (m[5] == n[5]) && (m[6] == n[6]) && (m[7] == n[7]) &&
			(m[8] == n[8]) && (m[9] == n[9]) && (m[10] == n[10]) && (m[11] == n[11]) &&
			(m[12] == n[12]) && (m[13] == n[13]) && (m[14] == n[14]) && (m[15] == n[15]);
	}




	inline friend Matrix4 operator*(float s, const Matrix4& rhs){
		return Matrix4(s * rhs[0], s * rhs[1], s * rhs[2], s * rhs[3], s * rhs[4], s * rhs[5], s * rhs[6], s * rhs[7], s * rhs[8], s * rhs[9], s * rhs[10], s * rhs[11], s * rhs[12], s * rhs[13], s * rhs[14], s * rhs[15]);
	}

	inline friend Vector4 operator*(const Vector4& v, const Matrix4& m)
	{
		return Vector4(v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3], v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7], v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11], v.x * m[12] + v.y * m[13] + v.z * m[14] + v.w * m[15]);
	}

	inline friend Vector3 operator*(const Vector3& v, const Matrix4& m)
	{
		return Vector3(v.x * m[0] + v.y * m[1] + v.z * m[2], v.x * m[4] + v.y * m[5] + v.z * m[6], v.x * m[8] + v.y * m[9] + v.z * m[10]);
	}




	Matrix4& transpose();
	Matrix4& invert();
	Matrix4& invertEuclidean();
	Matrix4& invertAffine();
	Matrix4& invertProjective();
	Matrix4& invertGeneral();		
	Matrix4& translate(float x, float y, float z);
	Matrix4& rotate(float angle, float x, float y, float z);
	Matrix4& rotateX(float angle);
	Matrix4& rotateY(float angle);
	Matrix4& rotateZ(float angle);
	Matrix4& scale(float sx, float sy, float sz);

	const float* getTranspose();
	float		getDeterminant();
	float		getCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8);
};
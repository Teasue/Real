#include <math.h>
#include "Matrix.h"


const float DEG2RAD = 3.141593f / 180;
const float EPSILON = 0.00001f;


Matrix2::Matrix2() {
	identity(); 
}

Matrix2::Matrix2(const float matrix[4]) { 
	set(matrix);
}

Matrix2::Matrix2(float m0, float m1, float m2, float m3) {
	set(m0, m1, m2, m3);
}

Matrix2& Matrix2::invert(){
	float determinant = m[0] * m[3] - m[1] * m[2];
	if (fabs(determinant) <= EPSILON)
	{
		return identity();
	}

	float tmp = m[0];
	float invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * m[3];
	m[1] = -invDeterminant * m[1];
	m[2] = -invDeterminant * m[2];
	m[3] = invDeterminant * tmp;

	return *this;
}




Matrix3::Matrix3() {
	identity();
}

Matrix3::Matrix3(const float matrix[9]) {
	set(matrix);
}

Matrix3::Matrix3(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8) {
	set(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}

Matrix3& Matrix3::invert(){
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = m[4] * m[8] - m[5] * m[7];
	tmp[1] = m[2] * m[7] - m[1] * m[8];
	tmp[2] = m[1] * m[5] - m[2] * m[4];
	tmp[3] = m[5] * m[6] - m[3] * m[8];
	tmp[4] = m[0] * m[8] - m[2] * m[6];
	tmp[5] = m[2] * m[3] - m[0] * m[5];
	tmp[6] = m[3] * m[7] - m[4] * m[6];
	tmp[7] = m[1] * m[6] - m[0] * m[7];
	tmp[8] = m[0] * m[4] - m[1] * m[3];

	determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
	if (fabs(determinant) <= EPSILON)
	{
		return identity();
	}

	invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * tmp[0];
	m[1] = invDeterminant * tmp[1];
	m[2] = invDeterminant * tmp[2];
	m[3] = invDeterminant * tmp[3];
	m[4] = invDeterminant * tmp[4];
	m[5] = invDeterminant * tmp[5];
	m[6] = invDeterminant * tmp[6];
	m[7] = invDeterminant * tmp[7];
	m[8] = invDeterminant * tmp[8];

	return *this;
}




Matrix4::Matrix4() {
	identity;
}

Matrix4::Matrix4(float f) {
	set(f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f);
}

Matrix4::Matrix4(const float matrix[16]) {
	set(matrix);
}

Matrix4::Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7,
	float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15) {
	set(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15);
}

Matrix4 Matrix4::zero(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
Matrix4 Matrix4::identity(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

Matrix4& Matrix4::transpose(){
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);

	return *this;
}

Matrix4& Matrix4::invert(){
	if (m[3] == 0 && m[7] == 0 && m[11] == 0 && m[15] == 1)
		this->invertAffine();
	else
	{
		this->invertGeneral();
	}

	return *this;
}

Matrix4& Matrix4::invertEuclidean(){
	float tmp;
	tmp = m[1];  m[1] = m[4];  m[4] = tmp;
	tmp = m[2];  m[2] = m[8];  m[8] = tmp;
	tmp = m[6];  m[6] = m[9];  m[9] = tmp;

	float x = m[12];
	float y = m[13];
	float z = m[14];
	m[12] = -(m[0] * x + m[4] * y + m[8] * z);
	m[13] = -(m[1] * x + m[5] * y + m[9] * z);
	m[14] = -(m[2] * x + m[6] * y + m[10] * z);

	return *this;
}

Matrix4& Matrix4::invertAffine(){
	Matrix3 r(m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]);
	r.invert();
	m[0] = r[0];  m[1] = r[1];  m[2] = r[2];
	m[4] = r[3];  m[5] = r[4];  m[6] = r[5];
	m[8] = r[6];  m[9] = r[7];  m[10] = r[8];

	float x = m[12];
	float y = m[13];
	float z = m[14];
	m[12] = -(r[0] * x + r[3] * y + r[6] * z);
	m[13] = -(r[1] * x + r[4] * y + r[7] * z);
	m[14] = -(r[2] * x + r[5] * y + r[8] * z);

	return *this;
}

float Matrix4::getDeterminant(){
	return m[0] * getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]) -
		m[1] * getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]) +
		m[2] * getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]) -
		m[3] * getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);
}

float Matrix4::getCofactor(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8){
	return m0 * (m4 * m8 - m5 * m7) - m1 * (m3 * m8 - m5 * m6) + m2 * (m3 * m7 - m4 * m6);
}

Matrix4& Matrix4::translate(float x, float y, float z){
	m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
	m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
	m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

	return *this;
}

Matrix4& Matrix4::scale(float x, float y, float z)
{
	m[0] *= x;   m[4] *= x;   m[8] *= x;   m[12] *= x;
	m[1] *= y;   m[5] *= y;   m[9] *= y;   m[13] *= y;
	m[2] *= z;   m[6] *= z;   m[10] *= z;   m[14] *= z;
	return *this;
}

Matrix4& Matrix4::rotate(float angle, float x, float y, float z)
{
	float c = cosf(angle * DEG2RAD);
	float s = sinf(angle * DEG2RAD);
	float c1 = 1.0f - c;
	float m0 = m[0], m4 = m[4], m8 = m[8], m12 = m[12],
		m1 = m[1], m5 = m[5], m9 = m[9], m13 = m[13],
		m2 = m[2], m6 = m[6], m10 = m[10], m14 = m[14];

	float r0 = x * x * c1 + c;
	float r1 = x * y * c1 + z * s;
	float r2 = x * z * c1 - y * s;
	float r4 = x * y * c1 - z * s;
	float r5 = y * y * c1 + c;
	float r6 = y * z * c1 + x * s;
	float r8 = x * z * c1 + y * s;
	float r9 = y * z * c1 - x * s;
	float r10 = z * z * c1 + c;

	m[0] = r0 * m0 + r4 * m1 + r8 * m2;
	m[1] = r1 * m0 + r5 * m1 + r9 * m2;
	m[2] = r2 * m0 + r6 * m1 + r10 * m2;
	m[4] = r0 * m4 + r4 * m5 + r8 * m6;
	m[5] = r1 * m4 + r5 * m5 + r9 * m6;
	m[6] = r2 * m4 + r6 * m5 + r10 * m6;
	m[8] = r0 * m8 + r4 * m9 + r8 * m10;
	m[9] = r1 * m8 + r5 * m9 + r9 * m10;
	m[10] = r2 * m8 + r6 * m9 + r10 * m10;
	m[12] = r0 * m12 + r4 * m13 + r8 * m14;
	m[13] = r1 * m12 + r5 * m13 + r9 * m14;
	m[14] = r2 * m12 + r6 * m13 + r10 * m14;

	return *this;
}
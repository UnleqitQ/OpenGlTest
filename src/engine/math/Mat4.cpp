#include "Mat4.hpp"
#include <stdexcept>
#include <cmath>

using namespace std::string_literals;

namespace engine::math {
	Mat4::Mat4()
		: m_v{0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0} {
	}
	Mat4::Mat4(float values[16])
		: m_v{values[0], values[1], values[2], values[3],
		values[4], values[5], values[6], values[7],
		values[8], values[9], values[10], values[11],
		values[12], values[13], values[14], values[15]} {
	}
	Mat4::Mat4(float value)
		: m_v{
		value, value, value, value,
		value, value, value, value,
		value, value, value, value,
		value, value, value, value} {
	}
	Mat4::Mat4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20,
		float m21, float m22, float m23, float m30, float m31, float m32, float m33)
		: m_v{m00, m01, m02, m03,
		m10, m11, m12, m13,
		m20, m21, m22, m23,
		m30, m31, m32, m33} {
	}
	float Mat4::operator[](int index) const {
		if (index < 0 || index >= 16) {
			throw std::out_of_range("Index out of range");
		}
		return m_v[index];
	}
	float Mat4::operator[](int row, int column) const {
		if (row < 0 || row >= 4 || column < 0 || column >= 4) {
			throw std::out_of_range("Index out of range");
		}
		return m_v[row * 4 + column];
	}
	Mat4 Mat4::operator()(int index, float value) const {
		if (index < 0 || index >= 16) {
			throw std::out_of_range("Index out of range");
		}
		float values[16];
		for (int i = 0; i < 16; i++) {
			values[i] = m_v[i];
		}
		values[index] = value;
		return Mat4(values);
	}
	Mat4 Mat4::operator()(int row, int column, float value) const {
		if (row < 0 || row >= 4 || column < 0 || column >= 4) {
			throw std::out_of_range("Index out of range");
		}
		float values[16];
		for (int i = 0; i < 16; i++) {
			values[i] = m_v[i];
		}
		values[row * 4 + column] = value;
		return Mat4(values);
	}
	float Mat4::m00() const {
		return m_v[0];
	}
	float Mat4::m01() const {
		return m_v[1];
	}
	float Mat4::m02() const {
		return m_v[2];
	}
	float Mat4::m03() const {
		return m_v[3];
	}
	float Mat4::m10() const {
		return m_v[4];
	}
	float Mat4::m11() const {
		return m_v[5];
	}
	float Mat4::m12() const {
		return m_v[6];
	}
	float Mat4::m13() const {
		return m_v[7];
	}
	float Mat4::m20() const {
		return m_v[8];
	}
	float Mat4::m21() const {
		return m_v[9];
	}
	float Mat4::m22() const {
		return m_v[10];
	}
	float Mat4::m23() const {
		return m_v[11];
	}
	float Mat4::m30() const {
		return m_v[12];
	}
	float Mat4::m31() const {
		return m_v[13];
	}
	float Mat4::m32() const {
		return m_v[14];
	}
	float Mat4::m33() const {
		return m_v[15];
	}
	const float* const Mat4::data() const {
		return m_v;
	}
	Mat4 Mat4::operator+(const Mat4& other) const {
		return Mat4(m_v[0] + other.m_v[0], m_v[1] + other.m_v[1], m_v[2] + other.m_v[2], m_v[3] + other.m_v[3],
			m_v[4] + other.m_v[4], m_v[5] + other.m_v[5], m_v[6] + other.m_v[6], m_v[7] + other.m_v[7],
			m_v[8] + other.m_v[8], m_v[9] + other.m_v[9], m_v[10] + other.m_v[10], m_v[11] + other.m_v[11],
			m_v[12] + other.m_v[12], m_v[13] + other.m_v[13], m_v[14] + other.m_v[14], m_v[15] + other.m_v[15]);
	}
	Mat4 Mat4::operator-(const Mat4& other) const {
		return Mat4(m_v[0] - other.m_v[0], m_v[1] - other.m_v[1], m_v[2] - other.m_v[2], m_v[3] - other.m_v[3],
			m_v[4] - other.m_v[4], m_v[5] - other.m_v[5], m_v[6] - other.m_v[6], m_v[7] - other.m_v[7],
			m_v[8] - other.m_v[8], m_v[9] - other.m_v[9], m_v[10] - other.m_v[10], m_v[11] - other.m_v[11],
			m_v[12] - other.m_v[12], m_v[13] - other.m_v[13], m_v[14] - other.m_v[14], m_v[15] - other.m_v[15]);
	}
	Mat4 Mat4::operator*(const Mat4& other) const {
		float m00 = m_v[0] * other.m_v[0] + m_v[1] * other.m_v[4] + m_v[2] * other.m_v[8] + m_v[3] * other.m_v[12];
		float m01 = m_v[0] * other.m_v[1] + m_v[1] * other.m_v[5] + m_v[2] * other.m_v[9] + m_v[3] * other.m_v[13];
		float m02 = m_v[0] * other.m_v[2] + m_v[1] * other.m_v[6] + m_v[2] * other.m_v[10] + m_v[3] * other.m_v[14];
		float m03 = m_v[0] * other.m_v[3] + m_v[1] * other.m_v[7] + m_v[2] * other.m_v[11] + m_v[3] * other.m_v[15];
		float m10 = m_v[4] * other.m_v[0] + m_v[5] * other.m_v[4] + m_v[6] * other.m_v[8] + m_v[7] * other.m_v[12];
		float m11 = m_v[4] * other.m_v[1] + m_v[5] * other.m_v[5] + m_v[6] * other.m_v[9] + m_v[7] * other.m_v[13];
		float m12 = m_v[4] * other.m_v[2] + m_v[5] * other.m_v[6] + m_v[6] * other.m_v[10] + m_v[7] * other.m_v[14];
		float m13 = m_v[4] * other.m_v[3] + m_v[5] * other.m_v[7] + m_v[6] * other.m_v[11] + m_v[7] * other.m_v[15];
		float m20 = m_v[8] * other.m_v[0] + m_v[9] * other.m_v[4] + m_v[10] * other.m_v[8] + m_v[11] * other.m_v[12];
		float m21 = m_v[8] * other.m_v[1] + m_v[9] * other.m_v[5] + m_v[10] * other.m_v[9] + m_v[11] * other.m_v[13];
		float m22 = m_v[8] * other.m_v[2] + m_v[9] * other.m_v[6] + m_v[10] * other.m_v[10] + m_v[11] * other.m_v[14];
		float m23 = m_v[8] * other.m_v[3] + m_v[9] * other.m_v[7] + m_v[10] * other.m_v[11] + m_v[11] * other.m_v[15];
		float m30 = m_v[12] * other.m_v[0] + m_v[13] * other.m_v[4] + m_v[14] * other.m_v[8] + m_v[15] * other.m_v[12];
		float m31 = m_v[12] * other.m_v[1] + m_v[13] * other.m_v[5] + m_v[14] * other.m_v[9] + m_v[15] * other.m_v[13];
		float m32 = m_v[12] * other.m_v[2] + m_v[13] * other.m_v[6] + m_v[14] * other.m_v[10] + m_v[15] * other.m_v[14];
		float m33 = m_v[12] * other.m_v[3] + m_v[13] * other.m_v[7] + m_v[14] * other.m_v[11] + m_v[15] * other.m_v[15];
		return Mat4(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
	}
	Mat4 Mat4::operator-() const {
		return Mat4(-m_v[0], -m_v[1], -m_v[2], -m_v[3], -m_v[4], -m_v[5], -m_v[6], -m_v[7], -m_v[8], -m_v[9], -m_v[10],
			-m_v[11], -m_v[12], -m_v[13], -m_v[14], -m_v[15]);
	}
	Mat4 Mat4::operator~() const {
		return Mat4(m_v[0], m_v[4], m_v[8], m_v[12], m_v[1], m_v[5], m_v[9], m_v[13], m_v[2], m_v[6], m_v[10], m_v[14],
			m_v[3], m_v[7], m_v[11], m_v[15]);
	}
	Mat4 Mat4::operator*(float scalar) const {
		return Mat4(m_v[0] * scalar, m_v[1] * scalar, m_v[2] * scalar, m_v[3] * scalar, m_v[4] * scalar, m_v[5] * scalar,
			m_v[6] * scalar, m_v[7] * scalar, m_v[8] * scalar, m_v[9] * scalar, m_v[10] * scalar, m_v[11] * scalar,
			m_v[12] * scalar, m_v[13] * scalar, m_v[14] * scalar, m_v[15] * scalar);
	}
	Mat4 Mat4::operator/(float scalar) const {
		return Mat4(m_v[0] / scalar, m_v[1] / scalar, m_v[2] / scalar, m_v[3] / scalar, m_v[4] / scalar, m_v[5] / scalar,
			m_v[6] / scalar, m_v[7] / scalar, m_v[8] / scalar, m_v[9] / scalar, m_v[10] / scalar, m_v[11] / scalar,
			m_v[12] / scalar, m_v[13] / scalar, m_v[14] / scalar, m_v[15] / scalar);
	}
	
	Mat4& Mat4::operator+=(const Mat4& other) {
		return *this = *this + other;
	}
	Mat4& Mat4::operator-=(const Mat4& other) {
		return *this = *this - other;
	}
	Mat4& Mat4::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	Mat4& Mat4::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	
	bool Mat4::operator==(const Mat4& other) const {
		for (int i = 0; i < 16; i++) {
			if (m_v[i] != other.m_v[i]) {
				return false;
			}
		}
		return true;
	}
	bool Mat4::operator!=(const Mat4& other) const {
		return !operator==(other);
	}
	float Mat4::determinant() const {
		float det = 0;
		for (int i = 0; i < 4; i++) {
			det += m_v[i] * (m_v[4 + (i + 1) % 4] *
				(m_v[8 + (i + 2) % 4] * m_v[12 + (i + 3) % 4] - m_v[8 + (i + 3) % 4] * m_v[12 + (i + 2) % 4]) -
				m_v[4 + (i + 2) % 4] *
					(m_v[8 + (i + 1) % 4] * m_v[12 + (i + 3) % 4] - m_v[8 + (i + 3) % 4] * m_v[12 + (i + 1) % 4]) +
				m_v[4 + (i + 3) % 4] *
					(m_v[8 + (i + 1) % 4] * m_v[12 + (i + 2) % 4] - m_v[8 + (i + 2) % 4] * m_v[12 + (i + 1) % 4]));
		}
		return det;
	}
	Mat4 Mat4::inverse() const {
		float det = determinant();
		if (det == 0) {
			throw std::runtime_error("Matrix is not invertible");
		}
		float invDet = 1.0f / det;
		
		float m00 = (m_v[5] * (m_v[10] * m_v[15] - m_v[11] * m_v[14]) - m_v[6] * (m_v[9] * m_v[15] - m_v[11] * m_v[13]) +
			m_v[7] * (m_v[9] * m_v[14] - m_v[10] * m_v[13])) * invDet;
		float m01 = (-m_v[1] * (m_v[10] * m_v[15] - m_v[11] * m_v[14]) + m_v[2] * (m_v[9] * m_v[15] - m_v[11] * m_v[13]) -
			m_v[3] * (m_v[9] * m_v[14] - m_v[10] * m_v[13])) * invDet;
		float m02 = (m_v[1] * (m_v[6] * m_v[15] - m_v[7] * m_v[14]) - m_v[2] * (m_v[5] * m_v[15] - m_v[7] * m_v[13]) +
			m_v[3] * (m_v[5] * m_v[14] - m_v[6] * m_v[13])) * invDet;
		float m03 = (-m_v[1] * (m_v[6] * m_v[11] - m_v[7] * m_v[10]) + m_v[2] * (m_v[5] * m_v[11] - m_v[7] * m_v[9]) -
			m_v[3] * (m_v[5] * m_v[10] - m_v[6] * m_v[9])) * invDet;
		
		float m10 = (-m_v[4] * (m_v[10] * m_v[15] - m_v[11] * m_v[14]) + m_v[6] * (m_v[8] * m_v[15] - m_v[11] * m_v[12]) -
			m_v[7] * (m_v[8] * m_v[14] - m_v[10] * m_v[12])) * invDet;
		float m11 = (m_v[0] * (m_v[10] * m_v[15] - m_v[11] * m_v[14]) - m_v[2] * (m_v[8] * m_v[15] - m_v[11] * m_v[12]) +
			m_v[3] * (m_v[8] * m_v[14] - m_v[10] * m_v[12])) * invDet;
		float m12 = (-m_v[0] * (m_v[6] * m_v[15] - m_v[7] * m_v[14]) + m_v[2] * (m_v[4] * m_v[15] - m_v[7] * m_v[12]) -
			m_v[3] * (m_v[4] * m_v[14] - m_v[6] * m_v[12])) * invDet;
		float m13 = (m_v[0] * (m_v[6] * m_v[11] - m_v[7] * m_v[10]) - m_v[2] * (m_v[4] * m_v[11] - m_v[7] * m_v[8]) +
			m_v[3] * (m_v[4] * m_v[10] - m_v[6] * m_v[8])) * invDet;
		
		float m20 = (m_v[4] * (m_v[9] * m_v[15] - m_v[11] * m_v[13]) - m_v[5] * (m_v[8] * m_v[15] - m_v[11] * m_v[12]) +
			m_v[7] * (m_v[8] * m_v[13] - m_v[9] * m_v[12])) * invDet;
		float m21 = (-m_v[0] * (m_v[9] * m_v[15] - m_v[11] * m_v[13]) + m_v[1] * (m_v[8] * m_v[15] - m_v[11] * m_v[12]) -
			m_v[3] * (m_v[8] * m_v[13] - m_v[9] * m_v[12])) * invDet;
		float m22 = (m_v[0] * (m_v[5] * m_v[15] - m_v[7] * m_v[13]) - m_v[1] * (m_v[4] * m_v[15] - m_v[7] * m_v[12]) +
			m_v[3] * (m_v[4] * m_v[13] - m_v[5] * m_v[12])) * invDet;
		float m23 = (-m_v[0] * (m_v[5] * m_v[11] - m_v[7] * m_v[9]) + m_v[1] * (m_v[4] * m_v[11] - m_v[7] * m_v[8]) -
			m_v[3] * (m_v[4] * m_v[9] - m_v[5] * m_v[8])) * invDet;
		
		float m30 = (-m_v[4] * (m_v[9] * m_v[14] - m_v[10] * m_v[13]) + m_v[5] * (m_v[8] * m_v[14] - m_v[10] * m_v[12]) -
			m_v[6] * (m_v[8] * m_v[13] - m_v[9] * m_v[12])) * invDet;
		float m31 = (m_v[0] * (m_v[9] * m_v[14] - m_v[10] * m_v[13]) - m_v[1] * (m_v[8] * m_v[14] - m_v[10] * m_v[12]) +
			m_v[2] * (m_v[8] * m_v[13] - m_v[9] * m_v[12])) * invDet;
		float m32 = (-m_v[0] * (m_v[5] * m_v[14] - m_v[6] * m_v[13]) + m_v[1] * (m_v[4] * m_v[14] - m_v[6] * m_v[12]) -
			m_v[2] * (m_v[4] * m_v[13] - m_v[5] * m_v[12])) * invDet;
		float m33 = (m_v[0] * (m_v[5] * m_v[10] - m_v[6] * m_v[9]) - m_v[1] * (m_v[4] * m_v[10] - m_v[6] * m_v[8]) +
			m_v[2] * (m_v[4] * m_v[9] - m_v[5] * m_v[8])) * invDet;
		
		return Mat4(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
	}
	Mat4 Mat4::identity() {
		return Mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
	}
	
	Vec4 operator*(const Mat4& matrix, const Vec4& vector) {
		float x =
			matrix.m_v[0] * vector.x() + matrix.m_v[1] * vector.y() + matrix.m_v[2] * vector.z() + matrix.m_v[3] * vector.w();
		float y =
			matrix.m_v[4] * vector.x() + matrix.m_v[5] * vector.y() + matrix.m_v[6] * vector.z() + matrix.m_v[7] * vector.w();
		float z = matrix.m_v[8] * vector.x() + matrix.m_v[9] * vector.y() + matrix.m_v[10] * vector.z() +
			matrix.m_v[11] * vector.w();
		float w = matrix.m_v[12] * vector.x() + matrix.m_v[13] * vector.y() + matrix.m_v[14] * vector.z() +
			matrix.m_v[15] * vector.w();
		return Vec4(x, y, z, w);
	}
	Vec4 operator*(const Vec4& vector, const Mat4& matrix) {
		float x = matrix.m_v[0] * vector.x() + matrix.m_v[4] * vector.y() + matrix.m_v[8] * vector.z() +
			matrix.m_v[12] * vector.w();
		float y = matrix.m_v[1] * vector.x() + matrix.m_v[5] * vector.y() + matrix.m_v[9] * vector.z() +
			matrix.m_v[13] * vector.w();
		float z = matrix.m_v[2] * vector.x() + matrix.m_v[6] * vector.y() + matrix.m_v[10] * vector.z() +
			matrix.m_v[14] * vector.w();
		float w = matrix.m_v[3] * vector.x() + matrix.m_v[7] * vector.y() + matrix.m_v[11] * vector.z() +
			matrix.m_v[15] * vector.w();
		return Vec4(x, y, z, w);
	}
	Vec3 operator*(const Mat4& matrix, const Vec3& vector) {
		Vec4 v4 = Vec4(vector, 1);
		Vec4 r = matrix * v4;
		return Vec3(r.x(), r.y(), r.z()) / r.w();
	}
	Vec3 operator*(const Vec3& vector, const Mat4& matrix) {
		Vec4 v4 = Vec4(vector, 1);
		Vec4 r = v4 * matrix;
		return Vec3(r.x(), r.y(), r.z()) / r.w();
	}
	
	Mat4 Mat4::translation(float x, float y, float z) {
		return Mat4(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1);
	}
	Mat4 Mat4::translation(const Vec3& translation) {
		return Mat4::translation(translation.x(), translation.y(), translation.z());
	}
	Mat4 Mat4::rotation(float angle, float x, float y, float z) {
		float c = std::cos(angle);
		float s = std::sin(angle);
		float t = 1 - c;
		return Mat4(
			t * x * x + c, t * x * y - s * z, t * x * z + s * y, 0,
			t * x * y + s * z, t * y * y + c, t * y * z - s * x, 0,
			t * x * z - s * y, t * y * z + s * x, t * z * z + c, 0,
			0, 0, 0, 1);
	}
	Mat4 Mat4::rotation(float angle, const Vec3& axis) {
		return Mat4::rotation(angle, axis.x(), axis.y(), axis.z());
	}
	Mat4 Mat4::scale(float x, float y, float z) {
		return Mat4(
			x, 0, 0, 0,
			0, y, 0, 0,
			0, 0, z, 0,
			0, 0, 0, 1);
	}
	Mat4 Mat4::scale(const Vec3& scale) {
		return Mat4::scale(scale.x(), scale.y(), scale.z());
	}
	Mat4 Mat4::perspective(float fov, float aspect, float near, float far) {
		float focalLength = 1.0f / std::tan(fov / 2.0f);
		return Mat4(
			focalLength / aspect, 0, 0, 0,
			0, focalLength, 0, 0,
			0, 0, -(far + near) / (far - near), -(2 * far * near) / (far - near),
			0, 0, -1, 0);
	}
	Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
		float lr = 1.0f / (left - right);
		float bt = 1.0f / (bottom - top);
		float nf = 1.0f / (near - far);
		return Mat4(
			-2 * lr, 0, 0, 0,
			0, -2 * bt, 0, 0,
			0, 0, 2 * nf, 0,
			(left + right) * lr, (top + bottom) * bt, (far + near) * nf, 1);
	}
	Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
		Vec3 f = (center - eye).normalize();
		Vec3 r = f.cross(up).normalize();
		Vec3 u = r.cross(f);
		return Mat4(
			r.x(), r.y(), r.z(), -r.dot(eye),
			u.x(), u.y(), u.z(), -u.dot(eye),
			-f.x(), -f.y(), -f.z(), f.dot(eye),
			0, 0, 0, 1);
	}
	
	std::ostream& operator<<(std::ostream& os, const Mat4& matrix) {
		return os << matrix.to_string(false);
	}
	std::string Mat4::to_string(bool pretty) const {
		if (pretty) {
			return "["s + std::to_string(m_v[0]) + ", " + std::to_string(m_v[1]) + ", " + std::to_string(m_v[2]) + ", " +
				std::to_string(m_v[3]) + "]\n[" + std::to_string(m_v[4]) + ", " + std::to_string(m_v[5]) + ", " +
				std::to_string(m_v[6]) + ", " + std::to_string(m_v[7]) + "]\n[" + std::to_string(m_v[8]) + ", " +
				std::to_string(m_v[9]) + ", " + std::to_string(m_v[10]) + ", " + std::to_string(m_v[11]) + "]\n[" +
				std::to_string(m_v[12]) + ", " + std::to_string(m_v[13]) + ", " + std::to_string(m_v[14]) + ", " +
				std::to_string(m_v[15]) + "]";
		}
		else {
			return "["s + std::to_string(m_v[0]) + ", " + std::to_string(m_v[1]) + ", " + std::to_string(m_v[2]) + ", " +
				std::to_string(m_v[3]) + "; " + std::to_string(m_v[4]) + ", " + std::to_string(m_v[5]) + ", " +
				std::to_string(m_v[6]) + ", " + std::to_string(m_v[7]) + "; " + std::to_string(m_v[8]) + ", " +
				std::to_string(m_v[9]) + ", " + std::to_string(m_v[10]) + ", " + std::to_string(m_v[11]) + "; " +
				std::to_string(m_v[12]) + ", " + std::to_string(m_v[13]) + ", " + std::to_string(m_v[14]) + ", " +
				std::to_string(m_v[15]) + "]";
		}
	}
} // engine::math
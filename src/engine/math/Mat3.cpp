#include "Mat3.hpp"
#include <stdexcept>

using namespace std::string_literals;

namespace engine::math {
	Mat3::Mat3() : m_v{0, 0, 0, 0, 0, 0, 0, 0, 0} {}
	Mat3::Mat3(float values[9]) : m_v{values[0], values[1], values[2], values[3], values[4], values[5], values[6],
		values[7], values[8]} {}
	Mat3::Mat3(float value) : m_v{value, value, value, value, value, value, value, value, value} {}
	Mat3::Mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22) : m_v{
		m00, m01, m02, m10, m11, m12, m20, m21, m22} {}
	
	float Mat3::operator[](int index) const {
		if (index < 0 || index >= 9) {
			throw std::out_of_range("Mat3 index out of range");
		}
		return m_v[index];
	}
	float Mat3::operator[](int row, int column) const {
		if (row < 0 || row >= 3 || column < 0 || column >= 3) {
			throw std::out_of_range("Mat3 index out of range");
		}
		return m_v[row * 3 + column];
	}
	Mat3 Mat3::operator()(int index, float value) const {
		if (index < 0 || index >= 9) {
			throw std::out_of_range("Mat3 index out of range");
		}
		float values[9];
		for (int i = 0; i < 9; i++) {
			values[i] = m_v[i];
		}
		values[index] = value;
		return Mat3(values);
	}
	Mat3 Mat3::operator()(int row, int column, float value) const {
		if (row < 0 || row >= 3 || column < 0 || column >= 3) {
			throw std::out_of_range("Mat3 index out of range");
		}
		float values[9];
		for (int i = 0; i < 9; i++) {
			values[i] = m_v[i];
		}
		values[row * 3 + column] = value;
		return Mat3(values);
	}
	float Mat3::m00() const {
		return m_v[0];
	}
	float Mat3::m01() const {
		return m_v[1];
	}
	float Mat3::m02() const {
		return m_v[2];
	}
	float Mat3::m10() const {
		return m_v[3];
	}
	float Mat3::m11() const {
		return m_v[4];
	}
	float Mat3::m12() const {
		return m_v[5];
	}
	float Mat3::m20() const {
		return m_v[6];
	}
	float Mat3::m21() const {
		return m_v[7];
	}
	float Mat3::m22() const {
		return m_v[8];
	}
	const float* const Mat3::data() const {
		return m_v;
	}
	Mat3 Mat3::operator+(const Mat3& other) const {
		return Mat3(m_v[0] + other.m_v[0], m_v[1] + other.m_v[1], m_v[2] + other.m_v[2],
			m_v[3] + other.m_v[3], m_v[4] + other.m_v[4], m_v[5] + other.m_v[5],
			m_v[6] + other.m_v[6], m_v[7] + other.m_v[7], m_v[8] + other.m_v[8]);
	}
	Mat3 Mat3::operator-(const Mat3& other) const {
		return Mat3(m_v[0] - other.m_v[0], m_v[1] - other.m_v[1], m_v[2] - other.m_v[2],
			m_v[3] - other.m_v[3], m_v[4] - other.m_v[4], m_v[5] - other.m_v[5],
			m_v[6] - other.m_v[6], m_v[7] - other.m_v[7], m_v[8] - other.m_v[8]);
	}
	Mat3 Mat3::operator*(const Mat3& other) const {
		return Mat3(m_v[0] * other.m_v[0] + m_v[1] * other.m_v[3] + m_v[2] * other.m_v[6],
			m_v[0] * other.m_v[1] + m_v[1] * other.m_v[4] + m_v[2] * other.m_v[7],
			m_v[0] * other.m_v[2] + m_v[1] * other.m_v[5] + m_v[2] * other.m_v[8],
			m_v[3] * other.m_v[0] + m_v[4] * other.m_v[3] + m_v[5] * other.m_v[6],
			m_v[3] * other.m_v[1] + m_v[4] * other.m_v[4] + m_v[5] * other.m_v[7],
			m_v[3] * other.m_v[2] + m_v[4] * other.m_v[5] + m_v[5] * other.m_v[8],
			m_v[6] * other.m_v[0] + m_v[7] * other.m_v[3] + m_v[8] * other.m_v[6],
			m_v[6] * other.m_v[1] + m_v[7] * other.m_v[4] + m_v[8] * other.m_v[7],
			m_v[6] * other.m_v[2] + m_v[7] * other.m_v[5] + m_v[8] * other.m_v[8]);
	}
	Mat3 Mat3::operator-() const {
		return Mat3(-m_v[0], -m_v[1], -m_v[2], -m_v[3], -m_v[4], -m_v[5], -m_v[6], -m_v[7], -m_v[8]);
	}
	Mat3 Mat3::operator~() const {
		return Mat3(m_v[0], m_v[3], m_v[6], m_v[1], m_v[4], m_v[7], m_v[2], m_v[5], m_v[8]);
	}
	Mat3 Mat3::operator*(float scalar) const {
		return Mat3(m_v[0] * scalar, m_v[1] * scalar, m_v[2] * scalar, m_v[3] * scalar, m_v[4] * scalar, m_v[5] * scalar,
			m_v[6] * scalar, m_v[7] * scalar, m_v[8] * scalar);
	}
	Mat3 Mat3::operator/(float scalar) const {
		return Mat3(m_v[0] / scalar, m_v[1] / scalar, m_v[2] / scalar, m_v[3] / scalar, m_v[4] / scalar, m_v[5] / scalar,
			m_v[6] / scalar, m_v[7] / scalar, m_v[8] / scalar);
	}
	
	Mat3& Mat3::operator+=(const Mat3& other) {
		return *this = *this + other;
	}
	Mat3& Mat3::operator-=(const Mat3& other) {
		return *this = *this - other;
	}
	Mat3& Mat3::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	Mat3& Mat3::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	
	bool Mat3::operator==(const Mat3& other) const {
		for (int i = 0; i < 9; i++) {
			if (m_v[i] != other.m_v[i]) {
				return false;
			}
		}
		return true;
	}
	bool Mat3::operator!=(const Mat3& other) const {
		return !operator==(other);
	}
	float Mat3::determinant() const {
		return m_v[0] * m_v[4] * m_v[8] + m_v[1] * m_v[5] * m_v[6] + m_v[2] * m_v[3] * m_v[7] -
			m_v[2] * m_v[4] * m_v[6] - m_v[1] * m_v[3] * m_v[8] - m_v[0] * m_v[5] * m_v[7];
	}
	Mat3 Mat3::inverse() const {
		float det = determinant();
		if (det == 0) {
			throw std::runtime_error("Mat3 is not invertible");
		}
		float invDet = 1.0f / det;
		return Mat3((m_v[4] * m_v[8] - m_v[5] * m_v[7]) * invDet, (m_v[2] * m_v[7] - m_v[1] * m_v[8]) * invDet,
			(m_v[1] * m_v[5] - m_v[2] * m_v[4]) * invDet, (m_v[5] * m_v[6] - m_v[3] * m_v[8]) * invDet,
			(m_v[0] * m_v[8] - m_v[2] * m_v[6]) * invDet, (m_v[2] * m_v[3] - m_v[0] * m_v[5]) * invDet,
			(m_v[3] * m_v[7] - m_v[4] * m_v[6]) * invDet, (m_v[1] * m_v[6] - m_v[0] * m_v[7]) * invDet,
			(m_v[0] * m_v[4] - m_v[1] * m_v[3]) * invDet);
	}
	Mat3 Mat3::identity() {
		return Mat3(
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		);
	}
	Vec3 operator*(const Mat3& matrix, const Vec3& vector) {
		return Vec3(
			matrix.m00() * vector.x() + matrix.m01() * vector.y() + matrix.m02() * vector.z(),
			matrix.m10() * vector.x() + matrix.m11() * vector.y() + matrix.m12() * vector.z(),
			matrix.m20() * vector.x() + matrix.m21() * vector.y() + matrix.m22() * vector.z()
		);
	}
	Vec3 operator*(const Vec3& vector, const Mat3& matrix) {
		return Vec3(
			matrix.m00() * vector.x() + matrix.m10() * vector.y() + matrix.m20() * vector.z(),
			matrix.m01() * vector.x() + matrix.m11() * vector.y() + matrix.m21() * vector.z(),
			matrix.m02() * vector.x() + matrix.m12() * vector.y() + matrix.m22() * vector.z()
		);
	}
	
	std::ostream& operator<<(std::ostream& os, const Mat3& matrix) {
		return os << matrix.to_string(false);
	}
	std::string Mat3::to_string(bool pretty) const {
		if (pretty) {
			return "["s + std::to_string(m00()) + ", " + std::to_string(m01()) + ", " + std::to_string(m02()) + "]\n[" +
				std::to_string(m10()) + ", " + std::to_string(m11()) + ", " + std::to_string(m12()) + "]\n[" +
				std::to_string(m20()) + ", " + std::to_string(m21()) + ", " + std::to_string(m22()) + "]";
		}
		else {
			return "["s + std::to_string(m00()) + ", " + std::to_string(m01()) + ", " + std::to_string(m02()) +
				"; " + std::to_string(m10()) + ", " + std::to_string(m11()) + ", " + std::to_string(m12()) +
				"; " + std::to_string(m20()) + ", " + std::to_string(m21()) + ", " + std::to_string(m22()) + "]";
		}
	}
} // engine::math
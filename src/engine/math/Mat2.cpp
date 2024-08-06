#include "Mat2.hpp"
#include <stdexcept>

using namespace std::string_literals;

namespace engine::math {
	Mat2::Mat2() : m_v{0, 0, 0, 0} {}
	Mat2::Mat2(float values[4]) : m_v{values[0], values[1], values[2], values[3]} {}
	Mat2::Mat2(float value) : m_v{value, value, value, value} {}
	Mat2::Mat2(float m00, float m01, float m10, float m11) : m_v{m00, m01, m10, m11} {}
	
	float Mat2::operator[](int index) const {
		if (index < 0 || index >= 4) {
			throw std::out_of_range("Mat2 index out of range");
		}
		return m_v[index];
	}
	float Mat2::operator[](int row, int column) const {
		if (row < 0 || row >= 2 || column < 0 || column >= 2) {
			throw std::out_of_range("Mat2 index out of range");
		}
		return m_v[row * 2 + column];
	}
	Mat2 Mat2::operator()(int index, float value) const {
		if (index < 0 || index >= 4) {
			throw std::out_of_range("Mat2 index out of range");
		}
		float values[4] = {m_v[0], m_v[1], m_v[2], m_v[3]};
		values[index] = value;
		return Mat2(values);
	}
	Mat2 Mat2::operator()(int row, int column, float value) const {
		if (row < 0 || row >= 2 || column < 0 || column >= 2) {
			throw std::out_of_range("Mat2 index out of range");
		}
		float values[4] = {m_v[0], m_v[1], m_v[2], m_v[3]};
		values[row * 2 + column] = value;
		return Mat2(values);
	}
	
	float Mat2::m00() const {
		return m_v[0];
	}
	float Mat2::m01() const {
		return m_v[1];
	}
	float Mat2::m10() const {
		return m_v[2];
	}
	float Mat2::m11() const {
		return m_v[3];
	}
	const float* const Mat2::data() const {
		return m_v;
	}
	
	Mat2 Mat2::operator+(const Mat2& other) const {
		return Mat2(m_v[0] + other.m_v[0], m_v[1] + other.m_v[1], m_v[2] + other.m_v[2], m_v[3] + other.m_v[3]);
	}
	Mat2 Mat2::operator-(const Mat2& other) const {
		return Mat2(m_v[0] - other.m_v[0], m_v[1] - other.m_v[1], m_v[2] - other.m_v[2], m_v[3] - other.m_v[3]);
	}
	Mat2 Mat2::operator*(const Mat2& other) const {
		return Mat2(m_v[0] * other.m_v[0] + m_v[1] * other.m_v[2], m_v[0] * other.m_v[1] + m_v[1] * other.m_v[3],
			m_v[2] * other.m_v[0] + m_v[3] * other.m_v[2], m_v[2] * other.m_v[1] + m_v[3] * other.m_v[3]);
	}
	Mat2 Mat2::operator-() const {
		return Mat2(-m_v[0], -m_v[1], -m_v[2], -m_v[3]);
	}
	Mat2 Mat2::operator~() const {
		return Mat2(m_v[0], m_v[2], m_v[1], m_v[3]);
	}
	Mat2 Mat2::operator*(float scalar) const {
		return Mat2(m_v[0] * scalar, m_v[1] * scalar, m_v[2] * scalar, m_v[3] * scalar);
	}
	Mat2 Mat2::operator/(float scalar) const {
		return Mat2(m_v[0] / scalar, m_v[1] / scalar, m_v[2] / scalar, m_v[3] / scalar);
	}
	
	Mat2& Mat2::operator+=(const Mat2& other) {
		return *this = *this + other;
	}
	Mat2& Mat2::operator-=(const Mat2& other) {
		return *this = *this - other;
	}
	Mat2& Mat2::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	Mat2& Mat2::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	
	bool Mat2::operator==(const Mat2& other) const {
		return m_v[0] == other.m_v[0] && m_v[1] == other.m_v[1] && m_v[2] == other.m_v[2] && m_v[3] == other.m_v[3];
	}
	bool Mat2::operator!=(const Mat2& other) const {
		return !operator==(other);
	}
	float Mat2::determinant() const {
		return m_v[0] * m_v[3] - m_v[1] * m_v[2];
	}
	Mat2 Mat2::inverse() const {
		float det = determinant();
		if (det == 0) {
			throw std::runtime_error("Mat2 is not invertible");
		}
		float invDet = 1.0f / det;
		return Mat2(m_v[3] * invDet, -m_v[1] * invDet, -m_v[2] * invDet, m_v[0] * invDet);
	}
	Mat2 Mat2::identity() {
		return Mat2(1, 0, 0, 1);
	}
	Vec2 operator*(const Mat2& matrix, const Vec2& vector) {
		return Vec2(matrix.m00() * vector.x() + matrix.m01() * vector.y(),
			matrix.m10() * vector.x() + matrix.m11() * vector.y());
	}
	Vec2 operator*(const Vec2& vector, const Mat2& matrix) {
		return Vec2(matrix.m00() * vector.x() + matrix.m10() * vector.y(),
			matrix.m01() * vector.x() + matrix.m11() * vector.y());
	}
	
	std::ostream& operator<<(std::ostream& os, const Mat2& matrix) {
		return os << matrix.to_string(false);
	}
	std::string Mat2::to_string(bool pretty) const {
		if (pretty) {
			return "["s + std::to_string(m00()) + ", " + std::to_string(m01()) + "]\n[" +
				std::to_string(m10()) + ", " + std::to_string(m11()) + "]";
		}
		else {
			return "["s + std::to_string(m00()) + ", " + std::to_string(m01()) +
				"; " + std::to_string(m10()) + ", " + std::to_string(m11()) + "]";
		}
	}
} // engine::math
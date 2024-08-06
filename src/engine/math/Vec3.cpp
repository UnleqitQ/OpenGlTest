#include "Vec3.hpp"
#include <cmath>

namespace engine::math {
	const Vec3 Vec3::ZERO = Vec3(0, 0, 0);
	const Vec3 Vec3::ONE = Vec3(1, 1, 1);
	const Vec3 Vec3::UNIT_X = Vec3(1, 0, 0);
	const Vec3 Vec3::UNIT_Y = Vec3(0, 1, 0);
	const Vec3 Vec3::UNIT_Z = Vec3(0, 0, 1);
	
	Vec3::Vec3() : m_x(0), m_y(0), m_z(0) {}
	Vec3::Vec3(float scalar) : m_x(scalar), m_y(scalar), m_z(scalar) {}
	Vec3::Vec3(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
	
	float Vec3::x() const {
		return m_x;
	}
	float Vec3::y() const {
		return m_y;
	}
	float Vec3::z() const {
		return m_z;
	}
	
	Vec3 Vec3::x(float x) const {
		return Vec3(x, m_y, m_z);
	}
	Vec3 Vec3::y(float y) const {
		return Vec3(m_x, y, m_z);
	}
	Vec3 Vec3::z(float z) const {
		return Vec3(m_x, m_y, z);
	}
	
	Vec3 Vec3::operator+(const Vec3& other) const {
		return Vec3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
	}
	Vec3 Vec3::operator-(const Vec3& other) const {
		return Vec3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
	}
	Vec3 Vec3::operator*(const Vec3& other) const {
		return Vec3(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z);
	}
	Vec3 Vec3::operator/(const Vec3& other) const {
		return Vec3(m_x / other.m_x, m_y / other.m_y, m_z / other.m_z);
	}
	Vec3 Vec3::operator*(float scalar) const {
		return Vec3(m_x * scalar, m_y * scalar, m_z * scalar);
	}
	Vec3 Vec3::operator/(float scalar) const {
		return Vec3(m_x / scalar, m_y / scalar, m_z / scalar);
	}
	Vec3 Vec3::operator-() const {
		return Vec3(-m_x, -m_y, -m_z);
	}
	
	Vec3& Vec3::operator+=(const Vec3& other) {
		return *this = *this + other;
	}
	Vec3& Vec3::operator-=(const Vec3& other) {
		return *this = *this - other;
	}
	Vec3& Vec3::operator*=(const Vec3& other) {
		return *this = *this * other;
	}
	Vec3& Vec3::operator/=(const Vec3& other) {
		return *this = *this / other;
	}
	Vec3& Vec3::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	Vec3& Vec3::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	
	bool Vec3::operator==(const Vec3& other) const {
		return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
	}
	bool Vec3::operator!=(const Vec3& other) const {
		return m_x != other.m_x || m_y != other.m_y || m_z != other.m_z;
	}
	
	float Vec3::dot(const Vec3& other) const {
		return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
	}
	Vec3 Vec3::cross(const Vec3& other) const {
		return Vec3(m_y * other.m_z - m_z * other.m_y, m_z * other.m_x - m_x * other.m_z,
			m_x * other.m_y - m_y * other.m_x);
	}
	float Vec3::magnitude() const {
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}
	Vec3 Vec3::normalize() const {
		return operator/(magnitude());
	}
	Vec3 Vec3::rotate(float angle, const Vec3& axis) const {
		float s = std::sin(angle);
		float c = std::cos(angle);
		float t = 1 - c;
		Vec3 n = axis.normalize();
		float x = this->m_x;
		float y = this->m_y;
		float z = this->m_z;
		return Vec3(
			(t * n.m_x * n.m_x + c) * x + (t * n.m_x * n.m_y - s * n.m_z) * y + (t * n.m_x * n.m_z + s * n.m_y) * z,
			(t * n.m_x * n.m_y + s * n.m_z) * x + (t * n.m_y * n.m_y + c) * y + (t * n.m_y * n.m_z - s * n.m_x) * z,
			(t * n.m_x * n.m_z - s * n.m_y) * x + (t * n.m_y * n.m_z + s * n.m_x) * y + (t * n.m_z * n.m_z + c) * z
		);
	}
	
	std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
		return os << vec.to_string();
	}
	std::string Vec3::to_string() const {
		return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ")";
	}
} // engine::math
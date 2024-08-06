#include "Vec2.hpp"
#include <cmath>

using namespace std::string_literals;

namespace engine::math {
	const Vec2 Vec2::ZERO = Vec2(0, 0);
	const Vec2 Vec2::ONE = Vec2(1, 1);
	const Vec2 Vec2::UNIT_X = Vec2(1, 0);
	const Vec2 Vec2::UNIT_Y = Vec2(0, 1);
	
	
	Vec2::Vec2() : m_x(0), m_y(0) {
	}
	Vec2::Vec2(float scalar) : m_x(scalar), m_y(scalar) {
		
	}
	Vec2::Vec2(float x, float y) : m_x(x), m_y(y) {
		
	}
	float Vec2::x() const {
		return m_x;
	}
	float Vec2::y() const {
		return m_y;
	}
	Vec2 Vec2::x(float x) const {
		return Vec2(x, m_y);
	}
	Vec2 Vec2::y(float y) const {
		return Vec2(m_x, y);
	}
	Vec2 Vec2::operator+(const Vec2& other) const {
		return Vec2(m_x + other.m_x, m_y + other.m_y);
	}
	Vec2 Vec2::operator-(const Vec2& other) const {
		return Vec2(m_x - other.m_x, m_y - other.m_y);
	}
	Vec2 Vec2::operator*(const Vec2& other) const {
		return Vec2(m_x * other.m_x, m_y * other.m_y);
	}
	Vec2 Vec2::operator/(const Vec2& other) const {
		return Vec2(m_x / other.m_x, m_y / other.m_y);
	}
	Vec2 Vec2::operator*(float scalar) const {
		return Vec2(m_x * scalar, m_y * scalar);
	}
	Vec2 Vec2::operator/(float scalar) const {
		return Vec2(m_x / scalar, m_y / scalar);
	}
	Vec2 Vec2::operator-() const {
		return Vec2(-m_x, -m_y);
	}
	
	Vec2& Vec2::operator+=(const Vec2& other) {
		return *this = *this + other;
	}
	Vec2& Vec2::operator-=(const Vec2& other) {
		return *this = *this - other;
	}
	Vec2& Vec2::operator*=(const Vec2& other) {
		return *this = *this * other;
	}
	Vec2& Vec2::operator/=(const Vec2& other) {
		return *this = *this / other;
	}
	Vec2& Vec2::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	Vec2& Vec2::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	
	bool Vec2::operator==(const Vec2& other) const {
		return m_x == other.m_x && m_y == other.m_y;
	}
	bool Vec2::operator!=(const Vec2& other) const {
		return m_x != other.m_x || m_y != other.m_y;
	}
	float Vec2::dot(const Vec2& other) const {
		return m_x * other.m_x + m_y * other.m_y;
	}
	float Vec2::cross(const Vec2& other) const {
		return m_x * other.m_y - m_y * other.m_x;
	}
	float Vec2::magnitude() const {
		return std::sqrt(m_x * m_x + m_y * m_y);
	}
	Vec2 Vec2::normalize() const {
		return operator/(magnitude());
	}
	Vec2 Vec2::rotate(float angle) const {
		float s = std::sin(angle);
		float c = std::cos(angle);
		return Vec2(m_x * c - m_y * s, m_x * s + m_y * c);
	}
	Vec2 Vec2::perpendicular() const {
		return Vec2(-m_y, m_x);
	}
	std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
		return os << vec.to_string();
	}
	std::string Vec2::to_string() const {
		return "("s + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
	}
} // engine::math
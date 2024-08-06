#include "Vec4.hpp"
#include <cmath>

using namespace std::string_literals;

namespace engine::math {
	const Vec4 Vec4::ZERO = Vec4(0, 0, 0, 0);
	const Vec4 Vec4::ONE = Vec4(1, 1, 1, 1);
	const Vec4 Vec4::UNIT_X = Vec4(1, 0, 0, 0);
	const Vec4 Vec4::UNIT_Y = Vec4(0, 1, 0, 0);
	const Vec4 Vec4::UNIT_Z = Vec4(0, 0, 1, 0);
	const Vec4 Vec4::UNIT_W = Vec4(0, 0, 0, 1);
	
	Vec4::Vec4() : m_x(0), m_y(0), m_z(0), m_w(0) {}
	Vec4::Vec4(float scalar) : m_x(scalar), m_y(scalar), m_z(scalar), m_w(scalar) {}
	Vec4::Vec4(Vec3 xyz) : m_x(xyz.x()), m_y(xyz.y()), m_z(xyz.z()), m_w(0) {}
	Vec4::Vec4(Vec3 xyz, float w) : m_x(xyz.x()), m_y(xyz.y()), m_z(xyz.z()), m_w(w) {}
	Vec4::Vec4(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {}
	
	float Vec4::x() const {
		return m_x;
	}
	float Vec4::y() const {
		return m_y;
	}
	float Vec4::z() const {
		return m_z;
	}
	float Vec4::w() const {
		return m_w;
	}
	Vec4 Vec4::x(float x) const {
		return Vec4(x, m_y, m_z, m_w);
	}
	Vec4 Vec4::y(float y) const {
		return Vec4(m_x, y, m_z, m_w);
	}
	Vec4 Vec4::z(float z) const {
		return Vec4(m_x, m_y, z, m_w);
	}
	Vec4 Vec4::w(float w) const {
		return Vec4(m_x, m_y, m_z, w);
	}
	
	Vec4 Vec4::operator+(const Vec4& other) const {
		return Vec4(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w);
	}
	Vec4 Vec4::operator-(const Vec4& other) const {
		return Vec4(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w);
	}
	Vec4 Vec4::operator*(const Vec4& other) const {
		return Vec4(m_x * other.m_x, m_y * other.m_y, m_z * other.m_z, m_w * other.m_w);
	}
	Vec4 Vec4::operator/(const Vec4& other) const {
		return Vec4(m_x / other.m_x, m_y / other.m_y, m_z / other.m_z, m_w / other.m_w);
	}
	Vec4 Vec4::operator*(float scalar) const {
		return Vec4(m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar);
	}
	Vec4 Vec4::operator/(float scalar) const {
		return Vec4(m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar);
	}
	Vec4 Vec4::operator-() const {
		return Vec4(-m_x, -m_y, -m_z, -m_w);
	}
	
	Vec4& Vec4::operator+=(const Vec4& other) {
		return *this = operator+(other);
	}
	Vec4& Vec4::operator-=(const Vec4& other) {
		return *this = operator-(other);
	}
	Vec4& Vec4::operator*=(const Vec4& other) {
		return *this = operator*(other);
	}
	Vec4& Vec4::operator/=(const Vec4& other) {
		return *this = operator/(other);
	}
	Vec4& Vec4::operator*=(float scalar) {
		return *this = operator*(scalar);
	}
	Vec4& Vec4::operator/=(float scalar) {
		return *this = operator/(scalar);
	}
	
	bool Vec4::operator==(const Vec4& other) const {
		return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z && m_w == other.m_w;
	}
	bool Vec4::operator!=(const Vec4& other) const {
		return !operator==(other);
	}
	float Vec4::dot(const Vec4& other) const {
		return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z + m_w * other.m_w;
	}
	float Vec4::magnitude() const {
		return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w);
	}
	Vec4 Vec4::normalize() const {
		return operator/(magnitude());
	}
	Vec4 Vec4::rotate(float angle, const Vec4& axis) const {
		float sinHalfAngle = std::sin(angle / 2);
		float cosHalfAngle = std::cos(angle / 2);
		
		float rX = axis.x() * sinHalfAngle;
		float rY = axis.y() * sinHalfAngle;
		float rZ = axis.z() * sinHalfAngle;
		float rW = cosHalfAngle;
		
		Vec4 rotationQ(rX, rY, rZ, rW);
		Vec4 conjugateQ(-rotationQ.x(), -rotationQ.y(), -rotationQ.z(), rotationQ.w());
		
		Vec4 w = rotationQ * (*this) * conjugateQ;
		return Vec4(w.x(), w.y(), w.z(), w.w());
	}
	std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
		return os << vec.to_string();
	}
	std::string Vec4::to_string() const {
		return "("s + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " +
			std::to_string(m_w) + ")";
	}
} // engine::math
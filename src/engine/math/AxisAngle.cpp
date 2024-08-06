#include "AxisAngle.hpp"
#include <cmath>
#include <stdexcept>

using namespace std::string_literals;

namespace engine::math {
	AxisAngle::AxisAngle() : m_x(0), m_y(0), m_z(0), m_angle(0) {
	}
	AxisAngle::AxisAngle(float x, float y, float z, float angle) : m_x(x), m_y(y), m_z(z), m_angle(angle) {
	}
	AxisAngle::AxisAngle(const Vec3& axis, float angle) : m_x(axis.x()), m_y(axis.y()), m_z(axis.z()), m_angle(angle) {
	}
	float AxisAngle::x() const {
		return m_x;
	}
	float AxisAngle::y() const {
		return m_y;
	}
	float AxisAngle::z() const {
		return m_z;
	}
	float AxisAngle::angle() const {
		return m_angle;
	}
	AxisAngle AxisAngle::x(float x) const {
		return AxisAngle(x, m_y, m_z, m_angle);
	}
	AxisAngle AxisAngle::y(float y) const {
		return AxisAngle(m_x, y, m_z, m_angle);
	}
	AxisAngle AxisAngle::z(float z) const {
		return AxisAngle(m_x, m_y, z, m_angle);
	}
	AxisAngle AxisAngle::angle(float angle) const {
		return AxisAngle(m_x, m_y, m_z, angle);
	}
	AxisAngle AxisAngle::operator+(const AxisAngle& other) const {
		Vec3 axis1 = Vec3(m_x, m_y, m_z).normalize();
		Vec3 axis2 = Vec3(other.m_x, other.m_y, other.m_z).normalize();
		if (axis1 == axis2 || axis1 == -axis2) {
			if (axis1 == axis2) {
				return angle(m_angle + other.m_angle);
			}
			else {
				return angle(m_angle - other.m_angle);
			}
		}
		
		Mat4 rotation1 = toMatrix();
		Mat4 rotation2 = other.toMatrix();
		Mat4 result = rotation1 * rotation2;
		return AxisAngle::fromMatrix(result);
	}
	AxisAngle AxisAngle::operator-(const AxisAngle& other) const {
		return operator+(-other);
	}
	AxisAngle AxisAngle::operator*(float scalar) const {
		return angle(m_angle * scalar);
	}
	AxisAngle AxisAngle::operator/(float scalar) const {
		return angle(m_angle / scalar);
	}
	AxisAngle AxisAngle::operator-() const {
		return angle(-m_angle);
	}
	AxisAngle& AxisAngle::operator+=(const AxisAngle& other) {
		return *this = *this + other;
	}
	AxisAngle& AxisAngle::operator-=(const AxisAngle& other) {
		return *this = *this - other;
	}
	AxisAngle& AxisAngle::operator*=(float scalar) {
		return *this = *this * scalar;
	}
	AxisAngle& AxisAngle::operator/=(float scalar) {
		return *this = *this / scalar;
	}
	Mat4 AxisAngle::toMatrix() const {
		const float c = std::cos(m_angle);
		const float s = std::sin(m_angle);
		const float t = 1 - c;
		const float x = m_x;
		const float y = m_y;
		const float z = m_z;
		return Mat4(
			c + x * x * t, x * y * t - z * s, x * z * t + y * s, 0,
			y * x * t + z * s, c + y * y * t, y * z * t - x * s, 0,
			z * x * t - y * s, z * y * t + x * s, c + z * z * t, 0,
			0, 0, 0, 1
		);
	}
	AxisAngle AxisAngle::fromMatrix(const Mat4& matrix) {
		const float trace = matrix[0, 0] + matrix[1, 1] + matrix[2, 2];
		if (trace > 0) {
			const float s = 0.5f / std::sqrt(trace + 1);
			return AxisAngle(
				(matrix[2, 1] - matrix[1, 2]) * s,
				(matrix[0, 2] - matrix[2, 0]) * s,
				(matrix[1, 0] - matrix[0, 1]) * s,
				std::acos(0.5f * (trace - 1))
			);
		}
		else if (matrix[0, 0] > matrix[1, 1] && matrix[0, 0] > matrix[2, 2]) {
			const float s = 2 * std::sqrt(1 + matrix[0, 0] - matrix[1, 1] - matrix[2, 2]);
			return AxisAngle(
				0.25f * s,
				(matrix[0, 1] + matrix[1, 0]) / s,
				(matrix[0, 2] + matrix[2, 0]) / s,
				(matrix[2, 1] - matrix[1, 2]) / s
			);
		}
		else if (matrix[1, 1] > matrix[2, 2]) {
			const float s = 2 * std::sqrt(1 + matrix[1, 1] - matrix[0, 0] - matrix[2, 2]);
			return AxisAngle(
				(matrix[0, 1] + matrix[1, 0]) / s,
				0.25f * s,
				(matrix[1, 2] + matrix[2, 1]) / s,
				(matrix[0, 2] - matrix[2, 0]) / s
			);
		}
		else {
			const float s = 2 * std::sqrt(1 + matrix[2, 2] - matrix[0, 0] - matrix[1, 1]);
			return AxisAngle(
				(matrix[0, 2] + matrix[2, 0]) / s,
				(matrix[1, 2] + matrix[2, 1]) / s,
				0.25f * s,
				(matrix[1, 0] - matrix[0, 1]) / s
			);
		}
	}
	Vec4 operator*(const AxisAngle& axisAngle, const Vec4& vec) {
		return axisAngle.toMatrix() * vec;
	}
	Vec4 operator*(const Vec4& vec, const AxisAngle& axisAngle) {
		return axisAngle * vec;
	}
	Vec3 operator*(const AxisAngle& axisAngle, const Vec3& vec) {
		Vec4 v4 = Vec4(vec, 1);
		Vec4 r = axisAngle * v4;
		return Vec3(r.x(), r.y(), r.z()) / r.w();
	}
	Vec3 operator*(const Vec3& vec, const AxisAngle& axisAngle) {
		return axisAngle * vec;
	}
	std::ostream& operator<<(std::ostream& os, const AxisAngle& axisAngle) {
		return os << axisAngle.to_string();
	}
	std::string AxisAngle::to_string() const {
		return "(["s + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + "], " +
			std::to_string(m_angle) + ")";
	}
} // engine::math
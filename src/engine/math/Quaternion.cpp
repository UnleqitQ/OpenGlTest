#include "Quaternion.hpp"
#include <cmath>

namespace engine {
	namespace math {
		Quaternion::Quaternion() : m_x(0), m_y(0), m_z(0), m_w(0) {
		
		}
		Quaternion::Quaternion(Vec4 vec) : m_x(vec.x()), m_y(vec.y()), m_z(vec.z()), m_w(vec.w()) {
		
		}
		Quaternion::Quaternion(float x, float y, float z, float w) : m_x(x), m_y(y), m_z(z), m_w(w) {
		
		}
		float Quaternion::x() const {
			return m_x;
		}
		float Quaternion::y() const {
			return m_y;
		}
		float Quaternion::z() const {
			return m_z;
		}
		float Quaternion::w() const {
			return m_w;
		}
		Quaternion Quaternion::x(float x) const {
			return Quaternion(x, m_y, m_z, m_w);
		}
		Quaternion Quaternion::y(float y) const {
			return Quaternion(m_x, y, m_z, m_w);
		}
		Quaternion Quaternion::z(float z) const {
			return Quaternion(m_x, m_y, z, m_w);
		}
		Quaternion Quaternion::w(float w) const {
			return Quaternion(m_x, m_y, m_z, w);
		}
		Quaternion Quaternion::operator+(const Quaternion& other) const {
			return Quaternion(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z, m_w + other.m_w);
		}
		Quaternion Quaternion::operator-(const Quaternion& other) const {
			return Quaternion(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z, m_w - other.m_w);
		}
		Quaternion Quaternion::operator*(const Quaternion& other) const {
			float x = m_w * other.m_x + m_x * other.m_w + m_y * other.m_z - m_z * other.m_y;
			float y = m_w * other.m_y - m_x * other.m_z + m_y * other.m_w + m_z * other.m_x;
			float z = m_w * other.m_z + m_x * other.m_y - m_y * other.m_x + m_z * other.m_w;
			float w = m_w * other.m_w - m_x * other.m_x - m_y * other.m_y - m_z * other.m_z;
			return Quaternion(x, y, z, w);
		}
		Quaternion Quaternion::operator*(float scalar) const {
			return Quaternion(m_x * scalar, m_y * scalar, m_z * scalar, m_w * scalar);
		}
		Quaternion Quaternion::operator/(float scalar) const {
			return Quaternion(m_x / scalar, m_y / scalar, m_z / scalar, m_w / scalar);
		}
		Quaternion Quaternion::operator-() const {
			return Quaternion(-m_x, -m_y, -m_z, -m_w);
		}
		Quaternion Quaternion::operator~() const {
			return Quaternion(-m_x, -m_y, -m_z, m_w);
		}
		
		Quaternion& Quaternion::operator+=(const Quaternion& other) {
			return *this = *this + other;
		}
		Quaternion& Quaternion::operator-=(const Quaternion& other) {
			return *this = *this - other;
		}
		Quaternion& Quaternion::operator*=(const Quaternion& other) {
			return *this = *this * other;
		}
		Quaternion& Quaternion::operator*=(float scalar) {
			return *this = *this * scalar;
		}
		Quaternion& Quaternion::operator/=(float scalar) {
			return *this = *this / scalar;
		}
		
		Vec4 Quaternion::asVec4() const {
			return Vec4(m_x, m_y, m_z, m_w);
		}
		Mat4 Quaternion::toMatrix() const {
			float xx = m_x * m_x;
			float xy = m_x * m_y;
			float xz = m_x * m_z;
			float xw = m_x * m_w;
			float yy = m_y * m_y;
			float yz = m_y * m_z;
			float yw = m_y * m_w;
			float zz = m_z * m_z;
			float zw = m_z * m_w;
			return Mat4(
				1 - 2 * (yy + zz), 2 * (xy - zw), 2 * (xz + yw), 0,
				2 * (xy + zw), 1 - 2 * (xx + zz), 2 * (yz - xw), 0,
				2 * (xz - yw), 2 * (yz + xw), 1 - 2 * (xx + yy), 0,
				0, 0, 0, 1
			);
		}
		Quaternion Quaternion::fromMatrix(const Mat4& matrix) {
			float trace = matrix[0, 0] + matrix[1, 1] + matrix[2, 2];
			if (trace > 0) {
				float s = 0.5f / std::sqrt(trace + 1);
				return Quaternion(
					(matrix[2, 1] - matrix[1, 2]) * s,
					(matrix[0, 2] - matrix[2, 0]) * s,
					(matrix[1, 0] - matrix[0, 1]) * s,
					0.25f / s
				);
			}
			else if (matrix[0, 0] > matrix[1, 1] && matrix[0, 0] > matrix[2, 2]) {
				float s = 2 * std::sqrt(1 + matrix[0, 0] - matrix[1, 1] - matrix[2, 2]);
				return Quaternion(
					0.25f * s,
					(matrix[0, 1] + matrix[1, 0]) / s,
					(matrix[0, 2] + matrix[2, 0]) / s,
					(matrix[2, 1] - matrix[1, 2]) / s
				);
			}
			else if (matrix[1, 1] > matrix[2, 2]) {
				float s = 2 * std::sqrt(1 + matrix[1, 1] - matrix[0, 0] - matrix[2, 2]);
				return Quaternion(
					(matrix[0, 1] + matrix[1, 0]) / s,
					0.25f * s,
					(matrix[1, 2] + matrix[2, 1]) / s,
					(matrix[0, 2] - matrix[2, 0]) / s
				);
			}
			else {
				float s = 2 * std::sqrt(1 + matrix[2, 2] - matrix[0, 0] - matrix[1, 1]);
				return Quaternion(
					(matrix[0, 2] + matrix[2, 0]) / s,
					(matrix[1, 2] + matrix[2, 1]) / s,
					0.25f * s,
					(matrix[0, 1] - matrix[1, 0]) / s
				);
			}
		}
		AxisAngle Quaternion::toAxisAngle() const {
			return AxisAngle::fromMatrix(toMatrix());
		}
		Quaternion Quaternion::fromAxisAngle(const AxisAngle& axisAngle) {
			return fromMatrix(axisAngle.toMatrix());
		}
		Vec4 operator*(const Quaternion& quaternion, const Vec4& vec) {
			return quaternion.toMatrix() * vec;
		}
		Vec4 operator*(const Vec4& vec, const Quaternion& quaternion) {
			return quaternion * vec;
		}
		Vec3 operator*(const Quaternion& quaternion, const Vec3& vec) {
			Vec4 v4 = Vec4(vec, 1);
			Vec4 r = quaternion * v4;
			return Vec3(r.x(), r.y(), r.z()) / r.w();
		}
		Vec3 operator*(const Vec3& vec, const Quaternion& quaternion) {
			return quaternion * vec;
		}
		std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion) {
			return os << quaternion.to_string();
		}
		std::string Quaternion::to_string() const {
			return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ", " + std::to_string(m_z) + ", " + std::to_string(m_w) + ")";
		}
	} // math
} // engine
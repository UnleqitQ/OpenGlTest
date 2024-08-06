#pragma once

#include "Mat4.hpp"
#include "Vec3.hpp"
#include <ostream>
#include <string>

namespace engine::math {
	
	class AxisAngle {
	private:
		float m_x, m_y, m_z;
		float m_angle;
	public:
		AxisAngle();
		AxisAngle(float x, float y, float z, float angle);
		AxisAngle(const Vec3& axis, float angle);
		
		AxisAngle(const AxisAngle& other) = default;
		AxisAngle(AxisAngle&& other) noexcept = default;
		AxisAngle& operator=(const AxisAngle& other) = default;
		AxisAngle& operator=(AxisAngle&& other) noexcept = default;
		~AxisAngle() = default;
		
		float x() const;
		float y() const;
		float z() const;
		float angle() const;
		
		AxisAngle x(float x) const;
		AxisAngle y(float y) const;
		AxisAngle z(float z) const;
		AxisAngle angle(float angle) const;
		
		AxisAngle operator+(const AxisAngle& other) const;
		AxisAngle operator-(const AxisAngle& other) const;
		AxisAngle operator*(float scalar) const;
		AxisAngle operator/(float scalar) const;
		AxisAngle operator-() const;
		
		AxisAngle& operator+=(const AxisAngle& other);
		AxisAngle& operator-=(const AxisAngle& other);
		AxisAngle& operator*=(float scalar);
		AxisAngle& operator/=(float scalar);
		
		Mat4 toMatrix() const;
		static AxisAngle fromMatrix(const Mat4& matrix);
		
		friend Vec4 operator*(const AxisAngle& axisAngle, const Vec4& vec);
		friend Vec4 operator*(const Vec4& vec, const AxisAngle& axisAngle);
		friend Vec3 operator*(const AxisAngle& axisAngle, const Vec3& vec);
		friend Vec3 operator*(const Vec3& vec, const AxisAngle& axisAngle);
		
		friend std::ostream& operator<<(std::ostream& os, const AxisAngle& axisAngle);
		std::string to_string() const;
	};
	
} // engine::math

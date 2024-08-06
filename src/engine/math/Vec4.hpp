#pragma once

#include "Vec3.hpp"
#include <ostream>
#include <string>

namespace engine::math {
	
	class Vec4 {
	private:
		float m_x, m_y, m_z, m_w;
	public:
		Vec4();
		Vec4(float scalar);
		Vec4(Vec3 xyz);
		Vec4(Vec3 xyz, float w);
		Vec4(float x, float y, float z, float w);
		
		Vec4(const Vec4& other) = default;
		Vec4(Vec4&& other) noexcept = default;
		Vec4& operator=(const Vec4& other) = default;
		Vec4& operator=(Vec4&& other) noexcept = default;
		~Vec4() = default;
		
		float x() const;
		float y() const;
		float z() const;
		float w() const;
		
		Vec4 x(float x) const;
		Vec4 y(float y) const;
		Vec4 z(float z) const;
		Vec4 w(float w) const;
		
		Vec4 operator+(const Vec4& other) const;
		Vec4 operator-(const Vec4& other) const;
		Vec4 operator*(const Vec4& other) const;
		Vec4 operator/(const Vec4& other) const;
		Vec4 operator*(float scalar) const;
		Vec4 operator/(float scalar) const;
		Vec4 operator-() const;
		
		Vec4& operator+=(const Vec4& other);
		Vec4& operator-=(const Vec4& other);
		Vec4& operator*=(const Vec4& other);
		Vec4& operator/=(const Vec4& other);
		Vec4& operator*=(float scalar);
		Vec4& operator/=(float scalar);
		
		bool operator==(const Vec4& other) const;
		bool operator!=(const Vec4& other) const;
		
		float dot(const Vec4& other) const;
		float magnitude() const;
		Vec4 normalize() const;
		Vec4 rotate(float angle, const Vec4& axis) const;
		
		friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);
		std::string to_string() const;
		
		static const Vec4 ZERO;
		static const Vec4 ONE;
		static const Vec4 UNIT_X;
		static const Vec4 UNIT_Y;
		static const Vec4 UNIT_Z;
		static const Vec4 UNIT_W;
	};
	
} // engine::math

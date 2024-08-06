#pragma once

#include <ostream>
#include <string>

namespace engine::math {
	
	class Vec3 {
	private:
		float m_x, m_y, m_z;
	public:
		Vec3();
		explicit Vec3(float scalar);
		Vec3(float x, float y, float z);
		
		Vec3(const Vec3& other) = default;
		Vec3(Vec3&& other) noexcept = default;
		Vec3& operator=(const Vec3& other) = default;
		Vec3& operator=(Vec3&& other) noexcept = default;
		~Vec3() = default;
		
		float x() const;
		float y() const;
		float z() const;
		
		Vec3 x(float x) const;
		Vec3 y(float y) const;
		Vec3 z(float z) const;
		
		Vec3 operator+(const Vec3& other) const;
		Vec3 operator-(const Vec3& other) const;
		Vec3 operator*(const Vec3& other) const;
		Vec3 operator/(const Vec3& other) const;
		Vec3 operator*(float scalar) const;
		Vec3 operator/(float scalar) const;
		Vec3 operator-() const;
		
		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(const Vec3& other);
		Vec3& operator/=(const Vec3& other);
		Vec3& operator*=(float scalar);
		Vec3& operator/=(float scalar);
		
		bool operator==(const Vec3& other) const;
		bool operator!=(const Vec3& other) const;
		
		float dot(const Vec3& other) const;
		Vec3 cross(const Vec3& other) const;
		float magnitude() const;
		Vec3 normalize() const;
		Vec3 rotate(float angle, const Vec3& axis) const;
		
		friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
		std::string to_string() const;
		
		static const Vec3 ZERO;
		static const Vec3 ONE;
		static const Vec3 UNIT_X;
		static const Vec3 UNIT_Y;
		static const Vec3 UNIT_Z;
	};
	
} // engine::math

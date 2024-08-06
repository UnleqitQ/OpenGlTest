#pragma once

#include <ostream>
#include <string>

namespace engine::math {
	
	class Vec2 {
	private:
		float m_x, m_y;
	public:
		Vec2();
		Vec2(float scalar);
		Vec2(float x, float y);
		
		Vec2(const Vec2& other) = default;
		Vec2(Vec2&& other) noexcept = default;
		Vec2& operator=(const Vec2& other) = default;
		Vec2& operator=(Vec2&& other) noexcept = default;
		~Vec2() = default;
		
		float x() const;
		float y() const;
		
		Vec2 x(float x) const;
		Vec2 y(float y) const;
		
		Vec2 operator+(const Vec2& other) const;
		Vec2 operator-(const Vec2& other) const;
		Vec2 operator*(const Vec2& other) const;
		Vec2 operator/(const Vec2& other) const;
		Vec2 operator*(float scalar) const;
		Vec2 operator/(float scalar) const;
		Vec2 operator-() const;
		
		Vec2& operator+=(const Vec2& other);
		Vec2& operator-=(const Vec2& other);
		Vec2& operator*=(const Vec2& other);
		Vec2& operator/=(const Vec2& other);
		Vec2& operator*=(float scalar);
		Vec2& operator/=(float scalar);
		
		bool operator==(const Vec2& other) const;
		bool operator!=(const Vec2& other) const;
		
		float dot(const Vec2& other) const;
		float cross(const Vec2& other) const;
		float magnitude() const;
		Vec2 normalize() const;
		Vec2 rotate(float angle) const;
		Vec2 perpendicular() const;
		
		friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);
		std::string to_string() const;
		
		static const Vec2 ZERO;
		static const Vec2 ONE;
		static const Vec2 UNIT_X;
		static const Vec2 UNIT_Y;
	};
	
} // engine::math

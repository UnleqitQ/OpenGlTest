#pragma once
#include "Vec2.hpp"
#include <ostream>
#include <string>

namespace engine::math {
	
	class Mat2 {
	private:
		float m_v[4];
	public:
		Mat2();
		Mat2(float values[4]);
		explicit Mat2(float value);
		Mat2(float m00, float m01, float m10, float m11);
		
		Mat2(const Mat2& other) = default;
		Mat2(Mat2&& other) noexcept = default;
		Mat2& operator=(const Mat2& other) = default;
		Mat2& operator=(Mat2&& other) noexcept = default;
		~Mat2() = default;
		
		float operator[](int index) const;
		float operator[](int row, int column) const;
		
		Mat2 operator()(int index, float value) const;
		Mat2 operator()(int row, int column, float value) const;
		
		float m00() const;
		float m01() const;
		float m10() const;
		float m11() const;
		
		const float* const data() const;
		
		Mat2 operator+(const Mat2& other) const;
		Mat2 operator-(const Mat2& other) const;
		Mat2 operator*(const Mat2& other) const;
		Mat2 operator-() const;
		Mat2 operator~() const;
		
		Mat2 operator*(float scalar) const;
		Mat2 operator/(float scalar) const;
		
		Mat2& operator+=(const Mat2& other);
		Mat2& operator-=(const Mat2& other);
		Mat2& operator*=(float scalar);
		Mat2& operator/=(float scalar);
		
		bool operator==(const Mat2& other) const;
		bool operator!=(const Mat2& other) const;
		
		float determinant() const;
		Mat2 inverse() const;
		
		friend Vec2 operator*(const Mat2& matrix, const Vec2& vector);
		friend Vec2 operator*(const Vec2& vector, const Mat2& matrix);
		
		static Mat2 identity();
		
		friend std::ostream& operator<<(std::ostream& os, const Mat2& matrix);
		std::string to_string(bool pretty = false) const;
	};
	
} // engine::math

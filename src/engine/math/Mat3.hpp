#pragma once

#include <ostream>
#include <string>
#include "Vec3.hpp"

namespace engine::math {
	
	class Mat3 {
	private:
		float m_v[9];
	public:
		Mat3();
		Mat3(float values[9]);
		explicit Mat3(float value);
		Mat3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);
		
		Mat3(const Mat3& other) = default;
		Mat3(Mat3&& other) noexcept = default;
		Mat3& operator=(const Mat3& other) = default;
		Mat3& operator=(Mat3&& other) noexcept = default;
		~Mat3() = default;
		
		float operator[](int index) const;
		float operator[](int row, int column) const;
		
		Mat3 operator()(int index, float value) const;
		Mat3 operator()(int row, int column, float value) const;
		
		float m00() const;
		float m01() const;
		float m02() const;
		float m10() const;
		float m11() const;
		float m12() const;
		float m20() const;
		float m21() const;
		float m22() const;
		
		const float* const data() const;
		
		Mat3 operator+(const Mat3& other) const;
		Mat3 operator-(const Mat3& other) const;
		Mat3 operator*(const Mat3& other) const;
		Mat3 operator-() const;
		Mat3 operator~() const;
		
		Mat3 operator*(float scalar) const;
		Mat3 operator/(float scalar) const;
		
		Mat3& operator+=(const Mat3& other);
		Mat3& operator-=(const Mat3& other);
		Mat3& operator*=(float scalar);
		Mat3& operator/=(float scalar);
		
		bool operator==(const Mat3& other) const;
		bool operator!=(const Mat3& other) const;
		
		float determinant() const;
		Mat3 inverse() const;
		
		friend Vec3 operator*(const Mat3& matrix, const Vec3& vector);
		friend Vec3 operator*(const Vec3& vector, const Mat3& matrix);
		
		static Mat3 identity();
		
		// We don't need transformation matrices here as they are done with 4x4 matrices
		
		friend std::ostream& operator<<(std::ostream& os, const Mat3& matrix);
		std::string to_string(bool pretty = false) const;
	};
	
} // engine::math

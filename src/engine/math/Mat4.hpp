#pragma once
#include "Vec4.hpp"
#include "Vec3.hpp"
#include <ostream>
#include <string>


namespace engine::math {
	
	class Mat4 {
	private:
		float m_v[16];
	public:
		Mat4();
		Mat4(float values[16]);
		explicit Mat4(float value);
		Mat4(float m00, float m01, float m02, float m03,
			 float m10, float m11, float m12, float m13,
			 float m20, float m21, float m22, float m23,
			 float m30, float m31, float m32, float m33);
		
		Mat4(const Mat4& other) = default;
		Mat4(Mat4&& other) noexcept = default;
		Mat4& operator=(const Mat4& other) = default;
		Mat4& operator=(Mat4&& other) noexcept = default;
		~Mat4() = default;
		
		float operator[](int index) const;
		float operator[](int row, int column) const;
		
		Mat4 operator()(int index, float value) const;
		Mat4 operator()(int row, int column, float value) const;
		
		float m00() const;
		float m01() const;
		float m02() const;
		float m03() const;
		float m10() const;
		float m11() const;
		float m12() const;
		float m13() const;
		float m20() const;
		float m21() const;
		float m22() const;
		float m23() const;
		float m30() const;
		float m31() const;
		float m32() const;
		float m33() const;
		
		const float* const data() const;
		
		Mat4 operator+(const Mat4& other) const;
		Mat4 operator-(const Mat4& other) const;
		Mat4 operator*(const Mat4& other) const;
		Mat4 operator-() const;
		Mat4 operator~() const;
		
		Mat4 operator*(float scalar) const;
		Mat4 operator/(float scalar) const;
		
		Mat4& operator+=(const Mat4& other);
		Mat4& operator-=(const Mat4& other);
		Mat4& operator*=(float scalar);
		Mat4& operator/=(float scalar);
		
		bool operator==(const Mat4& other) const;
		bool operator!=(const Mat4& other) const;
		
		float determinant() const;
		Mat4 inverse() const;
		
		friend Vec4 operator*(const Mat4& matrix, const Vec4& vector);
		friend Vec4 operator*(const Vec4& vector, const Mat4& matrix);
		friend Vec3 operator*(const Mat4& matrix, const Vec3& vector);
		friend Vec3 operator*(const Vec3& vector, const Mat4& matrix);
		
		static Mat4 identity();
		
		static Mat4 translation(float x, float y, float z);
		static Mat4 translation(const Vec3& translation);
		static Mat4 rotation(float angle, float x, float y, float z);
		static Mat4 rotation(float angle, const Vec3& axis);
		static Mat4 scale(float x, float y, float z);
		static Mat4 scale(const Vec3& scale);
		static Mat4 perspective(float fov, float aspect, float near, float far);
		static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
		static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
		
		friend std::ostream& operator<<(std::ostream& os, const Mat4& matrix);
		std::string to_string(bool pretty = false) const;
	};
} // engine::math

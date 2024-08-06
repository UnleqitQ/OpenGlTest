#pragma once

#include "Vec3.hpp"
#include "Vec4.hpp"
#include "Mat4.hpp"
#include "AxisAngle.hpp"
#include <ostream>
#include <string>

namespace engine {
	namespace math {
		
		class Quaternion {
		private:
			float m_x, m_y, m_z, m_w;
		public:
			Quaternion();
			explicit Quaternion(Vec4 vec);
			Quaternion(float x, float y, float z, float w);
			
			Quaternion(const Quaternion& other) = default;
			Quaternion(Quaternion&& other) noexcept = default;
			Quaternion& operator=(const Quaternion& other) = default;
			Quaternion& operator=(Quaternion&& other) noexcept = default;
			~Quaternion() = default;
			
			float x() const;
			float y() const;
			float z() const;
			float w() const;
			
			Quaternion x(float x) const;
			Quaternion y(float y) const;
			Quaternion z(float z) const;
			Quaternion w(float w) const;
			
			Quaternion operator+(const Quaternion& other) const;
			Quaternion operator-(const Quaternion& other) const;
			Quaternion operator*(const Quaternion& other) const;
			Quaternion operator*(float scalar) const;
			Quaternion operator/(float scalar) const;
			Quaternion operator-() const;
			Quaternion operator~() const;
			
			Quaternion& operator+=(const Quaternion& other);
			Quaternion& operator-=(const Quaternion& other);
			Quaternion& operator*=(const Quaternion& other);
			Quaternion& operator*=(float scalar);
			Quaternion& operator/=(float scalar);
			
			Vec4 asVec4() const;
			
			Mat4 toMatrix() const;
			static Quaternion fromMatrix(const Mat4& matrix);
			
			AxisAngle toAxisAngle() const;
			static Quaternion fromAxisAngle(const AxisAngle& axisAngle);
			
			friend Vec4 operator*(const Quaternion& quaternion, const Vec4& vec);
			friend Vec4 operator*(const Vec4& vec, const Quaternion& quaternion);
			friend Vec3 operator*(const Quaternion& quaternion, const Vec3& vec);
			friend Vec3 operator*(const Vec3& vec, const Quaternion& quaternion);
			
			friend std::ostream& operator<<(std::ostream& os, const Quaternion& quaternion);
			std::string to_string() const;
		};
	} // math
} // engine

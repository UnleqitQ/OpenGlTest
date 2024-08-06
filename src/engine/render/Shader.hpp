#pragma once

#include <vector>
#include <string>

#include "../math/Mat2.hpp"
#include "../math/Mat3.hpp"
#include "../math/Mat4.hpp"
#include "../math/Vec2.hpp"
#include "../math/Vec3.hpp"
#include "../math/Vec4.hpp"

namespace engine {
	
	class Shader {
	private:
		unsigned int m_id;
	
	public:
		Shader();
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		
		Shader(const Shader&) = default;
		Shader(Shader&&) = default;
		Shader& operator=(const Shader&) = default;
		Shader& operator=(Shader&&) = default;
		~Shader() = default;
		
		void use() const;
		void release() const;
		
		void destroy() const;
		
		void set_bool(const std::string& name, bool value) const;
		void set_bool(const std::string& name, const std::vector<bool>& value) const;
		void set_int(const std::string& name, int value) const;
		void set_int(const std::string& name, const std::vector<int>& value) const;
		void set_uint(const std::string& name, unsigned int value) const;
		void set_uint(const std::string& name, const std::vector<unsigned int>& value) const;
		void set_float(const std::string& name, float value) const;
		void set_float(const std::string& name, const std::vector<float>& value) const;
		
		void set_vec2(const std::string& name, const math::Vec2& value) const;
		void set_vec3(const std::string& name, const math::Vec3& value) const;
		void set_vec4(const std::string& name, const math::Vec4& value) const;
		
		void set_mat2(const std::string& name, const math::Mat2& value) const;
		void set_mat3(const std::string& name, const math::Mat3& value) const;
		void set_mat4(const std::string& name, const math::Mat4& value) const;
	
	private:
		int getUniformLocation(const std::string& name) const;
		
		static std::vector<Shader> s_shaders;
	public:
		static void destroyAll();
	};
	
} // engine

#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "GL/glew.h"

static std::string read_file(const std::string& path) {
	std::string content;
	std::ifstream file(path);
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		std::stringstream stream;
		stream << file.rdbuf();
		file.close();
		content = stream.str();
	}
	catch (std::ifstream::failure e) {
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}
	return content;
}

namespace engine {
	std::vector<Shader> Shader::s_shaders;
	Shader::Shader() : m_id(0) {
	}
	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
		std::string vertexSource = read_file(vertexPath);
		std::string fragmentSource = read_file(fragmentPath);
		
		// Compile shaders
		unsigned int vertexId, fragmentId;
		
		// Vertex shader_col_3d
		{
			const char* vertexSourceCStr = vertexSource.c_str();
			vertexId = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexId, 1, &vertexSourceCStr, nullptr);
			glCompileShader(vertexId);
			
			int success;
			char infoLog[512];
			glGetShaderiv(vertexId, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(vertexId, 512, nullptr, infoLog);
				std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}
		// Fragment shader_col_3d
		{
			const char* fragmentSourceCStr = fragmentSource.c_str();
			fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentId, 1, &fragmentSourceCStr, nullptr);
			glCompileShader(fragmentId);
			
			int success;
			char infoLog[512];
			glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(fragmentId, 512, nullptr, infoLog);
				std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			}
		}
		
		// Link shaders
		m_id = glCreateProgram();
		glAttachShader(m_id, vertexId);
		glAttachShader(m_id, fragmentId);
		glLinkProgram(m_id);
		
		// Check program
		int success;
		char infoLog[512];
		glGetProgramiv(m_id, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
			std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		
		// Delete shaders
		glDeleteShader(vertexId);
		glDeleteShader(fragmentId);
		
		s_shaders.push_back(*this);
	}
	void Shader::use() const {
		glUseProgram(m_id);
	}
	void Shader::release() const {
		glUseProgram(0);
	}
	void Shader::destroy() const {
		std::cout << "Destroying shader_col_3d " << m_id << std::endl;
		glDeleteProgram(m_id);
		erase_if(s_shaders, [this](const Shader& shader) {
			return shader.m_id == m_id;
		});
	}
	
	void Shader::set_bool(const std::string& name, bool value) const {
		glUniform1i(getUniformLocation(name), (int) value);
	}
	void Shader::set_bool(const std::string& name, const std::vector<bool>& value) const {
		std::vector<int> intValues(value.size());
		for (size_t i = 0; i < value.size(); i++) {
			intValues[i] = (int) value[i];
		}
		glUniform1iv(getUniformLocation(name), intValues.size(), intValues.data());
	}
	void Shader::set_int(const std::string& name, int value) const {
		glUniform1i(getUniformLocation(name), value);
	}
	void Shader::set_int(const std::string& name, const std::vector<int>& value) const {
		glUniform1iv(getUniformLocation(name), value.size(), value.data());
	}
	void Shader::set_uint(const std::string& name, unsigned int value) const {
		glUniform1ui(getUniformLocation(name), value);
	}
	void Shader::set_uint(const std::string& name, const std::vector<unsigned int>& value) const {
		glUniform1uiv(getUniformLocation(name), value.size(), value.data());
	}
	void Shader::set_float(const std::string& name, float value) const {
		glUniform1f(getUniformLocation(name), value);
	}
	void Shader::set_float(const std::string& name, const std::vector<float>& value) const {
		glUniform1fv(getUniformLocation(name), value.size(), value.data());
	}
	
	void Shader::set_vec2(const std::string& name, const math::Vec2& value) const {
		glUniform2f(getUniformLocation(name), value.x(), value.y());
	}
	void Shader::set_vec3(const std::string& name, const math::Vec3& value) const {
		glUniform3f(getUniformLocation(name), value.x(), value.y(), value.z());
	}
	void Shader::set_vec4(const std::string& name, const math::Vec4& value) const {
		glUniform4f(getUniformLocation(name), value.x(), value.y(), value.z(), value.w());
	}
	
	void Shader::set_mat2(const std::string& name, const math::Mat2& value) const {
		glUniformMatrix2fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	void Shader::set_mat3(const std::string& name, const math::Mat3& value) const {
		glUniformMatrix3fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	void Shader::set_mat4(const std::string& name, const math::Mat4& value) const {
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_TRUE, value.data());
	}
	int Shader::getUniformLocation(const std::string& name) const {
		return glGetUniformLocation(m_id, name.c_str());
	}
	void Shader::destroyAll() {
		while (!s_shaders.empty()) {
			s_shaders.back().destroy();
		}
	}
} // engine
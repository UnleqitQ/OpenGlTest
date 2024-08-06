#include "Material.hpp"

#include <iostream>

#include "GL/glew.h"

#include "../../vendor/stb/stb_image.h"

namespace engine::render {
	std::vector<Material> Material::s_materials;
	
	Material::Material()
		: m_id(0), m_texture() {
	}
	Material::Material(graphics::Texture& texture)
		: m_id(0), m_texture(texture) {
		
		if (texture.loaded()) {
			glGenTextures(1, &m_id);
			glBindTexture(GL_TEXTURE_2D, m_id);
			GLint internalFormat = GL_RGBA;
			GLenum format = texture.channels() == 3 ? GL_RGB : GL_RGBA;
			GLenum type = GL_UNSIGNED_BYTE;
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, texture.width(), texture.height(), 0, format, type,
				texture.data());
			glGenerateMipmap(GL_TEXTURE_2D);
			
			// Set the texture wrapping/filtering options (on the currently bound texture object).
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			std::cout << "Loaded texture into OpenGL: " << texture.path() << std::endl;
		}
		else {
			std::cerr << "Texture is not loaded: " << texture.path() << std::endl;
		}
	}
	void Material::destroy() const {
		glDeleteTextures(1, &m_id);
		
		erase_if(s_materials, [this](const Material& material) {
			return m_id == material.m_id;
		});
	}
	unsigned int Material::id() const {
		return m_id;
	}
	graphics::Texture Material::texture() const {
		return m_texture;
	}
	void Material::destroyAll() {
		while (!s_materials.empty()) {
			s_materials.back().destroy();
		}
	}
} // engine::render
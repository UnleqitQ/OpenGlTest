#include "Texture.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "../../vendor/stb/stb_image.h"

namespace engine::graphics {
	std::vector<Texture> Texture::s_textures;
	
	Texture::Texture()
		: m_path(""), m_width(0), m_height(0), m_channels(0), m_data(nullptr) {
	}
	Texture::Texture(const std::string& path)
		: m_path(path), m_width(0), m_height(0), m_channels(0), m_data(nullptr) {
	}
	Texture& Texture::load(int channels) {
		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(m_path.c_str(), &m_width, &m_height, nullptr, channels);
		m_channels = channels;
		if (m_data) {
			std::cout << "Loaded texture [" << m_width << "x" << m_height << ", " << m_channels << " channels]: " << m_path
				<< std::endl;
		}
		else {
			std::cerr << "Failed to load texture: " << m_path << std::endl;
		}
		
		s_textures.push_back(*this);
		
		return *this;
	}
	void Texture::destroy() {
		std::cout << "Destroying texture: " << m_path << std::endl;
		
		stbi_image_free(m_data);
		
		erase_if(s_textures, [this](const Texture& texture) {
			return texture.m_data == m_data;
		});
		
		m_data = nullptr;
	}
	bool Texture::loaded() const {
		return m_data != nullptr;
	}
	const std::string& Texture::path() const {
		return m_path;
	}
	const int Texture::width() const {
		return m_width;
	}
	const int Texture::height() const {
		return m_height;
	}
	const int Texture::channels() const {
		return m_channels;
	}
	const unsigned char* Texture::data() const {
		return m_data;
	}
	void Texture::destroyAll() {
		while (s_textures.size() > 0) {
			Texture texture = s_textures.back();
			texture.destroy();
		}
	}
	const math::Vec4 Texture::getPixel(int x, int y) const {
		if (!m_data) {
			return math::Vec4::ZERO;
		}
		
		int index = (y * m_width + x) * m_channels;
		
		float r = m_data[index + 0] / 255.0f;
		float g = m_data[index + 1] / 255.0f;
		float b = m_data[index + 2] / 255.0f;
		float a = m_channels == 4 ? m_data[index + 3] / 255.0f : 1.0f;
		
		return math::Vec4(r, g, b, a);
	}
	const math::Vec4 Texture::sample(float u, float v) const {
		int x = std::clamp(static_cast<int>(u * m_width), 0, m_width - 1);
		int y = std::clamp(static_cast<int>(v * m_height), 0, m_height - 1);
		return getPixel(x, y);
	}
	const math::Vec4 Texture::sample(const math::Vec2& uv) const {
		return sample(uv.x(), uv.y());
	}
	const math::Vec4 Texture::operator[](const math::Vec2& uv) const {
		return sample(uv.x(), uv.y());
	}
} // engine::graphics

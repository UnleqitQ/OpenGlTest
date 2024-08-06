#pragma once

#include <string>
#include <vector>
#include "../math/Vec4.hpp"
#include "../math/Vec2.hpp"

namespace engine::graphics {
	
	class Texture {
	private:
		std::string m_path;
		int m_width;
		int m_height;
		int m_channels;
		unsigned char* m_data;
		
	public:
		Texture();
		Texture(const std::string& path);
		
		Texture(const Texture& other) = default;
		Texture(Texture&& other) noexcept = default;
		Texture& operator=(const Texture& other) = default;
		Texture& operator=(Texture&& other) noexcept = default;
		~Texture() = default;
		
		Texture& load(int channels = 4);
		void destroy();
		
		bool loaded() const;
		
		const std::string& path() const;
		const int width() const;
		const int height() const;
		const int channels() const;
		const unsigned char* data() const;
		
		const math::Vec4 getPixel(int x, int y) const;
		const math::Vec4 sample(float u, float v) const;
		const math::Vec4 sample(const math::Vec2& uv) const;
		const math::Vec4 operator[](const math::Vec2& uv) const;
		
	private:
		static std::vector<Texture> s_textures;
		
	public:
		static void destroyAll();
	};
	
} // engine::graphics

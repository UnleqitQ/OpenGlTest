#pragma once

#include <string>
#include <vector>

#include "../graphics/Texture.hpp"

namespace engine::render {
	
	class Material {
	private:
		unsigned int m_id;
		graphics::Texture m_texture;
	public:
		Material();
		Material(graphics::Texture& texture);
		
		Material(const Material&) = default;
		Material(Material&&) = default;
		Material& operator=(const Material&) = default;
		Material& operator=(Material&&) = default;
		~Material() = default;
		
		void destroy() const;
		
		unsigned int id() const;
		graphics::Texture texture() const;
	private:
		static std::vector<Material> s_materials;
	
	public:
		static void destroyAll();
	};
	
} // engine::render

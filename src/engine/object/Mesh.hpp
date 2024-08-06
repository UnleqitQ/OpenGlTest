#pragma once

#include <vector>
#include "../math/Mat4.hpp"
#include "../math/Vec2.hpp"
#include "../math/Vec3.hpp"
#include "../math/Vec4.hpp"
#include "../graphics/Texture.hpp"

namespace engine::render {
	
	struct Vertex {
		math::Vec3 position;
		math::Vec2 texCoord;
	};
	
	class Mesh {
	private:
		// Data
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;
		
		// OpenGL
		unsigned int m_vao, m_vbo, m_ibo;
	
	public:
		Mesh();
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		
		Mesh(const Mesh& other) = default;
		Mesh(Mesh&& other) noexcept = default;
		Mesh& operator=(const Mesh& other) = default;
		Mesh& operator=(Mesh&& other) noexcept = default;
		~Mesh() = default;
		
		void draw() const;
		
		const std::vector<Vertex>& vertices() const;
		const std::vector<unsigned int>& indices() const;
		
		unsigned int vao() const;
		unsigned int vbo() const;
		unsigned int ibo() const;
		
		void destroy() const;
		
		static Mesh fromHeightmap(graphics::Texture& heightmap, float height_scale, int width, int height);
	
	private:
		static std::vector<Mesh> s_meshes;
	public:
		static void destroyAll();
	};
	
} // engine::render

#include "Mesh.hpp"

#include <iostream>
#include "GL/glew.h"

namespace engine::render {
	std::vector<Mesh> Mesh::s_meshes;
	Mesh::Mesh() : m_vertices(), m_indices(), m_vao(0), m_vbo(0), m_ibo(0) {
	}
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
		: m_vertices(vertices), m_indices(indices) {
		glGenVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);
		
		glGenBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		float data[vertices.size() * 5];
		for (size_t i = 0; i < vertices.size(); i++) {
			data[i * 5 + 0] = vertices[i].position.x();
			data[i * 5 + 1] = vertices[i].position.y();
			data[i * 5 + 2] = vertices[i].position.z();
			data[i * 5 + 3] = vertices[i].texCoord.x();
			data[i * 5 + 4] = vertices[i].texCoord.y();
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
		
		glGenBuffers(1, &m_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		
		glBindVertexArray(0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		s_meshes.push_back(*this);
	}
	
	void Mesh::draw() const {
		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
		
		glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
		
		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
	const std::vector<Vertex>& Mesh::vertices() const {
		return m_vertices;
	}
	const std::vector<unsigned int>& Mesh::indices() const {
		return m_indices;
	}
	unsigned int Mesh::vao() const {
		return m_vao;
	}
	unsigned int Mesh::vbo() const {
		return m_vbo;
	}
	unsigned int Mesh::ibo() const {
		return m_ibo;
	}
	void Mesh::destroy() const {
		std::cout << "Destroying mesh (vao=" << m_vao << ", vbo=" << m_vbo << ", ibo=" << m_ibo << ")" << std::endl;
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ibo);
		
		erase_if(s_meshes, [this](const Mesh& mesh) {
			return mesh.m_vao == m_vao;
		});
	}
	
	Mesh Mesh::fromHeightmap(graphics::Texture& heightmap, float height_scale, int width, int height) {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		for (int y0 = 0; y0 < height; y0++) {
			for (int x0 = 0; x0 < width; x0++) {
				float u = (float) x0 / (width - 1);
				float v = (float) y0 / (height - 1);
				float x = u * 2.0f - 1.0f;
				float y = v * 2.0f - 1.0f;
				float z = 0.0f;
				math::Vec4 s = heightmap.sample(u, v) * 2.0f - 1.0f;
				float h = s.x() * height_scale;
				vertices.push_back(Vertex(math::Vec3(x, y, z + h), math::Vec2(u, v)));
			}
		}
		for (int z = 0; z < height - 1; z++) {
			for (int x = 0; x < width - 1; x++) {
				indices.push_back(z * width + x);
				indices.push_back(z * width + x + 1);
				indices.push_back((z + 1) * width + x);
				indices.push_back((z + 1) * width + x);
				indices.push_back(z * width + x + 1);
				indices.push_back((z + 1) * width + x + 1);
			}
		}
		return Mesh(vertices, indices);
	}
	
	void Mesh::destroyAll() {
		while (!s_meshes.empty()) {
			s_meshes.back().destroy();
		}
	}
} // engine::render
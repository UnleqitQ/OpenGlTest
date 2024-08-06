#pragma once

#include "Mesh.hpp"
#include "../math/Vec3.hpp"
#include "../math/Vec4.hpp"
#include "../math/Mat4.hpp"
#include "Renderable.hpp"

namespace engine::object {
	
	class Object : public Renderable {
	private:
		render::Mesh m_mesh;
		math::Vec3 m_position;
		math::Vec3 m_rotation;
		math::Vec3 m_scale;
		math::Vec4 m_albedo;
	public:
		Object();
		Object(const render::Mesh& mesh);
		
		Object(const Object& other) = default;
		Object(Object&& other) noexcept = default;
		Object& operator=(const Object& other) = default;
		Object& operator=(Object&& other) noexcept = default;
		~Object() = default;
		
		const render::Mesh& mesh() const;
		const math::Vec3& position() const;
		const math::Vec3& rotation() const;
		const math::Vec3& scale() const;
		const math::Vec4& albedo() const;
		
		render::Mesh& mesh();
		math::Vec3& position();
		math::Vec3& rotation();
		math::Vec3& scale();
		math::Vec4& albedo();
		
		const math::Mat4 model() const;
		
		const render::Mesh get_mesh() const override {
			return m_mesh;
		}
		const math::Vec4 get_albedo() const override {
			return m_albedo;
		}
		const math::Mat4 get_model() const override {
			return model();
		}
	};
	
} // engine::object

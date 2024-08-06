#include "Object.hpp"

namespace engine::object {
	Object::Object()
		: m_mesh(), m_position(), m_rotation(), m_scale(), m_albedo() {
	}
	Object::Object(const render::Mesh& mesh)
		: m_mesh(mesh), m_position(math::Vec3::ZERO), m_rotation(math::Vec3::ZERO),
		m_scale(math::Vec3::ONE), m_albedo(math::Vec3::ONE) {
	}
	const render::Mesh& Object::mesh() const {
		return m_mesh;
	}
	const math::Vec3& Object::position() const {
		return m_position;
	}
	const math::Vec3& Object::rotation() const {
		return m_rotation;
	}
	const math::Vec3& Object::scale() const {
		return m_scale;
	}
	const math::Vec4& Object::albedo() const {
		return m_albedo;
	}
	render::Mesh& Object::mesh() {
		return m_mesh;
	}
	math::Vec3& Object::position() {
		return m_position;
	}
	math::Vec3& Object::rotation() {
		return m_rotation;
	}
	math::Vec3& Object::scale() {
		return m_scale;
	}
	math::Vec4& Object::albedo() {
		return m_albedo;
	}
	const math::Mat4 Object::model() const {
		math::Mat4 rot_x = math::Mat4::rotation(m_rotation.x(), math::Vec3::UNIT_X);
		math::Mat4 rot_y = math::Mat4::rotation(m_rotation.y(), math::Vec3::UNIT_Y);
		math::Mat4 rot_z = math::Mat4::rotation(m_rotation.z(), math::Vec3::UNIT_Z);
		math::Mat4 scale = math::Mat4::scale(m_scale);
		math::Mat4 translation = math::Mat4::translation(m_position);
		math::Mat4 rotation = rot_x * rot_y * rot_z;
		math::Mat4 model = translation * rotation * scale;
		return model;
	}
} // engine::object
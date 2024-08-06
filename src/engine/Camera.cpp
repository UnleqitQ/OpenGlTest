#include "Camera.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

static const float DEFAULT_FOV = 60.0f;
static const float DEFAULT_ASPECT_RATIO = 1.0f;
static const float DEFAULT_NEAR_CLIP = 0.1f;
static const float DEFAULT_FAR_CLIP = 1000.0f;

namespace engine {
	Camera::Camera()
		: m_fov(DEFAULT_FOV), m_aspect_ratio(DEFAULT_ASPECT_RATIO), m_near_clip(DEFAULT_NEAR_CLIP),
		m_far_clip(DEFAULT_FAR_CLIP),
		m_position(), m_rotation(), m_last_mouse_pos() {
	}
	Camera::Camera(float fov, float aspect_ratio, float near_clip, float far_clip)
		: m_fov(fov), m_aspect_ratio(aspect_ratio), m_near_clip(near_clip), m_far_clip(far_clip),
		m_position(), m_rotation(), m_last_mouse_pos() {
	}
	
	Camera& Camera::move(const math::Vec3& offset) {
		m_position += offset;
		return *this;
	}
	Camera& Camera::set_position(const math::Vec3& position) {
		m_position = position;
		return *this;
	}
	Camera& Camera::move_relative(const math::Vec3& offset) {
		return move(forward() * offset.z() + right() * offset.x() + up() * offset.y());
	}
	
	Camera& Camera::rotate(const math::Vec3& rotation) {
		math::Vec3 new_rotation = m_rotation + rotation;
		if (new_rotation.x() > M_PI / 2)
			new_rotation = new_rotation.x(M_PI / 2);
		if (new_rotation.x() < -M_PI / 2)
			new_rotation = new_rotation.x(-M_PI / 2);
		m_rotation = new_rotation;
		return *this;
	}
	Camera& Camera::set_rotation(const math::Vec3& rotation) {
		m_rotation = rotation;
		return *this;
	}
	
	const math::Vec3& Camera::position() const {
		return m_position;
	}
	const math::Vec3& Camera::rotation() const {
		return m_rotation;
	}
	math::Vec3& Camera::position() {
		return m_position;
	}
	math::Vec3& Camera::rotation() {
		return m_rotation;
	}
	
	void Camera::reset_mouse_pos() {
		double x, y;
		glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
		m_last_mouse_pos = math::Vec2(x, y);
	}
	
	void Camera::update(std::chrono::milliseconds delta_time) {
		math::Vec2 mp;
		{
			double x, y;
			glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
			mp = math::Vec2(x, y);
		}
		
		math::Vec2 md = mp - m_last_mouse_pos;
		m_last_mouse_pos = mp;
		
		rotate(math::Vec3(md.y(), md.x(), 0) * 0.01f);
		
		math::Vec3 movement;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
			movement -= math::Vec3::UNIT_Z;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
			movement += math::Vec3::UNIT_Z;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
			movement -= math::Vec3::UNIT_X;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
			movement += math::Vec3::UNIT_X;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
			movement += math::Vec3::UNIT_Y;
		if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			movement -= math::Vec3::UNIT_Y;
		
		math::Mat4 rotation_y = rot_y_matrix();
		movement = movement * rotation_y;
		move(movement * 0.1f);
	}
	
	float Camera::fov() const {
		return m_fov;
	}
	float Camera::aspect_ratio() const {
		return m_aspect_ratio;
	}
	float Camera::near_clip() const {
		return m_near_clip;
	}
	float Camera::far_clip() const {
		return m_far_clip;
	}
	Camera& Camera::fov(float fov) {
		m_fov = fov;
		return *this;
	}
	Camera& Camera::aspect_ratio(float aspect_ratio) {
		m_aspect_ratio = aspect_ratio;
		return *this;
	}
	Camera& Camera::near_clip(float near_clip) {
		m_near_clip = near_clip;
		return *this;
	}
	Camera& Camera::far_clip(float far_clip) {
		m_far_clip = far_clip;
		return *this;
	}
	
	math::Vec3 Camera::forward() const {
		math::Mat4 rotation_matrix = rot_matrix();
		return math::Vec3::UNIT_Z * rotation_matrix;
	}
	math::Vec3 Camera::right() const {
		math::Mat4 rotation_matrix = rot_matrix();
		return math::Vec3::UNIT_X * rotation_matrix;
	}
	math::Vec3 Camera::up() const {
		math::Mat4 rotation_matrix = rot_matrix();
		return math::Vec3::UNIT_Y * rotation_matrix;
	}
	
	math::Mat4 Camera::projection_matrix() const {
		return math::Mat4::perspective(m_fov, m_aspect_ratio, m_near_clip, m_far_clip);
	}
	math::Mat4 Camera::view_matrix() const {
		math::Mat4 rotation_matrix = rot_matrix();
		math::Mat4 translation_matrix = trans_matrix();
		return rotation_matrix * translation_matrix;
	}
	
	math::Mat4 Camera::trans_matrix() const {
		return math::Mat4::translation(-m_position);
	}
	math::Mat4 Camera::rot_x_matrix() const {
		return math::Mat4::rotation(m_rotation.x(), math::Vec3::UNIT_X);
	}
	math::Mat4 Camera::rot_y_matrix() const {
		return math::Mat4::rotation(m_rotation.y(), math::Vec3::UNIT_Y);
	}
	math::Mat4 Camera::rot_z_matrix() const {
		return math::Mat4::rotation(m_rotation.z(), math::Vec3::UNIT_Z);
	}
	math::Mat4 Camera::rot_matrix() const {
		math::Mat4 rot_x = rot_x_matrix();
		math::Mat4 rot_y = rot_y_matrix();
		math::Mat4 rot_z = rot_z_matrix();
		
		// Order of multiplication is important
		// We want to rotate around the x-axis first, then the y-axis, then the z-axis
		return rot_x * rot_y * rot_z;
	}
	std::ostream& operator<<(std::ostream& os, const Camera& c) {
		return os << "Camera{position=" << c.m_position << ", rotation=" << c.m_rotation << ", fov=" << c.m_fov
			<< ", aspect_ratio=" << c.m_aspect_ratio << ", near_clip=" << c.m_near_clip << ", far_clip=" << c.m_far_clip
			<< "}";
	}
	std::string Camera::to_string() const {
		return "[" + m_position.to_string() + ", " + m_rotation.to_string() + ", " + std::to_string(m_fov) + ", ("
			+ std::to_string(m_aspect_ratio) + ", " + std::to_string(m_near_clip) + ", " + std::to_string(m_far_clip)
			+ ")]";
	}
} // engine
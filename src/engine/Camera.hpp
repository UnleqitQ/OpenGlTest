#pragma once

#include "math/Vec3.hpp"
#include "math/Mat4.hpp"
#include "math/Vec2.hpp"
#include <ostream>
#include <string>
#include <chrono>

namespace engine {
	
	class Camera {
	private:
		// Static Camera properties
		float m_fov;
		float m_aspect_ratio;
		float m_near_clip;
		float m_far_clip;
		
		// Dynamic Camera properties
		math::Vec3 m_position;
		math::Vec3 m_rotation;
		
		math::Vec2 m_last_mouse_pos;
	public:
		Camera();
		Camera(float fov, float aspect_ratio, float near_clip, float far_clip);
		
		Camera(const Camera& other) = default;
		Camera(Camera&& other) noexcept = default;
		Camera& operator=(const Camera& other) = default;
		Camera& operator=(Camera&& other) noexcept = default;
		~Camera() = default;
		
		Camera& move(const math::Vec3& offset);
		Camera& set_position(const math::Vec3& position);
		Camera& move_relative(const math::Vec3& offset);
		
		Camera& rotate(const math::Vec3& rotation);
		Camera& set_rotation(const math::Vec3& rotation);
		
		const math::Vec3& position() const;
		const math::Vec3& rotation() const;
		math::Vec3& position();
		math::Vec3& rotation();
		
		void reset_mouse_pos();
		void update(std::chrono::milliseconds delta_time);
		
		float fov() const;
		float aspect_ratio() const;
		float near_clip() const;
		float far_clip() const;
		
		Camera& fov(float fov);
		Camera& aspect_ratio(float aspect_ratio);
		Camera& near_clip(float near_clip);
		Camera& far_clip(float far_clip);
		
		math::Vec3 forward() const;
		math::Vec3 right() const;
		math::Vec3 up() const;
		
		math::Mat4 projection_matrix() const;
		math::Mat4 view_matrix() const;
	private:
		math::Mat4 trans_matrix() const;
		math::Mat4 rot_x_matrix() const;
		math::Mat4 rot_y_matrix() const;
		math::Mat4 rot_z_matrix() const;
		math::Mat4 rot_matrix() const;
	
	public:
		friend std::ostream& operator<<(std::ostream& os, const Camera& c);
		std::string to_string() const;
	};
	
} // engine

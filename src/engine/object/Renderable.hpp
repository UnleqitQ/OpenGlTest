#pragma once

#include "Mesh.hpp"

namespace engine::object {
	
	class Renderable {
	public:
		virtual const render::Mesh get_mesh() const = 0;
		virtual const math::Vec4 get_albedo() const {
			static math::Vec4 albedo(1, 1, 1, 1);
			return albedo;
		}
		virtual const math::Mat4 get_model() const = 0;
	};
	
} // engine::object

#pragma once

#include <vector>
#include "../object/Renderable.hpp"
#include "../Camera.hpp"

namespace engine::render {
	
	/**
	 * This class provides helper functions for rendering.
	 * Currently it only is used for sorting objects for alpha blending to work correctly.
	 */
	class RenderHelper {
	public:
		static void sortObjects(std::vector<object::Renderable*>& objects, const Camera& camera);
	};
} // engine::render

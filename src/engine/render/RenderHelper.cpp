#include "RenderHelper.hpp"

#include <algorithm>
#include <cmath>
#include "../math/Mat4.hpp"
#include "../math/Vec3.hpp"
#include "../math/Vec4.hpp"

namespace engine::render {
	void RenderHelper::sortObjects(std::vector<object::Renderable*>& objects, const Camera& camera) {
		math::Mat4 view = camera.view_matrix();
		
		std::sort(objects.begin(), objects.end(), [&view](const object::Renderable* a, const object::Renderable* b) {
			math::Vec4 posA = view * a->get_model() * math::Vec4(0, 0, 0, 1);
			math::Vec4 posB = view * b->get_model() * math::Vec4(0, 0, 0, 1);
			
			posA /= posA.w();
			posB /= posB.w();
			
			return posA.z() < posB.z();
		});
	}
} // engine::render
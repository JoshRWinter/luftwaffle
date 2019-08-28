#ifndef COMP_EXPLOSION_CLOUD_HPP
#define COMP_EXPLOSION_CLOUD_HPP

#include "component.hpp"

namespace comp
{
	struct explosion_cloud : comp::component
	{
		static constexpr comp::type component_type = comp::type::EXPLOSION_CLOUD;

		explosion_cloud(ent::entity &entity, const float s)
			: component(component_type, entity)
			, shrink_timer(70)
			, scale(s)
		{}

		int shrink_timer;
		float scale;
	};
}

#endif

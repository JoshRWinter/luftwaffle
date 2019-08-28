#ifndef COMP_EXPLOSION_ARM_HPP
#define COMP_EXPLOSION_ARM_HPP

#include "component.hpp"

namespace comp
{
	struct explosion_arm : comp::component
	{
		static constexpr comp::type component_type = comp::type::EXPLOSION_ARM;

		explosion_arm(ent::entity &entity, float angle, float scale)
			: component(component_type, entity)
			, angle_update(mersenne(-0.05f, 0.05f))
			, angle(angle)
			, smoke_timer(0)
			, speed(mersenne(0.04f * scale, 0.05f * scale))
			, retard(scale / 1180.0f)
		{}

		float angle;
		float angle_update;
		int smoke_timer;
		float speed;
		float retard;
	};
}

#endif

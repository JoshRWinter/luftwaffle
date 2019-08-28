#ifndef COMP_MISSILE_HPP
#define COMP_MISSILE_HPP

#include "component.hpp"

namespace comp
{
	struct missile : comp::component
	{
		static constexpr comp::type component_type = comp::type::MISSILE;

		missile(ent::entity &entity, float a)
			: component(component_type, entity)
			, arming_timer(40)
			, smoke_timer(0.0f)
			, max_smoke_timer(8.0f) // value to reset smoke_timer to
			, xv(0.0f)
			, yv(0.0f)
			, speed(0.01f)
			, angle(a)
			, ttl(100)
		{}

		int arming_timer;
		float smoke_timer;
		float max_smoke_timer;
		float xv, yv;
		float speed;
		float angle;
		int ttl;
	};
}

#endif

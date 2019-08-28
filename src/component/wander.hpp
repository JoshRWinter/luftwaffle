#ifndef COMP_WANDER_HPP
#define COMP_WANDER_HPP

#include "component.hpp"

namespace comp
{
	struct wander : comp::component
	{
		static constexpr comp::type component_type = comp::type::WANDER;

		enum class wander_state { POPOUT, WANDERING };

		wander(ent::entity &entity, const float x, const float y, const float angle)
			: component(component_type, entity)
			, state(wander_state::POPOUT)
			, initial_angle(angle)
			, initial_x(x)
			, initial_y(y)
			, targetx(0.0f)
			, targety(0.0f)
			, timer(7)
		{}

		wander_state state;
		const float initial_angle;
		const float initial_x, initial_y;
		float targetx, targety;
		int timer;
	};
}

#endif

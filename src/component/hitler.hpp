#ifndef COMP_HITLER_HPP
#define COMP_HITLER_HPP

#include "component.hpp"

namespace comp
{
	struct hitler : comp::component
	{
		static constexpr comp::type component_type = comp::type::HITLER;

		hitler(ent::entity &entity)
			: component(component_type, entity)
			, childgun(NULL)
			, timer_next_jump(0)
			, jumptarget_x(0.0f)
			, jumptarget_y(0.0f)
			, target_angle(0.0f)
			, jumping(false)
		{}

		ent::entity *childgun;
		int timer_next_jump;
		float jumptarget_x;
		float jumptarget_y;
		float target_angle;
		bool jumping;
	};
}

#endif

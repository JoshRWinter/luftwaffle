#ifndef COMP_GORING_HPP
#define COMP_GORING_HPP

#include "component.hpp"

namespace comp
{
	struct goring : comp::component
	{
		static constexpr comp::type component_type = comp::type::GORING;

		enum class moving_type { COUNTER, CLOCKWISE, NONE };

		goring(ent::entity &entity)
			: component(component_type, entity)
			, moving(moving_type::NONE)
			, moving_type_timer(0)
			, speed(0.0f)
			, childgun(NULL)
		{}

		moving_type moving;
		int moving_type_timer;
		float speed;
		ent::entity *childgun;
	};
}

#endif

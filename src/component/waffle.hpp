#ifndef COMP_WAFFLE_HPP
#define COMP_WAFFLE_HPP

#include "component.hpp"

namespace comp
{
	struct waffle : comp::component
	{
		static constexpr comp::type component_type = comp::type::WAFFLE;

		enum class waffle_type { NORMAL, MID };

		waffle(ent::entity &entity, waffle_type t)
			: component(component_type, entity)
			, type(t)
			, childgun(NULL)
		{}

		waffle_type type;
		ent::entity *childgun;
	};
}

#endif

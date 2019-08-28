#ifndef COMP_HEALTH_HPP
#define COMP_HEALTH_HPP

#include "component.hpp"

namespace comp
{
	struct health : comp::component
	{
		static constexpr comp::type component_type = comp::type::HEALTH;

		health(ent::entity &entity, int h)
			: component(component_type, entity)
			, hitpoints(h)
		{}

		int hitpoints;
	};
}

#endif

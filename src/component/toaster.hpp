#ifndef COMP_TOASTER_HPP
#define COMP_TOASTER_HPP

#include "component.hpp"

namespace comp
{
	struct toaster : comp::component
	{
		static constexpr comp::type component_type = comp::type::TOASTER;

		constexpr static int SPAWN_TIMER_LOW = 100;
		constexpr static int SPAWN_TIMER_HIGH = 500;

		toaster(ent::entity &entity)
			: component(comp::type::TOASTER, entity)
			, spawn_timer(mersenne(SPAWN_TIMER_LOW, SPAWN_TIMER_HIGH))
		{}

		int spawn_timer;
	};
}

#endif

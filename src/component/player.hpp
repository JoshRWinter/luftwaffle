#ifndef COMP_PLAYER_HPP
#define COMP_PLAYER_HPP

#include "component.hpp"

namespace comp
{
	struct player : comp::component
	{
		static constexpr comp::type component_type = comp::type::PLAYER;
		static constexpr int MAX_ROCKET_COUNT = 8;
		static constexpr int MAX_LASER_COUNT = 24;

		player(ent::entity &entity)
			: component(component_type, entity)
			, rocket_count(MAX_ROCKET_COUNT)
			, laser_count(MAX_LASER_COUNT)
			, rocket_refill_timer(0)
			, laser_refill_timer(0)
			, rocket_refill_rate_timer(0)
			, laser_refill_rate_timer(0)
			, dead_timer(0)
			, xv(0.0f)
			, yv(0.0f)
			, childgun(NULL)
		{}

		int rocket_count;
		int laser_count;
		int rocket_refill_timer;
		int laser_refill_timer;
		int rocket_refill_rate_timer;
		int laser_refill_rate_timer;
		int dead_timer;
		ent::entity *childgun;
		float xv, yv;
	};
}

#endif

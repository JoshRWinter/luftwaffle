#ifndef COMP_LASER_HPP
#define COMP_LASER_HPP

#include "component.hpp"

namespace comp
{
	struct laser : comp::component
	{
		static constexpr comp::type component_type = comp::type::LASER;

		laser(ent::entity &entity, float angle, float speed, int dmg)
			: component(component_type, entity)
			, damage(dmg)
			, xv(cosf(angle) * speed)
			, yv(sinf(angle) * speed)
			, ttl(100)
			, arming_timer(9)
		{}

		float xv, yv;
		int damage;
		int ttl;
		int arming_timer;
	};
}

#endif

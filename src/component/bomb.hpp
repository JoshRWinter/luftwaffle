#ifndef COMP_BOMB_HPP
#define COMP_BOMB_HPP

#include "component.hpp"

namespace comp
{
	struct bomb : comp::component
	{
		static constexpr comp::type component_type = comp::type::BOMB;

		bomb(ent::entity &entity, const float angle)
			: component(component_type, entity)
			, ttl(100)
			, xv(cosf(angle) * 0.05f)
			, yv(sinf(angle) * 0.05f)
			, rotspeed(mersenne(1) ? -0.03f : 0.03f)
		{}

		int ttl;
		float xv, yv;
		float rotspeed;
	};
}

#endif

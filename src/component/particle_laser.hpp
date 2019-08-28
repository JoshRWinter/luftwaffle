#ifndef COMP_PARTICLE_LASER_HPP
#define COMP_PARTICLE_LASER_HPP

#include "component.hpp"

namespace comp
{
	struct particle_laser : comp::component
	{
		static constexpr comp::type component_type = comp::type::PARTICLE_LASER;


		particle_laser(ent::entity &entity, const float angle)
			: component(component_type, entity)
			, ttl(12)
			, speed(mersenne(0.12f, 0.16f))
			, xv(cosf(angle) * speed)
			, yv(sinf(angle) * speed)
		{}

		int ttl;
		float speed;
		float xv, yv;
	};
}

#endif

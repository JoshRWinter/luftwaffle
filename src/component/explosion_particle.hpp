#ifndef COMP_EXPLOSION_PARTICLE_HPP
#define COMP_EXPLOSION_PARTICLE_HPP

#include "component.hpp"

namespace comp
{
	struct explosion_particle : comp::component
	{
		static constexpr comp::type component_type = comp::type::EXPLOSION_PARTICLE;

		explosion_particle(ent::entity &entity, float scale)
			: component(component_type, entity)
			, start_timer(mersenne(0, 12))
			, target_size(scale / 3.5f)
			, growing(true)
			, freeze_timer(43)
		{}

		int start_timer;
		float target_size;
		bool growing;
		int freeze_timer;
	};
}

#endif

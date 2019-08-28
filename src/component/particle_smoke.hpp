#ifndef COMP_PARTICLE_SMOKE_HPP
#define COMP_PARTICLE_SMOKE_HPP

#include "component.hpp"

namespace comp
{
	struct particle_smoke : comp::component
	{
		static constexpr comp::type component_type = comp::type::PARTICLE_SMOKE;

		particle_smoke(ent::entity &entity)
			: component(component_type, entity)
		{}

	};
}

#endif

#ifndef COMP_ATLAS_RENDERABLE_HPP
#define COMP_ATLAS_RENDERABLE_HPP

#include "component.hpp"

#include "win.h"

namespace comp
{
	struct atlas_renderable : comp::component
	{
		static constexpr comp::type component_type = comp::type::ATLAS_RENDERABLE;

		atlas_renderable(ent::entity &entity, const unsigned short *tc, const win::color &c = win::color(1.0f, 1.0f, 1.0f, 1.0f))
			: component(component_type, entity)
			, color(c)
			, texcoords(tc)
		{}

		win::color color;
		const unsigned short *texcoords;
	};
}

#endif

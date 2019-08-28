#ifndef COMP_GLOW_RENDERABLE_HPP
#define COMP_GLOW_RENDERABLE_HPP

#include "component.hpp"

#include "win.h"

namespace comp
{
	struct glow_renderable : comp::component
	{
		static constexpr comp::type component_type = comp::type::GLOW_RENDERABLE;

		glow_renderable(ent::entity &entity, const win::color c, float bright, float rad)
			: component(component_type, entity)
			, color(c)
			, brightness(bright * 255.0f)
			, radius(rad)
		{}

		win::color color;
		int brightness;
		float radius;
	};
}

#endif

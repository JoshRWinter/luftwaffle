#ifndef COMP_PHYSICAL_HPP
#define COMP_PHYSICAL_HPP

#include "component.hpp"

namespace comp
{
	struct physical : comp::component
	{
		static constexpr comp::type component_type = comp::type::PHYSICAL;

		physical(ent::entity &entity, float xpos, float ypos, float width, float height, float rotation)
		: component(component_type, entity)
		, x(xpos)
		, y(ypos)
		, w(width)
		, h(height)
		, rot(rotation)
		{}

		bool collide(const physical &rhs) const
		{
			return x + w > rhs.x && x < rhs.x + rhs.w && y + h > rhs.y && y < rhs.y + rhs.h;
		}

		float distance(const physical &rhs) const
		{
			return win::distance(x, y, rhs.x, rhs.y);
		}

		void align(float, float);

		float x, y, w, h, rot;
	};
}

#endif

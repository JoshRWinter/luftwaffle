#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../luftwaffle.hpp"

namespace ent
{
	struct entity;
}

namespace comp
{
	enum class type
	{
		PHYSICAL,
		ATLAS_RENDERABLE,
		PLAYER,
		TOASTER
	};

	struct component
	{
		component(comp::type t, ent::entity &p)
			: type(t)
			, parent(p)
		{}

		comp::type type;
		ent::entity &parent;
	};

	struct physical : comp::component
	{
		physical(ent::entity &parent, float xpos, float ypos, float width, float height, float rotation)
			: component(comp::type::PHYSICAL, parent)
			, x(xpos)
			, y(ypos)
			, w(width)
			, h(height)
			, rot(rotation)
		{}

		float x, y, w, h, rot;
	};

	struct atlas_renderable : comp::component
	{
		atlas_renderable(ent::entity &parent, const unsigned short *tc)
			: component(comp::type::ATLAS_RENDERABLE, parent)
			, texcoords(tc)
		{}

		const unsigned short *texcoords;
	};

	struct player : comp::component
	{
		player(ent::entity &parent)
			: component(comp::type::PLAYER, parent)
		{}
	};
}

#endif

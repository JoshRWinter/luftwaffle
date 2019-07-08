#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../luftwaffle.hpp"

namespace comp
{
	struct component;
	enum class type;
	struct componentdb;
}

namespace ent
{
	constexpr int MAX_COMPONENTS = 4;
	struct entity
	{
		entity();

		comp::component *components[MAX_COMPONENTS];

		comp::component *component(comp::type);
		void attach(comp::component*);
		comp::component *detach(comp::type);
	};

	void new_player(game::world&);
}

#endif

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../luftwaffle.hpp"

namespace ent
{
	constexpr int MAX_COMPONENTS = 4;
	struct entity
	{
		entity();
		entity(const entity&) = delete;
		entity(entity&&) = delete;

		void operator=(const entity&) = delete;
		void operator=(entity&&) = delete;

		comp::component *components[MAX_COMPONENTS];

		template<typename T> T *component(const comp::type type)
		{
			for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
			{
				if(components[i] == NULL)
					continue;

				if(components[i]->type == type)
					return (T*)components[i];
			}

			return NULL;
		}

		void attach(comp::component&);
		comp::component &detach(comp::type);
	};

	void new_player(game::world&);
}

#endif

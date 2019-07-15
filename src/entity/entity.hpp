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

		template<typename T> T *component()
		{
			for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
			{
				if(components[i] == NULL)
					continue;

				if(components[i]->type == T::component_type)
					return (T*)components[i];
			}

			return NULL;
		}

		void attach(comp::component&);
		comp::component &detach(comp::type);
	};

	constexpr float PLAYER_WIDTH = 0.6f;
	constexpr float PLAYER_HEIGHT = 0.6f;
	void new_player(game::world&);

	constexpr float TOASTER_WIDTH = 0.72f;
	constexpr float TOASTER_HEIGHT = 0.9f;
	void new_toaster(game::world&);
}

#endif

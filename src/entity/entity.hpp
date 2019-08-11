#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../luftwaffle.hpp"

namespace ent
{
	struct component_store
	{
		comp::type type;
		comp::component *component;
	};

	constexpr int MAX_COMPONENTS = 4;
	struct entity
	{
		entity();
		entity(const entity&) = delete;
		entity(entity&&) = delete;

		void operator=(const entity&) = delete;
		void operator=(entity&&) = delete;

		template <typename T> T &component() const
		{
			for(int i = 0; i < MAX_COMPONENTS; ++i)
				if(components[i].type == T::component_type)
					return *(T*)components[i].component;

			win::bug("no component " + std::string(typeid(T).name()) + " on this ent");
		}

		template <typename T> T *try_component() const
		{
			for(int i = 0; i < MAX_COMPONENTS; ++i)
				if(components[i].type == T::component_type)
					return (T*)components[i].component;

			return NULL;
		}

		template <typename T> T &take_component()
		{
			for(int i = 0; i < MAX_COMPONENTS; ++i)
				if(components[i].type == T::component_type)
				{
					components[i].type = comp::type::NONE;
					return *(T*)components[i].component;
				}

			win::bug("no component " + std::string(typeid(T).name()) + " on this ent");
		}

		template <typename T> T *try_take_component()
		{
			for(int i = 0; i < MAX_COMPONENTS; ++i)
				if(components[i].type == T::component_type)
				{
					components[i].type = comp::type::NONE;
					return (T*)components[i].component;
				}

			return NULL;
		}

		void attach(comp::component&);
		void cleanup_check() const;

		component_store components[MAX_COMPONENTS];
	};
}

#endif

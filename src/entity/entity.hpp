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

		template<typename T> T &component()
		{
			const int index = get_component_index<T>();

			if(index != -1)
				return *(T*)components[index];

			win::bug("no component " + std::string(typeid(T).name()) + " on this ent");
		}

		template<typename T> T *try_component()
		{
			const int index = get_component_index<T>();

			return index != -1 ? (T*)components[index] : NULL;
		}

		template<typename T> T &take_component()
		{
			const int index = get_component_index<T>();;

			if(index != -1)
			{
				comp::component *tmp = components[index];
				components[index] = NULL;
				return *(T*)tmp;
			}

			win::bug("no component " + std::string(typeid(T).name()) + " on this ent");
		}

		template<typename T> T *try_take_component()
		{
			const int index = get_component_index<T>();

			if(index != -1)
			{
				comp::component *tmp = components[index];
				components[index] = NULL;
				return (T*)tmp;
			}

			return NULL;
		}

		void cleanup_check(); // only called in debug mode
		void attach(comp::component&);
		comp::component &detach(comp::type);

	private:
		template<typename T> int get_component_index()
		{
			for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
			{
				if(components[i] == NULL)
					continue;

				if(components[i]->type == T::component_type)
				{
#ifndef NDEBUG
					ent::entity::safety_check(components[i]);
#endif
					return i;
				}
			}

			return -1;
		}

		static void safety_check(const void*);
	};
}

#endif

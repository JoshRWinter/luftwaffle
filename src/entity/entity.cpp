#include "../luftwaffle.hpp"

ent::entity::entity()
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
		components[i] = NULL;
}

void ent::entity::cleanup_check()
{
#ifndef NDEBUG
	for(int i = 0; i < MAX_COMPONENTS; ++i)
		if(components[i] != NULL)
			win::bug("zombie component found");
#endif
}

void ent::entity::attach(comp::component &c)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i] != NULL)
			continue;

		components[i] = &c;
		return;
	}

	win::bug("exceeded max components for an entity");
}

comp::component &ent::entity::detach(const comp::type type)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i] == NULL)
			continue;

		if(components[i]->type != type)
			continue;

		comp::component &c = *components[i];
		components[i] = NULL;
		return c;
	}

	win::bug("no such component type " + std::to_string((int)type));
}

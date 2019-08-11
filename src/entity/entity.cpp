#include "../luftwaffle.hpp"

ent::entity::entity()
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
		components[i].type = comp::type::NONE;
}

void ent::entity::attach(comp::component &c)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i].type != comp::type::NONE)
			continue;

		components[i].type = c.type;
		components[i].component = &c;
		return;
	}

	win::bug("exceeded max components for an entity (" + std::to_string((int)c.type) + ")");
}

void ent::entity::cleanup_check() const
{
#ifndef NDEBUG
	for(int i = 0; i < MAX_COMPONENTS; ++i)
		if(components[i].type != comp::type::NONE)
			win::bug("zombie component found of type " + std::to_string((int)components[i].type));
#endif
}

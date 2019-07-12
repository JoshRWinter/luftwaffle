#include "../luftwaffle.hpp"

ent::entity::entity()
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
		components[i] = NULL;
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

/////////////////////
// entity creation
/////////////////////

void ent::new_player(game::world &world)
{
	if(world.objectdb.player.count() != 0)
		win::bug("already a player");

	ent::entity &entity = world.objectdb.entities.create();

	entity.attach(world.objectdb.physicals.create(entity, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f));
	entity.attach(world.objectdb.atlas_renderables_player.create(entity, world.asset.atlas.coords(game::asset::aid::PLAYER)));
	entity.attach(world.objectdb.player.create(entity));
}

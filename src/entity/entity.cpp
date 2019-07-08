#include "../luftwaffle.hpp"

ent::entity::entity()
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
		components[i] = NULL;
}

comp::component *ent::entity::component(const comp::type type)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i] == NULL)
			continue;

		if(components[i]->type == type)
			return components[i];
	}

	return NULL;
}

void ent::entity::attach(comp::component *const c)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i] != NULL)
			continue;

		components[i] = c;
		return;
	}

	win::bug("exceeded max components for an entity");
}

comp::component *ent::entity::detach(const comp::type type)
{
	for(int i = 0; i < ent::MAX_COMPONENTS; ++i)
	{
		if(components[i] == NULL)
			continue;

		if(components[i]->type != type)
			continue;

		comp::component *c = components[i];
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
	if(world.componentdb.player != NULL)
		win::bug("already a player");

	ent::entity *entity = world.componentdb.pool.entities.create();

	comp::physical *physical = world.componentdb.pool.physicals.create(entity, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	comp::atlas_renderable *renderable = world.componentdb.pool.atlas_renderables_player.create(entity, world.asset.atlas.coords(game::asset::aid::PLAYER));
	comp::player *player = world.componentdb.pool.player.create(entity);

	entity->attach(physical);
	entity->attach(renderable);
	entity->attach(player);

	world.componentdb.physicals.push_back(physical);
	world.componentdb.atlas_renderables_player.push_back(renderable);
	world.componentdb.player = player;
	fprintf(stderr, "%d renderable players\n", world.componentdb.atlas_renderables_player.size());
}

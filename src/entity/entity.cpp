#include "../luftwaffle.hpp"

#include <math.h>

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
// entity creation / deletion
/////////////////////

void ent::new_player(game::world &world)
{
	if(world.objectdb.player.count() != 0)
		win::bug("already a player");

	ent::entity &entity = world.objectdb.entities.create();

	entity.attach(world.objectdb.physicals.create(entity, -PLAYER_WIDTH / 2.0f, -PLAYER_HEIGHT / 2.0f, PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
	entity.attach(world.objectdb.atlas_renderable_players.create(entity, world.asset.atlas.coords(game::asset::aid::PLAYER)));
	entity.attach(world.objectdb.player.create(entity));
}


void ent::new_toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 0)
		win::bug("already a toaster");

	ent::entity &entity = world.objectdb.entities.create();

	entity.attach(world.objectdb.physicals.create(entity, 5.0f, 0.0f, TOASTER_WIDTH, TOASTER_HEIGHT, (M_PI / 2.0f) * mersenne(0, 3)));
	entity.attach(world.objectdb.atlas_renderable_toasters.create(entity, world.asset.atlas.coords(game::asset::aid::TOASTER)));
	entity.attach(world.objectdb.toaster.create(entity));
}

void ent::delete_toaster(game::world &world, ent::entity &entity)
{
	world.objectdb.physicals.destroy(*entity.component<comp::physical>());
	world.objectdb.toaster.destroy(*entity.component<comp::toaster>());
	world.objectdb.atlas_renderable_toasters.destroy(*entity.component<comp::atlas_renderable>());

	world.objectdb.entities.destroy(entity);
}


void ent::new_waffle(game::world &world, const comp::physical &toaster)
{
	ent::entity &entity = world.objectdb.entities.create();

	const float x = toaster.x + (ent::TOASTER_WIDTH / 2.0f) - (ent::WAFFLE_WIDTH / 2.0f);
	const float y = toaster.y + (ent::TOASTER_HEIGHT / 2.0f) - (ent::WAFFLE_HEIGHT / 2.0f);

	comp::physical &physical = world.objectdb.physicals.create(entity, x, y, ent::WAFFLE_WIDTH, ent::WAFFLE_HEIGHT, toaster.rot);
	comp::atlas_renderable &renderable = world.objectdb.atlas_renderable_waffles.create(entity, world.asset.atlas.coords(game::asset::aid::WAFFLE1));
	comp::wander &wander = world.objectdb.wander.create(entity, physical.x, physical.y, toaster.rot);
	comp::waffle &childgun = world.objectdb.waffles.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(wander);
	entity.attach(childgun);

	// the laser gun child entity
	ent::entity &lasergun_entity = world.objectdb.entities.create();

	comp::lasergun &lasergun = world.objectdb.laserguns.create(lasergun_entity, physical, 30);
	comp::physical &lasergun_physical = world.objectdb.physicals.create(lasergun_entity, 0.0f, 0.0f, ent::WAFFLE_WIDTH * 1.2f, ent::WAFFLE_HEIGHT * 1.2f, 0.0f);
	comp::atlas_renderable &lasergun_renderable = world.objectdb.atlas_renderable_laserguns.create(lasergun_entity, world.asset.atlas.coords(game::asset::aid::LASERGUN));

	lasergun_entity.attach(lasergun_physical);
	lasergun_entity.attach(lasergun_renderable);
	lasergun_entity.attach(lasergun);

	childgun.childgun = &lasergun_entity;
}

void ent::delete_waffle(game::world &world, ent::entity &entity)
{

	world.objectdb.physicals.destroy(*entity.component<comp::physical>());
	world.objectdb.atlas_renderable_players.destroy(*entity.component<comp::atlas_renderable>());
	world.objectdb.wander.destroy(*entity.component<comp::wander>());
	comp::waffle &waffle = *entity.component<comp::waffle>();
	ent::entity &child = *waffle.childgun;
	world.objectdb.waffles.destroy(waffle);

	world.objectdb.entities.destroy(entity);

	world.objectdb.physicals.destroy(*child.component<comp::physical>());
	world.objectdb.atlas_renderable_laserguns.destroy(*child.component<comp::atlas_renderable>());
	world.objectdb.laserguns.destroy(*child.component<comp::lasergun>());

	world.objectdb.entities.destroy(child);
}

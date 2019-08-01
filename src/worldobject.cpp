#include "luftwaffle.hpp"

#include <math.h>

/////////////////////////
// player
/////////////////////////
void game::new_player(game::world &world)
{
	if(world.objectdb.player.count() != 0)
		win::bug("already a player");

	ent::entity &entity = world.objectdb.entity.create();

	comp::physical &physical = world.objectdb.physical.create(entity, -PLAYER_WIDTH / 2.0f, -PLAYER_HEIGHT / 2.0f, PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f);
	comp::atlas_renderable &renderable = world.objectdb.atlas_renderable_player.create(entity, world.asset.atlas.coords(game::asset::aid::PLAYER));
	comp::player &player = world.objectdb.player.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(player);

	ent::entity &childgun = game::new_lasergun(world, game::lasergun_type::PLAYER, physical);
	player.childgun = &childgun;
}

/////////////////////////
// toaster
/////////////////////////
void game::new_toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 0)
		win::bug("already a toaster");

	ent::entity &entity = world.objectdb.entity.create();

	entity.attach(world.objectdb.physical.create(entity, 5.0f, 0.0f, TOASTER_WIDTH, TOASTER_HEIGHT, (M_PI / 2.0f) * mersenne(0, 3)));
	entity.attach(world.objectdb.atlas_renderable_toaster.create(entity, world.asset.atlas.coords(game::asset::aid::TOASTER)));
	entity.attach(world.objectdb.toaster.create(entity));
}

void game::delete_toaster(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.toaster.destroy(entity.take_component<comp::toaster>());
	world.objectdb.atlas_renderable_toaster.destroy(entity.take_component<comp::atlas_renderable>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// waffles
/////////////////////////
void game::new_waffle(game::world &world, const comp::physical &toaster)
{
	ent::entity &entity = world.objectdb.entity.create();

	const float x = toaster.x + (game::TOASTER_WIDTH / 2.0f) - (game::WAFFLE_WIDTH / 2.0f);
	const float y = toaster.y + (game::TOASTER_HEIGHT / 2.0f) - (game::WAFFLE_HEIGHT / 2.0f);

	comp::physical &physical = world.objectdb.physical.create(entity, x, y, game::WAFFLE_WIDTH, game::WAFFLE_HEIGHT, toaster.rot);
	comp::atlas_renderable &renderable = world.objectdb.atlas_renderable_waffle.create(entity, world.asset.atlas.coords(game::asset::aid::WAFFLE1));
	comp::wander &wander = world.objectdb.wander.create(entity, physical.x, physical.y, toaster.rot);
	comp::waffle &waffle = world.objectdb.waffle.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(wander);
	entity.attach(waffle);

	// the laser gun child entity
	ent::entity &childgun = game::new_lasergun(world, game::lasergun_type::WAFFLE, physical);
	waffle.childgun = &childgun;
}

void game::delete_waffle(game::world &world, ent::entity &entity)
{
	game::delete_lasergun(world, *entity.component<comp::waffle>().childgun);

	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_player.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.wander.destroy(entity.take_component<comp::wander>());
	comp::waffle &waffle = entity.take_component<comp::waffle>();
	ent::entity &child = *waffle.childgun;
	world.objectdb.waffle.destroy(waffle);

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);

	world.objectdb.physical.destroy(child.take_component<comp::physical>());
	world.objectdb.atlas_renderable_lasergun.destroy(child.take_component<comp::atlas_renderable>());
	world.objectdb.lasergun.destroy(child.take_component<comp::lasergun>());

	child.cleanup_check();
	world.objectdb.entity.destroy(child);
}


/////////////////////////
// laser guns
/////////////////////////
ent::entity &game::new_lasergun(game::world &world, const game::lasergun_type type, const comp::physical &parent_physical)
{
	int maxcooldown;
	float width;
	float height;
	int texture;

	switch(type)
	{
		case game::lasergun_type::WAFFLE:
			maxcooldown = LASERGUN_WAFFLE_MAX_COOLDOWN;
			width = LASERGUN_WAFFLE_WIDTH;
			height = LASERGUN_WAFFLE_HEIGHT;
			texture = game::asset::aid::LASERGUN_WAFFLE;
			break;
		case game::lasergun_type::PLAYER:
			maxcooldown = LASERGUN_PLAYER_MAX_COOLDOWN;
			width = LASERGUN_PLAYER_WIDTH;
			height = LASERGUN_PLAYER_HEIGHT;
			texture = game::asset::aid::LASERGUN_WAFFLE;
			break;
	}

	ent::entity &entity = world.objectdb.entity.create();

	comp::physical &physical = world.objectdb.physical.create(entity, 0.0f, 0.0f, width, height, 0.0f);
	comp::lasergun &lasergun = world.objectdb.lasergun.create(entity, parent_physical, maxcooldown);
	comp::atlas_renderable &renderable = world.objectdb.atlas_renderable_lasergun.create(entity, world.asset.atlas.coords(texture));

	entity.attach(physical);
	entity.attach(lasergun);
	entity.attach(renderable);

	return entity;
}

void game::delete_lasergun(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.lasergun.destroy(entity.take_component<comp::lasergun>());
	world.objectdb.atlas_renderable_lasergun.destroy(entity.take_component<comp::atlas_renderable>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// lasers
/////////////////////////
void game::new_laser(game::world &world, comp::physical &gun_physical, comp::lasergun &gun, int slot)
{
	ent::entity &entity = world.objectdb.entity.create();

	float x = gun_physical.x + (gun_physical.w / 2.0f) - (LASER_WIDTH / 2.0f);
	float y = gun_physical.y + (gun_physical.h / 2.0f) - (LASER_HEIGHT / 2.0f);

	x = x + cosf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;
	y = y + sinf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;

	comp::physical &physical = world.objectdb.physical.create(entity, x, y, LASER_WIDTH, LASER_HEIGHT, gun_physical.rot);
	comp::atlas_renderable &renderable = world.objectdb.atlas_renderable_laser.create(entity, world.asset.atlas.coords(game::asset::aid::LASER));
	comp::glow_renderable &glow_renderable = world.objectdb.glow_renderable.create(entity, win::color(255, 50, 50), 0.65f, 1.2f);
	comp::laser &laser = world.objectdb.laser.create(entity, physical.rot, 0.25f, 100);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(laser);
	entity.attach(glow_renderable);

}

void game::delete_laser(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_laser.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.laser.destroy(entity.take_component<comp::laser>());
	world.objectdb.glow_renderable.destroy(entity.take_component<comp::glow_renderable>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

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

	// child lasergun
	ent::entity &lg_entity = world.objectdb.entity.create();

	comp::physical &lg_physical = world.objectdb.physical.create(lg_entity, 0.0f, 0.0f, 0.8f, 0.8f, physical.rot);
	comp::atlas_renderable &lg_renderable = world.objectdb.atlas_renderable_lasergun.create(lg_entity, world.asset.atlas.coords(game::asset::aid::LASERGUN));
	comp::lasergun &lg_lasergun = world.objectdb.lasergun.create(lg_entity, physical, 10);

	lg_lasergun.guns[0].distance = 0.4f;

	lg_entity.attach(lg_physical);
	lg_entity.attach(lg_renderable);
	lg_entity.attach(lg_lasergun);

	player.childgun = &lg_entity;
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
	comp::waffle &childgun = world.objectdb.waffle.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(wander);
	entity.attach(childgun);

	// the laser gun child entity
	ent::entity &lasergun_entity = world.objectdb.entity.create();

	comp::lasergun &lasergun = world.objectdb.lasergun.create(lasergun_entity, physical, 30);
	comp::physical &lasergun_physical = world.objectdb.physical.create(lasergun_entity, 0.0f, 0.0f, game::WAFFLE_WIDTH * 1.2f, game::WAFFLE_HEIGHT * 1.2f, 0.0f);
	comp::atlas_renderable &lasergun_renderable = world.objectdb.atlas_renderable_lasergun.create(lasergun_entity, world.asset.atlas.coords(game::asset::aid::LASERGUN));

	lasergun_entity.attach(lasergun_physical);
	lasergun_entity.attach(lasergun_renderable);
	lasergun_entity.attach(lasergun);

	childgun.childgun = &lasergun_entity;
}

void game::delete_waffle(game::world &world, ent::entity &entity)
{
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
	comp::laser &laser = world.objectdb.laser.create(entity, physical.rot, 0.1f, 100);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(laser);
}

void game::delete_laser(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_laser.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.laser.destroy(entity.take_component<comp::laser>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

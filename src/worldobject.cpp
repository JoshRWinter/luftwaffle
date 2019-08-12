#include "luftwaffle.hpp"

#include <math.h>

/////////////////////////
// player
/////////////////////////
void game::new_player(game::world &world)
{
	if(world.objectdb.player.count() != 0)
		win::bug("already a player");

	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, -PLAYER_WIDTH / 2.0f, -PLAYER_HEIGHT / 2.0f, PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f);
	auto &renderable = world.objectdb.atlas_renderable_player.create(entity, world.asset.atlas.coords(game::asset::aid::PLAYER));
	auto &player = world.objectdb.player.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(player);

	auto &childgun = game::new_lasergun(world, game::lasergun_type::PLAYER, physical);
	player.childgun = &childgun;
}

/////////////////////////
// toaster
/////////////////////////
void game::new_toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 0)
		win::bug("already a toaster");

	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, 5.0f, 0.0f, TOASTER_WIDTH, TOASTER_HEIGHT, (M_PI / 2.0f) * mersenne(0, 3));
	auto &renderable = world.objectdb.atlas_renderable_toaster.create(entity, world.asset.atlas.coords(game::asset::aid::TOASTER));
	auto &toaster = world.objectdb.toaster.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(toaster);
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
void game::new_waffle(game::world &world, comp::physical &toaster, const comp::waffle::waffle_type type)
{
	int tex;
	float width;
	float height;

	switch(type)
	{
		case comp::waffle::waffle_type::NORMAL:
			tex = game::asset::aid::WAFFLE1;
			width = WAFFLE_WIDTH;
			height = WAFFLE_HEIGHT;
			break;

		case comp::waffle::waffle_type::MID:
			tex = game::asset::aid::MIDWAFFLE;
			width = WAFFLE_MID_WIDTH;
			height = WAFFLE_MID_HEIGHT;
			break;
	}
	auto &entity = world.objectdb.entity.create();

	const float x = toaster.x + (game::TOASTER_WIDTH / 2.0f) - (game::WAFFLE_WIDTH / 2.0f);
	const float y = toaster.y + (game::TOASTER_HEIGHT / 2.0f) - (game::WAFFLE_HEIGHT / 2.0f);

	auto &physical = world.objectdb.physical.create(entity, x, y, width, height, toaster.rot);
	auto &renderable = world.objectdb.atlas_renderable_waffle.create(entity, world.asset.atlas.coords(tex));
	auto &wander = world.objectdb.wander.create(entity, physical.x, physical.y, toaster.rot);
	auto &waffle = world.objectdb.waffle.create(entity, type);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(wander);
	entity.attach(waffle);

	// the laser gun child entity
	auto &childgun = game::new_lasergun(world, game::lasergun_type::WAFFLE, physical);
	waffle.childgun = &childgun;
}

void game::delete_waffle(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_player.destroy(entity.take_component<comp::atlas_renderable>());
	auto &waffle = entity.take_component<comp::waffle>();
	auto &child = *waffle.childgun;
	world.objectdb.waffle.destroy(waffle);

	auto *wander = entity.try_take_component<comp::wander>();
	if(wander != NULL)
		world.objectdb.wander.destroy(*wander);

	auto *attack = entity.try_take_component<comp::attack>();
	if(attack != NULL)
		world.objectdb.attack.destroy(*attack);

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);

	game::delete_lasergun(world, child);
}


/////////////////////////
// laser guns
/////////////////////////
ent::entity &game::new_lasergun(game::world &world, const game::lasergun_type type, const comp::physical &parent_physical)
{
	int texture;
	int maxcooldown;
	float width;
	float height;
	float speed;
	float damage;
	win::color color;

	switch(type)
	{
		case game::lasergun_type::WAFFLE:
			texture = game::asset::aid::LASERGUN_WAFFLE;
			maxcooldown = LASERGUN_WAFFLE_MAX_COOLDOWN;
			width = LASERGUN_WAFFLE_WIDTH;
			height = LASERGUN_WAFFLE_HEIGHT;
			speed = LASERGUN_WAFFLE_SPEED;
			damage = LASERGUN_WAFFLE_DAMAGE;
			color.red = 0.0f;
			color.green = 1.0f;
			color.blue = 0.0f;
			break;
		case game::lasergun_type::PLAYER:
			texture = game::asset::aid::LASERGUN_WAFFLE;
			maxcooldown = LASERGUN_PLAYER_MAX_COOLDOWN;
			width = LASERGUN_PLAYER_WIDTH;
			height = LASERGUN_PLAYER_HEIGHT;
			speed = LASERGUN_PLAYER_SPEED;
			damage = LASERGUN_PLAYER_DAMAGE;
			color.red = 1.0f;
			color.green = 0.0f;
			color.blue = 0.0f;
			break;
	}

	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, 0.0f, 0.0f, width, height, 0.0f);
	auto &lasergun = world.objectdb.lasergun.create(entity, parent_physical, maxcooldown, color, speed, damage);
	auto &renderable = world.objectdb.atlas_renderable_lasergun.create(entity, world.asset.atlas.coords(texture));

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
void game::new_laser(game::world &world, const comp::physical &gun_physical, const comp::lasergun &gun, int slot, const win::color &color, float speed, int dmg)
{
	auto &entity = world.objectdb.entity.create();

	float x = gun_physical.x + (gun_physical.w / 2.0f) - (LASER_WIDTH / 2.0f);
	float y = gun_physical.y + (gun_physical.h / 2.0f) - (LASER_HEIGHT / 2.0f);

	x = x + cosf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;
	y = y + sinf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;

	auto &physical = world.objectdb.physical.create(entity, x, y, LASER_WIDTH, LASER_HEIGHT, gun_physical.rot);
	auto &renderable = world.objectdb.atlas_renderable_laser.create(entity, world.asset.atlas.coords(game::asset::aid::LASER));
	auto &glow_renderable = world.objectdb.glow_renderable.create(entity, color, 0.55f, 0.8f);
	auto &laser = world.objectdb.laser.create(entity, physical.rot, speed, dmg);

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

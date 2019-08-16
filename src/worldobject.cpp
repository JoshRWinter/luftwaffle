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
	auto &health = world.objectdb.health.create(entity, 250);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(player);
	entity.attach(health);

	auto &childgun = game::new_lasergun(world, game::lasergun_type::PLAYER, physical);
	player.childgun = &childgun;
}

/////////////////////////
// toaster
/////////////////////////
void game::new_toaster(game::world &world, int sequence)
{
	if(world.objectdb.toaster.count() != 0)
		win::bug("already a toaster");

	auto &entity = world.objectdb.entity.create();

	float xpos = sequence == 0 ? 5.0f : mersenne(-30, 30);
	float ypos = sequence == 0 ? 1.0f : mersenne(-30, 30);

	auto &physical = world.objectdb.physical.create(entity, xpos, ypos, TOASTER_WIDTH, TOASTER_HEIGHT, (M_PI / 2.0f) * mersenne(0, 3));
	auto &renderable = world.objectdb.atlas_renderable_toaster.create(entity, world.asset.atlas.coords(game::asset::aid::TOASTER));
	auto &health = world.objectdb.health.create(entity, 250);
	auto &toaster = world.objectdb.toaster.create(entity);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(health);
	entity.attach(toaster);
}

void game::delete_toaster(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.toaster.destroy(entity.take_component<comp::toaster>());
	world.objectdb.atlas_renderable_toaster.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.health.destroy(entity.take_component<comp::health>());

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
	auto &health = world.objectdb.health.create(entity, type == comp::waffle::waffle_type::NORMAL ? 100 : 200);
	auto &waffle = world.objectdb.waffle.create(entity, type);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(wander);
	entity.attach(health);
	entity.attach(waffle);

	// the laser gun child entity
	auto &childgun = game::new_lasergun(world, game::lasergun_type::WAFFLE, physical);
	waffle.childgun = &childgun;
}

void game::delete_waffle(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_waffle.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.health.destroy(entity.take_component<comp::health>());
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
		case game::lasergun_type::GORING:
			texture = game::asset::aid::GORING_GUN;
			maxcooldown = LASERGUN_GORING_MAX_COOLDOWN;
			width = LASERGUN_GORING_WIDTH;
			height = LASERGUN_GORING_HEIGHT;
			speed = LASERGUN_GORING_SPEED;
			damage = LASERGUN_GORING_DAMAGE;
			color.red = 1.0f;
			color.green = 0.0f;
			color.blue = 1.0f;
			break;
		case game::lasergun_type::HITLER:
			texture = game::asset::aid::HITLER_GUN;
			maxcooldown = LASERGUN_HITLER_MAX_COOLDOWN;
			width = LASERGUN_HITLER_WIDTH;
			height = LASERGUN_HITLER_HEIGHT;
			speed = LASERGUN_HITLER_SPEED;
			damage = LASERGUN_HITLER_DAMAGE;
			color.red = 1.0f;
			color.green = 0.0f;
			color.blue = 1.0f;
			break;
	}

	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, 0.0f, 0.0f, width, height, 0.0f);
	auto &lasergun = world.objectdb.lasergun.create(entity, parent_physical, maxcooldown, color, speed, damage);
	auto &renderable = world.objectdb.atlas_renderable_lasergun.create(entity, world.asset.atlas.coords(texture));

	switch(type)
	{
		case game::lasergun_type::GORING:
			lasergun.guns[0].distance = 2.1f;
			lasergun.guns[0].angle_offset = 0.17f;
			lasergun.guns[1].distance = 2.1f;
			lasergun.guns[1].angle_offset = -0.17f;
		break;
		case game::lasergun_type::HITLER:
			lasergun.guns[0].distance = 1.7f;
			lasergun.guns[0].angle_offset = 0.17f;
			lasergun.guns[1].distance = 1.7f;
			lasergun.guns[1].angle_offset = -0.17f;
		break;
		default: break;
	}

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

/////////////////////////
// missiles
/////////////////////////

void game::new_missile(game::world &world, const comp::physical &gun_physical, const comp::lasergun &gun, const int slot)
{
	auto &entity = world.objectdb.entity.create();

	float x = gun_physical.x + (gun_physical.w / 2.0f) - (LASER_WIDTH / 2.0f);
	float y = gun_physical.y + (gun_physical.h / 2.0f) - (LASER_HEIGHT / 2.0f);

	x = x + cosf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;
	y = y + sinf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;

	auto &physical = world.objectdb.physical.create(entity, x, y, game::MISSILE_WIDTH, game::MISSILE_HEIGHT, gun_physical.rot);
	auto &renderable = world.objectdb.atlas_renderable_missile.create(entity, world.asset.atlas.coords(game::asset::aid::MISSILE));
	auto &missile = world.objectdb.missile.create(entity, physical.rot);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(missile);
}

void game::delete_missile(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_missile.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.missile.destroy(entity.take_component<comp::missile>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// explosion
/////////////////////////
void game::new_explosion(game::world &world, const float x, const float y, const float scale)
{
	// cloud
	{
		auto &entity = world.objectdb.entity.create();

		auto &physical = world.objectdb.physical.create(entity, x - (CLOUD_STARTING_SIZE / 2.0f), y - (CLOUD_STARTING_SIZE / 2.0f), CLOUD_STARTING_SIZE, CLOUD_STARTING_SIZE, mersenne(0, M_PI * 2.0));
		auto &renderable = world.objectdb.atlas_renderable_explosion_cloud.create(entity, world.asset.atlas.coords(game::asset::aid::EXPLOSION_CLOUD));
		auto &cloud = world.objectdb.explosion_cloud.create(entity, scale);

		entity.attach(physical);
		entity.attach(renderable);
		entity.attach(cloud);
	}

	// arms
	int arms;
	if(scale < 2.0f)
		arms = 3;
	else if(scale < 3)
		arms = 5;
	else
		arms = 7;

	const float spacing = (M_PI * 2.0) / arms;
	for(int i = 0; i < arms; ++i)
	{
		auto &entity = world.objectdb.entity.create();

		const float variance = 0.35f;
		float angle = (spacing * i) + mersenne(-variance, variance);

		auto &physical = world.objectdb.physical.create(entity, x, y, 0.0f, 0.0f, 0.0f);
		auto &arm = world.objectdb.explosion_arm.create(entity, angle, scale);

		entity.attach(physical);
		entity.attach(arm);
	}

	int particles;
	if(scale < 2.0f)
		particles = 5;
	if(scale < 3.0f)
		particles = 7;
	else
		particles = 9;

	for(int i = 0; i < particles; ++i)
	{
		auto &entity = world.objectdb.entity.create();

		const float box = scale / 3.0f;
		const float xpos = x + mersenne(-box, box);
		const float ypos = y + mersenne(-box, box);

		auto &physical = world.objectdb.physical.create(entity, xpos, ypos, 0.0f, 0.0f, 0.0f);
		auto &renderable = world.objectdb.atlas_renderable_explosion_particle.create(entity, world.asset.atlas.coords(game::asset::aid::EXPLOSION_PARTICLE_RED + mersenne(0, 2)));
		auto &particle = world.objectdb.explosion_particle.create(entity, scale);

		entity.attach(physical);
		entity.attach(renderable);
		entity.attach(particle);
	}
}

void game::delete_explosion_cloud(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_explosion_cloud.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.explosion_cloud.destroy(entity.take_component<comp::explosion_cloud>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

void game::delete_explosion_arm(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.explosion_arm.destroy(entity.take_component<comp::explosion_arm>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

void game::delete_explosion_particle(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_explosion_particle.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.explosion_particle.destroy(entity.take_component<comp::explosion_particle>());
}

/////////////////////////
// particle: smoke
/////////////////////////
void game::new_particle_smoke(game::world &world, const float x, const float y, const float size)
{
	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, x - (size / 2.0f), y - (size / 2.0f), size, size, mersenne(0, 2 * M_PI));
	auto &smoke = world.objectdb.particle_smoke.create(entity);
	auto &renderable = world.objectdb.atlas_renderable_particle_smoke.create(entity, world.asset.atlas.coords(game::asset::aid::SMOKE));

	entity.attach(physical);
	entity.attach(smoke);
	entity.attach(renderable);
}

void game::delete_particle_smoke(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.particle_smoke.destroy(entity.take_component<comp::particle_smoke>());
	world.objectdb.atlas_renderable_particle_smoke.destroy(entity.take_component<comp::atlas_renderable>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// particle: laser
/////////////////////////
void game::new_particle_laser(game::world &world, const float xpos, const float ypos, const float angle, const win::color &color)
{
	const int count = mersenne(2, 4);
	for(int i = 0; i < count; ++i)
	{
		auto &entity = world.objectdb.entity.create();

		const float adjust = 0.35f;
		const float adjusted_angle = angle + mersenne(-adjust, adjust);

		auto &physical = world.objectdb.physical.create(entity, xpos, ypos, game::PARTICLE_LASER_WIDTH, game::PARTICLE_LASER_HEIGHT, adjusted_angle);
		auto &particle = world.objectdb.particle_laser.create(entity, adjusted_angle);
		auto &renderable = world.objectdb.atlas_renderable_particle_laser.create(entity, world.asset.atlas.coords(game::asset::aid::LASER), color);

		entity.attach(physical);
		entity.attach(particle);
		entity.attach(renderable);
	}
}

void game::delete_particle_laser(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.particle_laser.destroy(entity.take_component<comp::particle_laser>());
	world.objectdb.atlas_renderable_particle_laser.destroy(entity.take_component<comp::atlas_renderable>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// goring
/////////////////////////
void game::new_goring(game::world &world, const float xpos, const float ypos)
{
	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, xpos, ypos, GORING_SIZE, GORING_SIZE, 0.0f);
	auto &renderable = world.objectdb.atlas_renderable_goring.create(entity, world.asset.atlas.coords(game::asset::aid::GORING));
	auto &health = world.objectdb.health.create(entity, 200);
	auto &goring = world.objectdb.goring.create(entity);

	auto &childgun = new_lasergun(world, game::lasergun_type::GORING, physical);
	goring.childgun = &childgun;

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(health);
	entity.attach(goring);
}

void game::delete_goring(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_goring.destroy(entity.take_component<comp::atlas_renderable>());
	auto &goring = entity.take_component<comp::goring>();
	auto childgun = goring.childgun;
	world.objectdb.goring.destroy(goring);

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);

	game::delete_lasergun(world, *childgun);
}

/////////////////////////
// hitler
/////////////////////////
void game::new_hitler(game::world &world, const float xpos, const float ypos)
{
	auto &entity = world.objectdb.entity.create();

	auto &physical = world.objectdb.physical.create(entity, xpos, ypos, game::HITLER_SIZE, game::HITLER_SIZE, 0.0f);
	auto &renderable = world.objectdb.atlas_renderable_hitler.create(entity, world.asset.atlas.coords(game::asset::aid::HITLER));
	auto &health = world.objectdb.health.create(entity, 400);
	auto &hitler = world.objectdb.hitler.create(entity);

	hitler.childgun = &game::new_lasergun(world, game::lasergun_type::HITLER, physical);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(health);
	entity.attach(hitler);
}

void game::delete_hitler(game::world &world, ent::entity &entity)
{
	auto &hitler = entity.take_component<comp::hitler>();
	auto childgun = hitler.childgun;

	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_hitler.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.hitler.destroy(hitler);

	game::delete_lasergun(world, *childgun);

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

/////////////////////////
// hitler
/////////////////////////
void game::new_bomb(game::world &world, const comp::physical &gun_physical, const comp::lasergun &gun, const int slot)
{
	auto &entity = world.objectdb.entity.create();

	float x = gun_physical.x + (gun_physical.w / 2.0f) - (LASER_WIDTH / 2.0f);
	float y = gun_physical.y + (gun_physical.h / 2.0f) - (LASER_HEIGHT / 2.0f);

	x = x + cosf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;
	y = y + sinf(gun_physical.rot + gun.guns[slot].angle_offset) * gun.guns[slot].distance;

	auto &physical = world.objectdb.physical.create(entity, x, y, game::BOMB_WIDTH, game::BOMB_HEIGHT, mersenne(0, M_PI * 2.0f));
	auto &renderable = world.objectdb.atlas_renderable_bomb.create(entity, world.asset.atlas.coords(game::asset::aid::BOMB));
	auto &bomb = world.objectdb.bomb.create(entity, gun_physical.rot);

	entity.attach(physical);
	entity.attach(renderable);
	entity.attach(bomb);
}

void game::delete_bomb(game::world &world, ent::entity &entity)
{
	world.objectdb.physical.destroy(entity.take_component<comp::physical>());
	world.objectdb.atlas_renderable_bomb.destroy(entity.take_component<comp::atlas_renderable>());
	world.objectdb.bomb.destroy(entity.take_component<comp::bomb>());

	entity.cleanup_check();
	world.objectdb.entity.destroy(entity);
}

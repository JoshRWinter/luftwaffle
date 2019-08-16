#include "../luftwaffle.hpp"

void sys::player(game::world &world)
{
	if(world.objectdb.player.count() == 0)
		game::new_player(world);

	auto &player = *world.objectdb.player.begin();

	auto &physical = player.entity.component<comp::physical>();
	auto &gun = player.childgun->component<comp::lasergun>();
	auto &health = player.entity.component<comp::health>();

	if(health.hitpoints < 1)
	{
		if(player.dead_timer++ == 0)
			game::new_explosion(world, physical.x + (game::PLAYER_WIDTH / 2.0f), physical.y + (game::PLAYER_HEIGHT / 2.0f), 1.25f);

		return;
	}

	// handle firing the guns
	if(world.input.left_click)
	{
		if(player.laser_count > 0)
		{
			gun.firing_laser = true;
			player.laser_refill_timer = 60;
		}
	}
	else gun.firing_laser = false;

	if(world.input.right_click)
	{
		if(player.rocket_count > 0)
		{
			gun.firing_missile = true;
			player.rocket_refill_timer = 200;
		}
	}
	else gun.firing_missile = false;

	if(--player.laser_refill_timer < 1)
	{
		if(--player.laser_refill_rate_timer < 1)
		{
			player.laser_refill_rate_timer = 5;
			if(++player.laser_count > comp::player::MAX_LASER_COUNT)
				player.laser_count = comp::player::MAX_LASER_COUNT;
		}
	}

	if(--player.rocket_refill_timer < 1)
	{
		if(--player.rocket_refill_rate_timer < 1)
		{
			player.rocket_refill_rate_timer = 10;
			if(++player.rocket_count > comp::player::MAX_ROCKET_COUNT)
				player.rocket_count = comp::player::MAX_ROCKET_COUNT;
		}
	}

	// point at the mouse
	physical.rot = win::align(physical.rot, atan2f(world.cursor.y, world.cursor.x), 0.2f);

	// movement
	const float DECEL = 0.0005f;
	const float ACCEL = 0.001f;
	const float MAX_SPEED = 0.05f;

	player.xv = win::zerof(player.xv, DECEL);
	player.yv = win::zerof(player.yv, DECEL);

	player.xv += cosf(world.input.direction) * ACCEL * world.input.speed;
	player.yv += sinf(world.input.direction) * ACCEL * world.input.speed;

	if(player.xv > MAX_SPEED) player.xv = MAX_SPEED;
	else if(player.xv < -MAX_SPEED) player.xv = -MAX_SPEED;
	if(player.yv > MAX_SPEED) player.yv = MAX_SPEED;
	else if(player.yv < -MAX_SPEED) player.yv = -MAX_SPEED;

	physical.x += player.xv;
	physical.y += player.yv;
}

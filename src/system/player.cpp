#include "../luftwaffle.hpp"

void sys::player(game::world &world)
{
	if(world.objectdb.player.count() == 0)
		game::new_player(world);

	auto &player = *world.objectdb.player.begin();

	auto &physical = player.entity.component<comp::physical>();
	auto &gun = player.childgun->component<comp::lasergun>();

	// handle firing the guns
	gun.firing_laser = world.input.left_click;
	gun.firing_missile = world.input.right_click;

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

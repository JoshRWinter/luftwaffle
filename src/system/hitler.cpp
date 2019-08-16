#include "../luftwaffle.hpp"

void sys::hitler(game::world &world)
{
	if(world.objectdb.hitler.count() != 1)
		return;

	auto &hitler = world.objectdb.hitler.begin()->entity.component<comp::hitler>();
	auto &physical = hitler.entity.component<comp::physical>();
	auto &player_physical = world.objectdb.player.begin()->entity.component<comp::physical>();
	auto &gun = hitler.childgun->component<comp::lasergun>();
	auto &health = hitler.entity.component<comp::health>();

	if(health.hitpoints < 1)
	{
		game::new_explosion(world, physical.x + (game::HITLER_SIZE / 2.0f), physical.y + (game::HITLER_SIZE / 2.0f), 5.0f);
		game::delete_hitler(world, hitler.entity);
		return;
	}

	const float player_angle = atan2f((player_physical.y + (game::PLAYER_HEIGHT / 2.0f)) - (physical.y + (game::HITLER_SIZE / 2.0f)),
							(player_physical.x + (game::PLAYER_WIDTH / 2.0f)) - (physical.x + (game::HITLER_SIZE / 2.0f)));

	physical.rot = player_angle;

	const float center_x = physical.x + (game::HITLER_SIZE / 2.0f);
	const float center_y = physical.y + (game::HITLER_SIZE / 2.0f);

	// jump around
	if(--hitler.timer_next_jump < 1 && !hitler.jumping)
	{
		hitler.timer_next_jump = mersenne(190, 230);
		hitler.jumping = true;
		hitler.target_angle += mersenne(2) ? (-M_PI / 2.0f) : (M_PI / 2.0f);

		const float dist = 4.5f;
		hitler.jumptarget_x = (player_physical.x + (game::PLAYER_WIDTH / 2.0f)) + (cosf(hitler.target_angle) * dist);
		hitler.jumptarget_y = (player_physical.y + (game::PLAYER_HEIGHT / 2.0f)) + (sinf(hitler.target_angle) * dist);
	}
	else if(hitler.jumping)
	{
		const float tolerance = 0.2f;

		if(fabsf(center_x - hitler.jumptarget_x) < tolerance && fabsf(center_y - hitler.jumptarget_y) < tolerance)
		{
			hitler.jumping = false;
		}

		const float jump_speed = 0.1f;
		const float jump_angle = atan2f(hitler.jumptarget_y - (physical.y + (game::HITLER_SIZE / 2.0f)), hitler.jumptarget_x - (physical.x + (game::HITLER_SIZE / 2.0f)));
		physical.x += cosf(jump_angle) * jump_speed;
		physical.y += sinf(jump_angle) * jump_speed;
	}

	if(!hitler.jumping)
	{
		if(gun.firing_laser && mersenne(30))
			gun.firing_laser = false;
		if(!gun.firing_laser && mersenne(45))
			gun.firing_laser = true;

		if(gun.firing_bomb && mersenne(30))
			gun.firing_bomb = false;
		if(!gun.firing_bomb && mersenne(70))
			gun.firing_bomb = true;
	}
	else
	{
		gun.firing_laser = false;
		gun.firing_bomb = false;
	}
}

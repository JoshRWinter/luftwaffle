#include "../luftwaffle.hpp"

void sys::goring(game::world &world)
{
	if(world.objectdb.goring.count() != 1)
		return;// game::new_goring(world, 5, 1);

	auto &goring = *world.objectdb.goring.begin();
	auto &physical = goring.entity.component<comp::physical>();
	auto &player_physical = world.objectdb.player.begin()->entity.component<comp::physical>();
	auto &gun = goring.childgun->component<comp::lasergun>();

	const float player_angle = atan2f((player_physical.y + (game::PLAYER_HEIGHT / 2.0f)) - (physical.y + (game::GORING_SIZE / 2.0f)),
							(player_physical.x + (game::PLAYER_WIDTH / 2.0f)) - (physical.x + (game::GORING_SIZE / 2.0f)));

	// face the player
	physical.rot = player_angle;

	if(--goring.moving_type_timer < 1)
	{
		goring.moving = (comp::goring::moving_type)mersenne(0, 2);
		goring.moving_type_timer = mersenne(10, 100);
	}

	float xv = 0.0f, yv = 0.0f;

	static constexpr float max_speed = 0.03f;
	const float accel = 0.001f;
	if(goring.moving != comp::goring::moving_type::NONE)
	{
		goring.speed += accel;
		if(goring.speed > max_speed)
			goring.speed = max_speed;

		float move_angle;
		if(goring.moving == comp::goring::moving_type::CLOCKWISE)
			move_angle = player_angle + ((3.0 * M_PI) / 2.0f);
		else
			move_angle = player_angle + (M_PI / 2.0f);

		xv = cosf(move_angle) * goring.speed;
		yv = sinf(move_angle) * goring.speed;
	}
	else
		goring.speed = win::zerof(goring.speed, accel);

	physical.x += xv;
	physical.y += yv;

	// fire guns
	if(mersenne(30))
		gun.firing_laser = !gun.firing_laser;
}

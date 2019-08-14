#include "../luftwaffle.hpp"

void sys::explosion_arm(game::world &world)
{
	for(auto &arm : world.objectdb.explosion_arm)
	{
		auto &physical = arm.entity.component<comp::physical>();

		physical.x += cosf(arm.angle) * arm.speed;
		physical.y += sinf(arm.angle) * arm.speed;

		arm.angle += arm.angle_update;
		arm.speed -= arm.retard;

		if(--arm.smoke_timer < 1)
		{
			arm.smoke_timer = (1.0f / arm.speed) / 15.0f;
			game::new_particle_smoke(world, physical.x, physical.y, arm.speed * 6.3f);
		}

		if(arm.speed < 0.0f)
			delete_explosion_arm(world, arm.entity);
	}
}

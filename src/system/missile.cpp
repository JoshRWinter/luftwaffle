#include "../luftwaffle.hpp"

void sys::missile(game::world &world)
{
	for(auto &missile : world.objectdb.missile)
	{
		auto &physical = missile.entity.component<comp::physical>();

		missile.speed += 0.002f;
		missile.xv = cosf(missile.angle) * missile.speed;
		missile.yv = sinf(missile.angle) * missile.speed;

		physical.x += missile.xv;
		physical.y += missile.yv;

		if(--missile.ttl < 1)
			game::delete_missile(world, missile.entity);
	}
}

#include "../luftwaffle.hpp"

void sys::laser(game::world &world)
{
	for(comp::laser &laser : world.objectdb.laser)
	{
		auto &physical = laser.entity.component<comp::physical>();

		--laser.arming_timer;

		physical.x += laser.xv;
		physical.y += laser.yv;

		// look for health objects to collide with
		bool stop = false;
		if(laser.arming_timer < 1)
		for(auto &health : world.objectdb.health)
		{
			auto &phys = health.entity.component<comp::physical>();

			if(physical.collide(phys))
			{
				health.hitpoints -= laser.damage;

				game::delete_laser(world, laser.entity);
				stop = true;
				break;
			}
		}
		if(stop)
			continue;

		if(--laser.ttl < 1)
			game::delete_laser(world, laser.entity);
	}
}

#include "../luftwaffle.hpp"

void sys::laser(game::world &world)
{
	for(comp::laser &laser : world.objectdb.laser)
	{
		comp::physical &physical = laser.entity.component<comp::physical>();

		physical.x += laser.xv;
		physical.y += laser.yv;

		if(--laser.ttl < 1)
			game::delete_laser(world, laser.entity);
	}
}

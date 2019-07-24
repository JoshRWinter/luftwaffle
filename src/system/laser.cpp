#include "../luftwaffle.hpp"

void sys::laser(game::world &world)
{
	for(comp::laser &laser : world.objectdb.lasers)
	{
		ent::entity &entity = laser.parent;
		comp::physical &physical = entity.component<comp::physical>();

		physical.x += laser.xv;
		physical.y += laser.yv;

		if(--laser.ttl < 1)
			game::delete_laser(world, entity);
	}
}

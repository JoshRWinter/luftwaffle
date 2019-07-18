#include "../luftwaffle.hpp"

void sys::lasergun(game::world &world)
{
	for(comp::lasergun &lasergun : world.objectdb.laserguns)
	{
		ent::entity &entity = lasergun.parent;
		comp::physical &physical = *entity.component<comp::physical>();
		const comp::physical &parent_physical = lasergun.waffle;

		physical.x = parent_physical.x + (parent_physical.w / 2.0f) - (physical.w / 2.0f);
		physical.y = parent_physical.y + (parent_physical.h / 2.0f) - (physical.h / 2.0f);
		physical.rot = parent_physical.rot;
	}
}

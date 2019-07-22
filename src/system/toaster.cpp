#include "../luftwaffle.hpp"

void sys::toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 1)
		ent::new_toaster(world);

	comp::toaster &toaster = *world.objectdb.toaster.begin();

	if(--toaster.spawn_timer == 0)
	{
		toaster.spawn_timer = mersenne(comp::toaster::SPAWN_TIMER_LOW, comp::toaster::SPAWN_TIMER_HIGH);
		ent::new_waffle(world, toaster.parent.component<comp::physical>());
	}
}

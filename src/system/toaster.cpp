#include "../luftwaffle.hpp"

void sys::toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 1)
		game::new_toaster(world);

	auto &toaster = *world.objectdb.toaster.begin();
	auto &physical = toaster.entity.component<comp::physical>();

	if(--toaster.spawn_timer == 0)
	{
		toaster.spawn_timer = mersenne(comp::toaster::SPAWN_TIMER_LOW, comp::toaster::SPAWN_TIMER_HIGH);
		//game::new_waffle(world, physical, mersenne(4) ? comp::waffle::waffle_type::MID : comp::waffle::waffle_type::NORMAL);
	}
}

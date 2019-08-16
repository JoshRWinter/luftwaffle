#include "../luftwaffle.hpp"

void sys::toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 1)
		game::new_toaster(world, world.toaster_sequence);

	auto &toaster = *world.objectdb.toaster.begin();
	auto &physical = toaster.entity.component<comp::physical>();
	auto &health = toaster.entity.component<comp::health>();

	if(--toaster.spawn_timer == 0)
	{
		toaster.spawn_timer = mersenne(comp::toaster::SPAWN_TIMER_LOW, comp::toaster::SPAWN_TIMER_HIGH);
		game::new_waffle(world, physical, mersenne(4) ? comp::waffle::waffle_type::MID : comp::waffle::waffle_type::NORMAL);
	}

	if(health.hitpoints < 1)
	{
		game::delete_toaster(world, toaster.entity);
		++world.toaster_sequence;
		game::new_explosion(world, physical.x + (game::TOASTER_WIDTH / 2.0f), physical.y + (game::TOASTER_HEIGHT / 2.0f), 2.6f);

		switch(world.toaster_sequence)
		{
			case 1:
				game::new_goring(world, physical.x + 5.0f, physical.y);
				break;
			case 2:
				game::new_hitler(world, physical.x - 5.0f, physical.y);
				break;
		}
	}
}

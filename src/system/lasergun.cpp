#include "../luftwaffle.hpp"

void sys::lasergun(game::world &world)
{
	for(comp::lasergun &lasergun : world.objectdb.lasergun)
	{
		auto &physical = lasergun.entity.component<comp::physical>();
		const auto &parent_physical = lasergun.parent_physical;

		physical.x = parent_physical.x + (parent_physical.w / 2.0f) - (physical.w / 2.0f);
		physical.y = parent_physical.y + (parent_physical.h / 2.0f) - (physical.h / 2.0f);
		physical.rot = parent_physical.rot;

		if(lasergun.timer_cooldown > 0)
			--lasergun.timer_cooldown;

		else if(lasergun.firing_laser)
		{
			game::new_laser(world, physical, lasergun, lasergun.last_slot = !lasergun.last_slot, lasergun.color, lasergun.speed, lasergun.damage);
			lasergun.timer_cooldown = lasergun.max_timer_cooldown;
		}
		else if(lasergun.firing_missile)
		{
			game::new_missile(world, physical, lasergun, lasergun.last_slot = !lasergun.last_slot);
			lasergun.timer_cooldown = lasergun.max_timer_cooldown * 2;
		}
		else if(lasergun.firing_bomb)
		{
			game::new_bomb(world, physical, lasergun, lasergun.last_slot = !lasergun.last_slot);
			lasergun.timer_cooldown = lasergun.max_timer_cooldown * 2;
		}
	}
}

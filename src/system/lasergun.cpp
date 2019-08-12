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
		else if(lasergun.firing)
		{
			game::new_laser(world, physical, lasergun, 0, lasergun.color, lasergun.speed, lasergun.damage);
			lasergun.timer_cooldown = lasergun.max_timer_cooldown;
		}
	}
}

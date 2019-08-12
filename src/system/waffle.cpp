#include "../luftwaffle.hpp"

void sys::waffle(game::world &world)
{
	for(comp::waffle &waffle : world.objectdb.waffle)
	{
		auto *attack = waffle.entity.try_component<comp::attack>();
		auto *wander = waffle.entity.try_component<comp::wander>();

		auto &physical = waffle.entity.component<comp::physical>();

		auto &player = *world.objectdb.player.begin();
		auto &player_physical = player.entity.component<comp::physical>();

		const float dist = win::distance(physical.x + (physical.w / 2.0f), physical.y + (physical.h / 2.0f), player_physical.x + (game::PLAYER_WIDTH / 2.0f), player_physical.y + (game::PLAYER_HEIGHT / 2.0f));
		if(dist < 3.0f)
		{
			if(wander != NULL)
			{
				world.objectdb.wander.destroy(waffle.entity.take_component<comp::wander>());
				comp::attack &new_attack = world.objectdb.attack.create(waffle.entity, physical);

				waffle.entity.attach(new_attack);
			}
		}
		else if(dist > 9.0f)
		{
			if(attack != NULL)
			{
				world.objectdb.attack.destroy(waffle.entity.take_component<comp::attack>());
				comp::wander &new_wander = world.objectdb.wander.create(waffle.entity, physical.x + (physical.w / 2.0f), physical.y + (physical.h / 2.0f), physical.rot);

				waffle.entity.attach(new_wander);
			}
		}
	}
}

#include "../luftwaffle.hpp"

void sys::waffle(game::world &world)
{
	for(comp::waffle &waffle : world.objectdb.waffle)
	{
		comp::attack *const attack = waffle.parent.try_component<comp::attack>();
		comp::wander *const wander = waffle.parent.try_component<comp::wander>();

		comp::physical &physical = waffle.parent.component<comp::physical>();

		comp::player &player = *world.objectdb.player.begin();
		comp::physical &player_physical = player.parent.component<comp::physical>();

		const float dist = win::distance(physical.x + (physical.w / 2.0f), physical.y + (physical.h / 2.0f), player_physical.x + (game::PLAYER_WIDTH / 2.0f), player_physical.y + (game::PLAYER_HEIGHT / 2.0f));
		if(dist < 3.0f)
		{
			if(wander != NULL)
			{
				world.objectdb.wander.destroy(waffle.parent.take_component<comp::wander>());
				comp::attack &new_attack = world.objectdb.attack.create(waffle.parent, physical);

				waffle.parent.attach(new_attack);
			}
		}
		else if(dist > 9.0f)
		{
			if(attack != NULL)
			{
				world.objectdb.attack.destroy(waffle.parent.take_component<comp::attack>());
				comp::wander &new_wander = world.objectdb.wander.create(waffle.parent, physical.x + (physical.w / 2.0f), physical.y + (physical.h / 2.0f), physical.rot);

				waffle.parent.attach(new_wander);
			}
		}
	}
}

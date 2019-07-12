#include "../luftwaffle.hpp"

void sys::player(game::world &world)
{
	if(world.objectdb.player.count() == 0)
		ent::new_player(world);
}

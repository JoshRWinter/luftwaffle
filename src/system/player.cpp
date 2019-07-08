#include "../luftwaffle.hpp"

void sys::player(game::world &world)
{
	if(world.componentdb.player == NULL)
		ent::new_player(world);
}

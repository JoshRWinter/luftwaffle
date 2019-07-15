#include "../luftwaffle.hpp"

void sys::toaster(game::world &world)
{
	if(world.objectdb.toaster.count() != 1)
		ent::new_toaster(world);
}

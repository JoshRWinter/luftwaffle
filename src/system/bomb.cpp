#include "../luftwaffle.hpp"

void sys::bomb(game::world &world)
{
	for(auto &bomb : world.objectdb.bomb)
	{
		auto &physical = bomb.entity.component<comp::physical>();

		physical.x += bomb.xv;
		physical.y += bomb.yv;

		physical.rot += bomb.rotspeed;

		if(--bomb.ttl < 1)
		{
			game::new_explosion(world, physical.x + (game::BOMB_WIDTH / 2.0f), physical.y + (game::BOMB_HEIGHT / 2.0f), 1.75f);
			game::delete_bomb(world, bomb.entity);
		}
	}
}

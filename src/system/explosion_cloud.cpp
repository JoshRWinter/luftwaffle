#include "../luftwaffle.hpp"

void sys::explosion_cloud(game::world &world)
{
	for(auto &cloud : world.objectdb.explosion_cloud)
	{
		auto &physical = cloud.entity.component<comp::physical>();

		if(--cloud.shrink_timer > 0)
		{
			const float grow = (cloud.scale - physical.w) / 6.0f;

			physical.w += grow;
			physical.h = physical.w;

			physical.x -= grow / 2.0f;
			physical.y -= grow / 2.0f;
		}
		else
		{
			const float shrink = 0.08f;
			physical.w -= shrink;
			physical.h = physical.w;

			physical.x += shrink / 2.0f;
			physical.y += shrink / 2.0f;

			if(physical.w < 0.0f)
			{
				delete_explosion_cloud(world, cloud.entity);
			}
		}
	}
}

#include "../luftwaffle.hpp"

void sys::explosion_cloud(game::world &world)
{
	for(auto &cloud : world.objectdb.explosion_cloud)
	{
		auto &physical = cloud.entity.component<comp::physical>();

		const float grow = (cloud.scale - physical.w) / 6.0f;

		physical.w += grow;
		physical.h += grow;

		physical.x -= grow / 2.0f;
		physical.y -= grow / 2.0f;
	}
}

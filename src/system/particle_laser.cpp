#include "../luftwaffle.hpp"

void sys::particle_laser(game::world &world)
{
	for(auto &particle : world.objectdb.particle_laser)
	{
		auto &physical = particle.entity.component<comp::physical>();

		physical.x += particle.xv;
		physical.y += particle.yv;

		if(--particle.ttl < 1)
		{
			game::delete_particle_laser(world, particle.entity);
		}
	}
}

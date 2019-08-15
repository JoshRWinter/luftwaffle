#include "../luftwaffle.hpp"

void sys::explosion_particle(game::world &world)
{
	for(auto &particle : world.objectdb.explosion_particle)
	{
		auto &physical = particle.entity.component<comp::physical>();

		if(--particle.start_timer > 0)
			continue;

		const float grow_rate = 0.06f;
		if(particle.growing)
		{
			if(physical.w < particle.target_size)
			{
				physical.w += grow_rate;
				physical.h = physical.w;

				physical.x -= grow_rate / 2.0f;
				physical.y -= grow_rate / 2.0f;
			}
			else if(--particle.freeze_timer < 1)
				particle.growing = false;
		}
		else
		{
			physical.w -= grow_rate;
			physical.h = physical.w;

			physical.x += grow_rate / 2.0f;
			physical.y += grow_rate / 2.0f;

			if(physical.w < 0.0f)
				delete_explosion_particle(world, particle.entity);
		}
	}
}

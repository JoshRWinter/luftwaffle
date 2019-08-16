#include "../luftwaffle.hpp"

void sys::particle_smoke(game::world &world)
{
	for(auto &smoke : world.objectdb.particle_smoke)
	{
		auto &physical = smoke.entity.component<comp::physical>();
		auto &renderable = smoke.entity.component<comp::atlas_renderable>();

		constexpr float grow = 0.01f;
		physical.w += grow;
		physical.h += grow;

		physical.x -= grow / 2.0f;
		physical.y -= grow / 2.0f;

		renderable.color.alpha -= 0.02f;
		if(renderable.color.alpha < 0.0f)
			game::delete_particle_smoke(world, smoke.entity);
	}
}

#include "../luftwaffle.hpp"

void sys::missile(game::world &world)
{
	for(auto &missile : world.objectdb.missile)
	{
		auto &physical = missile.entity.component<comp::physical>();

		missile.speed += 0.002f;
		missile.xv = cosf(missile.angle) * missile.speed;
		missile.yv = sinf(missile.angle) * missile.speed;

		physical.x += missile.xv;
		physical.y += missile.yv;

		missile.max_smoke_timer -= 0.15f;
		missile.max_smoke_timer = std::clamp(missile.max_smoke_timer, 1.999f, 100.0f);

		// look for healths to collide with
		bool stop = false;
		for(auto &health : world.objectdb.health)
		{
			const auto &phys = health.entity.component<comp::physical>();

			if(phys.collide(physical))
			{
				health.hitpoints -= 20;
				new_explosion(world, physical.x + (game::MISSILE_WIDTH / 2.0f), physical.y + (game::MISSILE_HEIGHT / 2.0f), 1.5f);
				delete_missile(world, missile.entity);
				stop = true;
				break;
			}
		}
		if(stop)
			continue;

		if(--missile.ttl < 1)
			game::delete_missile(world, missile.entity);

		if(--missile.smoke_timer < 1)
		{
			missile.smoke_timer = missile.max_smoke_timer;

			game::new_particle_smoke(world, (physical.x + (game::MISSILE_WIDTH / 2.0f)) - missile.xv, (physical.y + (game::MISSILE_HEIGHT / 2.0f)) - missile.yv, 0.2f);
		}
	}
}

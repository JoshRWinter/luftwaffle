#include "../luftwaffle.hpp"

ent::laser::laser(const float xp, const float yp, const float angle)
{
	x = xp - (WIDTH / 2.0f);
	y = yp - (HEIGHT / 2.0f);
	w = WIDTH;
	h = HEIGHT;
	rot = angle;

	ttl = TTL;
	xv = cosf(angle) * SPEED;
	yv = sinf(angle) * SPEED;
}

void ent::laser::process(game::world &world)
{
	for(auto laser = world.entity.lasers.begin(); laser != world.entity.lasers.end();)
	{
		laser->x += laser->xv;
		laser->y += laser->yv;

		if(--laser->ttl <= 0)
		{
			laser = world.entity.lasers.erase(laser);
			continue;
		}

		++laser;
	}
}

void ent::laser::render(game::renderer &renderer, const game::asset &asset, const std::vector<ent::laser> &lasers)
{
	for(const ent::laser &laser : lasers)
	{
		renderer.quad.add(laser, asset.atlas.coords(game::asset::aid::PLAYER));
	}
}

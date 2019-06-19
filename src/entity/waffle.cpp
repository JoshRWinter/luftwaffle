#include "../luftwaffle.hpp"

ent::waffle::waffle(const ent::toaster &toaster)
{
	x = (toaster.x + (ent::toaster::WIDTH / 2.0f)) - (ent::waffle::WIDTH / 2.0f);
	y = (toaster.y + (ent::toaster::HEIGHT / 2.0f)) - (ent::waffle::HEIGHT / 2.0f);
	w = ent::waffle::WIDTH;
	h = ent::waffle::HEIGHT;
	rot = toaster.rot;

	spawn_slide = SPAWN_SLIDE;
	health = 100;
}

void ent::waffle::process(game::world &world)
{
	for(auto waffle = world.entity.waffles.begin(); waffle != world.entity.waffles.end();)
	{
		if(waffle->spawn_slide > 0)
		{
			--waffle->spawn_slide;

			waffle->x += cosf(waffle->rot) * SPAWN_SLIDE_SPEED;
			waffle->y += sinf(waffle->rot) * SPAWN_SLIDE_SPEED;
		}

		++waffle;
	}
}

void ent::waffle::render(game::renderer &renderer, const game::asset &asset, const std::vector<ent::waffle> &waffles)
{
	for(const ent::waffle &waffle : waffles)
	{
		renderer.quad.add(waffle, asset.atlas.coords(game::asset::aid::PLAYER));
	}
}

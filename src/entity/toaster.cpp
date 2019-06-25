#define _USE_MATH_DEFINES
#include <math.h>

#include "../luftwaffle.hpp"

ent::toaster::toaster()
{
	iteration = 0;

	reset();
}

void ent::toaster::process(game::world &world)
{
	if(health < 1)
		reset();

	if(--spawn_timer == 0 || world.entity.waffles.size() == 0)
	{
		world.entity.waffles.push_back(ent::waffle(*this));
		spawn_timer = mersenne(SPAWN_TIMER_LOW, SPAWN_TIMER_HIGH);
	}
}

void ent::toaster::render(game::renderer &renderer, const game::asset &assets) const
{
	renderer.quad.add(*this, assets.atlas.coords(game::asset::aid::TOASTER));
}

void ent::toaster::reset()
{
	++iteration;

	health = 100;
	spawn_timer = mersenne(SPAWN_TIMER_LOW, SPAWN_TIMER_HIGH);

	x = 4.0f;//mersenne(-8.0f, 8.0f);
	y = 0.0f; //mersenne(-8.0f, 8.0f);
	w = WIDTH;
	h = HEIGHT;
	rot = (M_PI / 2.0f) * mersenne(1, 4);
}

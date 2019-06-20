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
	spawn_point.x = x;
	spawn_point.y = y;
	wait = 100;
	direction = rot;

	choose_wander_target();
}

void ent::waffle::process(game::world &world)
{
	for(auto waffle = world.entity.waffles.begin(); waffle != world.entity.waffles.end();)
	{
		// poppin' out the toaster
		if(waffle->spawn_slide > 0)
		{
			--waffle->spawn_slide;

			waffle->x += cosf(waffle->rot) * SPAWN_SLIDE_SPEED;
			waffle->y += sinf(waffle->rot) * SPAWN_SLIDE_SPEED;

			++waffle;
			continue;
		}

		// wanderin
		waffle->direction = atan2f(waffle->target.y - (waffle->y + (ent::waffle::HEIGHT / 2.0f)), waffle->target.x - (waffle->x + (ent::waffle::WIDTH / 2.0f)));

		if(waffle->wait <= 0)
		{
			waffle->align(waffle->direction, TURN_SPEED);
			waffle->x += cosf(waffle->rot) * SPEED;
			waffle->y += sinf(waffle->rot) * SPEED;
		}
		else --waffle->wait;

		if(mersenne(WAIT_PROBABLITY))
			waffle->wait = mersenne(WAIT_TIMER_LOW, WAIT_TIMER_HIGH);

		if(waffle->collide(waffle->target.x, waffle->target.y))
			waffle->choose_wander_target();

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

void ent::waffle::choose_wander_target()
{
	// choose a point near the parent toaster
	target.x = mersenne(spawn_point.x - WANDER_RANGE, spawn_point.x + WANDER_RANGE);
	target.y = mersenne(spawn_point.y - WANDER_RANGE, spawn_point.y + WANDER_RANGE);
}

#include <math.h>

#include "../luftwaffle.hpp"

ent::player::player()
{
	reset();
}

void ent::player::reset()
{
	x = 0.0f;
	w = WIDTH;
	h = HEIGHT;
	y = 0.0f;
	rot = 0.0f;

	xv = 0.0f;
	yv = 0.0f;
	fire_cooldown = 0;
}

void ent::player::process(game::world &world)
{
	align(atan2f(world.cursor.y, world.cursor.x), 0.2f);

	xv = win::zerof(xv, DECEL);
	yv = win::zerof(yv, DECEL);

	xv += cosf(world.input.direction) * ACCEL * world.input.speed;
	yv += sinf(world.input.direction) * ACCEL * world.input.speed;

	if(xv > MAX_SPEED) xv = MAX_SPEED;
	else if(xv < -MAX_SPEED) xv = -MAX_SPEED;
	if(yv > MAX_SPEED) yv = MAX_SPEED;
	else if(yv < -MAX_SPEED) yv = -MAX_SPEED;

	x += xv;
	y += yv;

	// shoot freakin lasers
	if(world.input.left_click)
	{
		if(fire_cooldown <= 0)
		{
			world.entity.lasers.push_back(ent::laser(x + (ent::player::WIDTH / 2.0f), y + (ent::player::HEIGHT / 2.0f), rot));

			fire_cooldown = FIRE_COOLDOWN;
		}
		else --fire_cooldown;
	}
}

void ent::player::render(game::renderer &renderer, const game::asset &asset) const
{
	renderer.quad.add(*this, asset.atlas.coords(0));
}

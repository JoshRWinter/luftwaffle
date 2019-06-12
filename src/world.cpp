#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: renderer(roll)
{
	reset();
}

void game::world::process()
{
	entity.player.process(*this);
}

void game::world::render()
{
	entity.player.render(renderer);

	renderer.quad.send();
}

void game::world::reset()
{
	cursor.x = 0.0f;
	cursor.y = 0.0f;


	entity.player.reset();
}

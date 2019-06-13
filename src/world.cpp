#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: asset(roll)
{
	reset();
}

void game::world::process()
{
	entity.player.process(*this);
}

void game::world::render(game::renderer &renderer)
{
	entity.player.render(renderer, asset);

	renderer.quad.send();

	renderer.drawfps();
}

void game::world::reset()
{
	entity.player.reset();
}

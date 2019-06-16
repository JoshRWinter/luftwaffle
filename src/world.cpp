#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: asset(roll)
{
	reset();
}

void game::world::process()
{
	entity.player.process(*this);
	entity.toaster.process();
}

void game::world::render(game::renderer &renderer)
{
	renderer.quad.set_center(entity.player.x, entity.player.y);

	entity.player.render(renderer, asset);
	entity.toaster.render(renderer, asset);

	renderer.quad.send();

	renderer.drawfps();
}

void game::world::reset()
{
	entity.player.reset();
}

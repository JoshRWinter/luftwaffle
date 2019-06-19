#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: asset(roll)
{
	reset();
}

void game::world::process()
{
	entity.player.process(*this);
	entity.toaster.process(*this);
	ent::waffle::process(*this);
}

void game::world::render(game::renderer &renderer)
{
	renderer.quad.set_center(entity.player.x, entity.player.y);

	glBindTexture(GL_TEXTURE_2D, asset.atlas.texture());
	entity.player.render(renderer, asset);
	entity.toaster.render(renderer, asset);
	ent::waffle::render(renderer, asset, entity.waffles);

	renderer.quad.send();

	renderer.drawfps();
}

void game::world::reset()
{
	entity.player.reset();
}

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
	ent::laser::process(*this);
}

void game::world::render(game::renderer &renderer)
{
	renderer.quad.set_center(entity.player.x + (ent::player::WIDTH / 2.0f), entity.player.y + (ent::player::HEIGHT / 2.0f));

	glBindTexture(GL_TEXTURE_2D, asset.atlas.texture());
	entity.player.render(renderer, asset);
	entity.toaster.render(renderer, asset);
	ent::waffle::render(renderer, asset, entity.waffles);
	ent::laser::render(renderer, asset, entity.lasers);

	renderer.quad.send();

	renderer.drawfps();
}

void game::world::reset()
{
	entity.player.reset();
}

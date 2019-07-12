#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: asset(roll)
{
	reset();
}

void game::world::process()
{
	sys::player(*this);
}

void game::world::render(game::renderer &renderer)
{
	for(comp::atlas_renderable &renderable : objectdb.atlas_renderables_player)
		renderer.quad.add(renderable);

	glBindTexture(GL_TEXTURE_2D, asset.atlas.texture());
	renderer.quad.send();

	renderer.drawfps();
}

void game::world::reset()
{
	objectdb.reset();
}

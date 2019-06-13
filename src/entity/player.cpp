#include "../luftwaffle.hpp"

ent::player::player()
{
	reset();
}

void ent::player::reset()
{
	x = 0.0f;
	w = SIZE;
	h = SIZE;
	y = 0.0f;
	rot = 0.0f;
}

void ent::player::process(const game::world &world)
{
	x = world.cursor.x;
	y = world.cursor.y;
}

void ent::player::render(game::renderer &renderer, const game::asset &asset) const
{
	glBindTexture(GL_TEXTURE_2D, asset.atlas.texture());
	renderer.quad.add(*this, asset.atlas.coords(0));
}

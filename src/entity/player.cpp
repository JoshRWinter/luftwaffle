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

void ent::player::render(game::renderer &renderer) const
{
	glBindTexture(GL_TEXTURE_2D, renderer.atlas.texture());
	renderer.quad.add(*this, renderer.atlas.coords(0));
}

#include "../luftwaffle.hpp"

game::renderer::renderer(win::roll &roll)
	: screen(-8.0f, 8.0f, -4.5f, 4.5f)
	, quad(roll, screen)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

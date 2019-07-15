#include <time.h>

#include "../luftwaffle.hpp"

game::renderer::renderer(win::display &display, win::roll &roll)
	: screen(-8.0f, 8.0f, -4.5f, 4.5f)
	, quad(roll, screen)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.85f, 1.0f, 1.0f);

	font_renderer = display.make_font_renderer(display.width(), display.height(), screen.left, screen.right, screen.bottom, screen.top);
	font.small = font_renderer.make_font(roll["asset/font/arial.ttf"], 0.275f);
}

void game::renderer::frame(const game::world &world)
{
	for(const comp::atlas_renderable &renderable : world.objectdb.atlas_renderables_toaster)
		quad.add(renderable);

	for(const comp::atlas_renderable &renderable : world.objectdb.atlas_renderables_player)
		quad.add(renderable);

	glBindTexture(GL_TEXTURE_2D, world.asset.atlas.texture());
	quad.send();

	drawfps();
}

void game::renderer::drawfps()
{
	// draw fps
	static int accumulate = 0;
	static int fps = 0;
	const int now = time(NULL);
	static int lasttime = 0;

	++accumulate;
	if(now != lasttime)
	{
		lasttime = now;
		fps = accumulate;
		accumulate = 0;
	}

	static char fpsbuffer[30];
	snprintf(fpsbuffer, sizeof(fpsbuffer), "fps: %d", fps);

	font_renderer.draw(font.small, fpsbuffer, screen.left + 0.1f, screen.top - font.small.size(), win::color(1.0f, 1.0f, 0.0f));
}

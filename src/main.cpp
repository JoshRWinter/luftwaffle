#include "luftwaffle.hpp"

int main()
{
	win::system system;
	win::display display = system.make_display("LUFTWAFFLE", 1280,  720);

	win::roll roll("asset");
	game::world world(roll);
	game::renderer renderer(roll);

	bool quit = false;
	display.event_button([&quit](const win::button button, bool press)
	{
		switch(button)
		{
			case win::button::ESC:
				quit = true;
				break;
		}
	});

	display.event_mouse([&world, &renderer, &display](const int x, const int y)
	{
		world.cursor.x = (((float)x / display.width()) * (renderer.screen.right * 2.0f)) - renderer.screen.right;
		world.cursor.y = -(((float)y / display.height()) * (renderer.screen.top * 2.0f)) + renderer.screen.top;
	});

	while(display.process() && !quit)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		world.process();
		world.render(renderer);

		display.swap();
	}

	return 0;
}

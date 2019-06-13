#include <chrono>

#include <math.h>

#include "luftwaffle.hpp"

int main()
{
	win::system system;
	win::display display = system.make_display("LUFTWAFFLE", 1280,  720);

	win::roll roll("asset");
	game::world world(roll);
	game::renderer renderer(roll);

	bool quit = false;
	display.event_button([&quit, &world](const win::button button, bool press)
	{
		switch(button)
		{
			case win::button::ESC:
				quit = true;
				break;
			case win::button::W:
			case win::button::UP:
				world.input.up = press;
				break;
			case win::button::A:
			case win::button::LEFT:
				world.input.left = press;
				break;
			case win::button::D:
			case win::button::RIGHT:
				world.input.right = press;
				break;
			case win::button::S:
			case win::button::DOWN:
				world.input.down = press;
				break;
		}

		float xpos = 0.0f;
		float ypos = 0.0f;

		if(world.input.up)
			ypos = 1.0f;
		else if(world.input.down)
			ypos = -1.0f;
		if(world.input.left)
			xpos = -1.0f;
		else if(world.input.right)
			xpos = 1.0f;

		world.input.direction = atan2f(ypos, xpos);
		world.input.speed = (world.input.up || world.input.down || world.input.right || world.input.left) * 3.0f;
	});

	display.event_mouse([&world, &renderer, &display](const int x, const int y)
	{
		world.cursor.x = (((float)x / display.width()) * (renderer.screen.right * 2.0f)) - renderer.screen.right;
		world.cursor.y = -(((float)y / display.height()) * (renderer.screen.top * 2.0f)) + renderer.screen.top;
	});

	while(display.process() && !quit)
	{
		auto start = std::chrono::high_resolution_clock::now();

		glClear(GL_COLOR_BUFFER_BIT);
		world.process();
		world.render(renderer);

		display.swap();

		while(std::chrono::duration<double, std::micro>(std::chrono::high_resolution_clock::now() - start).count() < 16667);
	}

	return 0;
}

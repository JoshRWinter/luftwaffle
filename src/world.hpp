#ifndef WORLD_HPP
#define WORLD_HPP

namespace game
{
	struct input
	{
		input()
			: direction(0.0f)
			, speed(0.0f)
			, left_click(false)
			, right_click(false)
			, up(false)
			, down(false)
			, right(false)
			, left(false)
		{}

		float direction;
		float speed;

		bool left_click;
		bool right_click;
		bool up, down, right, left;
	};

	struct world
	{
		world(win::roll&);

		void process();
		void render(game::renderer&);
		void reset();

		win::point cursor;
		game::input input;

		game::asset asset;

		game::objectdb objectdb;
	};
}

#endif

#ifndef WORLD_HPP
#define WORLD_HPP

namespace game
{
	struct input
	{
		input()
			: direction(0.0f)
			, speed(0.0f)
			, up(false)
			, down(false)
			, right(false)
			, left(false)
		{}

		float direction;
		float speed;

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

		struct
		{
			ent::player player;
			ent::toaster toaster;
		} entity;

		game::asset asset;
	};
}

#endif

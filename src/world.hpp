#ifndef WORLD_HPP
#define WORLD_HPP

namespace game
{
	struct world
	{
		world(win::roll&);

		void process();
		void render();
		void reset();

		struct { float x, y; } cursor;

		struct
		{
			ent::player player;
		} entity;

		game::renderer renderer;
	};
}

#endif

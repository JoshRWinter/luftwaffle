#ifndef WORLD_HPP
#define WORLD_HPP

namespace game
{
	struct world
	{
		world(win::roll&);

		void process();
		void render(game::renderer&);
		void reset();

		win::point cursor;

		struct
		{
			ent::player player;
		} entity;

		game::asset asset;
	};
}

#endif

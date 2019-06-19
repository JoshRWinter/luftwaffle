#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

namespace ent
{
	struct entity
	{
		bool collide(const ent::entity&, float tolerance = 0.0f) const;

		float x, y, w, h, rot;
	};

	struct player : ent::entity
	{
		static constexpr float SIZE = 0.7f;
		static constexpr float DECEL = 0.0005f;
		static constexpr float ACCEL = 0.001f;
		static constexpr float MAX_SPEED = 0.05f;

		player();
		void reset();
		void process(const game::world&);
		void render(game::renderer&, const game::asset&) const;

		float xv, yv;
	};

	struct toaster : ent::entity
	{
		static constexpr float WIDTH = 1.0f;
		static constexpr float HEIGHT = 1.0f;
		static constexpr float SPAWN_TIMER_LOW = 300;
		static constexpr float SPAWN_TIMER_HIGH = 500;

		toaster();
		void process(game::world&);
		void render(game::renderer&, const game::asset&) const;
		void reset();

		int health;
		int iteration;
		int spawn_timer;
	};

	struct waffle : ent::entity
	{
		static constexpr float WIDTH = 1.15f;
		static constexpr float HEIGHT = 1.15f;
		static constexpr float SPAWN_SLIDE = 10;
		static constexpr float SPAWN_SLIDE_SPEED = 0.1f;

		waffle(const ent::toaster&);

		static void process(game::world&);
		static void render(game::renderer&, const game::asset&, const std::vector<ent::waffle>&);

		int spawn_slide;
		int health;
	};
}

#endif

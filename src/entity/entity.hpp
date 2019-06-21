#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>

namespace ent
{
	struct entity
	{
		bool collide(const ent::entity&, float tolerance = 0.0f) const;
		bool collide(float, float) const;
		bool in_range(const ent::entity&, float) const;
		void align(float, float);

		float x, y, w, h, rot;
	};

	struct player : ent::entity
	{
		static constexpr float WIDTH = 0.7f;
		static constexpr float HEIGHT = 0.7f;
		static constexpr float DECEL = 0.0005f;
		static constexpr float ACCEL = 0.001f;
		static constexpr float MAX_SPEED = 0.05f;
		static constexpr float FIRE_COOLDOWN = 10;

		player();
		void reset();
		void process(game::world&);
		void render(game::renderer&, const game::asset&) const;

		float xv, yv;
		int fire_cooldown;
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
		static constexpr float WIDTH = 1.2f;
		static constexpr float HEIGHT = 1.2f;
		static constexpr float SPAWN_SLIDE = 10;
		static constexpr float SPAWN_SLIDE_SPEED = 0.1f;
		static constexpr float WANDER_RANGE = 7.0f;
		static constexpr float TURN_SPEED = 0.03f;
		static constexpr float SPEED = 0.03f;
		static constexpr float WAIT_TIMER_LOW = 30;
		static constexpr float WAIT_TIMER_HIGH = 210;
		static constexpr float WAIT_PROBABLITY = 300;

		waffle(const ent::toaster&);

		static void process(game::world&);
		static void render(game::renderer&, const game::asset&, const std::vector<ent::waffle>&);

		int spawn_slide;
		int wait;
		int health;
		float direction;
		win::point target; // go to here
		win::point spawn_point;

	private:
		void choose_wander_target();
	};

	struct laser : ent::entity
	{
		static constexpr float WIDTH = 0.5f;
		static constexpr float HEIGHT = 0.15f;
		static constexpr float SPEED = 0.1f;
		static constexpr float TTL = 50;

		laser(float, float, float);

		static void process(game::world&);
		static void render(game::renderer&, const game::asset&, const std::vector<ent::laser>&);

		int ttl;
		float xv;
		float yv;
	};
}

#endif

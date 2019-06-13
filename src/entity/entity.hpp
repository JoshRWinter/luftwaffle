#ifndef ENTITY_HPP
#define ENTITY_HPP

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
}

#endif

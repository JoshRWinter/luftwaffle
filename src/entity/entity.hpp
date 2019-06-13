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
		static constexpr int SIZE = 2.0f;

		player();
		void reset();
		void process(const game::world&);
		void render(game::renderer&, const game::asset&) const;
	};
}

#endif

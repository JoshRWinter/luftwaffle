#ifndef OBJECTDB_HPP
#define OBJECTDB_HPP

namespace game
{
	struct objectdb
	{
		objectdb() = default;
		objectdb(const objectdb&) = delete;
		objectdb(objectdb&&) = delete;
		void operator=(const objectdb&) = delete;
		void operator=(objectdb&&) = delete;

		objectpool<ent::entity, 100> entities;

		objectpool<comp::physical, 100> physicals;
		objectpool<comp::player, 1> player;
		objectpool<comp::toaster, 1> toaster;
		objectpool<comp::wander, 30> wander;
		objectpool<comp::wander, 30> attack;

		// renderable components are partitioned by entity
		objectpool<comp::atlas_renderable, 100> atlas_renderable_players;
		objectpool<comp::atlas_renderable, 100> atlas_renderable_toasters;
		objectpool<comp::atlas_renderable, 100> atlas_renderable_waffles;

		void reset()
		{
			entities.reset();

			physicals.reset();
			player.reset();
			toaster.reset();
			wander.reset();
			attack.reset();

			atlas_renderable_players.reset();
			atlas_renderable_toasters.reset();
			atlas_renderable_waffles.reset();
		}
	};
}

#endif

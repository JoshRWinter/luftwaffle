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
		objectpool<comp::waffle, 30> waffles;
		objectpool<comp::wander, 30> wander;
		objectpool<comp::wander, 30> attack;
		objectpool<comp::lasergun, 30> laserguns;
		objectpool<comp::laser, 100> lasers;

		// atlas-renderable components are partitioned by entity
		objectpool<comp::atlas_renderable, 1> atlas_renderable_players;
		objectpool<comp::atlas_renderable, 1> atlas_renderable_toasters;
		objectpool<comp::atlas_renderable, 30> atlas_renderable_waffles;
		objectpool<comp::atlas_renderable, 30> atlas_renderable_laserguns;
		objectpool<comp::atlas_renderable, 100> atlas_renderable_lasers;

		void reset()
		{
			reset_all_pools();
		}
	};
}

#endif

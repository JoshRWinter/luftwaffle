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

		pool::storage<ent::entity> entity;

		pool::storage<comp::physical> physical;
		pool::storage<comp::player, 1> player;
		pool::storage<comp::toaster, 1> toaster;
		pool::storage<comp::waffle> waffle;
		pool::storage<comp::wander> wander;
		pool::storage<comp::attack> attack;
		pool::storage<comp::lasergun> lasergun;
		pool::storage<comp::laser> laser;
		pool::storage<comp::glow_renderable> glow_renderable;

		// atlas-renderable components are partitioned by world object type
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_player;
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_toaster;
		pool::storage<comp::atlas_renderable> atlas_renderable_waffle;
		pool::storage<comp::atlas_renderable> atlas_renderable_lasergun;
		pool::storage<comp::atlas_renderable> atlas_renderable_laser;

		void reset()
		{
			pool::storage_base::reset_all();
		}
	};
}

#endif

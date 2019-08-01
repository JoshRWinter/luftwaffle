#ifndef OBJECTDB_HPP
#define OBJECTDB_HPP

namespace game
{
	struct objectdb
	{
#ifdef NDEBUG
		objectdb() = default;
#else
		objectdb() { if(global == NULL) global = this; }
#endif
		objectdb(const objectdb&) = delete;
		objectdb(objectdb&&) = delete;
		void operator=(const objectdb&) = delete;
		void operator=(objectdb&&) = delete;

		objectpool<ent::entity, 100> entity;

		objectpool<comp::physical, 100> physical;
		objectpool<comp::player, 1> player;
		objectpool<comp::toaster, 1> toaster;
		objectpool<comp::waffle, 30> waffle;
		objectpool<comp::wander, 30> wander;
		objectpool<comp::attack, 30> attack;
		objectpool<comp::lasergun, 30> lasergun;
		objectpool<comp::laser, 100> laser;
		objectpool<comp::glow_renderable, 25> glow_renderable;

		// atlas-renderable components are partitioned by world object type
		objectpool<comp::atlas_renderable, 1> atlas_renderable_player;
		objectpool<comp::atlas_renderable, 1> atlas_renderable_toaster;
		objectpool<comp::atlas_renderable, 30> atlas_renderable_waffle;
		objectpool<comp::atlas_renderable, 30> atlas_renderable_lasergun;
		objectpool<comp::atlas_renderable, 100> atlas_renderable_laser;

		void reset()
		{
			reset_all_pools();
		}

#ifndef NDEBUG
		static void safety_check(const void *p)
		{
			if(p < global || p >= global + sizeof(objectdb))
				win::bug("invalid reference to pool object");
		}
	private:
		inline static objectdb *global = NULL;
#endif
	};
}

#endif

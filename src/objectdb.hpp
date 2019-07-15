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

		// renderable components are partitioned by entity
		objectpool<comp::atlas_renderable, 100> atlas_renderables_player;
		objectpool<comp::atlas_renderable, 100> atlas_renderables_toaster;

		void reset()
		{
			entities.reset();

			physicals.reset();
			player.reset();
			toaster.reset();

			atlas_renderables_player.reset();
			atlas_renderables_toaster.reset();
		}
	};
}

#endif

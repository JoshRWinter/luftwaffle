#ifndef OBJECTDB_HPP
#define OBJECTDB_HPP

namespace game
{
	struct objectdb
	{
		objectpool<ent::entity, 100> entities;

		objectpool<comp::player, 1> player;
		objectpool<comp::physical, 100> physicals;

		// renderable components are partitioned by entity
		objectpool<comp::atlas_renderable, 100> atlas_renderables_player;

		void reset()
		{
			entities.reset();
			player.reset();
			physicals.reset();

			atlas_renderables_player.reset();
		}
	};
}

#endif
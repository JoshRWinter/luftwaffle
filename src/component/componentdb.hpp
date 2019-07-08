#ifndef COMPONENTDB_HPP
#define COMPONENTDB_HPP

#include <vector>

namespace comp
{
	struct componentdb
	{
		componentdb()
		{
			reset();
		}

		struct
		{
			objectpool<ent::entity, 100> entities;

			objectpool<comp::player, 1> player;
			objectpool<comp::physical, 100> physicals;

			// renderable components are partitioned by entity
			objectpool<comp::atlas_renderable, 100> atlas_renderables_player;
		} pool;

		comp::player *player;
		std::vector<comp::physical*> physicals;

		std::vector<comp::atlas_renderable*> atlas_renderables_player;

		void reset()
		{
			pool.entities.reset();
			pool.player.reset();
			pool.physicals.reset();

			pool.atlas_renderables_player.reset();

			player = NULL;
			physicals.clear();
			atlas_renderables_player.clear();
		}
	};
}

#endif

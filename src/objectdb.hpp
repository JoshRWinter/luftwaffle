#ifndef OBJECTDB_HPP
#define OBJECTDB_HPP

#include "component/atlas_renderable.hpp"
#include "component/attack.hpp"
#include "component/bomb.hpp"
#include "component/explosion_arm.hpp"
#include "component/explosion_cloud.hpp"
#include "component/explosion_particle.hpp"
#include "component/glow_renderable.hpp"
#include "component/goring.hpp"
#include "component/health.hpp"
#include "component/hitler.hpp"
#include "component/laser.hpp"
#include "component/lasergun.hpp"
#include "component/missile.hpp"
#include "component/particle_laser.hpp"
#include "component/particle_smoke.hpp"
#include "component/physical.hpp"
#include "component/player.hpp"
#include "component/toaster.hpp"
#include "component/waffle.hpp"
#include "component/wander.hpp"

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
		pool::storage<comp::missile> missile;
		pool::storage<comp::health> health;
		pool::storage<comp::explosion_cloud> explosion_cloud;
		pool::storage<comp::explosion_arm> explosion_arm;
		pool::storage<comp::explosion_particle> explosion_particle;
		pool::storage<comp::particle_smoke> particle_smoke;
		pool::storage<comp::particle_laser> particle_laser;
		pool::storage<comp::bomb> bomb;
		pool::storage<comp::glow_renderable> glow_renderable;
		pool::storage<comp::goring, 1> goring;
		pool::storage<comp::hitler, 1> hitler;

		// atlas-renderable components are partitioned by world object type
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_player;
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_toaster;
		pool::storage<comp::atlas_renderable> atlas_renderable_waffle;
		pool::storage<comp::atlas_renderable> atlas_renderable_lasergun;
		pool::storage<comp::atlas_renderable> atlas_renderable_laser;
		pool::storage<comp::atlas_renderable> atlas_renderable_missile;
		pool::storage<comp::atlas_renderable> atlas_renderable_explosion_cloud;
		pool::storage<comp::atlas_renderable> atlas_renderable_explosion_particle;
		pool::storage<comp::atlas_renderable> atlas_renderable_particle_smoke;
		pool::storage<comp::atlas_renderable> atlas_renderable_particle_laser;
		pool::storage<comp::atlas_renderable> atlas_renderable_bomb;
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_goring;
		pool::storage<comp::atlas_renderable, 1> atlas_renderable_hitler;

		void reset()
		{
			pool::storage_base::reset_all();
		}
	};
}

#endif

#ifndef COMP_LASERGUN_HPP
#define COMP_LASERGUN_HPP

#include "component.hpp"
#include "win.h"

#include "physical.hpp"

namespace comp
{
	struct lasergun : comp::component
	{
		static constexpr comp::type component_type = comp::type::LASERGUN;

		constexpr static int MAX_GUNS = 2;

		lasergun(ent::entity &entity, const comp::physical &parent_phys, int max_cooldown, const win::color &c, float spd, float dmg)
			: component(component_type, entity)
			, firing_laser(false)
			, firing_bomb(false)
			, max_timer_cooldown(max_cooldown)
			, timer_cooldown(0)
			, parent_physical(parent_phys)
			, color(c)
			, speed(spd)
			, damage(dmg)
			, last_slot(0)
		{
			memset(guns, 0, sizeof(guns));
		}

		struct gunposition { float angle_offset, distance; };

		bool firing_laser;
		bool firing_missile;
		bool firing_bomb;

		int timer_cooldown;
		const int max_timer_cooldown;
		const comp::physical &parent_physical;
		gunposition guns[MAX_GUNS];
		win::color color;
		float speed;
		float damage;
		int last_slot;
	};

}

#endif

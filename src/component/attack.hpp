#ifndef COMP_ATTACK_HPP
#define COMP_ATTACK_HPP

#include "component.hpp"

#include "physical.hpp"

namespace comp
{
	struct attack : comp::component
	{
		static constexpr comp::type component_type = comp::type::ATTACK;

		struct point { float x, y, rot; };

		attack(ent::entity &entity, comp::physical &spawn)
			: component(component_type, entity)
			, travel_angle(0.0f)
			, targetx(0.0f)
			, targety(0.0f)
			, timer(0)
			, firing(false)
		{
			spawn_point.x = spawn.x + (spawn.w / 2.0f);
			spawn_point.y = spawn.y + (spawn.h / 2.0f);
			spawn_point.rot = spawn.rot;
		}

		point spawn_point;
		float travel_angle;
		float targetx, targety;
		int timer;
		bool firing;
	};
}

#endif

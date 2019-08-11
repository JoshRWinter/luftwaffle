#include "../luftwaffle.hpp"

void sys::attack(game::world &world)
{
	for(comp::attack &attack : world.objectdb.attack)
	{
		comp::physical &physical = attack.entity.component<comp::physical>();

		ent::entity &player_entity = (*world.objectdb.player.begin()).entity;
		comp::physical &player_physical = player_entity.component<comp::physical>();

		if(!attack.firing && mersenne(120))
			attack.firing = true;
		if(attack.firing && mersenne(100))
			attack.firing = false;

		if(attack.timer > 0)
		{
			if(--attack.timer < 1)
			{
				const float WANDER_RADIUS = 5.0f;
				attack.targetx = mersenne(attack.spawn_point.x - WANDER_RADIUS, attack.spawn_point.x + WANDER_RADIUS);
				attack.targety = mersenne(attack.spawn_point.y - WANDER_RADIUS, attack.spawn_point.y + WANDER_RADIUS);
			}
		}

		if(attack.timer == 0)
		{
			const float target_travel_angle = atan2f(attack.targety - (physical.y + (physical.h / 2.0f)), attack.targetx - (physical.x + (physical.w / 2.0f)));
			attack.travel_angle = win::align(attack.travel_angle, target_travel_angle, 0.055f);

			const float ATTACK_SPEED = 0.04f;
			physical.x += cosf(attack.travel_angle) * ATTACK_SPEED;
			physical.y += sinf(attack.travel_angle) * ATTACK_SPEED;

			if(physical.x < attack.targetx && physical.x + physical.w > attack.targetx &&
				physical.y < attack.targety && physical.y + physical.h > attack.targety)
			{
				attack.timer = mersenne(100, 200);
			}
		}

		if(!attack.firing)
		{
			physical.rot = win::align(physical.rot, attack.travel_angle, 0.155f);
		}
		else
		{
			const float target_face_angle = atan2f((player_physical.y + (game::PLAYER_HEIGHT / 2.0f)) - (physical.y + (physical.h / 2.0f)), (player_physical.x + (game::PLAYER_WIDTH / 2.0f)) - (physical.x + (physical.w / 2.0f)));
			physical.align(target_face_angle, 0.085f);
		}
	}
}

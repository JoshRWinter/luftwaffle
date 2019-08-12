#include "../luftwaffle.hpp"

static void popout(comp::physical&, comp::wander&);
static void walkabout(comp::physical&, comp::wander&);

void sys::wander(game::world &world)
{
	for(comp::wander &wander : world.objectdb.wander)
	{
		comp::physical &physical = wander.entity.component<comp::physical>();

		if(wander.state == comp::wander::wander_state::POPOUT)
			popout(physical, wander);
		else
			walkabout(physical, wander);
	}
}

// pop out the toaster
void popout(comp::physical &physical, comp::wander &wander)
{
	const float POPOUT_SPEED = 0.10f;

	if(wander.timer-- > 0)
	{
		physical.x += cosf(wander.initial_angle) * POPOUT_SPEED;
		physical.y += sinf(wander.initial_angle) * POPOUT_SPEED;
	}
	else
	{
		wander.timer = 70;
		wander.state = comp::wander::wander_state::WANDERING;
	}
}

void walkabout(comp::physical &physical, comp::wander &wander)
{
	const float angle = atan2f(wander.targety - (physical.y + game::WAFFLE_HEIGHT / 2.0f), wander.targetx - (physical.x + (game::WAFFLE_WIDTH / 2.0f)));
	physical.rot = win::align(physical.rot, angle, 0.035f);


	if(wander.timer-- < 0)
	{
		const float SPEED = 0.03f;

		physical.x += cosf(physical.rot) * SPEED;
		physical.y += sinf(physical.rot) * SPEED;

		if(physical.x < wander.targetx && physical.x + game::WAFFLE_WIDTH > wander.targetx &&
			physical.y < wander.targety && physical.y + game::WAFFLE_HEIGHT > wander.targety)
		{
			wander.timer = mersenne(100, 500);
		}
	}
	else if(wander.timer == 0)
	{
		const float WANDER_RANGE = 6.0f;

		wander.targetx = wander.initial_x + mersenne(-WANDER_RANGE, WANDER_RANGE);
		wander.targety = wander.initial_y + mersenne(-WANDER_RANGE, WANDER_RANGE);
	}
}

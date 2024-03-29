#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: toaster_sequence(0)
	, asset(roll)
	, win(false)
{
	reset();
}

void game::world::process()
{
	if(win)
	{
		if(++win_timer > 100)
			reset();
		else
			return;
	}
	lose();

	sys::player(*this);
	sys::toaster(*this);
	sys::wander(*this);
	sys::attack(*this);
	sys::laser(*this);
	sys::waffle(*this);
	sys::missile(*this);
	sys::bomb(*this);
	sys::particle_smoke(*this);
	sys::particle_laser(*this);
	sys::explosion_cloud(*this);
	sys::explosion_arm(*this);
	sys::explosion_particle(*this);
	sys::goring(*this);
	sys::hitler(*this);
	sys::lasergun(*this);
}

void game::world::lose()
{
	if(objectdb.player.count() != 1)
		return;

	auto &player = *objectdb.player.begin();

	if(player.dead_timer > 100)
	{
		reset();
	}
}

void game::world::reset()
{
	win = false;
	win_timer = 0;
	objectdb.reset();
	toaster_sequence = 0;
}

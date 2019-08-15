#include "luftwaffle.hpp"

game::world::world(win::roll &roll)
	: asset(roll)
{
	reset();
}

void game::world::process()
{
	sys::player(*this);
	sys::toaster(*this);
	sys::wander(*this);
	sys::attack(*this);
	sys::lasergun(*this);
	sys::laser(*this);
	sys::waffle(*this);
	sys::missile(*this);
	sys::particle_smoke(*this);
	sys::explosion_cloud(*this);
	sys::explosion_arm(*this);
	sys::explosion_particle(*this);
}

void game::world::reset()
{
	objectdb.reset();
}

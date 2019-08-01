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
}

void game::world::reset()
{
	objectdb.reset();
}

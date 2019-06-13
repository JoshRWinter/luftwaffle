#include <win.h>
#include "asset.hpp"

game::asset::asset(win::roll &roll)
	: atlas(roll["asset/common.atlas"])
{}

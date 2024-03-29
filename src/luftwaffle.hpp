#ifndef LUFTWAFFLE_HPP
#define LUFTWAFFLE_HPP

#include <random>

#include <time.h>

#include <win.h>

inline struct mersenne_random
{
	mersenne_random() : generator(time(NULL)) {}

	float operator()(float low, float high)
	{
		return std::uniform_real_distribution<float>(low, high)(generator);
	}

	int operator()(int low, int high)
	{
		return std::uniform_int_distribution<int>(low, high)(generator);
	}

	bool operator()(unsigned chance)
	{
		return std::uniform_int_distribution<int>(0, chance - 1)(generator) == 0;
	}

	std::mt19937 generator;
} mersenne;

namespace game
{
	struct world;
	struct renderer;
}

#undef small // lol microsoft

#define _USE_MATH_DEFINES

#include "objectpool.hpp"
#include "asset.hpp"
#include "component/component.hpp"
#include "entity/entity.hpp"
#include "objectdb.hpp"
#include "worldobject.hpp"
#include "system/system.hpp"
#include "render/renderer.hpp"
#include "world.hpp"

#endif

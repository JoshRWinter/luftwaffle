#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "../luftwaffle.hpp"

namespace ent
{
	struct entity;
}

namespace comp
{
	enum class type
	{
		NONE,
		PHYSICAL,
		ATLAS_RENDERABLE,
		GLOW_RENDERABLE,
		PLAYER,
		WAFFLE,
		TOASTER,
		WANDER,
		ATTACK,
		LASERGUN,
		LASER,
		MISSILE,
		HEALTH,
		EXPLOSION_CLOUD,
		EXPLOSION_ARM,
		EXPLOSION_PARTICLE,
		PARTICLE_SMOKE,
		PARTICLE_LASER,
		GORING,
		HITLER,
		BOMB
	};

	struct component
	{
		component(comp::type t, ent::entity &parent)
			: type(t)
			, entity(parent)
		{}

		component(const component&) = delete;
		component(component&&) = delete;
		void operator=(const component&) = delete;
		void operator=(component&&) = delete;

		comp::type type;
		ent::entity &entity;
	};
}

#endif

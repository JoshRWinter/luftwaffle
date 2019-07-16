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
		PHYSICAL,
		ATLAS_RENDERABLE,
		PLAYER,
		TOASTER,
		WANDER,
		ATTACK
	};

	struct component
	{
		component(comp::type t, ent::entity &p)
			: type(t)
			, parent(p)
		{}

		component(const component&) = delete;
		component(component&&) = delete;
		void operator=(const component&) = delete;
		void operator=(component&&) = delete;

		comp::type type;
		ent::entity &parent;
	};

	struct physical : comp::component
	{
		constexpr static comp::type component_type = type::PHYSICAL;

		physical(ent::entity &parent, float xpos, float ypos, float width, float height, float rotation)
			: component(comp::type::PHYSICAL, parent)
			, x(xpos)
			, y(ypos)
			, w(width)
			, h(height)
			, rot(rotation)
		{}

		void align(float, float);

		float x, y, w, h, rot;
	};

	struct atlas_renderable : comp::component
	{
		constexpr static comp::type component_type = type::ATLAS_RENDERABLE;

		atlas_renderable(ent::entity &parent, const unsigned short *tc)
			: component(comp::type::ATLAS_RENDERABLE, parent)
			, texcoords(tc)
		{}

		const unsigned short *texcoords;
	};

	struct player : comp::component
	{
		constexpr static comp::type component_type = type::PLAYER;

		player(ent::entity &parent)
			: component(comp::type::PLAYER, parent)
			, xv(0.0f)
			, yv(0.0f)
		{}

		float xv, yv;
	};

	struct toaster : comp::component
	{
		constexpr static comp::type component_type = type::TOASTER;

		constexpr static int SPAWN_TIMER_LOW = 100;
		constexpr static int SPAWN_TIMER_HIGH = 500;

		toaster(ent::entity &parent)
			: component(comp::type::TOASTER, parent)
			, spawn_timer(mersenne(SPAWN_TIMER_LOW, SPAWN_TIMER_HIGH))
		{}

		int spawn_timer;
	};

	struct wander : comp::component
	{
		constexpr static comp::type component_type = comp::type::WANDER;

		enum class wander_state { POPOUT, WANDERING };

		wander(ent::entity &parent, const float x, const float y, const float angle)
			: component(comp::type::WANDER, parent)
			, state(wander_state::POPOUT)
			, initial_angle(angle)
			, initial_x(x)
			, initial_y(y)
			, targetx(0.0f)
			, targety(0.0f)
			, timer(7)
		{}

		wander_state state;
		const float initial_angle;
		const float initial_x, initial_y;
		float targetx, targety;
		int timer;
	};

	struct attack : comp::component
	{
		constexpr static comp::type component_type = comp::type::ATTACK;

		attack(ent::entity &parent)
			: component(comp::type::WANDER, parent)
		{}
	};
}

#endif

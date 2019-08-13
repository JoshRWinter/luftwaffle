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
		MISSILE
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

	struct physical : comp::component
	{
		static constexpr comp::type component_type = comp::type::PHYSICAL;

		physical(ent::entity &entity, float xpos, float ypos, float width, float height, float rotation)
			: component(component_type, entity)
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
		static constexpr comp::type component_type = comp::type::ATLAS_RENDERABLE;

		atlas_renderable(ent::entity &entity, const unsigned short *tc)
			: component(component_type, entity)
			, texcoords(tc)
		{}

		const unsigned short *texcoords;
	};

	struct glow_renderable : comp::component
	{
		static constexpr comp::type component_type = comp::type::GLOW_RENDERABLE;

		glow_renderable(ent::entity &entity, const win::color c, float bright, float rad)
			: component(component_type, entity)
			, color(c)
			, brightness(bright * 255.0f)
			, radius(rad)
		{}

		win::color color;
		int brightness;
		float radius;
	};

	struct player : comp::component
	{
		static constexpr comp::type component_type = comp::type::PLAYER;

		player(ent::entity &entity)
			: component(component_type, entity)
			, xv(0.0f)
			, yv(0.0f)
			, childgun(NULL)
		{}

		ent::entity *childgun;
		float xv, yv;
	};

	struct toaster : comp::component
	{
		static constexpr comp::type component_type = comp::type::TOASTER;

		constexpr static int SPAWN_TIMER_LOW = 100;
		constexpr static int SPAWN_TIMER_HIGH = 500;

		toaster(ent::entity &entity)
			: component(comp::type::TOASTER, entity)
			, spawn_timer(mersenne(SPAWN_TIMER_LOW, SPAWN_TIMER_HIGH))
		{}

		int spawn_timer;
	};

	struct waffle : comp::component
	{
		static constexpr comp::type component_type = comp::type::WAFFLE;

		enum class waffle_type { NORMAL, MID };

		waffle(ent::entity &entity, waffle_type t)
			: component(component_type, entity)
			, type(t)
			, childgun(NULL)
		{}

		waffle_type type;
		ent::entity *childgun;
	};

	struct wander : comp::component
	{
		static constexpr comp::type component_type = comp::type::WANDER;

		enum class wander_state { POPOUT, WANDERING };

		wander(ent::entity &entity, const float x, const float y, const float angle)
			: component(component_type, entity)
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

	struct lasergun : comp::component
	{
		static constexpr comp::type component_type = comp::type::LASERGUN;

		constexpr static int MAX_GUNS = 2;

		lasergun(ent::entity &entity, const comp::physical &parent_phys, int max_cooldown, const win::color &c, float spd, float dmg)
			: component(component_type, entity)
			, firing_laser(false)
			, max_timer_cooldown(max_cooldown)
			, timer_cooldown(0)
			, parent_physical(parent_phys)
			, color(c)
			, speed(spd)
			, damage(dmg)
		{
			memset(guns, 0, sizeof(guns));
		}

		struct gunposition { float angle_offset, distance; };

		bool firing_laser;
		bool firing_missile;

		int timer_cooldown;
		const int max_timer_cooldown;
		const comp::physical &parent_physical;
		gunposition guns[MAX_GUNS];
		win::color color;
		float speed;
		float damage;
	};

	struct laser : comp::component
	{
		static constexpr comp::type component_type = comp::type::LASER;

		laser(ent::entity &entity, float angle, float speed, int dmg)
			: component(component_type, entity)
			, damage(dmg)
			, xv(cosf(angle) * speed)
			, yv(sinf(angle) * speed)
			, ttl(100)
		{}

		float xv, yv;
		int damage;
		int ttl;
	};

	struct missile : comp::component
	{
		static constexpr comp::type component_type = comp::type::MISSILE;

		missile(ent::entity &entity, float a)
			: component(component_type, entity)
			, xv(0.0f)
			, yv(0.0f)
			, speed(0.01f)
			, angle(a)
			, ttl(100)
		{}

		float xv, yv;
		float speed;
		float angle;
		int ttl;
	};
}

#endif

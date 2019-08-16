#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

namespace game
{
	// player
	constexpr float PLAYER_WIDTH = 0.6f;
	constexpr float PLAYER_HEIGHT = 0.6f;
	void new_player(game::world&);

	// toaster
	constexpr float TOASTER_WIDTH = 0.72f;
	constexpr float TOASTER_HEIGHT = 0.9f;
	void new_toaster(game::world&);
	void delete_toaster(game::world&, ent::entity&);

	// waffle
	constexpr float WAFFLE_WIDTH = 0.6f;
	constexpr float WAFFLE_HEIGHT = 0.6f;

	constexpr float WAFFLE_MID_WIDTH = 0.9f;
	constexpr float WAFFLE_MID_HEIGHT = 0.9f;

	void new_waffle(game::world&, comp::physical&, comp::waffle::waffle_type type);
	void delete_waffle(game::world&, ent::entity&);

	// laser guns
	constexpr float LASERGUN_WAFFLE_WIDTH = 1.0f;
	constexpr float LASERGUN_WAFFLE_HEIGHT = 0.8f;
	constexpr int LASERGUN_WAFFLE_MAX_COOLDOWN = 10;
	constexpr float LASERGUN_WAFFLE_SPEED = 0.14f;
	constexpr int LASERGUN_WAFFLE_DAMAGE = 10;

	constexpr float LASERGUN_PLAYER_WIDTH = 0.8f;
	constexpr float LASERGUN_PLAYER_HEIGHT = 0.8f;
	constexpr int LASERGUN_PLAYER_MAX_COOLDOWN = 5;
	constexpr float LASERGUN_PLAYER_SPEED = 0.2f;
	constexpr int LASERGUN_PLAYER_DAMAGE = 10;

	constexpr float LASERGUN_GORING_WIDTH = 4.0f;
	constexpr float LASERGUN_GORING_HEIGHT = 1.0f;
	constexpr int LASERGUN_GORING_MAX_COOLDOWN = 13;
	constexpr float LASERGUN_GORING_SPEED = 0.1f;
	constexpr int LASERGUN_GORING_DAMAGE = 40;

	constexpr float LASERGUN_HITLER_WIDTH = 3.0f;
	constexpr float LASERGUN_HITLER_HEIGHT = 1.0f;
	constexpr int LASERGUN_HITLER_MAX_COOLDOWN = 13;
	constexpr float LASERGUN_HITLER_SPEED = 0.1f;
	constexpr int LASERGUN_HITLER_DAMAGE = 40;

	enum class lasergun_type
	{
		PLAYER,
		WAFFLE,
		GORING,
		HITLER
	};

	ent::entity &new_lasergun(game::world&, game::lasergun_type, const comp::physical&);
	void delete_lasergun(game::world&, ent::entity&);

	// lasers
	constexpr float LASER_WIDTH = 0.4f;
	constexpr float LASER_HEIGHT = 0.1f;
	void new_laser(game::world&, const comp::physical&, const comp::lasergun&, int, const win::color&, float, int);
	void delete_laser(game::world&, ent::entity&);

	// missiles
	constexpr float MISSILE_WIDTH = 0.55f;
	constexpr float MISSILE_HEIGHT = 0.17f;
	void new_missile(game::world&, const comp::physical &gun_physical, const comp::lasergun &gun, int slot);
	void delete_missile(game::world&, ent::entity&);

	// explosion
	constexpr float CLOUD_STARTING_SIZE = 0.5f;
	void new_explosion(game::world&, float, float, float);
	void delete_explosion_cloud(game::world&, ent::entity&);
	void delete_explosion_arm(game::world&, ent::entity&);
	void delete_explosion_particle(game::world&, ent::entity&);

	// smoke particles
	void new_particle_smoke(game::world&, float, float, float);
	void delete_particle_smoke(game::world&, ent::entity&);

	// laser particles
	constexpr float PARTICLE_LASER_WIDTH = 0.35f;
	constexpr float PARTICLE_LASER_HEIGHT = 0.04f;
	void new_particle_laser(game::world&, float, float, float, const win::color&);
	void delete_particle_laser(game::world&, ent::entity&);

	// goring
	constexpr float GORING_SIZE = 2.55f;
	void new_goring(game::world&, float, float);
	void delete_goring(game::world&, ent::entity&);

	// hitler
	constexpr float HITLER_SIZE = 3.0f;
	void new_hitler(game::world&, float, float);
	void delete_hitler(game::world&, ent::entity&);
}

#endif

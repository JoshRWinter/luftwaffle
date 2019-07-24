#ifndef WORLDOBJECT_HPP
#define WORLDOBJECT_HPP

namespace game
{
	constexpr float PLAYER_WIDTH = 0.6f;
	constexpr float PLAYER_HEIGHT = 0.6f;
	void new_player(game::world&);

	constexpr float TOASTER_WIDTH = 0.72f;
	constexpr float TOASTER_HEIGHT = 0.9f;
	void new_toaster(game::world&);
	void delete_toaster(game::world&, ent::entity&);

	constexpr float WAFFLE_WIDTH = 0.6f;
	constexpr float WAFFLE_HEIGHT = 0.6f;
	void new_waffle(game::world&, const comp::physical&);
	void delete_waffle(game::world&, ent::entity&);

	constexpr float LASER_WIDTH = 0.5f;
	constexpr float LASER_HEIGHT = 0.2f;
	void new_laser(game::world&, comp::physical&, comp::lasergun&, int);
	void delete_laser(game::world&, ent::entity&);
}

#endif

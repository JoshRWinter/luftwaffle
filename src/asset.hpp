#ifndef ASSET_HPP
#define ASSET_HPP

namespace game
{
	struct asset
	{
		enum aid // atlas id
		{
			PLAYER = 0,
			WAFFLE1 = 1,
			TOASTER = 2,
			LASER = 3,
			LASERGUN_WAFFLE = 4,
			MIDWAFFLE = 5,
			MISSILE = 6,
			EXPLOSION_CLOUD = 7,
			EXPLOSION_PARTICLE_RED = 8,
			EXPLOSION_PARTICLE_YELLOW = 9,
			EXPLOSION_PARTICLE_ORANGE = 10,
			SMOKE = 11,
			GORING = 12,
			GORING_GUN = 13,
			HITLER_GUN = 14,
			HITLER = 15
		};

		asset(win::roll&);

		win::atlas atlas;
	};
}

#endif

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
			LASER = 3
		};

		asset(win::roll&);

		win::atlas atlas;
	};
}

#endif

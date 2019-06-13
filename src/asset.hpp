#ifndef ASSET_HPP
#define ASSET_HPP

namespace game
{
	struct asset
	{
		enum class atlas
		{
			PLAYER = 0
		};

		asset(win::roll&);

		win::atlas atlas;
	};
}

#endif

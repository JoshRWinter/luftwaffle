#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

namespace game
{
	class quad
	{
	public:
		quad(win::roll&, const win::area&);

		void add(const ent::entity&, const unsigned short*);
		void send();

	private:
		win::program program;
		win::vao vao;
		win::ebo ebo;

		struct
		{
			win::vbo vertex_tcoffset;
			win::vbo position_size_rotation;
			win::vbo texcoords;
		} vbo;

		struct
		{
			std::vector<float> position_size_rotation;
			std::vector<unsigned short> texcoord;
		} buffer;

		struct
		{
			int projection;
		} uniform;
	};

	class renderer
	{
	public:
		renderer(win::roll&);

		// render passes
		win::area screen;
		win::atlas atlas;
		game::quad quad;
	};
}

#endif

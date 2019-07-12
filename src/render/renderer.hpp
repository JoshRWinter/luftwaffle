#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

namespace game
{
	class quad
	{
	public:
		quad(win::roll&, const win::area&);

		void set_center(float, float);
		void add(const comp::atlas_renderable&);
		void send();

	private:
		win::program program;
		win::vao vao;
		win::ebo ebo;

		win::point center;

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

	struct renderer
	{
		renderer(win::display&, win::roll&);

		void drawfps();

		// render passes
		win::area screen;
		game::quad quad;

		// fonts
		struct
		{
			win::font small;
		} font;
		win::font_renderer font_renderer;
	};
}

#endif

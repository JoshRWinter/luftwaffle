#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <vector>

namespace game
{
	class glow
	{
	public:
		glow(win::display &display, win::roll&, const win::area&);

		void set_center(float, float);
		void add(const comp::glow_renderable&);
		void send();

	private:
		win::program program;
		win::vao vao;
		win::ebo ebo;

		win::point center;

		struct
		{
			win::vbo triangle;
			win::vbo position_radius;
			win::vbo color_brightness;
		} vbo;

		struct
		{
			std::vector<float> position_radius;
			std::vector<unsigned char> color_brightness;
		} buffer;

		struct
		{
			int projection;
			int framebuffer_dims;
			int screen_dims;
		} uniform;
	};

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
			win::vbo color;
			win::vbo texcoords;
		} vbo;

		struct
		{
			std::vector<float> position_size_rotation;
			std::vector<unsigned char> color;
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

		void frame(const game::world&);

		win::area screen;

	private:
		void drawfps();

		// render passes
		game::quad quad;
		game::glow glow;

		// fonts
		struct
		{
			win::font small;
		} font;
		win::font_renderer font_renderer;
	};
}

#endif

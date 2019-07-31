#include "../luftwaffle.hpp"

game::glow::glow(win::display &display, win::roll &roll, const win::area &area)
{
	program = win::load_shaders(roll["src/render/glow.vert"], roll["src/render/glow.frag"]);
	glUseProgram(program);

	// uniforms
	uniform.projection = glGetUniformLocation(program, "projection");
	uniform.framebuffer_dims = glGetUniformLocation(program, "framebuffer_dims");
	uniform.screen_dims = glGetUniformLocation(program, "screen_dims");

	glUniform2i(uniform.framebuffer_dims, display.width(), display.height());
	glUniform2f(uniform.screen_dims, /*area.right * 2.0f*/16.0f, /*area.top * 2.0f*/9.0f);

	float matrix[16];
	win::init_ortho(matrix, area.left, area.right, area.bottom, area.top);
	glUniformMatrix4fv(uniform.projection, 1, false, matrix);

	const float verts[] =
	{
		-0.5f, 0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f, 0.5f
	};

	const unsigned indices[] =
	{
		0, 1, 2, 0, 2, 3
	};

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.triangle);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_radius);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 3, NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(float) * 3, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.color_brightness);
	glVertexAttribPointer(3, 3, GL_UNSIGNED_BYTE, true, sizeof(unsigned char) * 4, NULL);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glVertexAttribPointer(4, 1, GL_UNSIGNED_BYTE, true, sizeof(unsigned char) * 4, (void*)(sizeof(unsigned char) * 3));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
}

void game::glow::set_center(float x, float y)
{
	center.x = x;
	center.y = y;
}

void game::glow::add(const comp::glow_renderable &renderable)
{
	const comp::physical &physical = renderable.parent.component<comp::physical>();

	buffer.position_radius.push_back(physical.x + (physical.w / 2.0f) - (center.x + (game::PLAYER_WIDTH / 2.0f)));
	buffer.position_radius.push_back(physical.y + (physical.h / 2.0f) - (center.y + (game::PLAYER_HEIGHT / 2.0f)));
	buffer.position_radius.push_back(renderable.radius);

	buffer.color_brightness.push_back(renderable.color.red * 254);
	buffer.color_brightness.push_back(renderable.color.green * 254);
	buffer.color_brightness.push_back(renderable.color.blue * 254);

	buffer.color_brightness.push_back(renderable.brightness);
}

void game::glow::send()
{
	glUseProgram(program);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_radius);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.position_radius.size(), buffer.position_radius.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.color_brightness);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.color_brightness.size(), buffer.color_brightness.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, buffer.position_radius.size() / 3);

	buffer.position_radius.clear();
	buffer.color_brightness.clear();
}

#include "../luftwaffle.hpp"

game::quad::quad(win::roll &roll, const win::area &screen)
{
	program = win::load_shaders(roll["src/render/quad.vert"], roll["src/render/quad.frag"]);
	glUseProgram(program);

	float pmatrix[16];
	win::init_ortho(pmatrix, screen.left, screen.right, screen.bottom, screen.top);

	// shader uniforms
	uniform.projection = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(uniform.projection, 1, false, pmatrix);

	const float verts[]
	{
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f
	};

	const unsigned int elements[]
	{
		0, 1, 2, 2, 1, 3
	};

	glBindVertexArray(vao);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	// triangle verts, and tex coord offsets
	glBindBuffer(GL_ARRAY_BUFFER, vbo.vertex_tcoffset);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 4, NULL);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(float) * 4, (void*)(sizeof(float) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// position size & rotation data
	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_size_rotation);
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(float) * 5, NULL);
	glVertexAttribPointer(3, 2, GL_FLOAT, false, sizeof(float) * 5, (void*)(sizeof(float) * 2));
	glVertexAttribPointer(4, 1, GL_FLOAT, false, sizeof(float) * 5, (void*)(sizeof(float) * 4));
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	// texcoord data
	glBindBuffer(GL_ARRAY_BUFFER, vbo.texcoords);
	glVertexAttribPointer(5, 4, GL_UNSIGNED_SHORT, true, 0, NULL);
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(5);

	// color
	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glVertexAttribPointer(6, 4, GL_UNSIGNED_BYTE, true, 0, NULL);
	glVertexAttribDivisor(6, 1);
	glEnableVertexAttribArray(6);
}

void game::quad::set_center(float x, float y)
{
	center.x = x;
	center.y = y;
}

void game::quad::add(const comp::atlas_renderable &renderable)
{
	const comp::physical &physical = renderable.entity.component<comp::physical>();

	buffer.position_size_rotation.push_back(physical.x - (center.x + (game::PLAYER_WIDTH / 2.0f)));
	buffer.position_size_rotation.push_back(physical.y - (center.y + (game::PLAYER_HEIGHT / 2.0f)));
	buffer.position_size_rotation.push_back(physical.w);
	buffer.position_size_rotation.push_back(physical.h);
	buffer.position_size_rotation.push_back(physical.rot);

	buffer.texcoord.push_back(renderable.texcoords[0]);
	buffer.texcoord.push_back(renderable.texcoords[1]);
	buffer.texcoord.push_back(renderable.texcoords[2] - renderable.texcoords[0]);
	buffer.texcoord.push_back(renderable.texcoords[3] - renderable.texcoords[1]);

	buffer.color.push_back(renderable.color.red * 255);
	buffer.color.push_back(renderable.color.green * 255);
	buffer.color.push_back(renderable.color.blue * 255);
	buffer.color.push_back(renderable.color.alpha * 255);
}

void game::quad::add_raw(const float x, const float y, const float w, const float h, const float rot, const unsigned short *texcoords)
{
	buffer.position_size_rotation.push_back(x);
	buffer.position_size_rotation.push_back(y);
	buffer.position_size_rotation.push_back(w);
	buffer.position_size_rotation.push_back(h);
	buffer.position_size_rotation.push_back(rot);

	buffer.texcoord.push_back(texcoords[0]);
	buffer.texcoord.push_back(texcoords[1]);
	buffer.texcoord.push_back(texcoords[2] - texcoords[0]);
	buffer.texcoord.push_back(texcoords[3] - texcoords[1]);

	buffer.color.push_back(255);
	buffer.color.push_back(255);
	buffer.color.push_back(255);
	buffer.color.push_back(255);
}

void game::quad::send()
{
	glBindVertexArray(vao);
	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.position_size_rotation);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.position_size_rotation.size(), buffer.position_size_rotation.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.texcoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned short) * buffer.texcoord.size(), buffer.texcoord.data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(unsigned char) * buffer.color.size(), buffer.color.data(), GL_DYNAMIC_DRAW);

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL, buffer.position_size_rotation.size() / 5);

	buffer.position_size_rotation.clear();
	buffer.texcoord.clear();
	buffer.color.clear();
}

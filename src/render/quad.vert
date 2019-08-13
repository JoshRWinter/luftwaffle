#version 330 core

layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 tcoffset;
layout (location = 2) in vec2 position;
layout (location = 3) in vec2 size;
layout (location = 4) in float rot;
layout (location = 5) in vec4 texcoords;
layout (location = 6) in float alpha;

uniform mat4 projection;

out vec2 ftexcoord;
out float falpha;

void main()
{
	mat4 translate = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, position.x + (size.x / 2.0), position.y + (size.y / 2.0), 0.0, 1.0);
	mat4 rotate = mat4(cos(rot), sin(rot), 0.0, 0.0, -sin(rot), cos(rot), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

	gl_Position = projection * translate * rotate * vec4(vertex.x * size.x, vertex.y * size.y, 0.0, 1.0);

	ftexcoord = vec2(texcoords.x + (texcoords.z * tcoffset.x), texcoords.y + (texcoords.w * tcoffset.y));

	falpha = alpha;
}

#version 330 core

uniform mat4 projection;
uniform ivec2 framebuffer_dims;
uniform vec2 screen_dims;

layout (location = 0) in vec2 triangle;
layout (location = 1) in vec2 position;
layout (location = 2) in float radius;
layout (location = 3) in vec3 color;
layout (location = 4) in float brightness;

flat out ivec2 center;
flat out int glow_radius;
out vec3 fcolor;
out float fbrightness;

mat4 translate = mat4(1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, position.x, position.y, 0.0, 1.0);

void main()
{
	gl_Position = projection * translate * vec4(triangle.x * radius * 2, triangle.y * radius * 2, 0.0, 1.0);

	center.x = int((position.x / screen_dims.x) * framebuffer_dims.x) + (framebuffer_dims.x / 2);
	center.y = -int((position.y / screen_dims.y) * framebuffer_dims.y) + (framebuffer_dims.y / 2);

	glow_radius = int((radius / screen_dims.x) * framebuffer_dims.x);
	fcolor = color;
	fbrightness = brightness;
}

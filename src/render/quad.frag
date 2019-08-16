#version 330 core

uniform sampler2D tex;

in vec2 ftexcoord;
in vec4 fcolor;

out vec4 color;

void main()
{
	color = texture(tex, ftexcoord) * fcolor;
}

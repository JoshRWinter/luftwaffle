#version 330 core

uniform sampler2D tex;

in vec2 ftexcoord;
in float falpha;

out vec4 color;

void main()
{
	color = texture(tex, ftexcoord) * vec4(1.0, 1.0, 1.0, falpha);
}

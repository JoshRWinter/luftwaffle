#version 330 core

out vec4 color;

layout (origin_upper_left) in vec4 gl_FragCoord;
flat in ivec2 center;
flat in int glow_radius;
in vec3 fcolor;
in float fbrightness;

void main()
{
	int pixel_distance = int(distance(gl_FragCoord.xy, center));
	float intensity = (glow_radius - pixel_distance) / float(glow_radius);

	intensity = clamp(intensity, 0.0, 1.0);
	color = vec4(fcolor.xyz, intensity * fbrightness);
}

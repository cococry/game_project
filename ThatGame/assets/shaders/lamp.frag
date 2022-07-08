#version 460 core

out vec4 o_Color;

uniform vec3 u_LightColor;

void main() {
	o_Color = vec4(u_LightColor, 1.0);
}
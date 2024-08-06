#version 330 core

layout (location = 0) in vec4 passColor;

layout (location = 0) out vec4 color;

uniform vec4 albedo;

void main() {
	vec4 finalColor = passColor * albedo;
	color = finalColor;
}
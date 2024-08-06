#version 330 core

layout (location = 0) in vec2 passTexCoords;

layout (location = 0) out vec4 color;

uniform vec4 albedo;
uniform sampler2D tex;

void main() {
	vec4 texColor = texture(tex, passTexCoords);
	vec4 finalColor = texColor * albedo;
	color = finalColor;
}
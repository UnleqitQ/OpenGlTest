#version 330 core

layout (location = 0) in vec2 passTexCoords;

layout (location = 0) out vec4 color;

uniform vec4 albedo;
uniform float offsetScale;
uniform sampler2D tex;
uniform sampler2D offsetMap;

void main() {
	vec2 offset = texture(offsetMap, passTexCoords).xy * 2.0 - 1.0;
	vec2 texCoords = passTexCoords + offset * offsetScale;
	vec4 texColor = texture(tex, texCoords);
	vec4 finalColor = texColor * albedo;
	color = finalColor;
}
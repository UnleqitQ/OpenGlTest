#version 330 core

layout (location = 0) in vec2 passTexCoords;

layout (location = 0) out vec4 color;

uniform vec4 albedo;
uniform int texCount;
uniform sampler2D textures[32];
uniform int mixModes[31];

#define MIX_MODE_MULTIPLY 0
#define MIX_MODE_ADD 1
#define MIX_MODE_SUBTRACT 2
#define MIX_MODE_DIVIDE 3
#define MIX_MODE_SCREEN 4
#define MIX_MODE_OVERLAY 5
#define MIX_MODE_DARKEN 6
#define MIX_MODE_LIGHTEN 7
#define MIX_MODE_DIFFERENCE 8
#define MIX_MODE_EXCLUSION 9
#define MIX_MODE_SOFT_LIGHT 10
#define MIX_MODE_HARD_LIGHT 11

#define MIX_MODE_COLOR_DODGE 12
#define MIX_MODE_COLOR_BURN 13
#define MIX_MODE_LINEAR_DODGE 14
#define MIX_MODE_LINEAR_BURN 15
#define MIX_MODE_LINEAR_LIGHT 16
#define MIX_MODE_VIVID_LIGHT 17
#define MIX_MODE_PIN_LIGHT 18
#define MIX_MODE_HARD_MIX 19
#define MIX_MODE_REFLECT 20
#define MIX_MODE_GLOW 21
#define MIX_MODE_PHOENIX 22
#define MIX_MODE_HUE 23
#define MIX_MODE_SATURATION 24
#define MIX_MODE_COLOR 25
#define MIX_MODE_LUMINOSITY 26

vec3 rgbToHsv(vec3 rgb) {
	vec3 hsv;
	float min = min(min(rgb.r, rgb.g), rgb.b);
	float max = max(max(rgb.r, rgb.g), rgb.b);
	hsv.z = max;
	float delta = max - min;
	if (max != 0.0) {
		hsv.y = delta / max;
	}
	else {
		hsv.y = 0.0;
		hsv.x = 0.0;
		return hsv;
	}
	if (delta == 0.0) {
		hsv.x = 0.0;
		return hsv;
	}
	if (rgb.r == max) {
		hsv.x = (rgb.g - rgb.b) / delta;
	}
	else if (rgb.g == max) {
		hsv.x = 2.0 + (rgb.b - rgb.r) / delta;
	}
	else {
		hsv.x = 4.0 + (rgb.r - rgb.g) / delta;
	}
	hsv.x *= 60.0;
	if (hsv.x < 0.0) {
		hsv.x += 360.0;
	}
	return hsv;
}

vec3 hsvToRgb(vec3 hsv) {
	vec3 rgb;
	if (hsv.y == 0.0) {
		rgb.r = hsv.z;
		rgb.g = hsv.z;
		rgb.b = hsv.z;
		return rgb;
	}
	float h = hsv.x / 60.0;
	int i = int(h);
	float f = h - float(i);
	float p = hsv.z * (1.0 - hsv.y);
	float q = hsv.z * (1.0 - hsv.y * f);
	float t = hsv.z * (1.0 - hsv.y * (1.0 - f));
	if (i == 0) {
		rgb.r = hsv.z;
		rgb.g = t;
		rgb.b = p;
	}
	else if (i == 1) {
		rgb.r = q;
		rgb.g = hsv.z;
		rgb.b = p;
	}
	else if (i == 2) {
		rgb.r = p;
		rgb.g = hsv.z;
		rgb.b = t;
	}
	else if (i == 3) {
		rgb.r = p;
		rgb.g = q;
		rgb.b = hsv.z;
	}
	else if (i == 4) {
		rgb.r = t;
		rgb.g = p;
		rgb.b = hsv.z;
	}
	else {
		rgb.r = hsv.z;
		rgb.g = p;
		rgb.b = q;
	}
	return rgb;
}

vec3 mix(vec3 a, vec3 b, int mode) {
	if (mode == MIX_MODE_MULTIPLY) {
		return a * b;
	}
	if (mode == MIX_MODE_ADD) {
		return a + b;
	}
	if (mode == MIX_MODE_SUBTRACT) {
		return a - b;
	}
	if (mode == MIX_MODE_DIVIDE) {
		return a / b;
	}
	if (mode == MIX_MODE_SCREEN) {
		return 1.0 - (1.0 - a) * (1.0 - b);
	}
	if (mode == MIX_MODE_OVERLAY) {
		return a * (1.0 - b) + b * (1.0 - a);
	}
	if (mode == MIX_MODE_DARKEN) {
		return min(a, b);
	}
	if (mode == MIX_MODE_LIGHTEN) {
		return max(a, b);
	}
	if (mode == MIX_MODE_DIFFERENCE) {
		return abs(a - b);
	}
	if (mode == MIX_MODE_EXCLUSION) {
		return a + b - 2.0 * a * b;
	}
	if (mode == MIX_MODE_SOFT_LIGHT) {
		return (1.0 - b) * a * a + 2.0 * b * a;
	}
	if (mode == MIX_MODE_HARD_LIGHT) {
		vec3 c = 2.0 * a * b;
		vec3 d = 1.0 - 2.0 * (1.0 - a) * (1.0 - b);
		vec3 e = step(0.5, b);
		return c * e + d * (1.0 - e);
	}
	if (mode == MIX_MODE_COLOR_DODGE) {
		return a / (1.0 - b);
	}
	if (mode == MIX_MODE_COLOR_BURN) {
		return 1.0 - (1.0 - a) / b;
	}
	if (mode == MIX_MODE_LINEAR_DODGE) {
		return a + b;
	}
	if (mode == MIX_MODE_LINEAR_BURN) {
		return a + b - 1.0;
	}
	if (mode == MIX_MODE_LINEAR_LIGHT) {
		return a + 2.0 * b - 1.0;
	}
	if (mode == MIX_MODE_VIVID_LIGHT) {
		return a + 2.0 * b - 1.0;
	}
	if (mode == MIX_MODE_PIN_LIGHT) {
		return a + 2.0 * b - 1.0;
	}
	if (mode == MIX_MODE_HARD_MIX) {
		return step(0.5, a + b);
	}
	if (mode == MIX_MODE_REFLECT) {
		return a * a / (1.0 - b);
	}
	if (mode == MIX_MODE_GLOW) {
		return b * b / (1.0 - a);
	}
	if (mode == MIX_MODE_PHOENIX) {
		return min(a, b) - max(a, b) + 1.0;
	}
	if (mode == MIX_MODE_HUE) {
		vec3 hsvA = rgbToHsv(a);
		vec3 hsvB = rgbToHsv(b);
		return hsvToRgb(vec3(hsvB.x, hsvA.y, hsvA.z));
	}
	if (mode == MIX_MODE_SATURATION) {
		vec3 hsvA = rgbToHsv(a);
		vec3 hsvB = rgbToHsv(b);
		return hsvToRgb(vec3(hsvA.x, hsvB.y, hsvA.z));
	}
	if (mode == MIX_MODE_COLOR) {
		vec3 hsvA = rgbToHsv(a);
		vec3 hsvB = rgbToHsv(b);
		return hsvToRgb(vec3(hsvB.x, hsvB.y, hsvA.z));
	}
	if (mode == MIX_MODE_LUMINOSITY) {
		vec3 hsvA = rgbToHsv(a);
		vec3 hsvB = rgbToHsv(b);
		return hsvToRgb(vec3(hsvA.x, hsvA.y, hsvB.z));
	}
	return a;
}

void main() {
	if (texCount == 0) {
		color = albedo;
		return;
	}
	vec4 originalTexColor = texture(textures[0], passTexCoords);
	vec3 texColor = originalTexColor.rgb;
	for (int i = 1; i < texCount; i++) {
		vec4 nextTexColor = texture(textures[i], passTexCoords);
		texColor = mix(texColor, nextTexColor.rgb, mixModes[i - 1]);
		texColor = clamp(texColor, 0.0, 1.0);
	}
	vec4 finalColor = vec4(texColor, originalTexColor.a) * albedo;
	color = finalColor;
}
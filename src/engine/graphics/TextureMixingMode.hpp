#pragma once

namespace engine::graphics {
	
	enum class TextureMixingMode : int {
		Multiply = 0,
		Add = 1,
		Subtract = 2,
		Divide = 3,
		Screen = 4,
		Overlay = 5,
		Darken = 6,
		Lighten = 7,
		Difference = 8,
		Exclusion = 9,
		SoftLight = 10,
		HardLight = 11,
		ColorDodge = 12,
		ColorBurn = 13,
		LinearDodge = 14,
		LinearBurn = 15,
		LinearLight = 16,
		VividLight = 17,
		PinLight = 18,
		HardMix = 19,
		Reflect = 20,
		Glow = 21,
		Phoenix = 22,
		Hue = 23,
		Saturation = 24,
		Color = 25,
		Luminosity = 26
	};
	
} // engine::graphics

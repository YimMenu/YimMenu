#pragma once

namespace big
{
	constexpr const static auto gravity_presets = std::to_array({
		"Moon", 
		"Sun", 
		"Pluto", 
		"Space", 
		"Mercury", 
		"Venus",
		"Earth",
		"Mars", 
		"Jupiter", 
		"Saturn", 
		"Uranus", 
		"Neptune"
		});

	constexpr const static auto gravity_preset_values = std::to_array({
		1.6f,
		274.f,
		0.6f,
		0.f,
		3.7f,
		8.9f,
		9.8f,
		3.7f,
		24.8f,
		10.5f,
		8.7f,
		11.2f
		});
}

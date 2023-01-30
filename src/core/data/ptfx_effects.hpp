#pragma once

enum class PTFXEffects
{
	Lighting,
	Clown,
	Firework,
	Alien1,
	Alien2,
	Electric,
	Electric_Boosh,
	Water_Splash,
	Smoke,
	Ghost_Rider
};

struct PTFXEffectType {
	PTFXEffects type;
	const char name[32];
};

const PTFXEffectType ptfx_types[] = {
	{ PTFXEffects::Lighting,		"Lighting" },
	{ PTFXEffects::Clown,			"Clown" },
	{ PTFXEffects::Firework,		"Firework" },
	{ PTFXEffects::Alien1,			"Alien 1" },
	{ PTFXEffects::Alien2,			"Alien 2" },
	{ PTFXEffects::Electric,		"Electric" },
	{ PTFXEffects::Electric_Boosh,	"Electric Boosh" },
	{ PTFXEffects::Water_Splash,	"Water Splash" },
	{ PTFXEffects::Smoke,			"Smoke" },
	{ PTFXEffects::Ghost_Rider,		"Ghost Rider" },
};
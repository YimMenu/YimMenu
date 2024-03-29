#pragma once

#include "gta/joaat.hpp"
#include "natives.hpp"

enum Weapons : Hash
{
	WEAPON_UNARMED = "WEAPON_UNARMED"_J
};

enum Gadgets : Hash
{
	GADGET_OBJECT    = "OBJECT"_J,
	GADGET_PARACHUTE = "GADGET_PARACHUTE"_J
};

enum WeaponGroup : Hash
{
	GROUP_MELEE            = "GROUP_MELEE"_J,
	GROUP_UNARMED          = "GROUP_UNARMED"_J,
	GROUP_PISTOL           = "GROUP_PISTOL"_J,
	GROUP_RIFLE            = "GROUP_RIFLE"_J,
	GROUP_MG               = "GROUP_MG"_J,
	GROUP_SMG              = "GROUP_SMG"_J,
	GROUP_SHOTGUN          = "GROUP_SHOTGUN"_J,
	GROUP_STUNGUN          = "GROUP_STUNGUN"_J,
	GROUP_SNIPER           = "GROUP_SNIPER"_J,
	GROUP_HEAVY            = "GROUP_HEAVY"_J,
	GROUP_THROWN           = "GROUP_THROWN"_J,
	GROUP_FIREEXTINGUISHER = "GROUP_FIREEXTINGUISHER"_J,
	GROUP_PETROLCAN        = "GROUP_PETROLCAN"_J,
	GROUP_DIGISCANNER      = "GROUP_DIGISCANNER"_J,
	GROUP_NIGHTVISION      = "GROUP_NIGHTVISION"_J,
	GROUP_PARACHUTE        = "GROUP_PARACHUTE"_J
};

#pragma once
#include "weapon/CAmmoInfo.hpp"

struct SpecialAmmo
{
	char name[32];
	eAmmoSpecialType type;
};

constexpr std::array<SpecialAmmo, 7> SPECIAL_AMMOS = {{
    {"No Special Ammo", eAmmoSpecialType::None},
    {"Armor Piercing Ammo", eAmmoSpecialType::ArmorPiercing},
    {"Explosive Ammo", eAmmoSpecialType::Explosive},
    {"Full Metal Jacket Ammo", eAmmoSpecialType::FMJ},
    {"Hollow Point Ammo", eAmmoSpecialType::HollowPoint},
    {"Incendiary Ammo", eAmmoSpecialType::Incendiary},
    {"Tracer Ammo", eAmmoSpecialType::Tracer},
}};
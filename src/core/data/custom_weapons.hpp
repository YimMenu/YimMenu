#pragma once
#include "core/enums.hpp"

struct custom_weapon
{
	big::CustomWeapon id;
	const char name[32];
};

const custom_weapon custom_weapons[] = {
    {big::CustomWeapon::NONE, "No weapon"},
    {big::CustomWeapon::CAGE_GUN, "Cage Gun"},
    {big::CustomWeapon::DELETE_GUN, "Delete Gun"},
    {big::CustomWeapon::GRAVITY_GUN, "Gravity Gun"},
    {big::CustomWeapon::STEAL_VEHICLE_GUN, "Steal Vehicle Gun"},
    {big::CustomWeapon::REPAIR_GUN, "Repair Gun"},
    {big::CustomWeapon::VEHICLE_GUN, "Vehicle Gun"},
};
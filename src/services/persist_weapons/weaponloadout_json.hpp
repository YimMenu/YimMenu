#pragma once

namespace big
{
	struct weaponloadout_weapon_json
	{
		Hash weapon;
		Hash group;
		std::vector<Hash> component_array;
		int tint;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weaponloadout_weapon_json, weapon, group, component_array, tint)
	};


	struct weaponloadout_json
	{
		std::vector<weaponloadout_weapon_json> weapons;
		int parachutes;
		int parachute_tint;
		int parachute_pack_tint;
		int reserve_pack_tint;
		int smoke_trail[3];

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weaponloadout_json, weapons, parachutes, parachute_tint, parachute_pack_tint, reserve_pack_tint, smoke_trail)
	};
}
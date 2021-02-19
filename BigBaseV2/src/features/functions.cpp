#include "functions.hpp"
#include "gta/joaat.hpp"
#include "gta/levels.hpp"
#include "gta/PickupRewards.h"
#include "pointers.hpp"
#include "natives.hpp"
#include "notify.hpp"
#include "script.hpp"
#include "script_global.hpp"

namespace big
{
	void func::cage_ped(Ped ped)
	{
		Hash hash = RAGE_JOAAT("prop_gold_cont_01");

		Vector3 location = ENTITY::GET_ENTITY_COORDS(ped, true);
		OBJECT::CREATE_OBJECT(hash, location.x, location.y, location.z - 1.f, true, false, false);
	}

	void func::create_ambient_money(Vector3 location, int amount)
	{
		Hash hash = RAGE_JOAAT("PICKUP_MONEY_PAPER_BAG");

		OBJECT::CREATE_AMBIENT_PICKUP(hash, location.x, location.y, location.z + 0.5f, 0, amount, hash, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	}

	void func::create_ambient_rp(Vector3 location)
	{
		// vw_prop_vw_colle_imporage
		Hash hash = RAGE_JOAAT("vw_prop_vw_colle_alien");
		do {
			STREAMING::REQUEST_MODEL(hash);

			script::get_current()->yield(1ms);
		} while (!STREAMING::HAS_MODEL_LOADED(hash));

		OBJECT::CREATE_AMBIENT_PICKUP(0x2C014CA6, location.x, location.y, location.z + 0.5f, 0, 10, hash, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	}

	float func::deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	void func::delete_entity(Entity ent)
	{
		take_control_of_entity(ent);

		ENTITY::DETACH_ENTITY(ent, 1, 1);
		ENTITY::SET_ENTITY_VISIBLE(ent, false, false);
		NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(ent, true);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0, 0, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, 1, 1);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
		ENTITY::DELETE_ENTITY(&ent);
	}

	double func::distance_between_vectors(Vector3 a, Vector3 b)
	{
		return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	void func::force_kick_from_vehicle(Player player)
	{
		Ped ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player);

		for (int i = 0; i < 5 && PED::IS_PED_IN_ANY_VEHICLE(ped, true); i++)
		{
			TASK::CLEAR_PED_TASKS_IMMEDIATELY(ped);

			script::get_current()->yield(5ms);
		}
	}

	void func::get_active_character_slot(int* statSlot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), statSlot, true);
	}

	static const Hash pickups[] = { 0x550447A9, 0xF92F486C, 0x602941D0, 0xE013E01C, 0x881AB0A8, 0xA421A532, 0x5C517D97, 0xDE58E0B3, 0xF25A01B9, 0xF99E15D0, 0x20796A82, 0xE4BD2FC6, 0x84837FD7, 0x77F3F2DD, 0x116FC4E6, 0xC02CF125, 0x4BFB42D1, 0xE33D8630, 0x2C014CA6, 0xE175C698, 0x1CD2CF66, 0x8F707C18, 0xCE6FDD6B, 0x20893292, 0x14568F28, 0x711D02A4, 0x1E9A99F8, 0xDE78F17E, 0xFE18F3AF, 0x5DE0AD3E, 0x6773257D, 0xEE0E26F3, 0xA7EA40CE, 0xA04E8B0D, 0x6E717A95, 0x90EFDF3B, 0x4B5259BE, 0xC3CD8B31, 0x4C35269, 0x94FA0B5E, 0x31EA45C9, 0x80AB931C, 0xE7CF07CC, 0x4316CC09, 0xA5B8CAA9, 0x41D2CF56, 0x4F92184, 0x98D79EF, 0xFDEE8368, 0x65948212, 0xCC8B3905, 0x68605A36, 0xD0AACEF7, 0xA717F898, 0xB86AEE5B, 0x84D676D4, 0xA54AE7B7, 0xD3A39366, 0x2E071B5A, 0xCC7CCD1B, 0x65A7D8E9, 0x2C804FE3, 0xB2B5325E, 0x3B662889, 0xF33C83B0, 0x8187206F, 0x9299C95B, 0x741C684A, 0xBCC5C1F2, 0x81EE601E, 0x977C0F2, 0xFA51ABF5, 0x815D66E8, 0x8C0FCB13, 0x6E4E65C2, 0xDF711959, 0xBDD874BC, 0xB2930A14, 0xA91FDC8B, 0x789576E2, 0x8967B4F3, 0xF0EA0639, 0xFE73AB5, 0x872DC888, 0xBFEE6C3B, 0xF9E2DF1F, 0x3B0F70A7, 0x22B15640, 0xBD4DE242, 0xBDB6FFA5, 0x88EAACA7, 0x5E0683A1, 0x2E764125, 0x5307A4EC, 0x295691A9, 0x4E301CD0, 0x9CF13918, 0xBED46EC5, 0x693583AD, 0xFF0A8297, 0xC01EB678, 0x278D8734, 0xFD9CAEDE, 0xD8257ABF, 0xF5C5DADC, 0x8ADDEC75, 0x79284A9, 0x9F55D149, 0x85CAA9B1, 0x1D9588D3, 0x2F36B434, 0xD3722A5B, 0x2DD30479, 0x763F7121, 0x5EA16D74, 0xC69DE3FF, 0xAF692CA9, 0xF9AFB48F, 0x499A096A, 0x6C5B941A, 0x93EBB26, 0x624F7213, 0xA9355DCD, 0x5DB6C18A, 0xE46E11B4, 0x614BFCAC, 0x6D60976C, 0x4D36C349, 0x96B412A3, 0x3A4C2AD2, 0xEF2B7390, 0x1CD604C7, 0xFE2A352C, 0xC5B72713, 0x3DE942BD, 0x968339D, 0x5A26FE0, 0x7C119D58, 0xCC90A373, 0xFD16169E, 0xDDE4181A, 0xEBF89D5F, 0xE5121369 };
	bool func::is_crash_pickup(Hash hash)
	{
		for (Hash pickup : pickups)
			if (pickup == hash) return false;

		return true;
	}

	bool func::is_crash_reward(Hash hash)
	{
		switch (hash)
		{
		case REWARD_AMMO_ADVANCEDRIFLE:
		case REWARD_AMMO_APPISTOL:
		case REWARD_AMMO_ASSAULTRIFLE:
		case REWARD_AMMO_ASSAULTSHOTGUN:
		case REWARD_AMMO_ASSAULTSMG:
		case REWARD_AMMO_AUTOSHOTGUN:
		case REWARD_AMMO_BULLET_MP:
		case REWARD_AMMO_BULLPUPRIFLE:
		case REWARD_AMMO_BULLPUPSHOTGUN:
		case REWARD_AMMO_CARBINERIFLE:
		case REWARD_AMMO_COMBATMG:
		case REWARD_AMMO_COMBATPDW:
		case REWARD_AMMO_COMBATPISTOL:
		case REWARD_AMMO_COMPACTLAUNCHER:
		case REWARD_AMMO_COMPACTRIFLE:
		case REWARD_AMMO_DBSHOTGUN:
		case REWARD_AMMO_DOUBLEACTION:
		case REWARD_AMMO_FIREWORK:
		case REWARD_AMMO_FIREWORK_MP:
		case REWARD_AMMO_FLAREGUN:
		case REWARD_AMMO_GRENADE:
		case REWARD_AMMO_GRENADELAUNCHER:
		case REWARD_AMMO_GRENADELAUNCHER_MP:
		case REWARD_AMMO_GUSENBERG:
		case REWARD_AMMO_HEAVYPISTOL:
		case REWARD_AMMO_HEAVYSHOTGUN:
		case REWARD_AMMO_HEAVYSNIPER:
		case REWARD_AMMO_HOMINGLAUNCHER:
		case REWARD_AMMO_MACHINEPISTOL:
		case REWARD_AMMO_MARKSMANPISTOL:
		case REWARD_AMMO_MARKSMANRIFLE:
		case REWARD_AMMO_MG:
		case REWARD_AMMO_MICROSMG:
		case REWARD_AMMO_MINIGUN:
		case REWARD_AMMO_MINISMG:
		case REWARD_AMMO_MISSILE_MP:
		case REWARD_AMMO_MOLOTOV:
		case REWARD_AMMO_MUSKET:
		case REWARD_AMMO_PETROLCAN:
		case REWARD_AMMO_PIPEBOMB:
		case REWARD_AMMO_PISTOL:
		case REWARD_AMMO_PISTOL50:
		case REWARD_AMMO_PROXMINE:
		case REWARD_AMMO_PUMPSHOTGUN:
		case REWARD_AMMO_PUMPSHOTGUN_ENTER_VEHICLE:
		case REWARD_AMMO_RAILGUN:
		case REWARD_AMMO_RAYPISTOL:
		case REWARD_AMMO_REVOLVER:
		case REWARD_AMMO_RPG:
		case REWARD_AMMO_SAWNOFFSHOTGUN:
		case REWARD_AMMO_SMG:
		case REWARD_AMMO_SMOKEGRENADE:
		case REWARD_AMMO_SNIPERRIFLE:
		case REWARD_AMMO_SNSPISTOL:
		case REWARD_AMMO_SPECIALCARBINE:
		case REWARD_AMMO_STICKYBOMB:
		case REWARD_AMMO_STUNGUN:
		case REWARD_AMMO_VINTAGEPISTOL:
		case REWARD_ARMOUR:
		case REWARD_HEALTH:
		case REWARD_HEALTH_ENTER_VEHICLE:
		case REWARD_HEALTH_VARIABLE:
		case REWARD_MONEY_VARIABLE:
		case REWARD_PARACHUTE:
		case REWARD_STAT_HEALTH:
		case REWARD_STAT_HEALTH_VARIABLE:
		case REWARD_STAT_WEAPON:
		case REWARD_VEHICLE_FIX:
		case REWARD_WEAPON_ADVANCEDRIFLE:
		case REWARD_WEAPON_APPISTOL:
		case REWARD_WEAPON_ASSAULTRIFLE:
		case REWARD_WEAPON_ASSAULTRIFLE_MK2:
		case REWARD_WEAPON_ASSAULTSHOTGUN:
		case REWARD_WEAPON_ASSAULTSMG:
		case REWARD_WEAPON_AUTOSHOTGUN:
		case REWARD_WEAPON_BAT:
		case REWARD_WEAPON_BATTLEAXE:
		case REWARD_WEAPON_BOTTLE:
		case REWARD_WEAPON_BULLPUPRIFLE:
		case REWARD_WEAPON_BULLPUPRIFLE_MK2:
		case REWARD_WEAPON_BULLPUPSHOTGUN:
		case REWARD_WEAPON_CARBINERIFLE:
		case REWARD_WEAPON_CARBINERIFLE_MK2:
		case REWARD_WEAPON_COMBATMG:
		case REWARD_WEAPON_COMBATMG_MK2:
		case REWARD_WEAPON_COMBATPDW:
		case REWARD_WEAPON_COMBATPISTOL:
		case REWARD_WEAPON_COMPACTLAUNCHER:
		case REWARD_WEAPON_COMPACTRIFLE:
		case REWARD_WEAPON_CROWBAR:
		case REWARD_WEAPON_DAGGER:
		case REWARD_WEAPON_DBSHOTGUN:
		case REWARD_WEAPON_DOUBLEACTION:
		case REWARD_WEAPON_FIREWORK:
		case REWARD_WEAPON_FLAREGUN:
		case REWARD_WEAPON_FLASHLIGHT:
		case REWARD_WEAPON_GOLFCLUB:
		case REWARD_WEAPON_GRENADE:
		case REWARD_WEAPON_GRENADELAUNCHER:
		case REWARD_WEAPON_GUSENBERG:
		case REWARD_WEAPON_HAMMER:
		case REWARD_WEAPON_HATCHET:
		case REWARD_WEAPON_HEAVYPISTOL:
		case REWARD_WEAPON_HEAVYSHOTGUN:
		case REWARD_WEAPON_HEAVYSNIPER:
		case REWARD_WEAPON_HEAVYSNIPER_MK2:
		case REWARD_WEAPON_HOMINGLAUNCHER:
		case REWARD_WEAPON_KNIFE:
		case REWARD_WEAPON_KNUCKLE:
		case REWARD_WEAPON_MACHETE:
		case REWARD_WEAPON_MACHINEPISTOL:
		case REWARD_WEAPON_MARKSMANPISTOL:
		case REWARD_WEAPON_MARKSMANRIFLE:
		case REWARD_WEAPON_MARKSMANRIFLE_MK2:
		case REWARD_WEAPON_MG:
		case REWARD_WEAPON_MICROSMG:
		case REWARD_WEAPON_MINIGUN:
		case REWARD_WEAPON_MINISMG:
		case REWARD_WEAPON_MOLOTOV:
		case REWARD_WEAPON_MUSKET:
		case REWARD_WEAPON_NIGHTSTICK:
		case REWARD_WEAPON_PETROLCAN:
		case REWARD_WEAPON_PIPEBOMB:
		case REWARD_WEAPON_PISTOL:
		case REWARD_WEAPON_PISTOL50:
		case REWARD_WEAPON_PISTOL_MK2:
		case REWARD_WEAPON_POOLCUE:
		case REWARD_WEAPON_PROXMINE:
		case REWARD_WEAPON_PUMPSHOTGUN:
		case REWARD_WEAPON_PUMPSHOTGUN_MK2:
		case REWARD_WEAPON_RAILGUN:
		case REWARD_WEAPON_RAYCARBINE:
		case REWARD_WEAPON_RAYMINIGUN:
		case REWARD_WEAPON_RAYPISTOL:
		case REWARD_WEAPON_REVOLVER:
		case REWARD_WEAPON_REVOLVER_MK2:
		case REWARD_WEAPON_RPG:
		case REWARD_WEAPON_SAWNOFFSHOTGUN:
		case REWARD_WEAPON_SMG:
		case REWARD_WEAPON_SMG_MK2:
		case REWARD_WEAPON_SMOKEGRENADE:
		case REWARD_WEAPON_SNIPERRIFLE:
		case REWARD_WEAPON_SNSPISTOL:
		case REWARD_WEAPON_SNSPISTOL_MK2:
		case REWARD_WEAPON_SPECIALCARBINE:
		case REWARD_WEAPON_SPECIALCARBINE_MK2:
		case REWARD_WEAPON_STICKYBOMB:
		case REWARD_WEAPON_STONE_HATCHET:
		case REWARD_WEAPON_STUNGUN:
		case REWARD_WEAPON_SWITCHBLADE:
		case REWARD_WEAPON_VINTAGEPISTOL:
		case REWARD_WEAPON_WRENCH:
			return false;
		}

		return true;
	}

	void func::join_message(Player player)
	{
		if (!g_settings.options["join_message"]) return;

		char join_msg[64];
		sprintf(join_msg, "<C>%s</C> is joining...", g_pointers->m_get_player_name(player));

		notify::above_map(join_msg);
	}

	void func::join_session_type(session_type session)
	{
		if (session.id == -1)
			*script_global(1312443).at(2).as<int*>() = -1;
		else
			*script_global(1312854).as<int*>() = session.id;

		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 1);
		script::get_current()->yield(200ms);
		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 0);
	}

	bool func::raycast_entity(Entity* ent)
	{
		BOOL hit;
		Vector3 endCoords;
		Vector3 surfaceNormal;

		Vector3 camCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
		Vector3 dir = rotation_to_direction(rot);
		Vector3 farCoords;

		farCoords.x = camCoords.x + dir.x * 1000;
		farCoords.y = camCoords.y + dir.y * 1000;
		farCoords.z = camCoords.z + dir.z * 1000;

		int ray = SHAPETEST::_START_SHAPE_TEST_RAY(camCoords.x, camCoords.y, camCoords.z, farCoords.x, farCoords.y, farCoords.z, -1, 0, 7);
		SHAPETEST::GET_SHAPE_TEST_RESULT(ray, &hit, &endCoords, &surfaceNormal, ent);

		return (bool)hit;
	}
	
	void func::reset_vehicle_sell_stats()
	{
		get_active_character_slot(&g_temp.character_slot);

		char stat_string[64];
		sprintf(stat_string, "MP%d_MONEY_EARN_SELLING_VEH", g_temp.character_slot);

		STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_VEHICLE_SELL_TIME"), 0, true);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(stat_string), 50000, true);
	}
	
	Vector3 func::rotation_to_direction(Vector3 rotation)
	{
		float x = deg_to_rad(rotation.x);
		float z = deg_to_rad(rotation.z);

		float num = abs(cos(x));

		return Vector3
		{
			-sin(z) * num,
			cos(z) * num,
			sin(x)
		};
	}

	void func::set_car_sell_value(int value)
	{
		*script_global(99007).at(970).as<int*>() = value;
	}

	void func::set_player_bounty(Player player, int amount, bool anonymous)
	{
		int64_t args[22] =
		{
			RemoteEvents::Bounty,	// Hash
			0,
			player,					// Player
			1,
			amount,					// Bounty
			0,
			anonymous,				// Anonymous (caused by NPC or Lester)
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			*script_global(1652336).at(9).as<int*>(),
			*script_global(1652336).at(10).as<int*>()
		};

		for (uint8_t i = 0; i < 32; i++)
		{
			args[1] = i;

			g_pointers->m_trigger_script_event(true, args, 22, 1 << i);

			script::get_current()->yield();
		}
	}
	
	void func::set_player_level(int level)
	{
		get_active_character_slot(&g_temp.character_slot);

		char level_string[64];
		sprintf(level_string, "MP%d_CHAR_SET_RP_GIFT_ADMIN", g_temp.character_slot);

		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(level_string), levels[level - 1], 0);
	}

	Entity func::spawn_vehicle(const char* model, Vector3 location, float heading)
	{
		Hash hash = rage::joaat(model);

		if (hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				notify::above_map("~r~Failed to spawn model, did you give an incorrect model?");

				return -1;
			}

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, heading, true, false, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
				ENTITY::_SET_ENTITY_SOMETHING(veh, true);
				int networkId = NETWORK::VEH_TO_NET(veh);
				if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
				VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
			}

			return veh;
		}

		return -1;
	}

	void func::spoof_rank(int rank)
	{
		*script_global(1590682).at(PLAYER::PLAYER_ID(), 883).at(211).at(6).as<int*>() = rank;
	}

	bool func::take_control_of_entity(Entity ent)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return true;
		for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 5; i++)
		{
			bool in_spectator = NETWORK::NETWORK_IS_IN_SPECTATOR_MODE();
			if (in_spectator) NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(0, PLAYER::PLAYER_PED_ID());

			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

			if (in_spectator) NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(1, PLAYER::PLAYER_PED_ID());

			script::get_current()->yield();
		}
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}

	void func::toggle_protections(bool toggle)
	{
		auto& protections = g_settings.options["settings"]["script_protections"];

		protections["bounty"] = toggle;
		protections["ceo_ban"] = toggle;
		protections["ceo_kick"] = toggle;
		protections["ceo_money"] = toggle;
		protections["clear_wanted_level"] = toggle;
		protections["fake_deposit"] = toggle;
		protections["force_mission"] = toggle;
		protections["gta_banner"] = toggle;
		protections["kick"] = toggle;
		protections["personal_vehicle_destroyed"] = toggle;
		protections["remote_off_radar"] = toggle;
		protections["rotate_cam"] = toggle;
		protections["send_to_cutscene"] = toggle;
		protections["send_to_island"] = toggle;
		protections["sound_spam"] = toggle;
		protections["spectate"] = toggle;
		protections["force_teleport"] = toggle;
		protections["transaction_error"] = toggle;
		protections["vehicle_kick"] = toggle;

		g_settings.save();
	}
}
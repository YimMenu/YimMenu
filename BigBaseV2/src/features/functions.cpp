#include "functions.hpp"
#include "gta/enums.hpp"
#include "gta/levels.hpp"
#include "pointers.hpp"
#include "script_global.hpp"

namespace big::features::functions
{
	void get_active_character_slot(int* statSlot)
	{
		STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), statSlot, true);
	}

	void join_session_type(session_type session)
	{
		if (session.id == -1)
			*script_global(1312443).at(2).as<int*>() = -1;
		else
			*script_global(1312854).as<int*>() = session.id;

		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 1);
		script::get_current()->yield(200ms);
		MISC::SET_BIT(&*script_global(1312443).as<int*>(), 0);
	}

	void reset_vehicle_sell_stats()
	{
		get_active_character_slot(&g_temp.character_slot);

		char stat_string[64];
		sprintf(stat_string, "MP%d_MONEY_EARN_SELLING_VEH", g_temp.character_slot);

		STATS::STAT_SET_INT(RAGE_JOAAT("MPPLY_VEHICLE_SELL_TIME"), 0, true);
		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(stat_string), 50000, true);
	}

	void set_car_sell_value(int value)
	{
		*script_global(99007).at(970).as<int*>() = value;
	}

	void set_player_bounty(Player player, bool anonymous)
	{
		int64_t args[22] =
		{
			RemoteEvents::Bounty,	// Hash
			0,
			player,					// Player
			1,
			10000,					// Bounty
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

	void set_player_level(int level)
	{
		get_active_character_slot(&g_temp.character_slot);

		char level_string[64];
		sprintf(level_string, "MP%d_CHAR_SET_RP_GIFT_ADMIN", g_temp.character_slot);

		STATS::STAT_SET_INT(MISC::GET_HASH_KEY(level_string), levels[level - 1], 0);
	}

	void spoof_rank(int rank)
	{
		*script_global(1590682).at(PLAYER::PLAYER_ID(), 883).at(211).at(6).as<int*>() = rank;
	}

	void toggle_protections(bool toggle)
	{
		auto &protections = g_settings.options["settings"]["script_protections"];

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

	bool take_control_of_entity(Entity ent)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return true;
		for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 5; i++)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

			script::get_current()->yield();
		}
		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent)) return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}

	BOOL raycast_entity(Entity* ent)
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

		return hit;
	}

	float deg_to_rad(float deg)
	{
		double radian = (3.14159265359 / 180) * deg;
		return (float)radian;
	}

	Vector3 rotation_to_direction(Vector3 rotation)
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

	double distance_between_vectors(Vector3 a, Vector3 b)
	{
		return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	Entity spawn_vehicle(const char* model, Vector3 location, float heading)
	{
		Hash hash = MISC::GET_HASH_KEY(model);

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

	void create_ambient_money(Vector3 location, int amount)
	{
		Hash hash = RAGE_JOAAT("PICKUP_MONEY_PAPER_BAG");

		OBJECT::CREATE_AMBIENT_PICKUP(hash, location.x, location.y, location.z + 0.5f, 0, amount, hash, false, true);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
	}

	void cage_ped(Ped ped)
	{
		Hash hash = RAGE_JOAAT("prop_gold_cont_01");

		Vector3 location = ENTITY::GET_ENTITY_COORDS(ped, true);
		OBJECT::CREATE_OBJECT(hash, location.x, location.y, location.z - 1.f, true, false, false);
	}
}
#pragma once
#include "natives.hpp"
#include "pointers.hpp"

namespace big::ped
{
	inline void steal_outfit(const Ped target)
	{
		Ped ped = self::ped;
		
		if (ENTITY::GET_ENTITY_MODEL(ped) != ENTITY::GET_ENTITY_MODEL(target)) {
			g_notification_service->push("Error", "Model mismatch, use steal identity instead.");
			return;
		}
		for (int i = 0; i < 12; i++) {
			PED::SET_PED_COMPONENT_VARIATION
			(
				ped,
				i,
				PED::GET_PED_DRAWABLE_VARIATION(target, i),
				PED::GET_PED_TEXTURE_VARIATION(target, i),
				PED::GET_PED_PALETTE_VARIATION(target, i)
			);
		}
	}

	inline void steal_identity(const Ped target)
	{
		const int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(self::ped);
		const int current_health = ENTITY::GET_ENTITY_HEALTH(self::ped);
		const int current_armor = PED::GET_PED_ARMOUR(self::ped);

		PLAYER::SET_PLAYER_MODEL(self::id , ENTITY::GET_ENTITY_MODEL(target));
		script::get_current()->yield();
		PED::CLONE_PED_TO_TARGET(target, self::ped);
		ENTITY::SET_ENTITY_MAX_HEALTH(self::ped, max_health);
		ENTITY::SET_ENTITY_HEALTH(self::ped, current_health, 0);
		PED::SET_PED_ARMOUR(self::ped, current_armor);
	}

	inline int spawn_in_vehicle(std::string_view model, Vehicle veh, bool is_networked = true, bool clean_up = true)
	{
		if (const Hash hash = rage::joaat(model.data()); hash)
		{
			for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
			{
				STREAMING::REQUEST_MODEL(hash);

				script::get_current()->yield();
			}
			if (!STREAMING::HAS_MODEL_LOADED(hash))
			{
				g_notification_service->push_warning("Spawn", "Failed to spawn model, did you give an incorrect model?");

				return -1;
			}

			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
			Ped ped = PED::CREATE_PED_INSIDE_VEHICLE(veh, 0, hash, -1, is_networked, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(ped, "MPBitset", 0);
				ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(ped, clean_up);
			}

			return ped;
		}

		return -1;
	}

	inline void play_anim(char* Dict, char* ID)
	{
		STREAMING::REQUEST_ANIM_DICT(Dict);
		if (STREAMING::HAS_ANIM_DICT_LOADED(Dict))
		{
			g_notification_service->push_warning("Animation", "Playing Animation");
		}
		if (!STREAMING::HAS_ANIM_DICT_LOADED(Dict))
		{	
			return;
		}
		TASK::TASK_PLAY_ANIM(PLAYER::PLAYER_PED_ID(), Dict, ID, 4.0f, -4.0f, -1, 1, 1, 0, 0, 0);
	}
	
	inline Ped spawn(ePedType pedType, Hash hash, Vector3 location, float heading, bool is_networked = true)
	{
		for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
		{
			STREAMING::REQUEST_MODEL(hash);
			script::get_current()->yield();
		}

		if (!STREAMING::HAS_MODEL_LOADED(hash))
		{
			return 0;
		}

		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
		auto ped = PED::CREATE_PED(pedType, hash, location.x, location.y, location.z, heading, is_networked, false);
		*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

		script::get_current()->yield();

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

		return ped;
	}
	
	inline void play_scenario(char* Scene)
	{
		TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), Scene, 0, true);
	}

	static constexpr char const* animlistName[] = { "Sechs F", "Sechs M", "Private Dance", "Pole Dance", "Push Ups", "Sit Ups", "Celebrate", "Shocked", "Suicide Pistol", "Suicide Pill", "Showering" };
	
	static constexpr char* const animlistDict[] = { "rcmpaparazzo_2", "rcmpaparazzo_2", "mini@strip_club@private_dance@part1", "mini@strip_club@pole_dance@pole_dance1", "amb@world_human_push_ups@male@base", 
		"amb@world_human_sit_ups@male@base", "rcmfanatic1celebrate", "ragdoll@human", "mp_suicide", "mp_suicide", "mp_safehouseshower@male@" };
	
	static constexpr char* const animlistID[] = { "shag_loop_poppy", "shag_loop_a", "priv_dance_p1", "pd_dance_01", "base", "base", "celebrate", "electrocute", "pistol", "pill", "male_shower_idle_b" };
	
	
	static constexpr char const* scenelist[] = { "Coffee", "Smoke", "Binocular", "Freeway", "Slumped", "Standing", "Wash", "Park Attendant", "Cheering", "Clipboard", "Drill", "Cop Idle", 
		"Drinking", "Drug Dealer", "Drug Dealer Hard", "Film SHocking", "Leaf Blower", "Gardener", "Golf Player", "Guard Patrol", "Guard Stand", "Guard Stand Army", "Hammering", "Hangout", 
		"Hiker", "Hiker Standing", "Human Statue", "Janitor", "Jogging", "Jog Standing", "Leaning", "Maid Clean", "Flex", "Free Weights", "Musician", "Paparazzi", "Partying", "Picnic", 
		"Prostitute High Class", "Prostitute Low Class", "Pushups", "Seat Ledge", "Seat Ledge Nom Nom", "Seat Steps", "Seat Wall", "Seat Wall Eating", "Security Torch", "Situps", "Smoking", 
		"Smoking Pot", "Stand Fire", "Fishing", "Impatient", "Impatient Upright", "Stand Mobile", "Stand Mobile Upright", "Strip Watch Stand", "Stupor", "Sunbathe", "Sunbathe Back", 
		"Tennis Player", "Tourist Map", "Tourist mobile", "Welding", "Window Shop", "Yoga", "Aim", "BBQ", "BIN", "Shopping Cart", "Chin Ups", "Parking Meter", "Seat Bar", "Seat bench", 
		"Bench Press", "Strip Watch", "Medic Kneel", "Tend to Dead", "Time of Death", "Crowd Control", "Investigate" };
	
	static constexpr char* const sceneID[] = { "WORLD_HUMAN_AA_COFFEE", "WORLD_HUMAN_AA_SMOKE", "WORLD_HUMAN_BINOCULARS", "WORLD_HUMAN_BUM_FREEWAY", "WORLD_HUMAN_BUM_SLUMPED", "WORLD_HUMAN_BUM_STANDING", "WORLD_HUMAN_BUM_WASH",
		"WORLD_HUMAN_CAR_PARK_ATTENDANT", "WORLD_HUMAN_CHEERING", "WORLD_HUMAN_CLIPBOARD", "WORLD_HUMAN_CONST_DRILL", "WORLD_HUMAN_COP_IDLES", "WORLD_HUMAN_DRINKING", "WORLD_HUMAN_DRUG_DEALER",
		"WORLD_HUMAN_DRUG_DEALER_HARD", "WORLD_HUMAN_MOBILE_FILM_SHOCKING", "WORLD_HUMAN_GARDENER_LEAF_BLOWER", "WORLD_HUMAN_GARDENER_PLANT", "WORLD_HUMAN_GOLF_PLAYER", "WORLD_HUMAN_GUARD_PATROL",
		"WORLD_HUMAN_GUARD_STAND", "WORLD_HUMAN_GUARD_STAND_ARMY", "WORLD_HUMAN_HAMMERING", "WORLD_HUMAN_HANG_OUT_STREET", "WORLD_HUMAN_HIKER", "WORLD_HUMAN_HIKER_STANDING", "WORLD_HUMAN_HUMAN_STATUE",
		"WORLD_HUMAN_JANITOR", "WORLD_HUMAN_JOG", "WORLD_HUMAN_JOG_STANDING", "WORLD_HUMAN_LEANING", "WORLD_HUMAN_MAID_CLEAN", "WORLD_HUMAN_MUSCLE_FLEX", "WORLD_HUMAN_MUSCLE_FREE_WEIGHTS", "WORLD_HUMAN_MUSICIAN",
		"WORLD_HUMAN_PAPARAZZI", "WORLD_HUMAN_PARTYING", "WORLD_HUMAN_PICNIC", "WORLD_HUMAN_PROSTITUTE_HIGH_CLASS", "WORLD_HUMAN_PROSTITUTE_LOW_CLASS", "WORLD_HUMAN_PUSH_UPS", "WORLD_HUMAN_SEAT_LEDGE",
		"WORLD_HUMAN_SEAT_LEDGE_EATING", "WORLD_HUMAN_SEAT_STEPS", "WORLD_HUMAN_SEAT_WALL", "WORLD_HUMAN_SEAT_WALL_EATING", "WORLD_HUMAN_SECURITY_SHINE_TORCH", "WORLD_HUMAN_SIT_UPS", "WORLD_HUMAN_SMOKING",
		"WORLD_HUMAN_SMOKING_POT", "WORLD_HUMAN_STAND_FIRE", "WORLD_HUMAN_STAND_FISHING", "WORLD_HUMAN_STAND_IMPATIENT", "WORLD_HUMAN_STAND_IMPATIENT_UPRIGHT", "WORLD_HUMAN_STAND_MOBILE",
		"WORLD_HUMAN_STAND_MOBILE_UPRIGHT", "WORLD_HUMAN_STRIP_WATCH_STAND", "WORLD_HUMAN_STUPOR", "WORLD_HUMAN_SUNBATHE", "WORLD_HUMAN_SUNBATHE_BACK", "WORLD_HUMAN_TENNIS_PLAYER", "WORLD_HUMAN_TOURIST_MAP",
		"WORLD_HUMAN_TOURIST_MOBILE", "WORLD_HUMAN_WELDING", "WORLD_HUMAN_WINDOW_SHOP_BROWSE", "WORLD_HUMAN_YOGA", "PROP_HUMAN_ATM", "PROP_HUMAN_BBQ", "PROP_HUMAN_BUM_BIN", "PROP_HUMAN_BUM_SHOPPING_CART",
		"PROP_HUMAN_MUSCLE_CHIN_UPS_ARMY", "PROP_HUMAN_PARKING_METER", "PROP_HUMAN_SEAT_BAR", "PROP_HUMAN_SEAT_BENCH", "PROP_HUMAN_SEAT_MUSCLE_BENCH_PRESS", "PROP_HUMAN_SEAT_STRIP_WATCH", "CODE_HUMAN_MEDIC_KNEEL",
		"CODE_HUMAN_MEDIC_TEND_TO_DEAD", "CODE_HUMAN_MEDIC_TIME_OF_DEATH", "CODE_HUMAN_POLICE_CROWD_CONTROL", "CODE_HUMAN_POLICE_INVESTIGATE" };


	static constexpr char const* visionList[] = { "Camera View", "Stoned", "RedMist", "Cocaine", "Drug Gas", "Wobbly", "Drunk", "Bloom", "Contrast", "Nostalgic", "Hallucination", "Low Graphics", "Chop View", "AAAAAAAA"};
	
	static constexpr char* const visionID[] = { "CAMERA_secuirity_FUZZ", "stoned", "REDMIST", "drug_flying_base", "DRUG_gas_huffin", "drug_wobbly", "Drunk", "Bloom", "PlayerSwitchPulse", "MP_Killstreak", "player_transition", "cinema_001", "CHOP", "BarryFadeOut" };
	
	
	static constexpr char const* give_weapon[] = { "None", "Stock", "Upgraded" };
}

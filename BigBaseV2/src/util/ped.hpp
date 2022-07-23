#pragma once
#include "natives.hpp"

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
		Ped ped = self::ped;

		const int max_health = ENTITY::GET_ENTITY_MAX_HEALTH(ped);
		const int current_health = ENTITY::GET_ENTITY_HEALTH(ped);
		const int current_armor = PED::GET_PED_ARMOUR(ped);

		PLAYER::SET_PLAYER_MODEL(self::id , ENTITY::GET_ENTITY_MODEL(target));
		PED::CLONE_PED_TO_TARGET(target, ped);
		ENTITY::SET_ENTITY_MAX_HEALTH(ped, max_health);
		ENTITY::SET_ENTITY_HEALTH(ped, current_health, 0);
		PED::SET_PED_ARMOUR(ped, current_armor);
	}

	inline int spawn(std::string_view model, Vector3 location, float heading, bool is_networked = true)
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
			Ped ped = PED::CREATE_PED(0, hash, location.x, location.y, location.z, heading, is_networked, false);
			*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

			script::get_current()->yield();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			if (*g_pointers->m_is_session_started)
			{
				DECORATOR::DECOR_SET_INT(ped, "MPBitset", 0);
				ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(ped, true);
			}

			return ped;
		}

		return -1;
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

	inline void play_scenario(char* Scene)
	{
		TASK::TASK_START_SCENARIO_IN_PLACE(PLAYER::PLAYER_PED_ID(), Scene, 0, true);
	}

	static constexpr char const* animlistID[] = { "Sechs F", "Sechs M", "Private Dance", "Pole Dance", "Push Ups", "Sit Ups", "Celebrate", "Shocked", "Suicide 1", "Suicide 2", "Showering" };
	
	static constexpr char const* scenelist[] = { "Coffee", "Smoke", "Binocular", "Freeway", "Slumped", "Standing", "Wash", "Park Attendant", "Cheering", "Clipboard", "Drill", "Cop Idle", 
		"Drinking", "Drug Dealer", "Drug Dealer Hard", "Film SHocking", "Leaf Blower", "Gardener", "Golf Player", "Guard Patrol", "Guard Stand", "Guard Stand Army", "Hammering", "Hangout", 
		"Hiker", "Hiker Standing", "Human Statue", "Janitor", "Jogging", "Jog Standing", "Leaning", "Maid Clean", "Flex", "Free Weights", "Musician", "Paparazzi", "Partying", "Picnic", 
		"Prostitute High Class", "Prostitute Low Class", "Pushups", "Seat Ledge", "Seat Ledge Nom Nom", "Seat Steps", "Seat Wall", "Seat Wall Eating", "Security Torch", "Situps", "Smoking", 
		"Smoking Pot", "Stand Fire", "Fishing", "Impatient", "Impatient Upright", "Stand Mobile", "Stand Mobile Upright", "Strip Watch Stand", "Stupor", "Sunbathe", "Sunbathe Back", 
		"Tennis Player", "Tourist Map", "Tourist mobile", "Welding", "Window Shop", "Yoga", "Aim", "BBQ", "BIN", "Shopping Cart", "Chin Ups", "Parking Meter", "Seat Bar", "Seat bench", 
		"Bench Press", "Strip Watch", "Medic Kneel", "Tend to Dead", "Time of Death", "Crowd Control", "Investigate" };

	static constexpr char const* visionList[] = { "Camera View", "Stoned", "RedMist", "Cocaine", "Drug Gas", "Wobbly", "Drunk", "Bloom", "Contrast", "Nostalgic", "Hallucination", "Low Graphics", "Chop View", "AAAAAAAA"};
	
	static constexpr char const* give_weapon[] = { "None", "Stock", "Upgraded" };
}
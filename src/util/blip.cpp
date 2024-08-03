#pragma once
#include "blip.hpp"

namespace big::blip
{
	bool get_blip_location(Vector3& location, int sprite, int color)
	{
		Blip blip;
		for (blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite); HUD::DOES_BLIP_EXIST(blip) && color != -1 && HUD::GET_BLIP_COLOUR(blip) != color; blip = HUD::GET_NEXT_BLIP_INFO_ID(sprite))
			;

		if (!HUD::DOES_BLIP_EXIST(blip) || (color != -1 && HUD::GET_BLIP_COLOUR(blip) != color))
			return false;

		location = HUD::GET_BLIP_COORDS(blip);

		return true;
	}

	bool get_objective_location_iteration(Vector3& location, const std::unordered_set<BlipIcons> sprites, const std::unordered_set<BlipColors> blip_colors = {})
	{
		for (int i = 0; i < 1500; i++)
		{
			auto blip = g_pointers->m_gta.m_blip_list->m_Blips[i].m_pBlip;
			if (blip != nullptr
			    && ((sprites.contains((BlipIcons)blip->m_icon)
			            && (blip_colors.empty() || blip_colors.contains((BlipColors)blip->m_color)))
			        || (blip->m_display_bits & BlipIsGPSRoute)))
			{
				location.x = blip->m_position.x;
				location.y = blip->m_position.y;
				location.z = blip->m_position.z;
				return true;
			}
		}
		location = {};
		return false;
	}

	bool get_blip_location_from_offset(Vector3& location, int sprite)
	{
		Blip blip = HUD::GET_CLOSEST_BLIP_INFO_ID(sprite);
		if (HUD::DOES_BLIP_EXIST(blip))
		{
			location = HUD::GET_BLIP_COORDS(blip);
			return true;
		}
		return false;
	}

	bool get_objective_location(Vector3& location)
	{
		if (get_objective_location_iteration(location, {BlipIcons::RADAR_LEVEL}, {BlipColors::YellowMission, BlipColors::YellowMission2, BlipColors::Mission}))
			return true;
		if (get_objective_location_iteration(location, {BlipIcons::RADAR_RACEFLAG}, {BlipColors::None}))
			return true;
		if (get_objective_location_iteration(location, {BlipIcons::RADAR_LEVEL}, {BlipColors::Green, BlipColors::Blue}))
			return true;

		static const auto blip_icons = {BlipIcons::RADAR_OBJECTIVE_BLUE, BlipIcons::RADAR_OBJECTIVE_GREEN, BlipIcons::RADAR_OBJECTIVE_RED, BlipIcons::RADAR_OBJECTIVE_YELLOW, BlipIcons::RADAR_CRATEDROP, BlipIcons::RADAR_TARGET_A, BlipIcons::RADAR_TARGET_B, BlipIcons::RADAR_TARGET_C, BlipIcons::RADAR_TARGET_D, BlipIcons::RADAR_TARGET_E, BlipIcons::RADAR_TARGET_F, BlipIcons::RADAR_TARGET_G, BlipIcons::RADAR_TARGET_H, BlipIcons::RADAR_SM_CARGO, BlipIcons::RADAR_BAT_CARGO, BlipIcons::RADAR_DEAD_DROP_PACKAGE};
		for (const auto icon : blip_icons)
		{
			if (get_blip_location_from_offset(location, (int)icon))
				return true;
		}

		return false;
	}

	rage::CBlip* get_selected_blip()
	{
		for (int i = 0; i < 1500; i++)
		{
			auto blip = g_pointers->m_gta.m_blip_list->m_Blips[i].m_pBlip;
			if (blip && (blip->m_display_bits & BlipIsSelected))
			{
				return blip;
			}
		}
		return nullptr;
	}

	rage::CBlip* get_blip_from_blip_id(Blip blip_id)
	{
		for (int i = 0; i < 1500; i++)
		{
			auto blip = g_pointers->m_gta.m_blip_list->m_Blips[i].m_pBlip;
			if (blip && (blip->m_blip_array_index == blip_id))
			{
				return blip;
			}
		}
		return nullptr;
	}

	bool is_ped_a_friend(Ped ped)
	{
		bool is_hated_relationship = false;
		bool is_in_combat          = PED::IS_PED_IN_COMBAT(ped, self::ped);
		auto blip_id               = HUD::GET_BLIP_FROM_ENTITY(ped);
		auto blip_color            = HUD::GET_BLIP_HUD_COLOUR(blip_id);
		auto blip                  = get_blip_from_blip_id(blip_id);
		auto blip_is_enemy = (blip && (blip->m_icon == (int)BlipIcons::RADAR_LEVEL) && (blip->m_color == (uint32_t)BlipColors::BlipColorEnemy) && !(blip->m_display_bits & BlipIsFriendly));
		bool is_enemy = ((PED::GET_PED_CONFIG_FLAG(ped, 38, TRUE) == TRUE) || blip_is_enemy);

		switch (PED::GET_RELATIONSHIP_BETWEEN_PEDS(ped, self::ped))
		{
			case Dislike:
			case Wanted:
			case Hate: is_hated_relationship = blip_color != HUD_COLOUR_BLUE;
		}

		/*if (PED::GET_PED_TYPE(ped_handle) != PED_TYPE_ANIMAL)
			LOG(INFO) << " PED_TYPE " << PED::GET_PED_TYPE(ped_handle) << " hated " << is_hated_relationship << " combat " << is_in_combat << " enemy " << is_enemy << " blip_color " << blip_color;*/

		return (!is_hated_relationship && !is_in_combat && !is_enemy);
	}
}
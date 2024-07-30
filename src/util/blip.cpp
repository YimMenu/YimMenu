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
		if (get_objective_location_iteration(location, {BlipIcons::Circle}, {BlipColors::YellowMission, BlipColors::YellowMission2, BlipColors::Mission}))
			return true;
		if (get_objective_location_iteration(location, {BlipIcons::RaceFinish}, {BlipColors::None}))
			return true;
		if (get_objective_location_iteration(location, {BlipIcons::Circle}, {BlipColors::Green, BlipColors::Blue}))
			return true;
		if (get_objective_location_iteration(location, {BlipIcons::CrateDrop}))
			return true;

		auto blip_icons = {0, 1, 2, 143, 144, 145, 146, 280, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 535, 536, 537, 538, 539, 540, 541, 542};
		for (const auto& icon : blip_icons)
		{
			if (get_blip_location_from_offset(location, icon))
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
}
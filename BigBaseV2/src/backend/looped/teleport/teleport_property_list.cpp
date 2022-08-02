#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/enums.hpp"
#include "util/math.hpp"

namespace big
{
	struct teleport_hardcoded_item {
		std::string name;
		Vector3 location;
	};

	bool teleport_check_location(Vector3 location)
	{
		for (auto& [item_name, item_location] : g->teleport.property_list)
		{
			if (item_location.x != location.x || item_location.y != location.y || item_location.z != location.z)
			{
				if (math::distance_between_vectors(item_location, location) < 0.5f)
				{
					return false;
				}
			}
		}

		return true;
	}

	void looped::teleport_property_list()
	{
		static BlipColors last_player_color = BlipColors::WHITE_0;

		if (g->teleport.updated)
		{
			return;
		}

		if (!self::ped)
		{
			g->teleport.property_list.clear();
			last_player_color = BlipColors::WHITE_0;
			return;
		}

		HUD::HIDE_MINIMAP_INTERIOR_MAP_THIS_FRAME();

		BlipColors player_color = BlipColors::WHITE_PLAYER;
		auto player_ped_type = PED::GET_PED_TYPE(self::ped);

		if (player_ped_type == ePedType::PED_TYPE_PLAYER_0)
		{
			player_color = BlipColors::MICHAEL;
		}
		else if (player_ped_type == ePedType::PED_TYPE_PLAYER_1)
		{
			player_color = BlipColors::FRANKLIN;
		}
		else if (player_ped_type == ePedType::PED_TYPE_PLAYER_2)
		{
			player_color = BlipColors::TREVOR;
		}
		else if (*g_pointers->m_is_session_started)
		{
			Blip player_blip = HUD::GET_MAIN_PLAYER_BLIP_ID();
			player_color = (BlipColors)HUD::GET_BLIP_COLOUR(player_blip);
		}

		if (last_player_color != player_color)
		{
			g->teleport.property_list.clear();
		}

		const std::map<BlipIcons, std::string> property_items = {
			{ BlipIcons::SAFEHOUSE, "Safe House" },
			{ BlipIcons::DOCK, "Dock" },
			{ BlipIcons::GARAGE, "Garage" },
			{ BlipIcons::HANGAR, "Hangar" },
			{ BlipIcons::HELIPAD, "Helipad" },
			{ BlipIcons::BUSINESS, "Business" },
			{ BlipIcons::WAREHOUSE, "Warehouse" },
			{ BlipIcons::WAREHOUSE_VEHICLE, "Vehicle Warehouse" },
		};

		const std::map<BlipIcons, std::string> singleton_items = {
			{ BlipIcons::BIKER_CLUBHOUSE, "Clubhouse" },
			{ BlipIcons::YACHT, "Yacht" },
			{ BlipIcons::OFFICE, "Office" },
			{ BlipIcons::PRODUCTION_WEED, "Weed Farm" },
			{ BlipIcons::PRODUCTION_CRACK, "Cocaine Factory" },
			{ BlipIcons::PRODUCTION_FAKE_ID, "Document Forgery Office" },
			{ BlipIcons::PRODUCTION_METH, "Meth Lab" },
			{ BlipIcons::PRODUCTION_MONEY, "Counterfeit Cash Factory" },
			{ BlipIcons::PROPERTY_BUNKER, "Bunker" },
			{ BlipIcons::SM_HANGAR, "Hangar" },
			{ BlipIcons::NHP_BASE, "Facility" },
			{ BlipIcons::BAT_CLUB_PROPERTY, "Nightclub" },
			{ BlipIcons::ARENA_WORKSHOP, "Arena Workshop" },
			{ BlipIcons::ARCADE, "Arcade" },
			{ BlipIcons::SUB2, "Kosatka" },
			{ BlipIcons::AUTO_SHOP_PROPERTY, "Auto Shop" },
			{ BlipIcons::AGENCY, "Agency" },
		};

		const std::map<BlipIcons, teleport_hardcoded_item> hardcoded_items = {
			{ BlipIcons::CASINO, { "Casino", { 924.25f, 46.75f, 79.8f } } },
			{ BlipIcons::CAR_MEET, { "LS Car Meet", { 780.44f, -1867.65f, 27.99f } } },
		};

		for (auto& [sprite, name] : property_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				auto sprite = HUD::GET_BLIP_SPRITE(blip);
				BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

				if (
					color_idx == player_color ||
					color_idx == BlipColors::WHITE_0 ||
					color_idx == BlipColors::GREEN ||
					color_idx == BlipColors::WHITE_PLAYER
				) {
					Vector3 location = HUD::GET_BLIP_COORDS(blip);

					if (teleport_check_location(location))
					{
						Hash street_hash;
						Hash street_crossing_hash;
						PATHFIND::GET_STREET_NAME_AT_COORD(location.x, location.y, location.z, &street_hash, &street_crossing_hash);

						const char* street_name = HUD::GET_STREET_NAME_FROM_HASH_KEY(street_hash);

						g->teleport.property_list[name + " (" + street_name + ")"] = location;
					}
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
			}
		}

		for (auto& [sprite, name] : singleton_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				auto sprite = HUD::GET_BLIP_SPRITE(blip);
				BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

				if (
					color_idx == player_color ||
					color_idx == BlipColors::WHITE_0 ||
					color_idx == BlipColors::GREEN ||
					color_idx == BlipColors::WHITE_PLAYER
				) {
					Vector3 location = HUD::GET_BLIP_COORDS(blip);

					if (teleport_check_location(location))
					{
						g->teleport.property_list[name] = location;
					}
				}

				blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
			}
		}

		for (auto& [sprite, item] : hardcoded_items)
		{
			Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

			while (HUD::DOES_BLIP_EXIST(blip))
			{
				g->teleport.property_list[item.name] = item.location;
				break;
			}
		}

		last_player_color = player_color;
		g->teleport.updated = true;
	}
}
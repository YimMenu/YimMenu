#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "gta/enums.hpp"
#include "util/math.hpp"
#include "gta/joaat.hpp"

namespace big
{
	struct world_hardcoded_item {
		std::string name;
		Vector3 location;
	};

	bool world_check_location(Vector3 location)
	{
		for (auto& [item_name, item_location] : g->world.property_list)
		{
			if (
				abs(item_location.x - location.x) < 1.f && 
				abs(item_location.y - location.y) < 1.f && 
				abs(item_location.z - location.z) < 2.f
			) {
				return false;
			}
		}

		return true;
	}

	void looped::world_object_loop()
	{
		static BlipColors last_player_color = BlipColors::WAYPOINT;
		auto replay = *g_pointers->m_replay_interface;

		if (!self::ped || !replay)
		{
			LOG(WARNING) << "P: CLEAR 1";
			last_player_color = BlipColors::WAYPOINT;

			g->world.property_list.clear();
			g->world.property_list_updated = false;

			g->world.mission_veh_list.clear();
			g->world.mission_veh_list_updated = false;

			g->world.mission_ped_list.clear();
			g->world.mission_ped_list_updated = false;

			g->world.pickup_list.clear();
			g->world.pickup_list_updated = false;

			return;
		}

		BlipColors player_color = BlipColors::WAYPOINT;
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
			LOG(WARNING) << "P: CLEAR 2";
			g->world.property_list.clear();
			last_player_color = player_color;
		}

		if (!g->world.property_list_updated)
		{
			LOG(WARNING) << "C: " << (int)player_color;

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

			const std::map<BlipIcons, world_hardcoded_item> hardcoded_items = {
				{ BlipIcons::CASINO, { "Casino", { 924.25f, 46.75f, 79.8f } } },
				{ BlipIcons::CAR_MEET, { "LS Car Meet", { 780.44f, -1867.65f, 27.99f } } },
			};

			for (auto& [sprite, name] : property_items)
			{
				Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

				while (HUD::DOES_BLIP_EXIST(blip))
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (
						color_idx == player_color ||
						color_idx == BlipColors::WHITE_0 ||
						color_idx == BlipColors::GREEN ||
						color_idx == BlipColors::WHITE_PLAYER
					) {
						Vector3 location = HUD::GET_BLIP_COORDS(blip);

						if (world_check_location(location))
						{
							Hash street_hash;
							Hash street_crossing_hash;
							PATHFIND::GET_STREET_NAME_AT_COORD(location.x, location.y, location.z, &street_hash, &street_crossing_hash);

							const char* street_name = HUD::GET_STREET_NAME_FROM_HASH_KEY(street_hash);

							g->world.property_list[name + " (" + street_name + ")"] = location;
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
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (
						color_idx == player_color ||
						color_idx == BlipColors::WHITE_0 ||
						color_idx == BlipColors::GREEN ||
						color_idx == BlipColors::WHITE_PLAYER
					) {
						Vector3 location = HUD::GET_BLIP_COORDS(blip);

						if (world_check_location(location))
						{
							g->world.property_list[name] = location;
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
					g->world.property_list[item.name] = item.location;
					break;
				}
			}

			g->world.property_list_updated = true;
		}

		if (!g->world.mission_veh_list_updated)
		{
			g->world.mission_veh_list.clear();

			if (const auto veh_interface = replay->m_vehicle_interface; veh_interface)
			{
				const auto veh_interface_size = veh_interface->m_cur_vehicles;

				for (int32_t i = 0; i < veh_interface_size; i++)
				{
					auto veh_ptr = veh_interface->get_vehicle(i);

					if (!veh_ptr || !(veh_ptr->m_mission_bits & 0b0100) || !veh_ptr->m_navigation || !veh_ptr->m_model_info)
					{
						continue;
					}

					Vehicle veh = g_pointers->m_ptr_to_handle(veh_ptr);
					g->world.mission_veh_list[veh] = veh_ptr->m_model_info->m_model_hash;
				}
			}

			g->world.mission_veh_list_updated = true;
		}

		if (!g->world.mission_ped_list_updated)
		{
			g->world.mission_ped_list.clear();

			const std::vector<BlipIcons> ped_sprites = {
				BlipIcons::LEVEL,
				BlipIcons::AI
			};

			for (auto& sprite : ped_sprites)
			{
				Blip blip = HUD::GET_FIRST_BLIP_INFO_ID((int)sprite);

				while (HUD::DOES_BLIP_EXIST(blip))
				{
					BlipColors color_idx = (BlipColors)HUD::GET_BLIP_COLOUR(blip);

					if (
						color_idx == BlipColors::RED
					) {
						if (const auto ent = HUD::GET_BLIP_INFO_ID_ENTITY_INDEX(blip); ent)
						{
							eEntityType ent_type = (eEntityType)ENTITY::GET_ENTITY_TYPE(ent);

							if (ent_type == eEntityType::PED)
							{
								g->world.mission_ped_list[ent] = ENTITY::GET_ENTITY_MODEL(ent);
							}
							else if (ent_type == eEntityType::VEHICLE)
							{
								int num_of_seats = VEHICLE::GET_VEHICLE_MAX_NUMBER_OF_PASSENGERS(ent);

								for (int i = -1; i < num_of_seats; i++)
								{
									auto ped_in_seat = VEHICLE::GET_PED_IN_VEHICLE_SEAT(ent, num_of_seats, false);
									if (ped_in_seat)
									{
										g->world.mission_ped_list[ped_in_seat] = ENTITY::GET_ENTITY_MODEL(ped_in_seat);
									}
								}
							}
						}
					}

					blip = HUD::GET_NEXT_BLIP_INFO_ID((int)sprite);
				}
			}

			if (const auto ped_interface = replay->m_ped_interface; ped_interface)
			{
				const auto ped_interface_size = ped_interface->m_cur_peds;

				for (int32_t i = 0; i < ped_interface_size; i++)
				{
					auto ped_ptr = ped_interface->get_ped(i);

					if (!ped_ptr || !ped_ptr->m_navigation || !ped_ptr->m_model_info)
					{
						continue;
					}

					Ped ped = g_pointers->m_ptr_to_handle(ped_ptr);
					Hash model = ped_ptr->m_model_info->m_model_hash;

					bool skip = false;

					if (
						model == RAGE_JOAAT("Player_Zero") ||
						model == RAGE_JOAAT("Player_One") ||
						model == RAGE_JOAAT("Player_Two") ||
						model == RAGE_JOAAT("MP_M_Freemode_01") ||
						model == RAGE_JOAAT("MP_F_Freemode_01") ||
						model == RAGE_JOAAT("S_M_M_AmmyCountry") ||
						model == RAGE_JOAAT("U_M_Y_Tattoo_01") ||
						model == RAGE_JOAAT("S_M_M_HairDress_01") ||
						model == RAGE_JOAAT("S_F_M_Fembarber_01") ||
						model == RAGE_JOAAT("MP_M_ShopKeep_01") ||
						model == RAGE_JOAAT("S_F_M_Shop_HIGH") ||
						model == RAGE_JOAAT("S_F_Y_Shop_MID") ||
						model == RAGE_JOAAT("S_F_Y_Shop_LOW") ||
						model == RAGE_JOAAT("S_M_M_AutoShop_01")
					) {
						skip = true;
					}

					if (PED::IS_PED_IN_COMBAT(ped, self::ped) || (!skip && (ped_ptr->m_mission_bits & 0b0100)))
					{
						g->world.mission_ped_list[ped] = ped_ptr->m_model_info->m_model_hash;
					}
				}
			}

			g->world.mission_ped_list_updated = true;
		}


		if (!g->world.pickup_list_updated)
		{
			g->world.pickup_list.clear();

			if (const auto pickup_interface = replay->m_pickup_interface; pickup_interface)
			{
				const auto pickup_interface_size = pickup_interface->m_cur_pickups;

				for (int32_t i = 0; i < pickup_interface_size; i++)
				{
					auto pickup_ptr = pickup_interface->get_pickup(i);

					if (!pickup_ptr || !(pickup_ptr->m_mission_bits & 0b0100) || !pickup_ptr->m_navigation || !pickup_ptr->m_model_info)
					{
						continue;
					}

					Object pickup = g_pointers->m_ptr_to_handle(pickup_ptr);
					g->world.pickup_list[pickup] = pickup_ptr->m_model_info->m_model_hash;
				}
			}

			g->world.pickup_list_updated = true;
		}

	}
}

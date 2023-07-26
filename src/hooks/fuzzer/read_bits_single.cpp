#include "hooking.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/model_info.hpp"
#include "util/pools.hpp"

#include <entities/CDynamicEntity.hpp>

namespace big
{
	bool is_model_hash(rage::joaat_t hash)
	{
		return model_info::does_model_exist(hash);
	}

	bool is_object_model(rage::joaat_t hash)
	{
		return model_info::is_model_of_type(hash, eModelType::Object, eModelType::Time, eModelType::Weapon, eModelType::Destructable, eModelType::WorldObject, eModelType::Sprinkler, eModelType::Unk65, eModelType::LOD, eModelType::Unk132, eModelType::Building);
	}

	rage::joaat_t get_mismatched_model(rage::joaat_t original)
	{
		// TODO: trailer models?
		std::vector<rage::joaat_t> models = {
		    RAGE_JOAAT("player_zero"),           // ped
		    RAGE_JOAAT("kosatka"),               // submarine
		    RAGE_JOAAT("akula"),                 // heli
		    RAGE_JOAAT("alkonost"),              // plane
		    RAGE_JOAAT("jetmax"),                // boat
		    RAGE_JOAAT("faggio"),                // bike
		    RAGE_JOAAT("zentorno"),              // automobile
		    RAGE_JOAAT("apa_heist_apart2_door"), // object, pickup, pickup placement, door (?)
		    RAGE_JOAAT("freight"),               // train
		};

		auto info      = model_info::get_model(original);
		auto veh_model = model_info::get_vehicle_model(original);

		if (is_object_model(original))
			std::erase(models, RAGE_JOAAT("apa_heist_apart2_door"));
		else if (info && info->m_model_type == eModelType::Vehicle)
		{
			if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_BIKE)
				std::erase(models, RAGE_JOAAT("faggio"));
			else if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_SUBMARINE)
				std::erase(models, RAGE_JOAAT("kosatka"));
			else if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_BOAT)
				std::erase(models, RAGE_JOAAT("jetmax"));
			else if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_HELI)
				std::erase(models, RAGE_JOAAT("akula"));
			else if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_PLANE)
				std::erase(models, RAGE_JOAAT("alkonost"));
			else if (veh_model->m_vehicle_type == eVehicleType::VEHICLE_TYPE_TRAIN)
				std::erase(models, RAGE_JOAAT("freight"));
			else
				std::erase(models, RAGE_JOAAT("zentorno"));
		}
		else if (info && (info->m_model_type == eModelType::Ped || info->m_model_type == eModelType::OnlineOnlyPed))
			std::erase(models, RAGE_JOAAT("player_zero"));

		return models[rand() % models.size()];
	}

	rage::joaat_t get_crash_model(rage::joaat_t original)
	{
		auto info = model_info::get_model(original);

		if (is_object_model(original))
			return RAGE_JOAAT("urbanweeds01");
		else if (info && (info->m_model_type == eModelType::Ped || info->m_model_type == eModelType::OnlineOnlyPed))
			return RAGE_JOAAT("slod_human");
		else if (info && info->m_model_type == eModelType::Vehicle)
			return RAGE_JOAAT("arbitergt");
		else
			return (rand() % 2) ? RAGE_JOAAT("urbanweeds01") : RAGE_JOAAT("slod_human");
	}

	std::int16_t get_first_ped_id()
	{
		for (auto ped : pools::get_all_peds())
			if (auto net = static_cast<rage::CDynamicEntity*>(ped)->m_net_object; net && ped != g_local_player && (net->m_owner_id == -1 || net->m_owner_id == self::id))
				return net->m_object_id;

		LOG(INFO) << "nope";
		return -1;
	}

	std::int16_t get_first_veh_id()
	{
		for (auto veh : pools::get_all_vehicles())
			if (auto net = static_cast<rage::CDynamicEntity*>(veh)->m_net_object; net && (net->m_owner_id == -1 || net->m_owner_id == self::id))
				return net->m_object_id;

		return -1;
	}

	std::int16_t get_first_obj_id()
	{
		for (auto obj : pools::get_all_props())
			if (auto net = static_cast<rage::CDynamicEntity*>(obj)->m_net_object; net && (net->m_owner_id == -1 || net->m_owner_id == self::id))
				return net->m_object_id;

		return -1;
	}

	std::int16_t get_mismatched_net_id(std::int16_t original)
	{
		auto net_obj = g_pointers->m_gta.m_get_net_object(*g_pointers->m_gta.m_network_object_mgr, original, false);

		if (!net_obj)
			return -1;

		auto entity = reinterpret_cast<rage::CDynamicEntity*>(net_obj->GetGameObject());

		if (!entity)
			return -1;

		if (is_object_model(entity->m_model_info->m_hash))
			return (rand() % 2) ? get_first_ped_id() : get_first_veh_id();
		else if (entity->m_model_info->m_model_type == eModelType::Ped || entity->m_model_info->m_model_type == eModelType::OnlineOnlyPed)
			return (rand() % 2) ? get_first_obj_id() : get_first_veh_id();
		else if (entity->m_model_info->m_model_type == eModelType::Vehicle)
			return (rand() % 2) ? get_first_obj_id() : get_first_ped_id();

		return (rand() % 2) ? get_first_ped_id() : get_first_veh_id();
	}

	bool hooks::read_bits_single(void* data, int* out_value, int size, int offset)
	{
		auto orig = g_hooking->get_original<hooks::read_bits_single>()(data, out_value, size, offset);

		if (g.debug.fuzzer.enabled && g.debug.fuzzer.active && out_value && g.debug.fuzzer.thread_id == GetCurrentThreadId())
		{
			if (size == 13)
			{
				int option = rand() % 4;

				switch (option)
				{
				case 0: break; // do nothing
				case 1:        // mismatched IDs
				{
					auto _new = get_mismatched_net_id(*out_value);
					if (_new != -1)
						*out_value = _new;

					break;
				}
				case 2: // set to player
				{
					if (auto net_obj = g_local_player->m_net_object)
						*out_value = net_obj->m_object_id;
				}
				case 3: // set to itself
				{
					*out_value = g.debug.fuzzer.syncing_object_id;
				}
				}
			}
			else if (size == 32)
			{
				if (*out_value == 0 || is_model_hash(*out_value))
				{
					int option = rand() % 5;

					switch (option)
					{
					case 0:
					case 1:
					case 2: break;                                                // do nothing
					case 3: *out_value = get_mismatched_model(*out_value); break; // mismatched model
					case 4: *out_value = get_crash_model(*out_value); break;      // crash model
					}
				}
				else
				{
					if (rand() % 4)
						*out_value = rand(); // not much we can do here
				}
			}
			else
			{
				if (rand() % (5 - (size == 1)) == 0)
				{
					if (size == 1)
					{
						if (rand() % 4 == 0)
							*out_value = !*out_value; // flip bools
						else
							*out_value = true; // set to true
					}
					else
					{
						if (rand() % 2 == 0)
							*out_value = rand() % ((int)pow(2, size)); // random
						else
							*out_value = ((int)pow(2, size)) - 1; // max possible value
					}
				}
			}

			return true;
		}

		return orig;
	}
}
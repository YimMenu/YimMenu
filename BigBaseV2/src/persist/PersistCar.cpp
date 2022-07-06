#include "common.hpp"
#include "PersistCar.h"
#include "script.hpp"
#include "imgui.h"
#include "gui.hpp"
#include "fiber_pool.hpp"
#include "pointers.hpp"
#include "services/vehicle_helper/vehicle_helper.hpp"
#include <gta/VehicleValues.h>



namespace big
{
	void persist_car::save_vehicle(Vehicle vehicle, std::string file_name)
	{
		if (ENTITY::DOES_ENTITY_EXIST(vehicle) == FALSE || ENTITY::IS_ENTITY_A_VEHICLE(vehicle) == FALSE)
		{
			LOG(WARNING) << "Persist Car was passed an incorrect entity";
			return;
		}

		auto file_path = check_vehicle_folder();
		file_path /= file_name;
		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		file << get_full_vehicle_json(vehicle).dump(4);
		file.close();
	}

	Vehicle persist_car::load_vehicle(std::string file_name)
	{
		auto file_path = check_vehicle_folder();
		file_path /= file_name;
		std::ifstream file(file_path);

		nlohmann::json vehicle_json;
		file >> vehicle_json;
		file.close();

		return spawn_vehicle_full(vehicle_json, PLAYER::PLAYER_PED_ID());
	}

	std::vector<std::string> persist_car::list_files()
	{
		auto file_path = check_vehicle_folder();
		std::vector<std::string> return_value;
		for (const auto& p : std::filesystem::directory_iterator(file_path))
			if (p.path().extension() == ".json")
				return_value.push_back(p.path().filename().generic_string());
		return return_value;
	}

	Vehicle persist_car::clone_ped_car(Ped ped, Vehicle vehicle)
	{
		return spawn_vehicle_full(get_full_vehicle_json(vehicle), ped);
	}

	void persist_car::do_presentation_layer()
	{
		auto vehicle_files = persist_car::list_files();
		static std::string selected_vehicle_file;
		ImGui::PushItemWidth(250);
		ImGui::Text("Saved Vehicles");
		if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
		{
			for (auto pair : vehicle_files)
			{
				if (ImGui::Selectable(pair.c_str(), selected_vehicle_file == pair))
					selected_vehicle_file = pair;
			}
			ImGui::ListBoxFooter();
		}
		ImGui::SameLine();
		ImGui::BeginGroup();
		static char vehicle_file_name_input[50]{};
		ImGui::PushItemWidth(250);
		ImGui::InputText("Vehicle File Name", vehicle_file_name_input, IM_ARRAYSIZE(vehicle_file_name_input));
		if (ImGui::Button("Save Vehicle"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				do_save_vehicle(vehicle_file_name_input);
			} QUEUE_JOB_END_CLAUSE
		}
		if (ImGui::Button("Load Vehicle"))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				do_load_vehicle(selected_vehicle_file);
			} QUEUE_JOB_END_CLAUSE
		}
		ImGui::EndGroup();
	}

	Vehicle persist_car::spawn_vehicle_full(nlohmann::json vehicle_json, Ped ped)
	{
		Vehicle vehicle = spawn_vehicle(vehicle_json, ped);
		if (!vehicle_json["Tow"].is_null())
		{
			Vehicle tow = spawn_vehicle(vehicle_json["Tow"], ped);
			auto pos = ENTITY::GET_ENTITY_COORDS(tow, true);
			pos.x -= 10;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(tow, pos.x, pos.y, 0.f, TRUE, TRUE, FALSE);
			VEHICLE::ATTACH_VEHICLE_TO_TOW_TRUCK(vehicle, tow, -1, 0.f, 0.5f, 0.f);
			VEHICLE::SET_VEHICLE_TOW_TRUCK_ARM_POSITION(vehicle, 1.f);
			Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(tow, 2);
			ENTITY::SET_ENTITY_ROTATION(tow, 0, 0, rotation.z, 2, TRUE);
		}
		else if (!vehicle_json["Trailer"].is_null())
		{
			Vehicle trailer = spawn_vehicle(vehicle_json["Trailer"], ped);
			VEHICLE::ATTACH_VEHICLE_TO_TRAILER(vehicle, trailer, 1.0f);
			Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(trailer, 2);
			ENTITY::SET_ENTITY_ROTATION(trailer, 0, 0, rotation.z, 2, TRUE);
		}
		Vector3 rotation = ENTITY::GET_ENTITY_ROTATION(vehicle, 2);
		ENTITY::SET_ENTITY_ROTATION(vehicle, rotation.x, 0, rotation.z, 2, TRUE);
		return vehicle;
	}

	Vehicle persist_car::spawn_vehicle(nlohmann::json vehicle_json, Ped ped)
	{
		Vehicle vehicle = spawn_vehicle_json(vehicle_json, ped);
		std::vector<nlohmann::json> model_attachments = vehicle_json["Model Attachments"];
		for (nlohmann::json model_attachment : model_attachments)
		{
			auto attachment = model_attachment.get<model_attachment::model_attachment>();
			STREAMING::REQUEST_MODEL(attachment.model_hash);
			Object object = OBJECT::CREATE_OBJECT(attachment.model_hash, 0, 0, 0, TRUE, FALSE, FALSE);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(object, vehicle, 0, attachment.position.x, attachment.position.y, attachment.position.z, attachment.rotation.x, attachment.rotation.y, attachment.rotation.z, false, false, true, false, 0, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(attachment.model_hash);
		}
		std::vector<nlohmann::json> vehicle_attachments = vehicle_json["Vehicle Attachments"];
		for (nlohmann::json vehicle_attachment : vehicle_attachments)
		{
			Vehicle vehicle_to_attach = spawn_vehicle_json(vehicle_attachment["Vehicle"], ped);
			auto attachment = vehicle_attachment["Model Attachment"].get<model_attachment::model_attachment>();
			ENTITY::ATTACH_ENTITY_TO_ENTITY(vehicle_to_attach, vehicle, 0, attachment.position.x, attachment.position.y, attachment.position.z, attachment.rotation.x, attachment.rotation.y, attachment.rotation.z, false, false, true, false, 0, true);
			VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(vehicle_to_attach, false);
		}
		return vehicle;
	}

	Vehicle persist_car::spawn_vehicle_json(nlohmann::json vehicle_json, Ped ped)
	{
		Hash vehicle_hash = vehicle_json["Vehicle Model Hash"];

		auto pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		Vehicle vehicle = vehicle_helper::create_vehicle(vehicle_hash, pos.x, pos.y, pos.z, ENTITY::GET_ENTITY_HEADING(ped));
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
		VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, FALSE);
		VEHICLE::SET_VEHICLE_COLOURS(vehicle, vehicle_json["Primary Color"], vehicle_json["Secondary Color"]);
		if (!vehicle_json["Custom Primary Color"].is_null())
		{
			std::vector<int> primary_custom_color = vehicle_json["Custom Primary Color"];
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, primary_custom_color[0], primary_custom_color[1], primary_custom_color[2]);
		}
		if (!vehicle_json["Custom Secondary Color"].is_null())
		{
			std::vector<int> secondary_custom_color = vehicle_json["Custom Secondary Color"];
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, secondary_custom_color[0], secondary_custom_color[1], secondary_custom_color[2]);
		}
		VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, vehicle_json["Vehicle Window Tint"]);
		if (!vehicle_json["Radio Station"].is_null())
			AUDIO::SET_VEH_RADIO_STATION(vehicle, vehicle_json["Radio Station"].get<std::string>().c_str());
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, vehicle_json["Plate Text"].get<std::string>().c_str());
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle, vehicle_json["Plate Text Index"]);
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, vehicle_json["Pearlescent Color"], vehicle_json["Wheel Color"]);
		std::map<int, bool> vehicle_extras = vehicle_json["Vehicle Extras"];
		for (int i = 0; i <= 20; i++)
		{
			if (VEHICLE::DOES_EXTRA_EXIST(vehicle, i))
				VEHICLE::SET_VEHICLE_EXTRA(vehicle, i, vehicle_extras[i]);
		}
		if (!vehicle_json["Vehicle Livery"].is_null())
		{
			VEHICLE::SET_VEHICLE_LIVERY(vehicle, vehicle_json["Vehicle Livery"]);
		}
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(vehicle)) == TRUE || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(vehicle)))
		{
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, vehicle_json["Wheel Type"]);
			for (int i = MOD_SPOILERS; i <= MOD_LIVERY; i++)
			{
				BOOL bModOn = !vehicle_json[mod_names[i]].is_null();
				if (bModOn == TRUE)
				{
					if (i == MOD_TIRESMOKE)
					{
						std::vector<int> tire_smoke_color = vehicle_json["Tire Smoke Color"];
						VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, tire_smoke_color[0], tire_smoke_color[1], tire_smoke_color[2]);
						VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TIRESMOKE, TRUE);
					}
					else if (vehicle_json[mod_names[i]].is_array())
					{
						std::vector<int> mod = vehicle_json[mod_names[i]];
						VEHICLE::SET_VEHICLE_MOD(vehicle, i, mod[0], mod[1]);
					}
					else
					{
						VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, i, TRUE);
					}
				}
			}
			std::vector<bool> neon_lights = vehicle_json["Neon Lights"];
			for (int i = NEON_LEFT; i <= NEON_BACK; i++)
				VEHICLE::SET_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, i, neon_lights[i]);
			std::vector<int> neon_color = vehicle_json["Neon Color"];
			VEHICLE::SET_VEHICLE_NEON_LIGHTS_COLOUR_(vehicle, neon_color[0], neon_color[1], neon_color[2]);
			if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(vehicle, 0))
			{
				int convertableState = vehicle_json["Convertable State"];
				if (convertableState == 0 || convertableState == 3 || convertableState == 5)
					VEHICLE::RAISE_CONVERTIBLE_ROOF(vehicle, TRUE);
				else
					VEHICLE::LOWER_CONVERTIBLE_ROOF(vehicle, TRUE);
			}
			VEHICLE::SET_VEHICLE_INTERIOR_COLOR_(vehicle, vehicle_json["Interior Color"]);
			VEHICLE::SET_VEHICLE_DASHBOARD_COLOR_(vehicle, vehicle_json["Dash Color"]);
			if (vehicle_json["Clan Logo"] == TRUE)
				vehicle_helper::add_clan_logo_to_vehicle(vehicle, ped);
			VEHICLE::SET_VEHICLE_XENON_LIGHTS_COLOR_(vehicle, vehicle_json["Headlight Color"]);
		}
		return vehicle;
	}

	nlohmann::json persist_car::get_full_vehicle_json(Vehicle vehicle)
	{
		//The car needs to be rotated at 0,0,0 for the releative offset calculations to be accurate.
		ENTITY::SET_ENTITY_ROTATION(vehicle, 0, 0, 0, 0, TRUE);
		script::get_current()->yield();
		ENTITY::SET_ENTITY_ROTATION(vehicle, 0, 0, 0, 0, TRUE);
		nlohmann::json vehicle_json = get_vehicle_json(vehicle);
		vehicle_json["Model Attachments"] = get_model_attachments(vehicle);
		vehicle_json["Vehicle Attachments"] = get_vehicle_attachents(vehicle);
		Vehicle tow = VEHICLE::GET_ENTITY_ATTACHED_TO_TOW_TRUCK(vehicle);
		if (ENTITY::DOES_ENTITY_EXIST(tow))
		{
			vehicle_json["Tow"] = get_vehicle_json(tow);
			vehicle_json["Tow"]["Model Attachments"] = get_model_attachments(tow, true);
			vehicle_json["Tow"]["Vehicle Attachments"] = get_vehicle_attachents(tow);
		}
		if (VEHICLE::IS_VEHICLE_ATTACHED_TO_TRAILER(vehicle))
		{
			Vehicle trailer;
			VEHICLE::GET_VEHICLE_TRAILER_VEHICLE(vehicle, &trailer);
			vehicle_json["Trailer"] = get_vehicle_json(trailer);
			vehicle_json["Trailer"]["Model Attachments"] = get_model_attachments(trailer);
			vehicle_json["Trailer"]["Vehicle Attachments"] = get_vehicle_attachents(trailer);
		}
		return vehicle_json;
	}

	model_attachment::model_attachment persist_car::get_model_attachment(Vehicle vehicle, Object object)
	{
		Vector3 object_location = ENTITY::GET_ENTITY_COORDS(object, 0);
		Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_GIVEN_WORLD_COORDS(vehicle, object_location.x, object_location.y, object_location.z);
		Vector3 object_rotation = ENTITY::GET_ENTITY_ROTATION(object, 0);
		Vector3 vehicle_rotation = ENTITY::GET_ENTITY_ROTATION(vehicle, 0);
		Vector3 rotation;
		rotation.x = (object_rotation.x - vehicle_rotation.x);
		rotation.y = (object_rotation.y - vehicle_rotation.y);
		rotation.z = (object_rotation.z - vehicle_rotation.z);
		model_attachment::model_attachment attachment = { ENTITY::GET_ENTITY_MODEL(object), location, rotation };
		return attachment;
	}

	nlohmann::json persist_car::get_model_attachments(Vehicle vehicle, bool is_towed_vehicle)
	{
		std::vector<nlohmann::json> attached_objects;
		rage::CReplayInterface* replay_interface = *g_pointers->m_replay_interface;
		rage::CObjectInterface* object_interface = replay_interface->m_object_interface;
		int numObj = object_interface->m_max_objects;
		for (int i = 0; i < numObj; i++)
		{
			rage::fwEntity* pCObject = object_interface->get_object(i);
			if (pCObject == nullptr)
				continue;

			Object object = g_pointers->m_ptr_to_handle(pCObject);
			if (object == 0)
				break;

			if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(vehicle, object))
				continue;

			if (is_towed_vehicle && ENTITY::GET_ENTITY_MODEL(object) == 0xBC344305) //Don't save tow hook.
				continue;

			attached_objects.push_back(get_model_attachment(vehicle, object));
		};
		return attached_objects;
	}

	nlohmann::json persist_car::get_vehicle_attachents(Vehicle vehicle)
	{
		Vehicle trailer;
		VEHICLE::GET_VEHICLE_TRAILER_VEHICLE(vehicle, &trailer);
		std::vector<nlohmann::json> attached_vehicles;
		rage::CReplayInterface* replay_interface = *g_pointers->m_replay_interface;
		rage::CVehicleInterface* vehicle_interface = replay_interface->m_vehicle_interface;
		for (int i = 0; i < vehicle_interface->m_max_vehicles; i++)
		{
			auto* vehicle_ptr = vehicle_interface->get_vehicle(i);
			if (vehicle_ptr == nullptr)
				continue;

			Vehicle object = g_pointers->m_ptr_to_handle(vehicle_ptr);
			if (object == 0)
				break;

			if (!ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(vehicle, object))
				continue;

			if (object == VEHICLE::GET_ENTITY_ATTACHED_TO_TOW_TRUCK(vehicle) || VEHICLE::IS_VEHICLE_ATTACHED_TO_TOW_TRUCK(object, vehicle))
				continue;

			if (object == trailer || VEHICLE::IS_VEHICLE_ATTACHED_TO_TRAILER(object))
				continue;

			nlohmann::json model_attachment;
			model_attachment["Vehicle"] = get_vehicle_json(object);
			model_attachment["Model Attachment"] = get_model_attachment(vehicle, object);
			attached_vehicles.push_back(model_attachment);
		}
		return attached_vehicles;
	}

	nlohmann::json persist_car::get_vehicle_json(Vehicle vehicle)
	{
		nlohmann::json vehicle_json;

		vehicle_json["Vehicle Model Hash"] = ENTITY::GET_ENTITY_MODEL(vehicle);
		int primary_color, secondary_color;
		VEHICLE::GET_VEHICLE_COLOURS(vehicle, &primary_color, &secondary_color);
		vehicle_json["Primary Color"] = primary_color;
		vehicle_json["Secondary Color"] = secondary_color;
		if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle))
		{
			int custom_primary_color[3]{};
			VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, &custom_primary_color[0], &custom_primary_color[1], &custom_primary_color[2]);
			vehicle_json["Custom Primary Color"] = custom_primary_color;
		}
		if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(vehicle))
		{
			int custom_secondary_color[3]{};
			VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, &custom_secondary_color[0], &custom_secondary_color[1], &custom_secondary_color[2]);
			vehicle_json["Custom Secondary Color"] = custom_secondary_color;
		}
		vehicle_json["Vehicle Window Tint"] = VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle);
		auto radio_station = AUDIO::GET_PLAYER_RADIO_STATION_NAME();
		if (radio_station == nullptr)
			radio_station = "OFF";
		vehicle_json["Radio Station"] = radio_station;
		vehicle_json["Plate Text"] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(vehicle);
		vehicle_json["Plate Text Index"] = VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle);
		int pearlescent_color, wheel_color;
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &pearlescent_color, &wheel_color);
		vehicle_json["Pearlescent Color"] = pearlescent_color;
		vehicle_json["Wheel Color"] = wheel_color;
		std::map<int, bool> vehicle_extras;
		for (int i = 0; i <= 20; i++)
		{
			if (VEHICLE::DOES_EXTRA_EXIST(vehicle, i))
				vehicle_extras[i] = !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, i);
		}
		vehicle_json["Vehicle Extras"] = vehicle_extras;
		if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(vehicle) > 1) && VEHICLE::GET_VEHICLE_LIVERY(vehicle) >= 0)
		{
			vehicle_json["Vehicle Livery"] = VEHICLE::GET_VEHICLE_LIVERY(vehicle);
		}
		if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(vehicle)) == TRUE || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(vehicle)))
		{
			vehicle_json["Wheel Type"] = VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle);
			for (int i = MOD_SPOILERS; i <= MOD_LIVERY; i++)
			{
				BOOL is_mod_on = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, i);
				if (i == MOD_TIRESMOKE && is_mod_on == TRUE)
				{
					int tire_smoke_color[3]{};
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &tire_smoke_color[0], &tire_smoke_color[1], &tire_smoke_color[2]);
					vehicle_json["Tire Smoke Color"] = tire_smoke_color;
				}
				else if (is_mod_on == TRUE)
				{
					vehicle_json[mod_names[i]] = "TOGGLE";
				}
				if (VEHICLE::GET_VEHICLE_MOD(vehicle, i) != -1)
				{
					int vehicle_mod[2] = { VEHICLE::GET_VEHICLE_MOD(vehicle, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, i) };
					vehicle_json[mod_names[i]] = vehicle_mod;
				}
			}
			bool neon_lights[4]{};
			for (int i = NEON_LEFT; i <= NEON_BACK; i++)
				neon_lights[i] = VEHICLE::IS_VEHICLE_NEON_LIGHT_ENABLED_(vehicle, i);
			int neon_color[3]{};
			VEHICLE::GET_VEHICLE_NEON_LIGHTS_COLOUR_(vehicle, &neon_color[0], &neon_color[1], &neon_color[2]);
			vehicle_json["Neon Color"] = neon_color;
			vehicle_json["Neon Lights"] = neon_lights;
			if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(vehicle, 0))
				vehicle_json["Convertable State"] = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(vehicle);
			int interior_color, dashboard_color;
			VEHICLE::GET_VEHICLE_INTERIOR_COLOR_(vehicle, &interior_color);
			VEHICLE::GET_VEHICLE_DASHBOARD_COLOR_(vehicle, &dashboard_color);
			vehicle_json["Interior Color"] = interior_color;
			vehicle_json["Dash Color"] = dashboard_color;
			vehicle_json["Clan Logo"] = GRAPHICS::DOES_VEHICLE_HAVE_CREW_EMBLEM(vehicle, 0);
			vehicle_json["Headlight Color"] = VEHICLE::GET_VEHICLE_XENON_LIGHTS_COLOR_(vehicle);
		}
		return vehicle_json;
	}

	std::filesystem::path persist_car::check_vehicle_folder()
	{
		auto file_path = std::filesystem::path(std::getenv("appdata"));
		file_path /= "BigBaseV2";
		file_path /= "Vehicles";

		if (!std::filesystem::exists(file_path))
		{
			std::filesystem::create_directory(file_path);
		}
		else if (!std::filesystem::is_directory(file_path))
		{
			std::filesystem::remove(file_path);
			std::filesystem::create_directory(file_path);
		}

		return file_path;
	}

	void persist_car::do_save_vehicle(char* vehicle_file_name_input)
	{
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
		if (ENTITY::DOES_ENTITY_EXIST(vehicle))
		{
			std::string vehicle_file_name = vehicle_file_name_input;
			vehicle_file_name.append(".json");
			persist_car::save_vehicle(vehicle, vehicle_file_name);
			ZeroMemory(vehicle_file_name_input, sizeof(vehicle_file_name_input));
		}
	}

	void persist_car::do_load_vehicle(std::string& selected_vehicle_file)
	{
		if (!selected_vehicle_file.empty())
		{
			Vehicle vehicle = persist_car::load_vehicle(selected_vehicle_file);
			selected_vehicle_file.clear();
		}
	}
}
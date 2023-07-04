#include "xml_vehicles_service.hpp"

#include "file_manager.hpp"

namespace big
{

	xml_vehicles_service::xml_vehicles_service()
	{
		g_xml_vehicles_service = this;
	}

	void xml_vehicles_service::fetch_xml_files()
	{
		auto folder_path = g_file_manager->get_project_folder("xml_vehicles").get_path();

		try
		{
			for (const auto& entry : std::filesystem::directory_iterator(folder_path))
			{
				if (entry.path().extension() == ".xml")
				{
					pugi::xml_document doc;
					pugi::xml_parse_result result = doc.load_file(entry.path().c_str());

					if (result)
						m_all_xml_vehicles.emplace(std::pair<std::string, pugi::xml_document>(entry.path().filename().generic_string(), std::move(doc)));
					else
						LOG(WARNING) << "Failed to load XML file: " << entry.path().filename().string() << std::endl;
				}
			}
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching xml vehicles: " << e.what() << std::endl;
		}
	}

	Vehicle xml_vehicles_service::spawn_from_xml(pugi::xml_document& doc, Vector3 pos)
	{
		auto vehicle_node              = doc.child("Vehicle");
		auto vehicle_properties_node   = vehicle_node.child("VehicleProperties");
		auto vehicle_colors_node       = vehicle_properties_node.child("Colours");
		auto vehicle_attachments_node = vehicle_node.child("SpoonerAttachments");

		auto vehicle_handle = vehicle::spawn(vehicle_node.child("ModelHash").text().as_uint(),
		    pos,
		    ENTITY::GET_ENTITY_HEADING(self::ped),
		    *g_pointers->m_gta.m_is_session_started,
		    false);

		//Appearance
		VEHICLE::SET_VEHICLE_LIVERY(vehicle_handle, vehicle_properties_node.child("Livery").text().as_int());
		VEHICLE::SET_VEHICLE_MOD_COLOR_1(vehicle_handle,
		    vehicle_colors_node.child("Mod1_a").text().as_int(),
		    vehicle_colors_node.child("Mod1_b").text().as_int(),
		    vehicle_colors_node.child("Mod1_c").text().as_int());
		VEHICLE::SET_VEHICLE_MOD_COLOR_2(vehicle_handle,
		    vehicle_colors_node.child("Mod2_a").text().as_int(),
		    vehicle_colors_node.child("Mod2_b").text().as_int());

		VEHICLE::SET_VEHICLE_COLOURS(vehicle_handle,
		    vehicle_colors_node.child("Primary").text().as_int(),
		    vehicle_colors_node.child("Secondary").text().as_int());
		VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle_handle,
		    vehicle_colors_node.child("Pearl").text().as_int(),
		    vehicle_colors_node.child("Rim").text().as_int());

		if (vehicle_colors_node.child("IsPrimaryColourCustom").text().as_bool())
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle_handle,
			    vehicle_colors_node.child("Cust1_R").text().as_int(),
			    vehicle_colors_node.child("Cust1_G").text().as_int(),
			    vehicle_colors_node.child("Cust1_B").text().as_int());
		if (vehicle_colors_node.child("IsSecondaryColourCustom").text().as_bool())
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle_handle,
			    vehicle_colors_node.child("Cust2_R").text().as_int(),
			    vehicle_colors_node.child("Cust2_G").text().as_int(),
			    vehicle_colors_node.child("Cust2_B").text().as_int());
		VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle_handle,
		    vehicle_colors_node.child("tyreSmoke_R").text().as_int(),
		    vehicle_colors_node.child("tyreSmoke_G").text().as_int(),
		    vehicle_colors_node.child("tyreSmoke_B").text().as_int());

		ENTITY::SET_ENTITY_VISIBLE(vehicle_handle, vehicle_node.child("IsVisible").text().as_bool(), true);

        for (auto attachment_item = vehicle_attachments_node.first_child(); attachment_item; attachment_item = vehicle_attachments_node.next_sibling())
        {
            auto entity_attachment_node = attachment_item.child("Attachment");
            auto entity_model = attachment_item.child("ModelHash").text().as_uint();
        }
	}
}

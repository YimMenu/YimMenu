#include "outfit_service.hpp"

#include "natives.hpp"
#include "util/outfit.hpp"

namespace big
{
	void outfit_service::apply_outfit(nlohmann::json j, bool set_parachute)
	{
		bool was_components_set = false;
		for (auto& item : j["components"].items())
		{
			std::stringstream ss(item.key());
			int id = 0;
			ss >> id;

			if (!set_parachute && id == 5)
				continue;

			int drawable_id = item.value()["drawable_id"];
			int texture_id  = item.value()["texture_id"];
			if (PED::GET_PED_DRAWABLE_VARIATION(self::ped, id) != drawable_id || PED::GET_PED_TEXTURE_VARIATION(self::ped, id) != texture_id)
			{
				was_components_set = true;
				PED::SET_PED_COMPONENT_VARIATION(self::ped, id, drawable_id, texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, id));
				if (PED::GET_PED_DRAWABLE_VARIATION(self::ped, id) != drawable_id || PED::GET_PED_TEXTURE_VARIATION(self::ped, id) != texture_id) //Run it again Tony to make sure it actually changed.
					was_components_set = false;
			}
		}
		for (auto& item : j["props"].items())
		{
			std::stringstream ss(item.key());
			int id = 0;
			ss >> id;
			int drawable_id = item.value()["drawable_id"];
			int texture_id  = item.value()["texture_id"];
			if (drawable_id == -1 && PED::GET_PED_PROP_INDEX(self::ped, id, 1) != -1)
				PED::CLEAR_PED_PROP(self::ped, id, 1);
			else if (PED::GET_PED_PROP_INDEX(self::ped, id, 1) != drawable_id || PED::GET_PED_PROP_TEXTURE_INDEX(self::ped, id) != texture_id)
			{
				was_components_set = true;
				PED::SET_PED_PROP_INDEX(self::ped, id, drawable_id, texture_id, NETWORK::NETWORK_IS_GAME_IN_PROGRESS(), 1);
				if (id == 0)
				{
					//Prevent player ped from taking helmet off.
					PED::SET_PED_CONFIG_FLAG(self::ped, 34, true);
					PED::SET_PED_CONFIG_FLAG(self::ped, 36, true);
				}
			}
		}
		if (j.contains("blend_data") && was_components_set)
		{
			head_blend_data blend_data = j["blend_data"];
			PED::SET_PED_HEAD_BLEND_DATA(self::ped,
			    blend_data.shape_first_id,
			    blend_data.shape_second_id,
			    blend_data.shape_third_id,
			    blend_data.skin_first_id,
			    blend_data.skin_second_id,
			    blend_data.skin_third_id,
			    blend_data.shape_mix,
			    blend_data.skin_mix,
			    blend_data.third_mix,
			    blend_data.is_parent);
		}
	}
	void outfit_service::save_outfit(std::string filename)
	{
		outfit::components_t components;
		outfit::props_t props;
		auto model = ENTITY::GET_ENTITY_MODEL(self::ped);

		for (auto& item : components.items)
		{
			item.drawable_id     = PED::GET_PED_DRAWABLE_VARIATION(self::ped, item.id);
			item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

			item.texture_id     = PED::GET_PED_TEXTURE_VARIATION(self::ped, item.id);
			item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
		}

		for (auto& item : props.items)
		{
			item.drawable_id     = PED::GET_PED_PROP_INDEX(self::ped, item.id, 1);
			item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(self::ped, item.id) - 1;

			item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(self::ped, item.id);
			item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(self::ped, item.id, item.drawable_id) - 1;
		}

		nlohmann::json j;
		nlohmann::json j_components;
		nlohmann::json j_props;

		for (auto& item : components.items)
		{
			nlohmann::json tmp;
			tmp["drawable_id"]                    = item.drawable_id;
			tmp["texture_id"]                     = item.texture_id;
			j_components[std::to_string(item.id)] = tmp;
		}

		for (auto& item : props.items)
		{
			nlohmann::json tmp;
			tmp["drawable_id"]               = item.drawable_id;
			tmp["texture_id"]                = item.texture_id;
			j_props[std::to_string(item.id)] = tmp;
		}

		if (model == "mp_m_freemode_01"_J || model == "mp_f_freemode_01"_J)
		{
			head_blend_data blend_data{};
			PED::GET_PED_HEAD_BLEND_DATA(self::ped, (Any*)&blend_data);
			j["blend_data"] = blend_data;
		}

		j["components"] = j_components;
		j["props"]      = j_props;
		j["model"]      = model;

		static folder saved_outfit_path = g_file_manager.get_project_folder("saved_outfits");
		std::ofstream o(saved_outfit_path.get_file(filename).get_path());
		o << std::setw(4) << j << std::endl;
	}
}

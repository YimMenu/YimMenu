#pragma once
#include "script_global.hpp"

namespace big::outfit
{
	struct item_t
	{
		int id;
		std::string label;
		int drawable_id     = 0;
		int drawable_id_max = 0;
		int texture_id      = 0;
		int texture_id_max  = 0;
	};

	struct outfit_t
	{
		std::vector<item_t> components = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_BERD"_T.data()},
		    {2, "OUTFIT_HAIR"_T.data()},
		    {3, "OUTFIT_UPPR"_T.data()},
		    {4, "OUTFIT_LOWR"_T.data()},
		    {5, "OUTFIT_HAND"_T.data()},
		    {6, "OUTFIT_FEET"_T.data()},
		    {7, "OUTFIT_TEEF"_T.data()},
		    {8, "OUTFIT_ACCS"_T.data()},
		    {9, "OUTFIT_TASK"_T.data()},
		    {10, "OUTFIT_DECL"_T.data()},
		    {11, "OUTFIT_JBIB"_T.data()}};

		std::vector<item_t> props = {{0, "OUTFIT_HEAD"_T.data()},
		    {1, "OUTFIT_GLASSES"_T.data()},
		    {2, "OUTFIT_EARS"_T.data()},
		    {3, "OUTFIT_UNK1"_T.data()},
		    {4, "OUTFIT_UNK2"_T.data()},
		    {5, "OUTFIT_UNK3"_T.data()},
		    {6, "OUTFIT_WATCH"_T.data()},
		    {7, "OUTFIT_WRIST"_T.data()},
		    {8, "OUTFIT_UNK4"_T.data()}};

		void update(Ped ped)
		{
			for (auto& item : components)
			{
				item.drawable_id     = PED::GET_PED_DRAWABLE_VARIATION(ped, item.id);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_DRAWABLE_VARIATIONS(ped, item.id) - 1;

				item.texture_id     = PED::GET_PED_TEXTURE_VARIATION(ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_TEXTURE_VARIATIONS(ped, item.id, item.drawable_id) - 1;
			}
			for (auto& item : props)
			{
				item.drawable_id     = PED::GET_PED_PROP_INDEX(ped, item.id, 1);
				item.drawable_id_max = PED::GET_NUMBER_OF_PED_PROP_DRAWABLE_VARIATIONS(ped, item.id) - 1;

				item.texture_id = PED::GET_PED_PROP_TEXTURE_INDEX(ped, item.id);
				item.texture_id_max = PED::GET_NUMBER_OF_PED_PROP_TEXTURE_VARIATIONS(ped, item.id, item.drawable_id) - 1;
			}
		}

		void apply(Ped ped)
		{
			for (auto& item : components)
			{
				PED::SET_PED_COMPONENT_VARIATION(ped, item.id, item.drawable_id, item.texture_id, PED::GET_PED_PALETTE_VARIATION(self::ped, item.id));
			}

			for (auto& item : props)
			{
				if (item.drawable_id == -1 || item.texture_id == -1)
					PED::CLEAR_PED_PROP(self::ped, item.id, 1);
				else
					PED::SET_PED_PROP_INDEX(self::ped, item.id, item.drawable_id, item.texture_id, TRUE, 1);
			}
		}

		static std::filesystem::path get_path()
		{
			static std::filesystem::path p = g_file_manager->get_project_folder("saved_outfits").get_path();
			return p;
		}

		std::filesystem::path get_path(std::filesystem::path name)
		{
			return get_path() / name;
		}

		std::vector<std::string> get_outfits()
		{
			std::vector<std::string> saved_outfits;
			for (const auto& directory_entry : std::filesystem::directory_iterator(get_path()))
				saved_outfits.push_back(directory_entry.path().filename().generic_string());
			return saved_outfits;
		}

		void save_json(std::filesystem::path name)
		{
			nlohmann::json j;
			nlohmann::json j_components;
			nlohmann::json j_props;

			for (auto& item : components)
			{
				nlohmann::json tmp;
				tmp["drawable_id"]                    = item.drawable_id;
				tmp["texture_id"]                     = item.texture_id;
				j_components[std::to_string(item.id)] = tmp;
			}

			for (auto& item : props)
			{
				nlohmann::json tmp;
				tmp["drawable_id"]               = item.drawable_id;
				tmp["texture_id"]                = item.texture_id;
				j_props[std::to_string(item.id)] = tmp;
			}

			j["components"] = j_components;
			j["props"]      = j_props;

			if (name.extension() != ".json")
				name += ".json";

			std::ofstream o(get_path() / name);
			o << std::setw(4) << j << std::endl;
		}

		void load_json(std::filesystem::path name)
		{
			if (name.extension() != ".json")
				name += ".json";

			std::ifstream i(get_path() / name);
			nlohmann::json j;
			i >> j;

			for (auto& item : j["components"].items())
			{
				std::stringstream ss(item.key());
				int id = 0;
				ss >> id;
				for (auto& element : components)
				{
					if (element.id == id)
					{
						element.drawable_id = item.value()["drawable_id"];
						element.texture_id  = item.value()["texture_id"];
					}	
				}
			}

			for (auto& item : j["props"].items())
			{
				std::stringstream ss(item.key());
				int id = 0;
				ss >> id;
				for (auto& element : props)
				{
					if (element.id == id)
					{
						element.drawable_id = item.value()["drawable_id"];
						element.texture_id  = item.value()["texture_id"];
					}
				}
			}
		}

		std::string export_to_clipboard()
		{
			std::stringstream ss;
			for (auto& item : components)
				ss << 0 << " " << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
			for (auto& item : props)
				ss << 1 << " " << item.id << " " << item.drawable_id << " " << item.texture_id << " ";
			return ss.str();
		}

		void import_from_clipboard(std::string str)
		{
			std::stringstream ss(str);
			int is_prop     = 0;
			int id          = 0;
			int drawable_id = 0;
			int texture_id  = 0;
			while (ss >> is_prop >> id >> drawable_id >> texture_id)
			{
				if (!ss.fail())
				{
					if (!is_prop)
					{
						for (auto& item : components)
						{
							if (item.id == id)
							{
								item.drawable_id = drawable_id;
								item.texture_id  = texture_id;
							}
						}
					}
					else
					{
						for (auto& item : props)
						{
							if (item.id == id)
							{
								item.drawable_id = drawable_id;
								item.texture_id  = texture_id;
							}
						}
					}
				}
				else
				{
					break;
				}
			}
		}

		outfit_t& operator=(const outfit_t& other)
		{
			if (this != &other)
			{
				for (size_t i = 0; i < components.size(); i++)
				{
					components[i].drawable_id = other.components[i].drawable_id;
					components[i].drawable_id_max = other.components[i].drawable_id_max;
				}
				for (size_t i = 0; i < props.size(); i++)
				{
					props[i].texture_id       = other.props[i].texture_id;
					props[i].texture_id_max = other.props[i].texture_id_max;
				}
			}
			return *this;
		}
	};

	inline char* get_slot_name_address(int slot)
	{
		return script_global(2359296).at(0, 5568).at(681).at(2460).at(slot, 8).as<char*>();
	}

	inline int* get_component_drawable_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1336).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_component_texture_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1610).at(slot, 13).at(id, 1).as<int*>();
	}

	inline int* get_prop_drawable_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(1884).at(slot, 10).at(id, 1).as<int*>();
	}

	inline int* get_prop_texture_id_address(int slot, int id)
	{
		return script_global(2359296).at(0, 5568).at(681).at(2095).at(slot, 10).at(id, 1).as<int*>();
	}
}
#include "custom_teleport_service.hpp"

namespace big
{
	std::filesystem::path custom_teleport_service::get_telelocations_file_path()
	{
		return g_file_manager.get_project_file("telelocations.json").get_path();
	}

	std::vector<telelocation> custom_teleport_service::saved_locations_filtered_list(std::string filter)
	{
		std::vector<telelocation> filterlist{};

		static auto to_lower = [=](std::string text) -> std::string {
			std::transform(text.begin(), text.end(), text.begin(), ::tolower);
			return text;
		};

		for (auto& location : all_saved_locations | std::views::values | std::views::join)
			if (to_lower(location.name).find(to_lower(filter)) != std::string::npos)
				filterlist.push_back(location);

		return filterlist;
	}

	bool custom_teleport_service::fetch_saved_locations()
	{
		all_saved_locations.clear();

		auto path = get_telelocations_file_path();
		std::ifstream file(path, std::ios::binary);

		try
		{
			if (!file.is_open())
				return false;

			nlohmann::json j;
			file >> j;
			all_saved_locations = j.get<std::map<std::string, std::vector<telelocation>>>();

			return true;
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching saved locations: " << e.what() << '\n';
			return false;
		}

		return false;
	}

	bool custom_teleport_service::save_new_location(const std::string& category, telelocation t)
	{
		const auto& pair = all_saved_locations.insert({category, {t}});
		if (!pair.second)
		{
			pair.first->second.push_back(t);
		}

		auto path = get_telelocations_file_path();

		std::ofstream file_out(path, std::ofstream::trunc | std::ofstream::binary);
		if (!file_out.is_open())
			return false;

		nlohmann::json j = all_saved_locations;
		file_out << j.dump(4);
		file_out.close();

		g_notification_service.push_success("GUI_TAB_CUSTOM_TELEPORT"_T.data(), std::format("Succesfully saved location {}", t.name));

		return true;
	}

	bool custom_teleport_service::delete_saved_location(const std::string& category, const std::string& location_name)
	{
		auto path = get_telelocations_file_path();

		const auto& it = all_saved_locations.find(category);
		if (it == all_saved_locations.end())
			return false;

		std::erase_if(it->second, [location_name](telelocation t) {
			return t.name == location_name;
		});

		if (!it->second.size())
		{
			all_saved_locations.erase(category);
		}

		std::ofstream file_out(path, std::ofstream::trunc | std::ofstream::binary);
		if (!file_out.is_open())
			return false;

		nlohmann::json j = all_saved_locations;
		file_out << j.dump(4);
		file_out.close();

		return true;
	}

	telelocation* custom_teleport_service::get_saved_location_by_name(std::string name)
	{
		for (auto& loc : g_custom_teleport_service.saved_locations_filtered_list())
			if (loc.name == name)
				return &loc;

		return nullptr;
	}
}

#include "ped_animations_service.hpp"

#include "gta/enums.hpp"
#include "util/notify.hpp"
#include "util/ped.hpp"

namespace big
{
	std::filesystem::path ped_animation_service::get_ped_animations_file_path()
	{
		return g_file_manager.get_project_file("ped_animations.json").get_path();
	}

	std::vector<ped_animation> ped_animation_service::saved_animations_filtered_list(std::string filter = "")
	{
		std::vector<ped_animation> filterlist{};

		static auto to_lower = [=](std::string text) -> std::string {
			std::transform(text.begin(), text.end(), text.begin(), ::tolower);
			return text;
		};

		for (auto& ped_animation : all_saved_animations | std::views::values | std::views::join)
			if (to_lower(ped_animation.name).find(to_lower(filter)) != std::string::npos)
				filterlist.push_back(ped_animation);

		return filterlist;
	}

	bool ped_animation_service::fetch_saved_animations()
	{
		all_saved_animations.clear();

		auto path = get_ped_animations_file_path();
		std::ifstream file(path, std::ios::binary);

		try
		{
			if (!file.is_open())
				return false;

			nlohmann::json j;
			file >> j;
			all_saved_animations = j.get<std::map<std::string, std::vector<ped_animation>>>();

			return true;
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed fetching saved animations: " << e.what() << "\n";
		}

		return false;
	}

	bool ped_animation_service::save_new_animation(const std::string& category, ped_animation p)
	{
		const auto& pair = all_saved_animations.insert({category, {p}});
		if (!pair.second)
		{
			pair.first->second.push_back(p);
		}

		auto path = get_ped_animations_file_path();

		std::ofstream file_out(path, std::ofstream::trunc | std::ofstream::binary);
		if (!file_out.is_open())
			return false;

		nlohmann::json j = all_saved_animations;
		file_out << j.dump(4);
		file_out.close();

		g_notification_service->push_success("Animations", std::format("Succesfully saved location {}", p.name));

		return true;
	}

	bool ped_animation_service::delete_saved_animation(const std::string& category, ped_animation p)
	{
		auto path = get_ped_animations_file_path();

		const auto& it = all_saved_animations.find(category);
		if (it == all_saved_animations.end())
			return false;

		std::erase_if(it->second, [p](ped_animation p_) {
			return p_.name == p.name;
		});

		if (!it->second.size())
		{
			all_saved_animations.erase(category);
		}

		std::ofstream file_out(path, std::ofstream::trunc | std::ofstream::binary);
		if (!file_out.is_open())
			return false;

		nlohmann::json j = all_saved_animations;
		file_out << j.dump(4);
		file_out.close();

		return true;
	}

	ped_animation* ped_animation_service::get_animation_by_name(std::string name)
	{
		for (auto& anim : saved_animations_filtered_list())
			if (anim.name == name)
				return &anim;

		return nullptr;
	}

	void ped_animation_service::play_saved_ped_animation(ped_animation p, Ped ped)
	{
		ped::ped_play_animation(ped, p.dict, p.anim, p.blendin, p.blendout, p.time_to_play, p.flags, p.start_phase, false, {p.pos[0], p.pos[1], p.pos[2]}, {p.rot[0], p.rot[1], p.rot[2]});
	}
}
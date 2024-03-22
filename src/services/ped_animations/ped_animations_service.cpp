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

	std::vector<ped_animation> ped_animation_service::saved_animations_ambient_list()
	{
		std::vector<ped_animation> ambientlist{};

		for (auto& ped_animation : all_saved_animations | std::views::values | std::views::join)
			if (ped_animation.ambient)
				ambientlist.push_back(ped_animation);

		return ambientlist;
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

		g_notification_service.push_success("Animations", std::format("Succesfully saved location {}", p.name));

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

	void ped_animation_service::ambient_animations_prompt_tick()
	{
		if (!g.self.prompt_ambient_animations)
			return;

		auto ambient_list = saved_animations_ambient_list();

		ped_animation closest_ambient_animation{};
		float distance = 500;

		for (auto& anim : ambient_list)
		{
			Vector3 anim_vector = {anim.pos[0], anim.pos[1], anim.pos[2]};

			auto new_distance = math::distance_between_vectors(self::pos, anim_vector);
			if (new_distance < distance)
			{
				closest_ambient_animation = anim;
				distance                  = new_distance;
			}
		}

		if (math::distance_between_vectors(self::pos,
		        {closest_ambient_animation.pos[0], closest_ambient_animation.pos[1], closest_ambient_animation.pos[2]})
		    < 5)
		{
			if (!ENTITY::IS_ENTITY_PLAYING_ANIM(self::ped,
			        closest_ambient_animation.dict.data(),
			        closest_ambient_animation.anim.data(),
			        3))
			{
				notify::display_help_text(
				    std::format("~b~Ambient Animation~w~\nPress ~INPUT_PICKUP~ to play ~g~{}", closest_ambient_animation.name));
				if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_PICKUP))
				{
					play_saved_ped_animation(closest_ambient_animation, self::ped);
				}
			}
			else
			{
				notify::display_help_text(std::format("Press ~INPUT_PICKUP~ to stop playing ~g~{}", closest_ambient_animation.name));
				if (PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_PICKUP))
				{
					TASK::CLEAR_PED_TASKS(self::ped);
				}
			}
		}
	}
}

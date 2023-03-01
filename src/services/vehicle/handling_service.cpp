#include "handling_service.hpp"

#include "gta_util.hpp"

namespace big
{
	handling_service::handling_service() :
	    m_profiles_folder(g_file_manager->get_project_folder("./handling_profiles"))
	{
		g_handling_service = this;

		load_files();
	}

	handling_service::~handling_service()
	{
		g_handling_service = nullptr;
	}

	std::size_t handling_service::load_files()
	{
		std::size_t files_loaded{};
		m_handling_profiles.clear();

		for (const auto& item : std::filesystem::directory_iterator(m_profiles_folder.get_path()))
		{
			if (!item.is_regular_file())
				continue;

			auto file_path = item.path();
			if (file_path.extension() == ".json")
			{
				auto profile_file = std::ifstream(file_path, std::ios::binary);
				nlohmann::json j;
				profile_file >> j;
				profile_file.close();

				m_handling_profiles.emplace(file_path.stem().string(), j.get<handling_profile>());

				++files_loaded;
			}
			// deprecate this
			else if (file_path.extension() == ".bin")
			{
				LOG(WARNING) << "Attempting to convert old handling files, this feature will be removed in the future.";

				auto profile_file = std::ifstream(file_path, std::ios::binary);
				auto profile      = handling_profile();
				profile_file.read(reinterpret_cast<char*>(&profile), 328);// hardcoded old size to prevent overreading
				profile_file.close();

				const auto new_save = file_path.stem().string();

				// this will make sure we only copy the fields we want to copy
				nlohmann::json j          = profile;
				const auto save_file_path = m_profiles_folder.get_file("./" + new_save + ".json");
				auto save_file            = std::ofstream(save_file_path.get_path(), std::ios::binary);
				save_file << j.dump(4);

				// remove old file
				std::filesystem::remove(file_path);

				m_handling_profiles.emplace(new_save, j.get<handling_profile>());

				++files_loaded;
			}
		}

		return files_loaded;
	}

	handling_profiles& handling_service::profiles()
	{
		return m_handling_profiles;
	}

	handling_profile* handling_service::active_profile()
	{
		return m_active_profile;
	}

	void handling_service::apply_profile(handling_profile* profile)
	{
		if (const auto vehicle = gta_util::get_local_vehicle(); vehicle)
		{
			profile->apply_to(vehicle);
			m_active_profile = profile;
		}
	}

	bool handling_service::save_profile(std::string name)
	{
		const auto vehicle = gta_util::get_local_vehicle();
		if (!vehicle)
			return false;

		name += ".json";
		const auto save = m_profiles_folder.get_file(name);

		auto profile = handling_profile(vehicle);

		auto save_file   = std::ofstream(save.get_path(), std::ios::binary);
		nlohmann::json j = profile;
		save_file << j.dump(4);
		save_file.close();

		// reset our profile to prevent copying members we don't want to exist
		profile = handling_profile();
		profile = j.get<handling_profile>();

		m_handling_profiles.emplace(save.get_path().stem().string(), std::move(profile));

		return true;
	}

	bool handling_service::backup_vehicle()
	{
		const auto vehicle = gta_util::get_local_vehicle();
		if (!vehicle)
			return false;

		const auto hash = vehicle->m_handling_data->m_model_hash;
		if (const auto& it = m_vehicle_backups.find(hash); it != m_vehicle_backups.end())
			return false;

		m_vehicle_backups.emplace(hash, handling_profile(vehicle));

		return true;
	}

	void handling_service::restore_vehicle() const
	{
		const auto vehicle = gta_util::get_local_vehicle();
		if (!vehicle)
			return;

		if (const auto& it = m_vehicle_backups.find(vehicle->m_handling_data->m_model_hash); it != m_vehicle_backups.end())
		{
			it->second.apply_to(vehicle);
		}
	}
}
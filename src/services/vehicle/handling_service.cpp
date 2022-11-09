#include "gta_util.hpp"
#include "handling_service.hpp"

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

		for (const auto& item : std::filesystem::directory_iterator(m_profiles_folder.get_path()))
		{
			if (!item.is_regular_file())
				continue;
			if (auto file_path = item.path(); file_path.extension() == ".bin")
			{
				auto profile = std::make_unique<handling_profile>();
				auto profile_file = std::ifstream(file_path, std::ios::binary);
				profile_file.read(reinterpret_cast<char*>(profile.get()), sizeof(handling_profile));
				profile_file.close();

				m_handling_profiles.emplace(file_path.stem().string(), std::move(profile));

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

		name += ".bin";
		const auto save = m_profiles_folder.get_file(name);

		auto profile = std::make_unique<handling_profile>(vehicle);

		auto save_file = std::ofstream(save.get_path(), std::ios::binary);
		save_file.write(reinterpret_cast<const char*>(profile.get()), sizeof(handling_profile));
		save_file.close();

		m_handling_profiles.emplace(name, std::move(profile));

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

		m_vehicle_backups.emplace(hash, std::make_unique<handling_profile>(vehicle));

		return true;
	}

	void handling_service::restore_vehicle() const
	{
		const auto vehicle = gta_util::get_local_vehicle();
		if (!vehicle)
			return;

		if (const auto& it = m_vehicle_backups.find(vehicle->m_handling_data->m_model_hash); it != m_vehicle_backups.end())
		{
			it->second->apply_to(vehicle);
		}
	}
}
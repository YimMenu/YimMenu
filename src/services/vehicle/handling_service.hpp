#pragma once
#include "handling_profile.hpp"

namespace big
{
	using handling_profiles = std::map<std::string, handling_profile>;
	class handling_service final
	{
	public:
		handling_service();
		~handling_service();

		handling_service(const handling_service&)                = delete;
		handling_service(handling_service&&) noexcept            = delete;
		handling_service& operator=(const handling_service&)     = delete;
		handling_service& operator=(handling_service&&) noexcept = delete;

		std::size_t load_files();
		handling_profiles& profiles();

		handling_profile* active_profile();
		void apply_profile(handling_profile* profile);
		bool save_profile(std::string name);

		bool backup_vehicle();
		void restore_vehicle() const;

	private:
		const folder m_profiles_folder;

		handling_profile* m_active_profile;
		handling_profiles m_handling_profiles;

		// contains the handling profiles of a vehicles before they're been modified
		std::unordered_map<uint32_t, handling_profile> m_vehicle_backups;
	};

	inline handling_service* g_handling_service{};
}
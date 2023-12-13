#pragma once
#include "weapon_item.hpp"
#include "weapon_component.hpp"

namespace big
{

	class weapon_file
	{
	public:
		struct version_info
		{
			std::string m_game_build;
			std::string m_online_version;
			uint32_t m_file_version;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(version_info, m_game_build, m_online_version, m_file_version)
		} version_info{};

		std::map<std::string, weapon_item> weapon_map;
		std::map<std::string, weapon_component> weapon_components;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapon_file, version_info, weapon_map, weapon_components)

		bool up_to_date(uint32_t file_version) const
		{
			return file_version == version_info.m_file_version;
		}
	};
}
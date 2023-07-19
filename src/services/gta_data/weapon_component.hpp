#pragma once

namespace big
{
	class weapon_component final
	{
	public:
		std::string m_name;
		Hash m_hash;
		std::string m_display_name;
		std::string m_display_desc;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapon_component, m_name, m_hash, m_display_name, m_display_desc)
	};
}
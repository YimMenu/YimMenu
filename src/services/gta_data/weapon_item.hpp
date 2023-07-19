#pragma once

namespace big
{
	class weapon_item final
	{
	public:
		std::string m_name;
		std::string m_display_name;
		std::string m_weapon_type;
		std::uint32_t m_hash;
		std::uint32_t m_reward_hash;
		std::uint32_t m_reward_ammo_hash;
		std::vector<std::string> m_attachments;
		bool m_throwable;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapon_item, m_name, m_display_name, m_weapon_type, m_hash, m_reward_hash, m_reward_ammo_hash, m_attachments, m_throwable)
	};
}
#pragma once

namespace big
{
#pragma pack(push, 4)
	class weapon_item final
	{
	public:
		char m_name[32];
		char m_display_name[32];
		char m_weapon_type[16];
		std::uint32_t m_hash;
		std::uint32_t m_reward_hash;
		std::uint32_t m_reward_ammo_hash;
		bool m_throwable;
	};
#pragma pack(pop)
}
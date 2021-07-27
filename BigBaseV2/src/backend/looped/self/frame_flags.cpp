#include "backend/looped/looped.hpp"
#include "core/enums.hpp"

namespace big
{
	enum eFrameFlags : std::uint32_t
	{
		eFrameFlagExplosiveAmmo = 1 << 3,
		eFrameFlagFireAmmo = 1 << 4,
		eFrameFlagExplosiveMelee = 1 << 5,
		eFrameFlagSuperJump = 1 << 6,
	};

	void looped::self_frame_flags()
	{
		if (g_local_player == nullptr || g_local_player->m_player_info == nullptr) return;

		uint32_t& flags = g_local_player->m_player_info->m_frame_flags;

		if (g.self.frame_flags.explosive_ammo)
			flags |= eFrameFlagExplosiveAmmo;

		if (g.self.frame_flags.explosive_melee)
			flags |= eFrameFlagExplosiveMelee;

		if (g.self.frame_flags.fire_ammo)
			flags |= eFrameFlagFireAmmo;

		if (g.self.frame_flags.super_jump)
			flags |= eFrameFlagSuperJump;
	}
}
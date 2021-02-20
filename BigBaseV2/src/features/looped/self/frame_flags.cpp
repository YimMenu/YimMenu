#include "features/self.hpp"
#include "gta/enums.hpp"

namespace big
{
	void self::frame_flags()
	{
		if (g_local_ped == nullptr) return;

		uint32_t& flags = g_local_ped->m_player_info->m_frame_flags;
		auto& frame_flags = g_settings.options["frame_flags"];

		if (frame_flags["explosive_ammo"])
			flags |= eFrameFlagExplosiveAmmo;

		if (frame_flags["explosive_melee"])
			flags |= eFrameFlagExplosiveMelee;

		if (frame_flags["fire_ammo"])
			flags |= eFrameFlagFireAmmo;

		if (frame_flags["super_jump"])
			flags |= eFrameFlagSuperJump;
	}
}
#pragma once

namespace big
{
	inline struct g_self_t
	{
		bool passive    = false;
		bool free_cam   = false;
		bool no_ragdoll = false;

		bool noclip                       = false;
		float noclip_aim_speed_multiplier = 0.25f;
		float noclip_speed_multiplier     = 20.f;
		bool noclip_x_axis_rot            = false;
		bool noclip_collision             = false;

		bool off_radar        = false;
		bool ghost_org        = false;
		bool unlimited_oxygen = false;
		bool god_mode         = false;
		bool clean_player     = true;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_self_t, noclip_aim_speed_multiplier, noclip_speed_multiplier)
	} g_self{};
}
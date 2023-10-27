#pragma once

namespace big
{
	inline struct g_protections_t
	{
		struct script_events
		{
			bool ceo_money                  = true;
			bool clear_wanted_level         = true;
			bool force_mission              = true;
			bool force_teleport             = true;
			bool gta_banner                 = true;
			bool mc_teleport                = true;
			bool personal_vehicle_destroyed = true;
			bool remote_off_radar           = false;
			bool rotate_cam                 = true;
			bool send_to_cutscene           = true;
			bool send_to_location           = true;
			bool sound_spam                 = true;
			bool spectate                   = true;
			bool give_collectible           = true;
			bool vehicle_kick               = false;
			bool teleport_to_warehouse      = true;
			bool start_activity             = true;
			bool send_sms                   = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_events, ceo_money, clear_wanted_level, force_mission, force_teleport, gta_banner, mc_teleport, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate, give_collectible, vehicle_kick, teleport_to_warehouse, start_activity, send_sms)
		} script_events{};

		bool rid_join       = false;
		bool receive_pickup = false;
		bool admin_check    = true;
		bool force_relay_connections = false;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_protections_t, script_events, rid_join, receive_pickup, admin_check)
	} g_protections{};
}
#pragma once
#include "backend/reactions/interloper_reaction.hpp"
#include "backend/reactions/reaction.hpp"
#include "core/data/ptfx_effects.hpp"
#include "enums.hpp"
#include "file_manager.hpp"

#include <bitset>
#include <imgui.h>
#include <rage/rlSessionInfo.hpp>
#include <weapon/CAmmoInfo.hpp>
#include <weapon/CWeaponInfo.hpp>

class CNetGamePlayer;

namespace rage
{
	class scrThread;
	class scrProgram;
}

namespace big
{
	class menu_settings
	{
	public:
		void destroy();
		void init(const file& save_file);

		void attempt_save();
		bool load();

	private:
		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false);
		bool save();
		bool write_default_config();

	private:
		bool m_running;

		std::unique_ptr<file> m_save_file;

		nlohmann::json m_default_options;
		nlohmann::json m_options;

	public:
		int friend_count = 0;
		int player_count = 0;

		CNetGamePlayer* m_syncing_player = nullptr;
		std::unordered_map<std::uint64_t, std::uint64_t> m_spoofed_peer_ids;

		int m_remote_controller_vehicle = -1;
		int m_remote_controlled_vehicle = -1;

		int m_mod_net_id  = -1;
		int m_test_net_id = -1;

		rage::scrThread* m_hunt_the_beast_thread = nullptr;

		rage::scrThread* m_dance_thread   = nullptr;
		rage::scrProgram* m_dance_program = nullptr;

		rage::scrThread* m_mission_creator_thread = nullptr;

		struct cmd_executor
		{
			bool enabled = false;
		} cmd_executor{};
		struct debug
		{
			struct logs
			{
				bool metric_logs{};
				bool packet_logs{};

				bool script_hook_logs{};

				struct script_event
				{
					bool logs = false;

					bool filter_player    = true;
					std::int8_t player_id = -1;

					bool block_all = false; //should not save

					NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_event, logs, filter_player, player_id)
				} script_event{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(logs, metric_logs, packet_logs, script_hook_logs, script_event)
			} logs{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(debug, logs)
		} debug{};

		struct tunables
		{
			bool disable_phone = false;
			bool no_idle_kick  = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(tunables, disable_phone, no_idle_kick)
		} tunables{};

		struct notifications
		{
			struct pair
			{
				bool log    = false;
				bool notify = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(pair, log, notify)
			};

			pair gta_thread_kill{};
			pair gta_thread_start{};

			pair network_player_mgr_init{};
			pair network_player_mgr_shutdown{};

			struct player_join
			{
				bool above_map = true;
				bool log       = false;
				bool notify    = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(player_join, above_map, log, notify)
			} player_join{};

			pair player_leave{};

			pair send_net_info_to_lobby{};
			pair transaction_rate_limit{};
			pair mismatch_sync_type{};
			pair out_of_allowed_range_sync_type{};
			pair invalid_sync{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(notifications, gta_thread_kill, gta_thread_start, network_player_mgr_init, network_player_mgr_shutdown, player_join, player_leave, send_net_info_to_lobby, transaction_rate_limit, mismatch_sync_type, out_of_allowed_range_sync_type, invalid_sync)
		} notifications{};

		struct reactions
		{
			reaction bounty{"Bounty", "Blocked Bounty from %s", "%s tried to set a bounty on me!"};
			reaction ceo_kick{"CEO Kick", "Blocked CEO Kick from %s", "%s tried to kick me from my CEO!"};
			reaction ceo_money{"CEO Money", "Blocked CEO Money from %s", "%s tried to drop money on me!"};
			reaction clear_wanted_level{"Clear Wanted Level", "Blocked Clear Wanted Level from %s", "%s tried to clear my wanted level!"};
			reaction crash{"Crash", "Blocked Crash from %s", "%s tried to crash me!"};
			reaction end_session_kick{"End Session Kick", "Blocked End Session Kick from %s", "%s tried to kick me out!"};
			reaction fake_deposit{"Fake Deposit", "Blocked Fake Deposit from %s", "%s tried to show me a fake money notification!"};
			reaction force_mission{"Force Mission", "Blocked Force Mission from %s", "%s tried to force me into a mission!"};
			reaction force_teleport{"Force Teleport", "Blocked Force Teleport from %s", "%s tried to teleport me!"};
			reaction gta_banner{"GTA Banner", "Blocked GTA Banner from %s", "Blocked GTA Banner from %s"}; // please don't enable this
			reaction kick_from_interior{"Kick From Interior", "Blocked Kick From Interior from %s", "%s tried to kick me from my interior!"};
			reaction mc_teleport{"MC Teleport", "Blocked MC Teleport from %s", "%s tried to teleport me!"};
			reaction network_bail{"Network Bail", "Blocked Network Bail from %s", "%s tried to kick me out!"};
			reaction personal_vehicle_destroyed{"Personal Vehicle Destroyed", "Blocked Personal Vehicle Destroyed from %s", "%s tried to show me a fake insurance notification!"};
			reaction remote_off_radar{"Remote Off Radar", "Blocked Remote Off Radar from %s", "%s tried to give me off radar!"};
			reaction rotate_cam{"Rotate Cam", "Blocked Rotate Cam from %s", "%s tried to mess with my camera!"};
			reaction send_to_cutscene{"Send To Cutscene", "Blocked Send To Cutscene from %s", "%s tried to force me into a cutscene!"};
			reaction send_to_location{"Send To Location", "Blocked Send To Location from %s", "%s tried to send me to Cayo Perico!"};
			reaction sound_spam{"Sound Spam", "Blocked Sound Spam from %s", "%s tried to spam annoying sounds at me!"};
			reaction spectate_notification{"Spectate", "Blocked Spectate from %s", "Blocked Spectate from %s"};
			reaction give_collectible{"Give Collectible", "Blocked Give Collectible from %s", "%s tried to give me a collectible!"};
			reaction transaction_error{"Transaction Error", "Blocked Transaction Error from %s", "%s tried to show me a transaction error!"};
			reaction tse_freeze{"TSE Freeze", "Blocked TSE Freeze from %s", "%s tried to softlock my game!"};
			reaction tse_sender_mismatch{"TSE Sender Mismatch", "Blocked TSE Sender Mismatch from %s", "Blocked TSE Sender Mismatch from %s"};
			reaction vehicle_kick{"Vehicle Kick", "Blocked Vehicle Kick from %s", "%s tried to kick me from my vehicle!"};
			reaction teleport_to_warehouse{"Teleport To Warehouse", "Blocked Teleport To Warehouse from %s", "%s tried to teleport me to a warehouse!"};
			reaction start_activity{"Start Activity", "Blocked Start Activity from %s", "Blocked Start Activity from %s"};
			reaction start_script{"Start Script", "Blocked Start Script from %s", "Blocked Start Script from %s"};
			reaction null_function_kick{"Null Function Kick", "Blocked Null Function Kick from %s", "%s tried to kick me out!"};
			reaction destroy_personal_vehicle{"Destroy Personal Vehicle", "Blocked Destroy Personal Vehicle from %s", "%s tried to destroy my personal vehicle!"};
			reaction trigger_business_raid{"Trigger Business Raid", "Blocked Trigger Business Raid from %s", "%s tried to trigger a business raid!"};
			reaction turn_into_beast{"Turn Into Beast", "Blocked Turn Into Beast from %s", "%s tried to turn me into the beast!"};
			reaction remote_wanted_level{"Remote Wanted Level", "Blocked Remote Wanted Level from %s", "%s tried to give me a wanted level!"};
			interloper_reaction remote_wanted_level_others{"Remote Wanted Level On Other Players", "%s is attempting to give a wanted level to %s!", "%s is attempting to give a wanted level to %s!", false, false};

			reaction clear_ped_tasks{"Clear Ped Tasks", "Blocked Clear Ped Tasks from %s", "%s tried to freeze me!"};
			reaction remote_ragdoll{"Remote Ragdoll", "Blocked Remote Ragdoll from %s", "%s tried to ragdoll me!"};
			reaction kick_vote{"Kick Vote", "%s is voting to kick you!", "%s is voting to kick me!"};
			reaction report_cash_spawn{"Cash Spawn", "%s is spawning cash", "%s is spawning cash"};
			reaction modder_detection{"Modder Detection", "%s is detected as a modder by the anticheat", "%s is detected as a modder by the anticheat"};
			reaction request_control_event{"Request Control Event", "Blocked Request Control Event from %s", "%s tried to mess with my vehicle!"};
			reaction report{"Report", "Blocked Report from %s", "%s tried to report me!"};

			interloper_reaction breakup_others{"Breakup Kicks On Other Players", "%s is trying to breakup kick %s!", "%s is trying to breakup kick %s!", true, true}; // blockable only when host but we have no way to specify that atm
			reaction lost_connection_kick{"Lost Connection Kick", "Blocked Lost Connection Kick from %s", "%s tried to kick me out!"};
			reaction gamer_instruction_kick{"Gamer Instruction Kick", "Blocked Gamer Instruction Kick from %s", "%s tried to kick me out!"};
			interloper_reaction lost_connection_kick_others{"Lost Connection Kick On Other Players", "%s is trying to lost connection kick %s!", "%s is trying to lost connection kick %s!", true, false};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(reactions, bounty, ceo_money, ceo_kick, clear_wanted_level, crash, end_session_kick, fake_deposit, force_mission, force_teleport, gta_banner, kick_from_interior, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate_notification, give_collectible, transaction_error, tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, trigger_business_raid, start_activity, start_script, null_function_kick, destroy_personal_vehicle, clear_ped_tasks, turn_into_beast, remote_wanted_level, remote_wanted_level_others, remote_ragdoll, kick_vote, report_cash_spawn, modder_detection, request_control_event, report, breakup_others, gamer_instruction_kick, lost_connection_kick, lost_connection_kick_others)
		} reactions{};

		struct player
		{
			int character_slot = 1;
			bool spectating    = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(player, character_slot, spectating)
		} player{};

		struct protections
		{
			struct script_events
			{
				bool bounty                     = true;
				bool ceo_money                  = true;
				bool clear_wanted_level         = true;
				bool fake_deposit               = true;
				bool force_mission              = true;
				bool force_teleport             = true;
				bool gta_banner                 = false;
				bool mc_teleport                = true;
				bool personal_vehicle_destroyed = true;
				bool remote_off_radar           = true;
				bool rotate_cam                 = true;
				bool send_to_cutscene           = true;
				bool send_to_location           = true;
				bool sound_spam                 = true;
				bool spectate                   = true;
				bool give_collectible           = true;
				bool vehicle_kick               = true;
				bool teleport_to_warehouse      = true;
				bool start_activity             = true;
				bool send_sms                   = true;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_events, bounty, ceo_money, clear_wanted_level, fake_deposit, force_mission, force_teleport, gta_banner, mc_teleport, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate, give_collectible, vehicle_kick, teleport_to_warehouse, start_activity, send_sms)
			} script_events{};

			bool desync_kick     = false;
			bool rid_join        = false;
			bool lessen_breakups = false; // disabled by default due to anticheat concerns
			bool receive_pickup  = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(protections, script_events, rid_join, lessen_breakups, desync_kick, receive_pickup)
		} protections{};

		struct self
		{
			struct ptfx_effects
			{
				bool show          = false;
				float size         = 0.2f;
				int select         = 0;
				const char* asset  = "scr_agencyheist";
				const char* effect = "scr_fbi_mop_drips";
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ptfx_effects, show, size)
			} ptfx_effects{};

			bool clean_player                          = false;
			bool force_wanted_level                    = false;
			bool free_cam                              = false;
			bool invisibility                          = false;
			bool local_visibility                      = true;
			bool never_wanted                          = false;
			bool no_ragdoll                            = false;
			bool noclip                                = false;
			bool off_radar                             = false;
			bool super_run                             = false;
			bool no_collision                          = false;
			bool unlimited_oxygen                      = false;
			bool no_water_collision                    = false;
			int wanted_level                           = 0;
			bool god_mode                              = false;
			bool part_water                            = false;
			bool proof_bullet                          = false;
			bool proof_fire                            = false;
			bool proof_collision                       = false;
			bool proof_melee                           = false;
			bool proof_explosion                       = false;
			bool proof_steam                           = false;
			bool proof_drown                           = false;
			bool proof_water                           = false;
			uint32_t proof_mask                        = 0;
			bool hide_radar                            = false;
			bool hide_ammo                             = false;
			int selected_hud_component                 = 1;
			std::array<bool, 22> hud_components_states = {false};
			bool force_show_hud_element                = false;
			bool force_show_hud                        = false;
			bool mobile_radio                          = false;
			bool fast_respawn                          = false;
			bool auto_tp                               = false;
			bool super_jump                            = false;
			bool beast_jump                            = false;
			bool superman                              = false;

			// do not save below entries
			bool dance_mode = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(self, ptfx_effects, clean_player, force_wanted_level, free_cam, invisibility, local_visibility, never_wanted, no_ragdoll, noclip, off_radar, super_run, no_collision, unlimited_oxygen, no_water_collision, wanted_level, god_mode, part_water, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_drown, proof_water, proof_mask, hide_radar, hide_ammo, selected_hud_component, hud_components_states, force_show_hud_element, force_show_hud, mobile_radio, fast_respawn, auto_tp, super_jump, beast_jump, superman)
		} self{};

		struct session
		{
			int local_weather     = 0;
			bool override_time    = {};
			bool override_weather = false;
			struct custom_time
			{
				int hour{}, minute{}, second{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(custom_time, hour, minute, second)
			} custom_time;
			bool chat_force_clean      = false;
			bool log_chat_messages     = false;
			bool log_text_messages     = false;
			bool decloak_players       = false;
			bool force_session_host    = false;
			bool force_script_host     = false;
			bool player_magnet_enabled = false;
			int player_magnet_count    = 32;
			bool is_team               = false;
			bool name_spoof_enabled    = false;
			bool advertise_menu        = false;
			std::string spoofed_name   = "";
			bool join_in_sctv_slots    = false;

			const char chat_command_prefix = '/';
			const char chat_output_prefix  = '>';

			bool chat_commands                                   = false;
			CommandAccessLevel chat_command_default_access_level = CommandAccessLevel::FRIENDLY;

			bool kick_chat_spammers          = false;
			bool kick_host_when_forcing_host = false;

			bool explosion_karma = false;
			bool damage_karma    = false;

			bool disable_traffic = false;
			bool disable_peds    = false;
			bool force_thunder   = false;

			bool block_ceo_money      = false;
			bool randomize_ceo_colors = false;
			bool block_jobs           = false;
			bool block_muggers        = false;
			bool block_ceo_raids      = false;

			int send_to_apartment_idx = 1;
			int send_to_warehouse_idx = 1;

			// not to be saved
			bool join_queued = false;
			rage::rlSessionInfo info;
			bool never_wanted_all = false;
			bool off_radar_all    = false;
			bool semi_godmode_all = false;
			bool wanted_level_all = false;

			bool show_cheating_message = false;
			bool anonymous_bounty      = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session, local_weather, override_time, override_weather, custom_time, chat_force_clean, log_chat_messages, log_text_messages, decloak_players, force_session_host, force_script_host, player_magnet_enabled, player_magnet_count, is_team, name_spoof_enabled, advertise_menu, spoofed_name, join_in_sctv_slots, kick_chat_spammers, kick_host_when_forcing_host, explosion_karma, damage_karma, disable_traffic, disable_peds, force_thunder, block_ceo_money, randomize_ceo_colors, block_jobs, block_muggers, block_ceo_raids, send_to_apartment_idx, send_to_warehouse_idx, chat_commands, chat_command_default_access_level, show_cheating_message, anonymous_bounty)
		} session{};

		struct settings
		{
			struct hotkeys
			{
				bool editing_menu_toggle = false;
				int menu_toggle          = VK_INSERT;
				int teleport_waypoint    = 0;
				int teleport_objective   = 0;
				int noclip               = 0;
				int bringvehicle         = 0;
				int invis                = 0;
				int heal                 = 0;
				int fill_inventory       = 0;
				int skip_cutscene        = 0;
				int freecam              = 0;
				int superrun             = 0;
				int superjump            = 0;
				int beastjump            = 0;
				int invisveh             = 0;
				int localinvisveh        = 0;
				int fast_quit            = 0;
				int cmd_excecutor        = 0x55; // U

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(hotkeys, editing_menu_toggle, menu_toggle, teleport_waypoint, teleport_objective, noclip, bringvehicle, invis, heal, fill_inventory, skip_cutscene, freecam, superrun, superjump, beastjump, invisveh, localinvisveh, fast_quit, cmd_excecutor)
			} hotkeys{};

			bool dev_dlc = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(settings, hotkeys, dev_dlc)
		} settings{};

		struct spawn_vehicle
		{
			bool preview_vehicle = false;
			bool spawn_inside    = false;
			bool spawn_maxed     = false;
			std::string plate    = "";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawn_vehicle, preview_vehicle, spawn_inside, spawn_maxed, plate)
		} spawn_vehicle{};

		struct clone_pv
		{
			bool preview_vehicle = false;
			bool spawn_inside    = false;
			bool spawn_clone     = false;
			bool spawn_maxed     = false;
			bool clone_plate     = false;
			std::string plate    = "";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(clone_pv, preview_vehicle, spawn_inside, spawn_clone, spawn_maxed, clone_plate, plate)
		} clone_pv{};

		struct world
		{
			struct train
			{
				bool derail_train = false;
				bool drive_train  = false;
			} train{};

			struct water
			{
				bool part_water = false;
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(water, part_water)
			} water{};

			struct spawn_ped
			{
				bool preview_ped       = false;
				bool spawn_invincible  = false;
				bool spawn_invisible   = false;
				bool spawn_as_attacker = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawn_ped, preview_ped, spawn_invincible, spawn_invisible, spawn_as_attacker)
			} spawn_ped{};

			struct custom_time
			{
				int local_weather     = 0;
				bool override_time    = {};
				bool override_weather = false;
				int hour{}, minute{}, second{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(custom_time, local_weather, hour, minute, second)
			} custom_time;


			struct blackhole
			{
				bool enable           = false;
				bool include_peds     = false;
				bool include_vehicles = false;
				float scale           = 6.f;
				float color[3]        = {1, 1, 1};
				int alpha             = 150;
				rage::fvector3 pos;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(blackhole, enable, include_peds, include_vehicles, color, alpha)
			} blackhole{};

			struct nearby
			{
				bool ignore     = false;
				bool ped_rain   = false;
				bool veh_rain   = false;
				bool high_alert = false;
				bool ped_rush   = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(nearby, ignore, ped_rain, veh_rain, high_alert, ped_rush)
			} nearby{};

			struct model_swapper
			{
				std::vector<std::pair<std::string, std::string>> models;
				std::mutex m;
				bool update = false;
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(model_swapper, models)
			} model_swapper{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(world, water, spawn_ped, custom_time, blackhole, model_swapper, nearby)
		} world{};

		struct spoofing
		{
			bool hide_from_player_list = false;

			bool spoof_blip = false;
			int blip_type   = 0; // actual blip type + 1

			bool spoof_rank = false;
			int rank        = 1;

			bool spoof_job_points = false;
			int job_points        = 1;

			bool spoof_kd_ratio = false;
			float kd_ratio      = 2.0f;

			bool spoof_bad_sport = false;
			int badsport_type    = 0;

			bool spoof_player_model  = false;
			std::string player_model = "";

			bool spoof_cheater = false;

			bool spoof_hide_god      = true;
			bool spoof_hide_spectate = true;

			bool spoof_crew_data = false;
			std::string crew_tag = "";
			bool rockstar_crew   = false;
			bool square_crew_tag = false;

			bool spoof_session_region_type  = false;
			int session_region_type         = 0;
			bool spoof_session_language     = false;
			int session_language            = 0;
			bool spoof_session_player_count = false;
			int session_player_count        = 25;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spoofing, hide_from_player_list, spoof_cheater, spoof_hide_god, spoof_hide_spectate, spoof_crew_data, crew_tag, rockstar_crew, square_crew_tag, spoof_session_region_type, session_region_type, spoof_session_language, session_language, spoof_session_player_count, session_player_count, spoof_blip, blip_type, spoof_rank, rank, spoof_job_points, job_points, spoof_bad_sport, badsport_type, spoof_kd_ratio, kd_ratio, spoof_player_model, player_model)
		} spoofing{};

		struct vehicle
		{
			struct speedo_meter
			{
				float x = .9f;
				float y = .72f;

				bool enabled   = false;
				bool left_side = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(speedo_meter, x, y, enabled, left_side)
			} speedo_meter{};

			struct fly
			{
				bool dont_stop    = false;
				bool enabled      = false;
				bool no_collision = false;
				bool stop_on_exit = false;
				float speed       = 100;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(fly, dont_stop, enabled, no_collision, stop_on_exit, speed)
			} fly{};

			struct rainbow_paint
			{
				RainbowPaintType type = RainbowPaintType::Off;
				bool neon             = false;
				bool primary          = false;
				bool secondary        = false;
				bool smoke            = false;
				int speed             = 0;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(rainbow_paint, type, neon, primary, secondary, smoke, speed)
			} rainbow_paint{};

			SpeedUnit speed_unit = SpeedUnit::MIPH;

			bool god_mode        = false;
			bool proof_bullet    = false;
			bool proof_fire      = false;
			bool proof_collision = false;
			bool proof_melee     = false;
			bool proof_explosion = false;
			bool proof_steam     = false;
			bool proof_water     = false;
			uint32_t proof_mask  = 0;

			AutoDriveDestination auto_drive_destination = AutoDriveDestination::STOPPED;
			AutoDriveStyle auto_drive_style             = AutoDriveStyle::LAW_ABIDING;
			float auto_drive_speed                      = 1;
			bool auto_turn_signals                      = false;
			eBoostBehaviors boost_behavior              = eBoostBehaviors::DEFAULT;
			bool drive_on_water                         = false;
			bool horn_boost                             = false;
			bool instant_brake                          = false;
			bool block_homing                           = true;
			bool ls_customs                             = false; // don't save this to disk
			bool seatbelt                               = false;
			bool turn_signals                           = false;
			bool vehicle_jump                           = false;
			bool keep_vehicle_repaired                  = false;
			bool no_water_collision                     = false;
			bool disable_engine_auto_start              = false;
			bool change_engine_state_immediately        = false;
			bool vehinvisibility                        = false;
			bool localveh_visibility                    = false;
			bool localped_visibility                    = true;
			bool keep_on_ground                         = false;
			bool no_collision                           = false;
			bool unlimited_weapons                      = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(vehicle, speedo_meter, fly, rainbow_paint, speed_unit, god_mode, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_water, proof_mask, auto_drive_destination, auto_drive_style, auto_drive_speed, auto_turn_signals, boost_behavior, drive_on_water, horn_boost, instant_brake, block_homing, seatbelt, turn_signals, vehicle_jump, keep_vehicle_repaired, no_water_collision, disable_engine_auto_start, change_engine_state_immediately, vehinvisibility, localveh_visibility, localped_visibility, keep_on_ground, no_collision, unlimited_weapons)
		} vehicle{};

		struct weapons
		{
			struct ammo_special
			{
				bool toggle                 = false;
				eAmmoSpecialType type       = eAmmoSpecialType::None;
				eExplosionTag explosion_tag = eExplosionTag::DONTCARE;

				NLOHMANN_JSON_SERIALIZE_ENUM(eAmmoSpecialType,
				    {
				        {eAmmoSpecialType::None, "none"},
				        {eAmmoSpecialType::ArmorPiercing, "armor_piercing"},
				        {eAmmoSpecialType::Explosive, "explosive"},
				        {eAmmoSpecialType::FMJ, "fmj"},
				        {eAmmoSpecialType::HollowPoint, "hollow_point"},
				        {eAmmoSpecialType::Incendiary, "incendiary"},
				        {eAmmoSpecialType::Tracer, "tracer"},
				    })
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ammo_special, toggle, type, explosion_tag)
			} ammo_special{};

			struct gravity_gun
			{
				bool launch_on_release = false;
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(gravity_gun, launch_on_release)
			} gravity_gun;

			struct aimbot
			{
				bool enable                 = false;
				bool smoothing              = true;
				float smoothing_speed       = 2.f;
				bool on_player              = true;
				bool on_enemy               = false;
				bool on_police              = false;
				bool on_npc                 = false;
				float fov                   = 90.f;
				float distance              = 200.f;
				std::uint32_t selected_bone = 0x796E; // Default to head
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(aimbot, enable, smoothing, smoothing_speed, fov, selected_bone)
			} aimbot{};

			CustomWeapon custom_weapon    = CustomWeapon::NONE;
			bool force_crosshairs         = false;
			bool infinite_ammo            = false;
			bool infinite_mag             = false;
			float increased_damage        = 1;
			bool no_recoil                = false;
			bool no_spread                = false;
			std::string vehicle_gun_model = "bus";
			bool increased_c4_limit       = false;
			bool increased_flare_limit    = false;
			bool rapid_fire               = false;
			bool interior_weapon          = false;
			bool triggerbot               = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapons, ammo_special, custom_weapon, aimbot, force_crosshairs, infinite_ammo, infinite_mag, increased_damage, no_recoil, no_spread, vehicle_gun_model, increased_c4_limit, increased_flare_limit, rapid_fire, gravity_gun, interior_weapon, triggerbot)
		} weapons{};

		struct window
		{
			ImU32 color     = 3357612055;
			float gui_scale = 1.f;

			ImFont* font_title     = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small     = nullptr;
			ImFont* font_icon      = nullptr;

			bool switched_view = true;

			struct ingame_overlay
			{
				bool opened                = true;
				bool show_with_menu_opened = false;

				bool show_fps              = true;
				bool show_players          = true;
				bool show_time             = true;
				bool show_replay_interface = true;
				bool show_game_versions    = true;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ingame_overlay, opened, show_with_menu_opened, show_fps, show_players, show_time, show_replay_interface, show_game_versions)
			} ingame_overlay{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(window, color, gui_scale, switched_view, ingame_overlay)
		} window{};

		struct context_menu
		{
			bool enabled = false;

			uint8_t allowed_entity_types = static_cast<uint8_t>(ContextEntityType::PED) | static_cast<uint8_t>(ContextEntityType::PLAYER) | static_cast<uint8_t>(ContextEntityType::VEHICLE) | static_cast<uint8_t>(ContextEntityType::OBJECT);

			ImU32 selected_option_color = 4278255360;

			bool bounding_box_enabled = true;
			ImU32 bounding_box_color  = 4278255360;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(context_menu, enabled, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
		} context_menu{};

		struct esp
		{
			bool enabled                    = true;
			bool hide_self                  = true;
			float global_render_distance[2] = {0.f, 600.f};
			float tracer_render_distance[2] = {200.f, 600.f};
			float box_render_distance[2]    = {0.f, 150.f};
			bool tracer                     = true;
			float tracer_draw_position[2]   = {0.5f, 1.f};
			bool box                        = true;
			bool health                     = true;
			bool armor                      = true;
			bool god                        = true;
			bool distance                   = true;
			bool name                       = true;
			bool change_esp_color_from_dist = false;
			bool scale_health_from_dist     = false;
			bool scale_armor_from_dist      = false;
			float distance_threshold[2]     = {100.f, 200.f};
			ImU32 enemy_color               = 4281479904;
			ImU32 enemy_near_color          = 4283794943;
			ImU32 default_color             = 4285713522;
			ImU32 friend_color              = 4293244509;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(esp, enabled, hide_self, global_render_distance, tracer_render_distance, box_render_distance, tracer, tracer_draw_position, box, health, armor, god, distance, name, change_esp_color_from_dist, scale_health_from_dist, scale_armor_from_dist, distance_threshold, enemy_color, enemy_near_color, default_color, friend_color)
		} esp{};

		struct session_browser
		{
			bool region_filter_enabled = true;
			int region_filter          = 0;

			bool language_filter_enabled = false;
			int language_filter          = 0;

			bool pool_filter_enabled = false;
			int pool_filter          = 0;

			bool player_count_filter_enabled = false;
			int player_count_filter_minimum  = 0;
			int player_count_filter_maximum  = 32;

			int sort_method    = 0;
			int sort_direction = 0;

			bool replace_game_matchmaking = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session_browser, region_filter_enabled, region_filter, language_filter_enabled, language_filter, player_count_filter_enabled, player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, replace_game_matchmaking, pool_filter_enabled, pool_filter)
		} session_browser{};

		struct ugc
		{
			bool infinite_model_memory;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(ugc, infinite_model_memory)
		} ugc{};

		struct stat_editor
		{
			struct stat
			{
				int radio_button_index      = 0;
				std::string int_text        = "";
				std::string int_value       = "";
				bool int_read               = false;
				std::string bool_text       = "";
				std::string bool_value      = "";
				bool bool_read              = false;
				std::string float_text      = "";
				std::string float_value     = "";
				bool float_read             = false;
				std::string increment_text  = "";
				std::string increment_value = "";
				bool increment_loop_write   = false;
				std::string date_text       = "";
				std::string date_value      = "";
				bool date_read              = false;
				std::string string_text     = "";
				std::string string_value    = "";
				bool string_read            = false;
				std::string label_text      = "";
				std::string label_value     = "";
				std::string user_id_text    = "";
				std::string user_id_value   = "";
				bool user_id_read           = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(stat, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read, float_text, float_value, float_read, increment_text, increment_value, increment_loop_write, date_text, date_value, date_read, string_text, string_value, string_read, label_text, label_value, user_id_text, user_id_value, user_id_read)
			} stat{};

			struct packed_stat
			{
				int radio_button_index = 0;

				std::string int_text  = "";
				std::string int_value = "";
				bool int_read         = false;

				std::string bool_text  = "";
				std::string bool_value = "";
				bool bool_read         = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(packed_stat, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read)
			} packed_stat{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(stat_editor, stat, packed_stat)
		} stat_editor{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(menu_settings, debug, tunables, notifications, player, protections, self, session, settings, spawn_vehicle, clone_pv, spoofing, vehicle, weapons, window, context_menu, esp, session_browser, ugc, reactions, world, stat_editor)
	};

	inline auto g = menu_settings();
}

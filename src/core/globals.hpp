#pragma once
#include <rage/rlSessionInfo.hpp>
#include <weapon/CAmmoInfo.hpp>
#include <weapon/CWeaponInfo.hpp>
#include "enums.hpp"
#include "file_manager.hpp"
#include <imgui.h>
#include <bitset>

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

		int m_mod_net_id = -1;
		int m_test_net_id = -1;

		rage::scrThread* m_hunt_the_beast_thread = nullptr;

		rage::scrThread* m_dance_thread = nullptr;
		rage::scrProgram* m_dance_program = nullptr;

		rage::scrThread* m_mission_creator_thread = nullptr;

		struct debug
		{
			struct logs
			{
				bool metric_logs{};

				bool script_hook_logs{};

				struct script_event
				{
					bool logs = false;

					bool filter_player = true;
					std::int8_t player_id = -1;

					NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_event, logs, filter_player, player_id)
				} script_event{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(logs, metric_logs, script_hook_logs, script_event)
			} logs{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(debug, logs)
		} debug{};

		struct tunables
		{
			bool disable_phone = false;
			bool no_idle_kick = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(tunables, disable_phone, no_idle_kick)
		} tunables{};
		
		struct notifications
		{
			struct pair
			{
				bool log = false;
				bool notify = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(pair, log, notify)
			};

			struct received_event
			{
				pair clear_ped_task{};
				pair kick_vote{};
				pair report_cash_spawn{};
				pair modder_detect{};
				pair request_control_event{};
				pair vehicle_temp_action{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(received_event, clear_ped_task, kick_vote, report_cash_spawn, modder_detect, request_control_event, vehicle_temp_action)
			} received_event{};

			struct script_event_handler
			{
				pair bounty{};
				pair ceo_ban{};
				pair ceo_kick{};
				pair ceo_money{};
				pair clear_wanted_level{};
				pair crash{};
				pair fake_deposit{};
				pair force_mission{};
				pair force_teleport{};
				pair gta_banner{};
				pair mc_teleport{};
				pair network_bail{};
				pair personal_vehicle_destroyed{};
				pair remote_off_radar{};
				pair rotate_cam{};
				pair send_to_cutscene{};
				pair send_to_location{};
				pair sound_spam{};
				pair spectate{};
				pair switch_player_model{};
				pair transaction_error{};
				pair tse_freeze{};
				pair tse_sender_mismatch{};
				pair vehicle_kick{};
				pair teleport_to_warehouse{};
				pair start_activity{};
				pair null_function_kick{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_event_handler,
					bounty, ceo_ban, ceo_kick, clear_wanted_level, crash, fake_deposit, force_mission, force_teleport,
					gta_banner, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam,
					send_to_cutscene, send_to_location, sound_spam, spectate, switch_player_model, transaction_error,
					tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, start_activity, null_function_kick)
			} script_event_handler{};

			pair gta_thread_kill{};
			pair gta_thread_start{};

			pair network_player_mgr_init{};
			pair network_player_mgr_shutdown{};

			struct player_join
			{
				bool above_map = true;
				bool log = false;
				bool notify = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(player_join, above_map, log, notify)
			} player_join{};
			pair player_leave{};

			pair reports{};

			pair send_net_info_to_lobby{};
			pair transaction_rate_limit{};
			pair mismatch_sync_type{};
			pair out_of_allowed_range_sync_type{};
			pair invalid_sync{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(notifications,
				received_event, script_event_handler, gta_thread_kill, gta_thread_start, network_player_mgr_init,
				network_player_mgr_shutdown, player_join, player_leave, reports, send_net_info_to_lobby,
				transaction_rate_limit, mismatch_sync_type, out_of_allowed_range_sync_type, invalid_sync)
		} notifications{};
		
		struct player
		{
			int character_slot = 1;
			int set_level = 130;
			bool spectating = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(player, character_slot, set_level, spectating)
		} player{};

		struct protections 
		{
			struct script_events 
			{
				bool bounty = true;
				bool ceo_ban = true;
				bool ceo_kick = true;
				bool ceo_money = true;
				bool clear_wanted_level = true;
				bool crash = true;
				bool fake_deposit = true;
				bool force_mission = true;
				bool force_teleport = true;
				bool gta_banner = true;
				bool mc_teleport = true;
				bool network_bail = true;
				bool personal_vehicle_destroyed = true;
				bool remote_off_radar = true;
				bool rotate_cam = true;
				bool send_to_cutscene = true;
				bool send_to_location = true;
				bool sound_spam = true;
				bool spectate = true;
				bool switch_player_model = true;
				bool transaction_error = true;
				bool vehicle_kick = true;
				bool teleport_to_warehouse = true;
				bool start_activity = true;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_events,
					bounty, ceo_ban, ceo_kick, ceo_money, clear_wanted_level, crash, fake_deposit,
					force_mission, force_teleport, gta_banner, mc_teleport, network_bail,
					personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene,
					send_to_location, sound_spam, spectate, switch_player_model, transaction_error,
					vehicle_kick, teleport_to_warehouse, start_activity)
			} script_events{};

			bool script_host_kick = true;
			bool rid_join = false;
			bool lessen_breakups = false; // disabled by default due to anticheat concerns

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(protections, script_events, script_host_kick, rid_join, lessen_breakups)
		} protections{};

		struct self 
		{
			bool clean_player = false;
			bool force_wanted_level = false;
			bool free_cam = false;
			bool invisibility = false;
			bool local_visibility = true;
			bool never_wanted = false;
			bool no_ragdoll = false;
			bool noclip = false;
			bool off_radar = false;
			bool super_run = false;
			bool no_collision = false;
			bool unlimited_oxygen = false;
			bool no_water_collision = false;
			int wanted_level = 0;
			bool god_mode = false;
			bool proof_bullet = false;
			bool proof_fire = false;
			bool proof_collision = false;
			bool proof_melee = false;
			bool proof_explosion = false;
			bool proof_steam = false;
			bool proof_drown = false;
			bool proof_water = false;
			uint32_t proof_mask = 0;
			bool hide_radar = false;
			bool hide_ammo = false;
			int selected_hud_component = 1;
			std::array<bool, 22> hud_components_states = { false };
			bool force_show_hud_element = false;
			bool force_show_hud = false;
			bool mobile_radio = false;
			bool fast_respawn = false;
			bool auto_tp = false;

			// do not save below entries
			bool dance_mode = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(self,
				clean_player, force_wanted_level, free_cam, invisibility, local_visibility, never_wanted, no_ragdoll,
				noclip, off_radar, super_run, no_collision, unlimited_oxygen, no_water_collision, wanted_level, god_mode,
				proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_drown, proof_water,
				proof_mask, hide_radar, hide_ammo, selected_hud_component, hud_components_states, force_show_hud_element,
				force_show_hud, mobile_radio, fast_respawn, auto_tp)
		} self{};

		struct session
		{
			int local_weather = 0;
			bool override_time = {};
			bool override_weather = false;
			struct custom_time
			{
				int hour{}, minute{}, second{};

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(custom_time, hour, minute, second)
			} custom_time;
			bool disable_chat_filter = false;
			bool log_chat_messages = false;
			bool log_text_messages = false;
			bool decloak_players = false;
			bool force_session_host = false;
			bool force_script_host = false;
			bool player_magnet_enabled = false;
			int player_magnet_count = 32;
			bool is_team = false;
			bool name_spoof_enabled = false;
			bool advertise_menu = false;
			std::string spoofed_name = "";
			bool join_in_sctv_slots = false;

			const char chat_command_prefix = '/';
			const char chat_output_prefix = '>';

			bool chat_commands = false;
			CommandAccessLevel chat_command_default_access_level = CommandAccessLevel::FRIENDLY;

			bool kick_chat_spammers = false;
			bool kick_host_when_forcing_host = false;

			bool explosion_karma = false;
			bool damage_karma = false;

			bool disable_traffic = false;
			bool disable_peds = false;
			bool force_thunder = false;

			bool block_ceo_money = false;
			bool randomize_ceo_colors = false;

			int send_to_apartment_idx = 1;
			int send_to_warehouse_idx = 1;

			// not to be saved
			bool join_queued = false;
			rage::rlSessionInfo info;
			bool never_wanted_all = false;
			bool off_radar_all = false;
			bool semi_godmode_all = false;
			bool wanted_level_all = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session,
				local_weather, override_time, override_weather, custom_time, disable_chat_filter, log_chat_messages,
				log_text_messages, decloak_players, force_session_host, force_script_host, player_magnet_enabled,
				player_magnet_count, is_team, name_spoof_enabled, advertise_menu, spoofed_name, join_in_sctv_slots,
				kick_chat_spammers, kick_host_when_forcing_host, explosion_karma, damage_karma, disable_traffic,
				disable_peds, force_thunder, block_ceo_money, randomize_ceo_colors, send_to_apartment_idx, send_to_warehouse_idx,
				chat_commands, chat_command_default_access_level)
		} session{};

		struct settings
		{
			struct hotkeys
			{
				bool editing_menu_toggle = false;
				int menu_toggle = VK_INSERT;
				int teleport_waypoint = 0;
				int teleport_objective = 0;
				int noclip = 0;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(hotkeys, editing_menu_toggle, menu_toggle, teleport_waypoint, teleport_objective, noclip)
			} hotkeys{};

			bool dev_dlc = false;
			
			NLOHMANN_DEFINE_TYPE_INTRUSIVE(settings, hotkeys, dev_dlc)
		} settings{};

		struct spawn_vehicle
		{
			bool preview_vehicle = false;
			bool spawn_inside = false;
			bool spawn_maxed = false;
			std::string plate = "";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawn_vehicle, preview_vehicle, spawn_inside, spawn_maxed, plate)
		} spawn_vehicle{};

		struct clone_pv
		{
			bool preview_vehicle = false;
			bool spawn_inside = false;
			bool spawn_clone = false;
			bool spawn_maxed = false;
			bool clone_plate = false;
			std::string plate = "";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(clone_pv, preview_vehicle, spawn_inside, spawn_clone, spawn_maxed, clone_plate, plate)
		} clone_pv{};

		struct spawn_ped
		{
			bool preview_ped = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawn_ped, preview_ped)
		} spawn_ped{};

		struct spoofing
		{
			bool spoof_username = false;
			bool spoof_local_username = false;
			std::string username = "";

			// enabling this by default causes confusion and many get dropped out of their sessions
			bool spoof_ip = false;
			std::array<int, 4> ip_address = { 42, 42, 42, 42 };

			bool spoof_rockstar_id = false;
			uint64_t rockstar_id = 0;

			bool spoof_cheater = false;

			bool spoof_hide_god = true;
			bool spoof_hide_spectate = true;

			bool spoof_rockstar_dev = false;
			bool spoof_rockstar_qa = false;

			bool spoof_crew_data = false;
			std::string crew_tag = "";
			bool rockstar_crew = false;
			bool square_crew_tag = false;

			bool spoof_session_region_type = false;
			int session_region_type = 0;
			bool spoof_session_language = false;
			int session_language = 0;
			bool spoof_session_player_count = false;
			int session_player_count = 25;

			// don't save
			bool should_spoof_rockstar_id = false;
			uint64_t applied_spoof_rockstar_id = 0;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spoofing,
				spoof_username, spoof_local_username, username, spoof_ip, ip_address, spoof_rockstar_id, rockstar_id,
				spoof_cheater, spoof_hide_god, spoof_hide_spectate, spoof_rockstar_dev, spoof_rockstar_qa, spoof_crew_data,
				crew_tag, rockstar_crew, square_crew_tag, spoof_session_region_type, session_region_type, spoof_session_language,
				session_language, spoof_session_player_count, session_player_count)
		} spoofing{};

		struct vehicle
		{
			struct speedo_meter
			{
				float x = .9f;
				float y = .72f;

				bool enabled = false;
				bool left_side = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(speedo_meter, x, y, enabled, left_side)
			} speedo_meter{};

			struct fly
			{
				bool dont_stop = false;
				bool enabled = false;
				bool no_collision = false;
				bool stop_on_exit = false;
				float speed = 1;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(fly, dont_stop, enabled, no_collision, stop_on_exit, speed)
			} fly{};

			struct rainbow_paint
			{
				RainbowPaintType type = RainbowPaintType::Off;
				bool neon = false;
				bool primary = false;
				bool secondary = false;
				bool smoke = false;
				int speed = 0;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(rainbow_paint, type, neon, primary, secondary, smoke, speed)
			} rainbow_paint{};

			SpeedUnit speed_unit = SpeedUnit::MIPH;

			bool god_mode = false;
			bool proof_bullet = false;
			bool proof_fire = false;
			bool proof_collision = false;
			bool proof_melee = false;
			bool proof_explosion = false;
			bool proof_steam = false;
			bool proof_water = false;
			uint32_t proof_mask = 0;

			AutoDriveDestination auto_drive_destination = AutoDriveDestination::STOPPED;
			AutoDriveStyle auto_drive_style = AutoDriveStyle::LAW_ABIDING;
			float auto_drive_speed = 1;
			bool auto_turn_signals = false;
			eBoostBehaviors boost_behavior = eBoostBehaviors::DEFAULT;
			bool drive_on_water = false;
			bool horn_boost = false;
			bool instant_brake = false;
			bool block_homing = true;
			bool ls_customs = false; // don't save this to disk
			bool seatbelt = false;
			bool turn_signals = false;
			bool vehicle_jump = false;
			bool keep_vehicle_repaired = false;
			bool no_water_collision = false;
			bool disable_engine_auto_start = false;
			bool change_engine_state_immediately = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(vehicle,
				speedo_meter, fly, rainbow_paint, speed_unit, god_mode,
				proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_water, proof_mask,
				auto_drive_destination, auto_drive_style, auto_drive_speed, auto_turn_signals, boost_behavior,
				drive_on_water, horn_boost, instant_brake, block_homing, seatbelt, turn_signals, vehicle_jump,
				keep_vehicle_repaired, no_water_collision, disable_engine_auto_start, change_engine_state_immediately)
		} vehicle{};

		struct weapons
		{
			struct ammo_special
			{
				bool toggle = false;
				eAmmoSpecialType type = eAmmoSpecialType::None;
				eExplosionTag explosion_tag = eExplosionTag::DONTCARE;

				NLOHMANN_JSON_SERIALIZE_ENUM(eAmmoSpecialType, {
					{ eAmmoSpecialType::None, "none" },
					{ eAmmoSpecialType::ArmorPiercing, "armor_piercing" },
					{ eAmmoSpecialType::Explosive, "explosive" },
					{ eAmmoSpecialType::FMJ, "fmj" },
					{ eAmmoSpecialType::HollowPoint, "hollow_point" },
					{ eAmmoSpecialType::Incendiary, "incendiary" },
					{ eAmmoSpecialType::Tracer, "tracer" },
				})
				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ammo_special, toggle, type, explosion_tag)
			} ammo_special{};

			CustomWeapon custom_weapon = CustomWeapon::NONE;
			bool force_crosshairs = false;
			bool infinite_ammo = false;
			bool infinite_mag = false;
			float increased_damage = 1;
			bool no_recoil = false;
			bool no_spread = false;
			std::string vehicle_gun_model = "bus";
			bool bypass_c4_limit = false;
			bool rapid_fire = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(weapons,
				ammo_special, custom_weapon, force_crosshairs, infinite_ammo, infinite_mag, increased_damage, no_recoil,
				no_spread, vehicle_gun_model, bypass_c4_limit, rapid_fire)
		} weapons{};

		struct window
		{
			ImU32 color = 3357612055;
			float gui_scale = 1.f;

			ImFont* font_title = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small = nullptr;
			ImFont* font_icon = nullptr;

			bool switched_view = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(window, color, gui_scale, switched_view)
		} window{};

		struct context_menu
		{
			bool enabled = false;

			uint8_t allowed_entity_types =
				static_cast<uint8_t>(ContextEntityType::PED) |
				static_cast<uint8_t>(ContextEntityType::PLAYER) |
				static_cast<uint8_t>(ContextEntityType::VEHICLE) |
				static_cast<uint8_t>(ContextEntityType::OBJECT);

			ImU32 selected_option_color = 4278255360;

			bool bounding_box_enabled = true;
			ImU32 bounding_box_color = 4278255360;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(context_menu,
				enabled, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
		} context_menu{};

		struct esp
		{
			bool enabled = true;
			bool hide_self = true;
			float global_render_distance[2] = { 0.f, 600.f };
			float tracer_render_distance[2] = { 200.f, 600.f };
			float box_render_distance[2] = { 0.f, 150.f };
			bool tracer = true;
			float tracer_draw_position[2] = { 0.5f, 1.f };
			bool box = true;
			bool health = true;
			bool armor = true;
			bool god = true;
			bool distance = true;
			bool name = true;
			bool change_esp_color_from_dist = false;
			bool scale_health_from_dist = false;
			bool scale_armor_from_dist = false;
			float distance_threshold[2] = { 100.f, 200.f };
			ImU32 enemy_color = 4281479904;
			ImU32 enemy_near_color = 4283794943;
			ImU32 default_color = 4285713522;
			ImU32 friend_color = 4293244509;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(esp,
				enabled, hide_self, global_render_distance, tracer_render_distance, box_render_distance, tracer, tracer_draw_position,
				box, health, armor, god, distance, name, change_esp_color_from_dist, scale_health_from_dist, scale_armor_from_dist,
				distance_threshold, enemy_color, enemy_near_color, default_color, friend_color)
		} esp{};

		struct session_browser
		{
			bool region_filter_enabled = true;
			int region_filter = 0;

			bool language_filter_enabled = false;
			int language_filter = 0;

			bool player_count_filter_enabled = false;
			int player_count_filter_minimum = 0;
			int player_count_filter_maximum = 32;

			int sort_method = 0;
			int sort_direction = 0;

			bool replace_game_matchmaking = false;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session_browser,
				region_filter_enabled, region_filter, language_filter_enabled, language_filter, player_count_filter_enabled,
				player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, replace_game_matchmaking)
		} session_browser{};


		NLOHMANN_DEFINE_TYPE_INTRUSIVE(menu_settings,
			debug, tunables, notifications, player, protections, self, session, settings, spawn_vehicle, clone_pv,
			spawn_ped, spoofing, vehicle, weapons, window, context_menu, esp, session_browser)
	};

	inline auto g = menu_settings();
}

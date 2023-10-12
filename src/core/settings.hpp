#pragma once
#include "backend/reactions/interloper_reaction.hpp"
#include "backend/reactions/reaction.hpp"
#include "enums.hpp"

#include <imgui.h>
#include <rage/rlSessionInfo.hpp>

#define TYPING_TICKS 3
#define ROCKET_LAUNCH_SPEED 1200
#define ROCKET_RANGE 1000
#define ROCKET_LOCK_ON_RANGE 500
#define ROCKET_TIME_BEFORE_HOMING 0.75
#define ROCKET_LIFETIME 15

class CNetGamePlayer;
enum class eNetObjType;

namespace rage
{
	class scrThread;
	class scrProgram;
}

namespace big
{
	struct remote_player_teleport
	{
		std::int16_t m_player_net_id;
		rage::fvector3 m_position;
	};

	class menu_settings
	{
	public:
		void init(const file& save_file);

		void attempt_save();
		bool load();
		bool write_default_config();

	private:
		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false);
		bool save();

	private:
		file m_save_file;

		nlohmann::json m_default_options;
		nlohmann::json m_options;

	public:
		CNetGamePlayer* m_syncing_player  = nullptr;
		eNetObjType m_syncing_object_type = (eNetObjType)-1;

		std::unordered_map<uint16_t, remote_player_teleport> m_remote_player_teleports;

		bool in_script_vm = false;

		struct tunables
		{
			bool disable_phone = false;
			bool no_idle_kick  = false;

		} tunables{};

		struct notifications
		{
			struct pair
			{
				bool log    = false;
				bool notify = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(pair, log, notify)
			};

			pair gta_thread_kill{}, gta_thread_start{};

			pair player_join, player_leave{};

			pair transaction_rate_limit{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(notifications, player_join, player_leave, transaction_rate_limit)
		} notifications{};

		struct reactions
		{
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
			reaction send_to_interior{"Send To Interior", "Blocked Send To Interior from %s", "%s tried to send me to an interior!"};
			reaction sound_spam{"Sound Spam", "Blocked Sound Spam from %s", "%s tried to spam annoying sounds at me!"};
			reaction spectate_notification{"Spectate Notification", "Blocked Spectate Notification from %s", "Blocked Spectate Notification from %s"};
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
			reaction report_cash_spawn{"Cash Spawn", "%s is spawning cash!", "%s is spawning cash!"};
			reaction modder_detection{"Modder Detection", "%s is detected as a modder!", "%s is detected as a modder!"};
			reaction game_anti_cheat_modder_detection{"Game Anti-Cheat Modder Detection", "%s is detected as a modder by the game anti-cheat!", "%s is detected as a modder by the game anti-cheat!"};
			reaction request_control_event{"Request Control Event", "Blocked Request Control Event from %s", "%s tried to mess with my vehicle!"};
			reaction report{"Report", "Blocked Report from %s", "%s tried to report me!"};
			reaction spectate{"Spectate", "%s is spectating you", "%s is spectating me!"};

			reaction gamer_instruction_kick{"Gamer Instruction Kick", "Blocked Gamer Instruction Kick from %s", "%s tried to kick me out!"};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(reactions, ceo_money, ceo_kick, clear_wanted_level, crash, end_session_kick, fake_deposit, force_mission, force_teleport, gta_banner, kick_from_interior, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate_notification, give_collectible, transaction_error, tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, trigger_business_raid, start_activity, start_script, null_function_kick, destroy_personal_vehicle, clear_ped_tasks, turn_into_beast, remote_wanted_level, remote_wanted_level_others, remote_ragdoll, kick_vote, report_cash_spawn, modder_detection, game_anti_cheat_modder_detection, request_control_event, report, gamer_instruction_kick, send_to_interior, spectate)
		} reactions{};

		struct player
		{
			bool spectating = false;
		} player{};

		struct protections
		{
			struct script_events
			{
				bool ceo_money                  = true;
				bool clear_wanted_level         = true;
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

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(script_events, ceo_money, clear_wanted_level, force_mission, force_teleport, gta_banner, mc_teleport, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate, give_collectible, vehicle_kick, teleport_to_warehouse, start_activity, send_sms)
			} script_events{};

			bool rid_join       = false;
			bool receive_pickup = false;
			bool admin_check    = true;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(protections, script_events, rid_join, receive_pickup, admin_check)
		} protections{};

		struct self
		{
			struct ptfx_effects
			{
				bool show          = false;
				float size         = 0.2f;
				const char* asset  = "scr_agencyheist";
				const char* effect = "scr_fbi_mop_drips";
			} ptfx_effects{};

			bool passive                      = false;
			bool free_cam                     = false;
			bool no_ragdoll                   = false;
			bool noclip                       = false;
			float noclip_aim_speed_multiplier = 0.25f;
			float noclip_speed_multiplier     = 20.f;
			bool off_radar                    = false;
			bool ghost_org                    = false;
			bool unlimited_oxygen             = false;
			bool god_mode                     = false;
			bool clean_player                 = false;

			struct hud
			{
				std::atomic_uint_fast8_t typing = 0;
			} hud{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(self, noclip_aim_speed_multiplier, noclip_speed_multiplier)
		} self{};

		struct session
		{
			bool log_chat_messages                 = false;
			bool decloak_players                   = false;
			bool force_session_host                = false;
			bool force_script_host                 = false;
			bool lock_session                      = false;
			bool allow_friends_into_locked_session = true;

			CommandAccessLevel chat_command_default_access_level = CommandAccessLevel::FRIENDLY;

			bool force_thunder = false;

			bool join_queued = false;
			rage::rlSessionInfo info;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session, log_chat_messages)
		} session{};

		struct settings
		{
			struct hotkeys
			{
				int menu_toggle = VK_INSERT;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(hotkeys, menu_toggle)
			} hotkeys{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(settings, hotkeys)
		} settings{};

		int spawn_vehicle_type = 0;

		struct spawn_vehicle
		{
			bool spawn_inside = false;
			bool spawn_maxed  = false;
			std::string plate = "";

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(spawn_vehicle, spawn_maxed, plate)
		} spawn_vehicle{};

		struct clone_pv
		{
			bool spawn_inside  = false;
			bool spawn_clone   = false;
			std::string garage = "";
		} clone_pv{};

		struct persist_car
		{
			bool spawn_inside                      = false;
			std::string persist_vehicle_sub_folder = "";
		} persist_car{};

		struct world
		{
			struct custom_time
			{
				bool override_time = {};
				int hour{}, minute{}, second{};
			} custom_time;

			struct nearby
			{
				bool ignore = false;

				struct auto_disarm
				{
					bool enable = false;
				} auto_disarm{};
			} nearby{};

			int local_weather = 0;
		} world{};

		struct spoofing
		{
			bool spoof_hide_god      = true;
			bool spoof_hide_spectate = true;
		} spoofing{};

		struct vehicle
		{
			bool god_mode            = false;
			bool block_homing        = false;
			bool seatbelt            = false;
			bool vehicle_jump        = false;
			bool keep_engine_running = false;
			bool all_vehs_in_heists  = false;
			bool veh_boost           = false;

			AutoDriveDestination auto_drive_destination = AutoDriveDestination::STOPPED;
			AutoDriveStyle auto_drive_style             = AutoDriveStyle::LAW_ABIDING;
			float auto_drive_speed                      = 8;

			struct vehicle_ammo_special
			{
				bool enabled                 = false;
				bool rocket_improve_tracking = true;

				float rocket_launch_speed       = ROCKET_LAUNCH_SPEED;
				float rocket_range              = ROCKET_RANGE;
				float rocket_lock_on_range      = ROCKET_LOCK_ON_RANGE;
				float rocket_time_before_homing = ROCKET_TIME_BEFORE_HOMING;
				float rocket_lifetime           = ROCKET_LIFETIME;

				float m_rocket_launch_speed       = 0;
				float m_rocket_range              = 0;
				float m_rocket_lock_on_range      = 0;
				float m_rocket_time_before_homing = 0;
				float m_rocket_lifetime           = 0;
			} vehicle_ammo_special{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(vehicle, auto_drive_destination, auto_drive_style, auto_drive_speed)
		} vehicle{};

		struct weapons
		{
			bool infinite_ammo = false;
			bool infinite_mag  = false;
			bool rapid_fire    = false;

			struct aimbot
			{
				bool enable    = false;
				float distance = 1000.f;
			} aimbot{};
		} weapons{};

		struct window
		{
			ImU32 background_color = 3696311571;
			ImU32 text_color       = 4294967295;
			ImU32 button_color     = 2947901213;
			ImU32 frame_color      = 2942518340;
			float gui_scale        = 1.f;

			ImFont* font_title     = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small     = nullptr;
			ImFont* font_icon      = nullptr;

			bool demo          = false;
			bool switched_view = true;

			struct ingame_overlay
			{
				bool opened                = true;
				bool show_with_menu_opened = false;

				bool show_fps           = true;
				bool show_indicators    = true;
				bool show_game_versions = true;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ingame_overlay, opened, show_with_menu_opened, show_fps, show_indicators, show_game_versions)
			} ingame_overlay{};

			struct ingame_overlay_indicators
			{
				bool show_player_godmode  = true;
				bool show_vehicle_godmode = true;
				bool show_ammo            = false;

				NLOHMANN_DEFINE_TYPE_INTRUSIVE(ingame_overlay_indicators, show_player_godmode, show_vehicle_godmode, show_ammo)
			} ingame_overlay_indicators{};

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(window, background_color, text_color, button_color, frame_color, gui_scale, switched_view, ingame_overlay, ingame_overlay_indicators)
		} window{};

		struct context_menu
		{
			bool enabled = false;

			uint8_t allowed_entity_types = static_cast<uint8_t>(ContextEntityType::PED) | static_cast<uint8_t>(ContextEntityType::PLAYER) | static_cast<uint8_t>(ContextEntityType::VEHICLE) | static_cast<uint8_t>(ContextEntityType::OBJECT);

			ImU32 selected_option_color = 4278255360;

			bool bounding_box_enabled = true;
			ImU32 bounding_box_color  = 4278255360;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(context_menu, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
		} context_menu{};

		struct esp
		{
			bool enabled                    = true;
			float global_render_distance[2] = {0.f, 600.f};
			bool distance                   = true;
			ImU32 default_color             = 4285713522;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(esp, enabled, global_render_distance, distance, default_color)
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

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(session_browser, region_filter_enabled, region_filter, language_filter_enabled, language_filter, player_count_filter_enabled, player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, pool_filter_enabled, pool_filter)
		} session_browser{};

		struct persist_weapons
		{
			std::string weapon_loadout_file;

			NLOHMANN_DEFINE_TYPE_INTRUSIVE(persist_weapons, weapon_loadout_file)
		} persist_weapons{};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(menu_settings, notifications, protections, self, settings, spawn_vehicle, vehicle, window, context_menu, esp, session_browser, reactions, persist_weapons)
	};

	inline auto g = menu_settings();
}

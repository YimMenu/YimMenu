#pragma once
#include "backend/reactions/interloper_reaction.hpp"
#include "backend/reactions/reaction.hpp"
#include "core/data/color.hpp"
#include "core/data/hud_colors.hpp"
#include "core/data/ptfx_effects.hpp"
#include "core/data/remote_player_teleport.hpp"
#include "enums.hpp"
#include "file_manager.hpp"

#include <bitset>
#include <rage/rlSessionInfo.hpp>
#include <weapon/CAmmoInfo.hpp>
#include <weapon/CAmmoRocketInfo.hpp>
#include <weapon/CWeaponInfo.hpp>

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>

#define TYPING_TICKS 3

class CNetGamePlayer;
enum class eNetObjType;

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
		void init(const file& save_file);

		void attempt_save();
		bool load();
		bool write_default_config();

	private:
		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false);
		bool save();

	private:
		// Json Parser: Generator Ignore
		file m_save_file;

		// Json Parser: Generator Ignore
		nlohmann::json m_default_options;

		// Json Parser: Generator Ignore
		nlohmann::json m_options;

	public:
		// TODO: This shouldn't be here.
		CNetGamePlayer* m_syncing_player = nullptr;

		// TODO: This shouldn't be here.
		// Json Parser: Generator Ignore
		eNetObjType m_syncing_object_type = (eNetObjType)-1;

		// TODO: This shouldn't be here.
		// Json Parser: Generator Ignore
		int m_remote_controller_vehicle = -1;
		// TODO: This shouldn't be here.
		// Json Parser: Generator Ignore
		int m_remote_controlled_vehicle = -1;

		// TODO: This shouldn't be here.
		// Json Parser: Generator Ignore
		std::unordered_map<uint16_t, remote_player_teleport> m_remote_player_teleports;

		// TODO: This shouldn't be here.
		rage::scrThread* m_hunt_the_beast_thread = nullptr;

		// TODO: This shouldn't be here.
		rage::scrThread* m_dance_thread = nullptr;
		// TODO: This shouldn't be here.
		rage::scrProgram* m_dance_program = nullptr;

		// TODO: This shouldn't be here.
		rage::scrThread* m_mission_creator_thread = nullptr;

		struct cmd_executor_t
		{
			// Json Parser: Generator Ignore
			bool enabled = false;
		};
		// Json Parser: Generator Ignore
		cmd_executor_t cmd_executor{};

		// TODO: This shouldn't be here.
		rage::scrThread* m_modshop_thread = nullptr;

		// TODO: This shouldn't be here.
		// Json Parser: Generator Ignore
		bool in_script_vm = false;

		struct debug_t
		{
			struct logs_t
			{
				bool metric_logs{};
				bool packet_logs{};

				bool script_hook_logs{};

				struct script_event_t
				{
					bool logs = false;

					bool filter_player    = true;
					std::int8_t player_id = -1;

					// Json Parser: Ignore
					bool block_all = false;
				};
				script_event_t script_event{};
			};
			logs_t logs{};

			struct fuzzer_t
			{
				// Json Parser: Ignore
				bool enabled = false;

				// Json Parser: Ignore
				bool enabled_object_types[14];

				// TODO: This shouldn't be here.
				// Json Parser: Generator Ignore
				bool active = false;

				// TODO: This shouldn't be here.
				// Json Parser: Generator Ignore
				int thread_id = 0;

				// TODO: This shouldn't be here.
				// Json Parser: Generator Ignore
				std::int16_t syncing_object_id = -1;
			};
			// Json Parser: Ignore
			fuzzer_t fuzzer{};

			bool window_hook = false;
		};
		debug_t debug{};

		struct tunables_t
		{
			bool disable_phone = false;
			bool no_idle_kick  = false;
		};
		tunables_t tunables{};

		struct notifications_t
		{
			struct pair
			{
				bool log    = false;
				bool notify = false;
			};

			pair gta_thread_kill{};
			pair gta_thread_start{};

			pair network_player_mgr_init{};
			pair network_player_mgr_shutdown{};

			struct player_join_t
			{
				bool above_map = true;
				bool log       = false;
				bool notify    = false;
			};
			player_join_t player_join{};

			pair player_leave{};

			pair send_net_info_to_lobby{};
			pair transaction_rate_limit{};
			pair mismatch_sync_type{};
			pair out_of_allowed_range_sync_type{};
			pair invalid_sync{};
		};
		notifications_t notifications{};

		struct reactions_t
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
			interloper_reaction spectate_others{"Spectate Others", "%s is spectating %s!", "%s is spectating %s!", false, false};

			reaction gamer_instruction_kick{"Gamer Instruction Kick", "Blocked Gamer Instruction Kick from %s", "%s tried to kick me out!"};
		};
		reactions_t reactions{};

		struct player_t
		{
			bool spectating = false;
		};
		player_t player{};

		struct player_db_t
		{
			bool update_player_online_states   = true;
			bool notify_when_online            = false;
			bool notify_when_joinable          = true;
			bool notify_when_unjoinable        = false;
			bool notify_when_offline           = false;
			bool notify_on_session_type_change = false;
			bool notify_on_session_change      = false;
			bool notify_on_spectator_change    = false;
			bool notify_on_become_host         = false;
			bool notify_on_transition_change   = false;
			bool notify_on_mission_change      = false;
		};
		player_db_t player_db{};

		struct protections_t
		{
			struct script_events_t
			{
				bool bounty                     = true;
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
			};
			script_events_t script_events{};

			bool rid_join                = false;
			bool receive_pickup          = false;
			bool admin_check             = true;
			bool kick_rejoin             = true;
			bool force_relay_connections = false;
		};
		protections_t protections{};

		struct self_t
		{
			struct ptfx_effects_t
			{
				bool show  = false;
				float size = 0.2f;
				int select = 0;

				std::string asset = "scr_agencyheist";

				std::string effect = "scr_fbi_mop_drips";
			};
			ptfx_effects_t ptfx_effects{};

			struct ipls_t
			{
				int select = 0;
			};
			ipls_t ipls{};

			bool clean_player                 = false;
			bool force_wanted_level           = false;
			bool passive                      = false;
			bool free_cam                     = false;
			bool invisibility                 = false;
			bool local_visibility             = true;
			bool never_wanted                 = false;
			bool no_ragdoll                   = false;
			bool noclip                       = false;
			float noclip_aim_speed_multiplier = 0.25f;
			float noclip_speed_multiplier     = 20.f;
			bool off_radar                    = false;
			bool ghost_org                    = false;
			bool super_run                    = false;
			bool no_collision                 = false;
			bool unlimited_oxygen             = false;
			bool no_water_collision           = false;
			int wanted_level                  = 0;
			bool god_mode                     = false;
			bool part_water                   = false;
			bool proof_bullet                 = false;
			bool proof_fire                   = false;
			bool proof_collision              = false;
			bool proof_melee                  = false;
			bool proof_explosion              = false;
			bool proof_steam                  = false;
			bool proof_drown                  = false;
			bool proof_water                  = false;
			uint32_t proof_mask               = 0;
			bool mobile_radio                 = false;
			bool fast_respawn                 = false;
			bool auto_tp                      = false;
			bool super_jump                   = false;
			bool beast_jump                   = false;
			bool healthregen                  = false;
			float healthregenrate             = 1.0f;
			bool superman                     = false;
			bool custom_weapon_stop           = true;
			bool prompt_ambient_animations    = false;
			std::string persist_outfit        = "";
			bool persist_outfits_mis          = false;

			struct hud_t
			{
				bool color_override                                      = false;
				bool color_override_initialized                          = false;
				std::array<color, hud_colors.size()> hud_color_overrides = {};

				// Json Parser: Ignore
				std::array<color, hud_colors.size()> hud_color_defaults = {};

				bool hide_radar                            = false;
				bool hide_ammo                             = false;
				int selected_hud_component                 = 1;
				std::array<bool, 22> hud_components_states = {false};
				bool force_show_hud_element                = false;
				bool force_show_hud                        = false;

				// Json Parser: Generator Ignore
				std::atomic_uint_fast8_t typing = 0;
			};
			hud_t hud{};

			// Json Parser: Ignore
			bool dance_mode = false;
		};
		self_t self{};

		struct session_t
		{
			bool log_chat_messages                 = false;
			bool log_text_messages                 = false;
			bool decloak_players                   = false;
			bool unhide_players_from_player_list   = true;
			bool force_session_host                = false;
			bool force_script_host                 = false;
			bool player_magnet_enabled             = false;
			int player_magnet_count                = 32;
			bool is_team                           = false;
			bool join_in_sctv_slots                = false;
			bool lock_session                      = false;
			bool allow_friends_into_locked_session = false;

			// TODO: This shouldn't be here.
			// Json Parser: Generator Ignore
			const char chat_command_prefix = '/';
			// TODO: This shouldn't be here.
			// Json Parser: Generator Ignore
			const char chat_output_prefix = '>';

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

			// TODO: This shouldn't be here.
			// Json Parser: Generator Ignore
			bool join_queued = false;

			// TODO: This shouldn't be here.
			// Json Parser: Generator Ignore
			rage::rlSessionInfo info;

			// Json Parser: Ignore
			bool never_wanted_all = false;
			// Json Parser: Ignore
			bool off_radar_all = false;
			// Json Parser: Ignore
			bool semi_godmode_all = false;
			// Json Parser: Ignore
			bool wanted_level_all = false;
			// Json Parser: Ignore
			bool vehicle_fix_all = false;

			bool show_cheating_message = false;
			bool anonymous_bounty      = true;

			bool fast_join = false;
		};
		session_t session{};

		struct settings_t
		{
			bool dev_dlc = false;

			struct hotkeys_t
			{
				bool editing_menu_toggle = false;

				// TODO: This shouldn't be here.
				// Json Parser: Generator Ignore
				std::atomic<bool> is_mp_chat_active;

				int menu_toggle             = VK_INSERT;
				int teleport_waypoint       = 0;
				int teleport_objective      = 0;
				int teleport_pv             = 0;
				int teleport_selected       = 0;
				int noclip                  = 0;
				int vehicle_flymode         = 0;
				int bringvehicle            = 0;
				int invis                   = 0;
				int heal                    = 0;
				int fill_inventory          = 0;
				int skip_cutscene           = 0;
				int freecam                 = 0;
				int superrun                = 0;
				int passive                 = 0;
				int superjump               = 0;
				int beastjump               = 0;
				int invisveh                = 0;
				int localinvisveh           = 0;
				int fill_ammo               = 0;
				int fast_quit               = 0;
				int cmd_excecutor           = 'U';
				int repairpv                = 0;
				int open_vehicle_controller = 0;
				int clear_wanted            = 0;
				int random_ped_components   = 0;
			};
			hotkeys_t hotkeys{};
		};
		settings_t settings{};

		struct spawn_vehicle_t
		{
			bool preview_vehicle = false;
			bool spawn_inside    = false;
			bool spawn_maxed     = false;
			std::string plate    = "";
			int spawn_type       = 0;
		};
		spawn_vehicle_t spawn_vehicle{};

		struct clone_pv_t
		{
			bool preview_vehicle = false;
			bool spawn_inside    = false;
			bool spawn_clone     = false;
			bool spawn_maxed     = false;
			bool clone_plate     = false;
			std::string plate    = "";
			std::string garage   = "";
		};
		clone_pv_t clone_pv{};

		struct persist_car_t
		{
			bool preview_vehicle                   = false;
			bool spawn_inside                      = false;
			std::string persist_vehicle_sub_folder = "";
		};
		persist_car_t persist_car{};

		struct world_t
		{
			struct orbital_drone_t
			{
				// Json Parser: Ignore
				bool enabled = false;

				bool detect_player       = false;
				float nav_ovverride_fast = 3.f;
				float nav_ovverride_slow = 0.25f;
			};
			orbital_drone_t orbital_drone{};

			struct train_t
			{
				bool drive_train  = false;
				bool derail_train = false;
			};
			train_t train{};

			struct water_t
			{
				bool part_water = false;
			};
			water_t water{};

			struct spawn_ped_t
			{
				bool preview_ped       = false;
				bool spawn_invincible  = false;
				bool spawn_invisible   = false;
				bool spawn_as_attacker = false;
			};
			spawn_ped_t spawn_ped{};

			struct custom_time_t
			{
				bool override_time = {};
				int hour{};
				int minute{};
				int second{};

			};
            custom_time_t custom_time{};

			struct blackhole_t
			{
				// Json Parser: Ignore
				bool enable = false;

				bool include_peds     = false;
				bool include_vehicles = false;

				float scale    = 6.f;
				float color[3] = {1, 1, 1};
				int alpha      = 150;

				// Json Parser: Generator Ignore
				rage::fvector3 pos;
			};
			blackhole_t blackhole{};

			struct nearby_t
			{
				bool ignore     = false;
				bool ped_rain   = false;
				bool veh_rain   = false;
				bool high_alert = false;
				bool ped_rush   = false;
				bool combative  = false;

				struct auto_disarm_t
				{
					bool enable     = false;
					bool neutralize = false;
				};
				auto_disarm_t auto_disarm{};
			};
			nearby_t nearby{};

			struct model_swapper_t
			{
				std::vector<std::pair<std::string, std::string>> models;

				// TODO: This shouldn't be here
				// Json Parser: Generator Ignore
				std::mutex m;

				// Json Parser: Ignore
				bool update = false;
			};
			model_swapper_t model_swapper{};


			bool override_weather = false;
			int local_weather     = 0;

			bool blackout = false;
		};
		world_t world{};

		struct spoofing_t
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

			bool spoof_session_region_type      = false;
			int session_region_type             = 0;
			bool spoof_session_language         = false;
			int session_language                = 0;
			bool spoof_session_player_count     = false;
			int session_player_count            = 25;
			bool spoof_session_bad_sport_status = false;
			bool session_bad_sport              = false;

			bool voice_chat_audio = false;
		};
		spoofing_t spoofing{};

		struct vehicle_t
		{
			struct speedo_meter_t
			{
				float x = .9f;
				float y = .72f;

				bool enabled           = false;
				bool left_side         = false;
				bool show_current_gear = true;
			};
			speedo_meter_t speedo_meter{};

			struct fly_t
			{
				bool dont_stop    = false;
				bool enabled      = false;
				bool no_collision = false;
				bool stop_on_exit = false;
				float speed       = 100;
			};
			fly_t fly{};

			struct rainbow_paint_t
			{
				RainbowPaintType type = RainbowPaintType::Off;
				bool neon             = false;
				bool primary          = false;
				bool secondary        = false;
				bool smoke            = false;
				int speed             = 1;
			};
			rainbow_paint_t rainbow_paint{};

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

			// Json Parser: Ignore
			bool ls_customs = false;

			bool seatbelt                        = false;
			bool turn_signals                    = false;
			bool vehicle_jump                    = false;
			bool keep_vehicle_repaired           = false;
			bool no_water_collision              = false;
			bool disable_engine_auto_start       = false;
			bool change_engine_state_immediately = false;
			bool keep_engine_running             = false;
			bool keep_vehicle_clean              = false;
			bool vehinvisibility                 = false;
			bool localveh_visibility             = false;
			bool keep_on_ground                  = false;
			bool no_collision                    = false;
			bool unlimited_weapons               = false;
			bool siren_mute                      = false;
			bool all_vehs_in_heists              = false;

			struct vehicle_ammo_special_t
			{
				bool enabled                       = false;
				eAmmoSpecialType type              = eAmmoSpecialType::None;
				eExplosionTag explosion_tag        = eExplosionTag::EXP_TAG_ROGUE_CANNON;
				float speed                        = 2000;
				float time_between_shots           = 0.04;
				float alternate_wait_time          = -1;
				float weapon_range                 = 250;
				float rocket_time_between_shots    = 0.66;
				float rocket_alternate_wait_time   = 0.66;
				float rocket_lock_on_range         = 500;
				float rocket_range                 = 1000;
				float rocket_reload_time           = -1;
				eExplosionTag rocket_explosion_tag = eExplosionTag::TANKSHELL;
				float rocket_lifetime              = 15;
				float rocket_launch_speed          = 1200;
				float rocket_time_before_homing    = 0.75;
				bool rocket_improve_tracking       = true;
			};
			vehicle_ammo_special_t vehicle_ammo_special{};
		};
		vehicle_t vehicle{};

		struct weapons_t
		{
			struct ammo_special_t
			{
				bool toggle                 = false;
				eAmmoSpecialType type       = eAmmoSpecialType::None;
				eExplosionTag explosion_tag = eExplosionTag::DONTCARE;
			};
			ammo_special_t ammo_special{};

			struct gravity_gun_t
			{
				bool launch_on_release = false;
			};
			gravity_gun_t gravity_gun{};

			struct paintgun_t
			{
				bool rainbow = false;
				float speed  = 1.f;
				float col[4] = {0.f, 0.f, 1.f, 1.f};
			};
			paintgun_t paintgun{};

			struct aimbot_t
			{
				bool enable           = false;
				bool smoothing        = true;
				float smoothing_speed = 2.f;

				// Json Parser: Ignore
				bool on_player = true;

				// Json Parser: Ignore
				bool on_enemy = false;

				// Json Parser: Ignore
				bool on_police = false;

				// Json Parser: Ignore
				bool on_npc = false;

				float fov              = 90.f;
				float distance         = 200.f;
				uint32_t selected_bone = 0x796E; // Default to head
			};
			aimbot_t aimbot{};

			CustomWeapon custom_weapon    = CustomWeapon::NONE;
			bool infinite_ammo            = false;
			bool always_full_ammo         = false;
			bool infinite_mag             = false;
			float increased_damage        = 1;
			bool increase_damage          = false;
			bool no_recoil                = false;
			bool no_spread                = false;
			std::string vehicle_gun_model = "bus";
			bool increased_c4_limit       = false;
			bool increased_flare_limit    = false;
			bool rapid_fire               = false;
			bool interior_weapon          = false;
			bool triggerbot               = false;
			bool infinite_range           = false;
			bool enable_weapon_hotkeys    = false;
			std::map<int, std::vector<uint32_t>> weapon_hotkeys{};
		};
		weapons_t weapons{};

		struct window_t
		{
			ImU32 background_color = 3696311571;
			ImU32 text_color       = 4294967295;
			ImU32 button_color     = 2947901213;
			ImU32 frame_color      = 2942518340;
			float gui_scale        = 1.f;

			// Those ptr shouldn't be here...
			ImFont* font_title     = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small     = nullptr;
			ImFont* font_icon      = nullptr;

			bool demo          = false;
			bool switched_view = true;

			struct ingame_overlay_t
			{
				bool opened                = true;
				bool show_with_menu_opened = false;

				bool show_fps              = true;
				bool show_indicators       = true;
				bool show_players          = true;
				bool show_time             = true;
				bool show_replay_interface = true;
				bool show_position         = false;
				bool show_game_versions    = true;
			};
			ingame_overlay_t ingame_overlay{};

			struct ingame_overlay_indicators_t
			{
				bool show_player_godmode   = true;
				bool show_off_radar        = true;
				bool show_vehicle_godmode  = true;
				bool show_never_wanted     = true;
				bool show_infinite_ammo    = false;
				bool show_always_full_ammo = false;
				bool show_infinite_mag     = false;
				bool show_aimbot           = false;
				bool show_triggerbot       = false;
				bool show_invisibility     = false;
			};
			ingame_overlay_indicators_t ingame_overlay_indicators{};

			struct vehicle_control_t
			{
				// Json Parser: Ignore
				bool opened                 = false;
				bool operation_animation    = true;
				bool render_distance_on_veh = false;
				float max_summon_range      = 200.f;
			} vehicle_control{};
		};
		window_t window{};

		struct context_menu_t
		{
			bool enabled = false;

			uint8_t allowed_entity_types = static_cast<uint8_t>(ContextEntityType::PED) | static_cast<uint8_t>(ContextEntityType::PLAYER) | static_cast<uint8_t>(ContextEntityType::VEHICLE) | static_cast<uint8_t>(ContextEntityType::OBJECT);

			ImU32 selected_option_color = 4278255360;

			bool bounding_box_enabled = true;
			ImU32 bounding_box_color  = 4278255360;
		};
		context_menu_t context_menu{};

		struct esp_t
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
		};
		esp_t esp{};

		struct session_browser_t
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
		};
		session_browser_t session_browser{};

		struct ugc_t
		{
			bool infinite_model_memory;
		};
		ugc_t ugc{};

		struct stat_editor_t
		{
			struct stat_t
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
			};
			stat_t stat{};

			struct packed_stat_t
			{
				int radio_button_index = 0;

				std::string int_text  = "";
				std::string int_value = "";
				bool int_read         = false;

				std::string bool_text  = "";
				std::string bool_value = "";
				bool bool_read         = false;
			};
			packed_stat_t packed_stat{};
		};
		stat_editor_t stat_editor{};

		struct lua_t
		{
			bool enable_auto_reload_changed_scripts = false;
		};
		lua_t lua{};

		struct persist_weapons_t
		{
			bool enabled = false;
			std::string weapon_loadout_file;
		};
		persist_weapons_t persist_weapons{};

		struct vfx_t
		{
			bool enable_custom_sky_color = false;

			float azimuth_east[4]       = {1, 0, 0, 0};
			float azimuth_west[4]       = {1, 0, 0, 0};
			float azimuth_transition[4] = {1, 0, 0, 0};
			float zenith[4]             = {1, 0, 0, 0};

			float stars_intensity = 1;
		};
		vfx_t vfx{};
	};

	inline auto g = menu_settings();
}

// GENERATED BY settings_json_serde_gen.py
// Mark setting that must always be excluded from JSON serialization,
// even when generating the structural representation of the settings, with `// Json Parser: Generator Ignore`
// Mark setting that should not be persistently stored between multiple instances of the DLL being loaded with `// Json Parser: Ignore`
namespace big
{
//#define SERIALIZE_EVERYTHING
#ifdef SERIALIZE_EVERYTHING
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vfx_t, enable_custom_sky_color, azimuth_east, azimuth_west, azimuth_transition, zenith, stars_intensity)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::persist_weapons_t, enabled, weapon_loadout_file)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::lua_t, enable_auto_reload_changed_scripts)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t::packed_stat_t, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t::stat_t, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read, float_text, float_value, float_read, increment_text, increment_value, increment_loop_write, date_text, date_value, date_read, string_text, string_value, string_read, label_text, label_value, user_id_text, user_id_value, user_id_read)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t, stat, packed_stat)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::ugc_t, infinite_model_memory)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::session_browser_t, region_filter_enabled, region_filter, language_filter_enabled, language_filter, pool_filter_enabled, pool_filter, player_count_filter_enabled, player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, replace_game_matchmaking)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::esp_t, enabled, hide_self, global_render_distance, tracer_render_distance, box_render_distance, tracer, tracer_draw_position, box, health, armor, god, distance, name, change_esp_color_from_dist, scale_health_from_dist, scale_armor_from_dist, distance_threshold, enemy_color, enemy_near_color, default_color, friend_color)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::context_menu_t, enabled, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::vehicle_control_t, opened, operation_animation, render_distance_on_veh, max_summon_range)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::ingame_overlay_indicators_t, show_player_godmode, show_off_radar, show_vehicle_godmode, show_never_wanted, show_infinite_ammo, show_always_full_ammo, show_infinite_mag, show_aimbot, show_triggerbot, show_invisibility)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::ingame_overlay_t, opened, show_with_menu_opened, show_fps, show_indicators, show_players, show_time, show_replay_interface, show_position, show_game_versions)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t, background_color, text_color, button_color, frame_color, gui_scale, demo, switched_view, ingame_overlay, ingame_overlay_indicators, vehicle_control)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::aimbot_t, enable, smoothing, smoothing_speed, on_player, on_enemy, on_police, on_npc, fov, distance, selected_bone)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::paintgun_t, rainbow, speed, col)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::gravity_gun_t, launch_on_release)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::ammo_special_t, toggle, type, explosion_tag)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t, ammo_special, gravity_gun, paintgun, aimbot, custom_weapon, infinite_ammo, always_full_ammo, infinite_mag, increased_damage, increase_damage, no_recoil, no_spread, vehicle_gun_model, increased_c4_limit, increased_flare_limit, rapid_fire, interior_weapon, triggerbot, infinite_range, enable_weapon_hotkeys, weapon_hotkeys)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::vehicle_ammo_special_t, enabled, type, explosion_tag, speed, time_between_shots, alternate_wait_time, weapon_range, rocket_time_between_shots, rocket_alternate_wait_time, rocket_lock_on_range, rocket_range, rocket_reload_time, rocket_explosion_tag, rocket_lifetime, rocket_launch_speed, rocket_time_before_homing, rocket_improve_tracking)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::rainbow_paint_t, type, neon, primary, secondary, smoke, speed)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::fly_t, dont_stop, enabled, no_collision, stop_on_exit, speed)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::speedo_meter_t, x, y, enabled, left_side, show_current_gear)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t, speedo_meter, fly, rainbow_paint, speed_unit, god_mode, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_water, proof_mask, auto_drive_destination, auto_drive_style, auto_drive_speed, auto_turn_signals, boost_behavior, drive_on_water, horn_boost, instant_brake, block_homing, ls_customs, seatbelt, turn_signals, vehicle_jump, keep_vehicle_repaired, no_water_collision, disable_engine_auto_start, change_engine_state_immediately, keep_engine_running, keep_vehicle_clean, vehinvisibility, localveh_visibility, keep_on_ground, no_collision, unlimited_weapons, siren_mute, all_vehs_in_heists, vehicle_ammo_special)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::spoofing_t, hide_from_player_list, spoof_blip, blip_type, spoof_rank, rank, spoof_job_points, job_points, spoof_kd_ratio, kd_ratio, spoof_bad_sport, badsport_type, spoof_player_model, player_model, spoof_cheater, spoof_hide_god, spoof_hide_spectate, spoof_crew_data, crew_tag, rockstar_crew, square_crew_tag, spoof_session_region_type, session_region_type, spoof_session_language, session_language, spoof_session_player_count, session_player_count, spoof_session_bad_sport_status, session_bad_sport, voice_chat_audio)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::model_swapper_t, models, update)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::nearby_t::auto_disarm_t, enable, neutralize)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::nearby_t, ignore, ped_rain, veh_rain, high_alert, ped_rush, combative, auto_disarm)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::blackhole_t, enable, include_peds, include_vehicles, scale, color, alpha)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::custom_time_t, override_time, hour, minute, second)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::spawn_ped_t, preview_ped, spawn_invincible, spawn_invisible, spawn_as_attacker)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::water_t, part_water)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::train_t, drive_train, derail_train)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::orbital_drone_t, enabled, detect_player, nav_ovverride_fast, nav_ovverride_slow)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t, orbital_drone, train, water, spawn_ped, custom_time, blackhole, nearby, model_swapper, override_weather, local_weather, blackout)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::persist_car_t, preview_vehicle, spawn_inside, persist_vehicle_sub_folder)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::clone_pv_t, preview_vehicle, spawn_inside, spawn_clone, spawn_maxed, clone_plate, plate, garage)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::spawn_vehicle_t, preview_vehicle, spawn_inside, spawn_maxed, plate, spawn_type)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::settings_t::hotkeys_t, editing_menu_toggle, menu_toggle, teleport_waypoint, teleport_objective, teleport_pv, teleport_selected, noclip, vehicle_flymode, bringvehicle, invis, heal, fill_inventory, skip_cutscene, freecam, superrun, passive, superjump, beastjump, invisveh, localinvisveh, fill_ammo, fast_quit, cmd_excecutor, repairpv, open_vehicle_controller, clear_wanted, random_ped_components)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::settings_t, dev_dlc, hotkeys)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::session_t, log_chat_messages, log_text_messages, decloak_players, unhide_players_from_player_list, force_session_host, force_script_host, player_magnet_enabled, player_magnet_count, is_team, join_in_sctv_slots, lock_session, allow_friends_into_locked_session, chat_commands, chat_command_default_access_level, kick_chat_spammers, kick_host_when_forcing_host, explosion_karma, damage_karma, disable_traffic, disable_peds, force_thunder, block_ceo_money, randomize_ceo_colors, block_jobs, block_muggers, block_ceo_raids, send_to_apartment_idx, send_to_warehouse_idx, never_wanted_all, off_radar_all, semi_godmode_all, wanted_level_all, vehicle_fix_all, show_cheating_message, anonymous_bounty, fast_join)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::hud_t, color_override, color_override_initialized, hud_color_overrides, hud_color_defaults, hide_radar, hide_ammo, selected_hud_component, hud_components_states, force_show_hud_element, force_show_hud)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::ipls_t, select)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::ptfx_effects_t, show, size, select, asset, effect)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t, ptfx_effects, ipls, clean_player, force_wanted_level, passive, free_cam, invisibility, local_visibility, never_wanted, no_ragdoll, noclip, noclip_aim_speed_multiplier, noclip_speed_multiplier, off_radar, ghost_org, super_run, no_collision, unlimited_oxygen, no_water_collision, wanted_level, god_mode, part_water, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_drown, proof_water, proof_mask, mobile_radio, fast_respawn, auto_tp, super_jump, beast_jump, healthregen, healthregenrate, superman, custom_weapon_stop, prompt_ambient_animations, persist_outfit, persist_outfits_mis, hud, dance_mode)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::protections_t::script_events_t, bounty, ceo_money, clear_wanted_level, force_mission, force_teleport, gta_banner, mc_teleport, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate, give_collectible, vehicle_kick, teleport_to_warehouse, start_activity, send_sms)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::protections_t, script_events, rid_join, receive_pickup, admin_check, kick_rejoin, force_relay_connections)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::player_db_t, update_player_online_states, notify_when_online, notify_when_joinable, notify_when_unjoinable, notify_when_offline, notify_on_session_type_change, notify_on_session_change, notify_on_spectator_change, notify_on_become_host, notify_on_transition_change, notify_on_mission_change)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::player_t, spectating)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::reactions_t, bounty, ceo_kick, ceo_money, clear_wanted_level, crash, end_session_kick, fake_deposit, force_mission, force_teleport, gta_banner, kick_from_interior, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, send_to_interior, sound_spam, spectate_notification, give_collectible, transaction_error, tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, start_activity, start_script, null_function_kick, destroy_personal_vehicle, trigger_business_raid, turn_into_beast, remote_wanted_level, remote_wanted_level_others, clear_ped_tasks, remote_ragdoll, kick_vote, report_cash_spawn, modder_detection, game_anti_cheat_modder_detection, request_control_event, report, spectate, spectate_others, gamer_instruction_kick)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t::player_join_t, above_map, log, notify)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t::pair, log, notify)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t, gta_thread_kill, gta_thread_start, network_player_mgr_init, network_player_mgr_shutdown, player_join, player_leave, send_net_info_to_lobby, transaction_rate_limit, mismatch_sync_type, out_of_allowed_range_sync_type, invalid_sync)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::tunables_t, disable_phone, no_idle_kick)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t::fuzzer_t, enabled, enabled_object_types)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t::logs_t::script_event_t, logs, filter_player, player_id, block_all)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t::logs_t, metric_logs, packet_logs, script_hook_logs, script_event)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t, logs, fuzzer, window_hook)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings, debug, tunables, notifications, reactions, player, player_db, protections, self, session, settings, spawn_vehicle, clone_pv, persist_car, world, spoofing, vehicle, weapons, window, context_menu, esp, session_browser, ugc, stat_editor, lua, persist_weapons, vfx)
#else
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vfx_t, enable_custom_sky_color, azimuth_east, azimuth_west, azimuth_transition, zenith, stars_intensity)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::persist_weapons_t, enabled, weapon_loadout_file)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::lua_t, enable_auto_reload_changed_scripts)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t::packed_stat_t, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t::stat_t, radio_button_index, int_text, int_value, int_read, bool_text, bool_value, bool_read, float_text, float_value, float_read, increment_text, increment_value, increment_loop_write, date_text, date_value, date_read, string_text, string_value, string_read, label_text, label_value, user_id_text, user_id_value, user_id_read)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::stat_editor_t, stat, packed_stat)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::ugc_t, infinite_model_memory)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::session_browser_t, region_filter_enabled, region_filter, language_filter_enabled, language_filter, pool_filter_enabled, pool_filter, player_count_filter_enabled, player_count_filter_minimum, player_count_filter_maximum, sort_method, sort_direction, replace_game_matchmaking)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::esp_t, enabled, hide_self, global_render_distance, tracer_render_distance, box_render_distance, tracer, tracer_draw_position, box, health, armor, god, distance, name, change_esp_color_from_dist, scale_health_from_dist, scale_armor_from_dist, distance_threshold, enemy_color, enemy_near_color, default_color, friend_color)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::context_menu_t, enabled, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::vehicle_control_t, operation_animation, render_distance_on_veh, max_summon_range)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::ingame_overlay_indicators_t, show_player_godmode, show_off_radar, show_vehicle_godmode, show_never_wanted, show_infinite_ammo, show_always_full_ammo, show_infinite_mag, show_aimbot, show_triggerbot, show_invisibility)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t::ingame_overlay_t, opened, show_with_menu_opened, show_fps, show_indicators, show_players, show_time, show_replay_interface, show_position, show_game_versions)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::window_t, background_color, text_color, button_color, frame_color, gui_scale, demo, switched_view, ingame_overlay, ingame_overlay_indicators, vehicle_control)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::aimbot_t, enable, smoothing, smoothing_speed, fov, distance, selected_bone)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::paintgun_t, rainbow, speed, col)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::gravity_gun_t, launch_on_release)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t::ammo_special_t, toggle, type, explosion_tag)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::weapons_t, ammo_special, gravity_gun, paintgun, aimbot, custom_weapon, infinite_ammo, always_full_ammo, infinite_mag, increased_damage, increase_damage, no_recoil, no_spread, vehicle_gun_model, increased_c4_limit, increased_flare_limit, rapid_fire, interior_weapon, triggerbot, infinite_range, enable_weapon_hotkeys, weapon_hotkeys)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::vehicle_ammo_special_t, enabled, type, explosion_tag, speed, time_between_shots, alternate_wait_time, weapon_range, rocket_time_between_shots, rocket_alternate_wait_time, rocket_lock_on_range, rocket_range, rocket_reload_time, rocket_explosion_tag, rocket_lifetime, rocket_launch_speed, rocket_time_before_homing, rocket_improve_tracking)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::rainbow_paint_t, type, neon, primary, secondary, smoke, speed)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::fly_t, dont_stop, enabled, no_collision, stop_on_exit, speed)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t::speedo_meter_t, x, y, enabled, left_side, show_current_gear)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::vehicle_t, speedo_meter, fly, rainbow_paint, speed_unit, god_mode, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_water, proof_mask, auto_drive_destination, auto_drive_style, auto_drive_speed, auto_turn_signals, boost_behavior, drive_on_water, horn_boost, instant_brake, block_homing, seatbelt, turn_signals, vehicle_jump, keep_vehicle_repaired, no_water_collision, disable_engine_auto_start, change_engine_state_immediately, keep_engine_running, keep_vehicle_clean, vehinvisibility, localveh_visibility, keep_on_ground, no_collision, unlimited_weapons, siren_mute, all_vehs_in_heists, vehicle_ammo_special)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::spoofing_t, hide_from_player_list, spoof_blip, blip_type, spoof_rank, rank, spoof_job_points, job_points, spoof_kd_ratio, kd_ratio, spoof_bad_sport, badsport_type, spoof_player_model, player_model, spoof_cheater, spoof_hide_god, spoof_hide_spectate, spoof_crew_data, crew_tag, rockstar_crew, square_crew_tag, spoof_session_region_type, session_region_type, spoof_session_language, session_language, spoof_session_player_count, session_player_count, spoof_session_bad_sport_status, session_bad_sport, voice_chat_audio)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::model_swapper_t, models)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::nearby_t::auto_disarm_t, enable, neutralize)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::nearby_t, ignore, ped_rain, veh_rain, high_alert, ped_rush, combative, auto_disarm)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::blackhole_t, include_peds, include_vehicles, scale, color, alpha)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::custom_time_t, override_time, hour, minute, second)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::spawn_ped_t, preview_ped, spawn_invincible, spawn_invisible, spawn_as_attacker)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::water_t, part_water)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::train_t, drive_train, derail_train)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t::orbital_drone_t, detect_player, nav_ovverride_fast, nav_ovverride_slow)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::world_t, orbital_drone, train, water, spawn_ped, custom_time, blackhole, nearby, model_swapper, override_weather, local_weather, blackout)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::persist_car_t, preview_vehicle, spawn_inside, persist_vehicle_sub_folder)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::clone_pv_t, preview_vehicle, spawn_inside, spawn_clone, spawn_maxed, clone_plate, plate, garage)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::spawn_vehicle_t, preview_vehicle, spawn_inside, spawn_maxed, plate, spawn_type)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::settings_t::hotkeys_t, editing_menu_toggle, menu_toggle, teleport_waypoint, teleport_objective, teleport_pv, teleport_selected, noclip, vehicle_flymode, bringvehicle, invis, heal, fill_inventory, skip_cutscene, freecam, superrun, passive, superjump, beastjump, invisveh, localinvisveh, fill_ammo, fast_quit, cmd_excecutor, repairpv, open_vehicle_controller, clear_wanted, random_ped_components)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::settings_t, dev_dlc, hotkeys)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::session_t, log_chat_messages, log_text_messages, decloak_players, unhide_players_from_player_list, force_session_host, force_script_host, player_magnet_enabled, player_magnet_count, is_team, join_in_sctv_slots, lock_session, allow_friends_into_locked_session, chat_commands, chat_command_default_access_level, kick_chat_spammers, kick_host_when_forcing_host, explosion_karma, damage_karma, disable_traffic, disable_peds, force_thunder, block_ceo_money, randomize_ceo_colors, block_jobs, block_muggers, block_ceo_raids, send_to_apartment_idx, send_to_warehouse_idx, show_cheating_message, anonymous_bounty, fast_join)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::hud_t, color_override, color_override_initialized, hud_color_overrides, hide_radar, hide_ammo, selected_hud_component, hud_components_states, force_show_hud_element, force_show_hud)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::ipls_t, select)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t::ptfx_effects_t, show, size, select, asset, effect)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::self_t, ptfx_effects, ipls, clean_player, force_wanted_level, passive, free_cam, invisibility, local_visibility, never_wanted, no_ragdoll, noclip, noclip_aim_speed_multiplier, noclip_speed_multiplier, off_radar, ghost_org, super_run, no_collision, unlimited_oxygen, no_water_collision, wanted_level, god_mode, part_water, proof_bullet, proof_fire, proof_collision, proof_melee, proof_explosion, proof_steam, proof_drown, proof_water, proof_mask, mobile_radio, fast_respawn, auto_tp, super_jump, beast_jump, healthregen, healthregenrate, superman, custom_weapon_stop, prompt_ambient_animations, persist_outfit, persist_outfits_mis, hud)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::protections_t::script_events_t, bounty, ceo_money, clear_wanted_level, force_mission, force_teleport, gta_banner, mc_teleport, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate, give_collectible, vehicle_kick, teleport_to_warehouse, start_activity, send_sms)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::protections_t, script_events, rid_join, receive_pickup, admin_check, kick_rejoin, force_relay_connections)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::player_db_t, update_player_online_states, notify_when_online, notify_when_joinable, notify_when_unjoinable, notify_when_offline, notify_on_session_type_change, notify_on_session_change, notify_on_spectator_change, notify_on_become_host, notify_on_transition_change, notify_on_mission_change)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::player_t, spectating)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::reactions_t, bounty, ceo_kick, ceo_money, clear_wanted_level, crash, end_session_kick, fake_deposit, force_mission, force_teleport, gta_banner, kick_from_interior, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, send_to_interior, sound_spam, spectate_notification, give_collectible, transaction_error, tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, start_activity, start_script, null_function_kick, destroy_personal_vehicle, trigger_business_raid, turn_into_beast, remote_wanted_level, remote_wanted_level_others, clear_ped_tasks, remote_ragdoll, kick_vote, report_cash_spawn, modder_detection, game_anti_cheat_modder_detection, request_control_event, report, spectate, spectate_others, gamer_instruction_kick)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t::player_join_t, above_map, log, notify)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t::pair, log, notify)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::notifications_t, gta_thread_kill, gta_thread_start, network_player_mgr_init, network_player_mgr_shutdown, player_join, player_leave, send_net_info_to_lobby, transaction_rate_limit, mismatch_sync_type, out_of_allowed_range_sync_type, invalid_sync)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::tunables_t, disable_phone, no_idle_kick)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t::logs_t::script_event_t, logs, filter_player, player_id)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t::logs_t, metric_logs, packet_logs, script_hook_logs, script_event)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings::debug_t, logs, window_hook)
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(menu_settings, debug, tunables, notifications, reactions, player, player_db, protections, self, session, settings, spawn_vehicle, clone_pv, persist_car, world, spoofing, vehicle, weapons, window, context_menu, esp, session_browser, ugc, stat_editor, lua, persist_weapons, vfx)
#endif
}

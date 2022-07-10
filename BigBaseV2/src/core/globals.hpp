#pragma once
#include "CAmmoInfo.hpp"
#include "CWeaponInfo.hpp"
#include "enums.hpp"
#include "file_manager.hpp"
#include "imgui.h"
#include <bitset>

namespace big
{
	class menu_settings;
	inline menu_settings* g{};

	class menu_settings {
		nlohmann::json default_options;
		nlohmann::json options;

		struct debug
		{
			bool script_event_logging = false;
		};

		struct notifications
		{
			struct pair
			{
				bool log = false;
				bool notify = false;
			};

			struct
			{
				pair clear_ped_task{};
				pair report_cash_spawn{};
				pair modder_detect{};
				pair request_control_event{};
				pair vehicle_temp_action{};
			} received_event{};

			struct
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
				pair send_to_island{};
				pair sound_spam{};
				pair spectate{};
				pair transaction_error{};
				pair tse_freeze{};
				pair vehicle_kick{};
			} script_event_handler{};

			pair gta_thread_kill{};
			pair gta_thread_start{};

			pair net_array_error{};

			pair network_player_mgr_init{};
			pair network_player_mgr_shutdown{};

			struct
			{
				bool above_map = true;
				bool log = false;
				bool notify = false;
			} player_join;
			pair player_leave{};

			pair reports{};

			pair send_net_info_to_lobby{};
			pair transaction_rate_limit{};
			pair invalid_sync{};
		};

		struct player {
			int character_slot = 1;
			int set_level = 130;
			bool spectating = false;
		};

		struct protections {
			struct script_events {
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
				bool send_to_island = true;
				bool sound_spam = true;
				bool spectate = true;
				bool transaction_error = true;
				bool vehicle_kick = true;
			};

			script_events script_events{};
		};

		struct rgb {
			bool fade = false;
			bool spasm = false;
			int r = 255;
			int g = 0;
			int b = 0;
			int speed = 0;
		};

		struct self {
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
		};

		struct session
		{
			int local_weather = 0;
			bool override_time = {};
			bool override_weather = false;
			struct
			{
				int hour{}, minute{}, second{};
			} custom_time;
		};

		struct settings {
			struct hotkeys
			{
				bool editing_menu_toggle = false;
				int menu_toggle = VK_INSERT;
				int teleport_waypoint = 0;
			};

			hotkeys hotkeys{};
		};

		struct spawn
		{
			bool preview_vehicle = false;
			bool spawn_inside = false;
			bool spawn_maxed = false;
			std::string plate = "";
		};

		struct clone_pv
		{
			bool preview_vehicle = false;
			bool spawn_inside = false;
			bool spawn_clone = false;
			bool spawn_maxed = false;
			bool clone_plate = false;
			std::string plate = "";
		};

		struct spoofing
		{
			bool spoof_username = false;
			std::string username = "";

			bool spoof_ip = true;
			int ip_address[4] = { 42, 42, 42, 42 };

			bool spoof_rockstar_id = false;
			uint64_t rockstar_id = 0;
		};

		struct tunables {
			bool disable_phone = false;
			bool no_idle_kick = false;
		};

		struct vehicle {
			struct speedo_meter {
				SpeedoMeter type = SpeedoMeter::DISABLED;

				float x = .9f;
				float y = .72f;

				bool left_side = false;
			};

			struct fly
			{
				bool dont_stop = false;
				bool enabled = false;
				bool no_collision = false;
				bool stop_on_exit = false;
				float speed = 1;
			};

			bool god_mode = false;
			bool proof_bullet = false;
			bool proof_fire = false;
			bool proof_collision = false;
			bool proof_melee = false;
			bool proof_explosion = false;
			bool proof_steam = false;
			bool proof_water = false;
			uint32_t proof_mask = 0;

			bool auto_drive_to_waypoint = false;
			bool auto_drive_wander = false;
			bool auto_turn_signals = false;
			bool drive_on_water = false;
			bool horn_boost = false;
			bool vehicle_jump = false;
			bool instant_brake = false;
			bool is_targetable = true;
			bool ls_customs = false; // don't save this to dis
			bool seatbelt = false;
			bool turn_signals = false;
			int auto_drive_speed = 1;
			int driving_style_flags = 443;
			int driving_style_id = 0;
			int rainbow_paint = 0;
			speedo_meter speedo_meter{};
			fly fly{};
		};

		struct weapons {
			struct ammo_special
			{
				bool toggle = false;
				eAmmoSpecialType type = eAmmoSpecialType::None;
				eImpactType impactType = eImpactType::DEFAULT_BULLETS;
			} ammo_special;

			CustomWeapon custom_weapon = CustomWeapon::NONE;
			bool force_crosshairs = false;
			bool infinite_ammo = false;
			bool infinite_mag = false;
			float increased_damage = 1;
			bool no_recoil = false;
			bool no_spread = false;
			char vehicle_gun_model[12] = "bus";
		};

		struct window {
			bool debug = false;
			bool handling = false;
			bool log = false;
			bool main = true;
			bool users = true;
			bool player = false;

			ImU32 color = 3357612055;

			ImFont* font_title = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small = nullptr;

			bool switched_view = true;
		};

		struct context_menu
		{
			bool enabled = true;

			uint8_t allowed_entity_types =
				static_cast<uint8_t>(ContextEntityType::PED) |
				static_cast<uint8_t>(ContextEntityType::PLAYER) |
				static_cast<uint8_t>(ContextEntityType::VEHICLE) |
				static_cast<uint8_t>(ContextEntityType::OBJECT);

			ImU32 selected_option_color = 4278255360;

			bool bounding_box_enabled = true;
			ImU32 bounding_box_color = 4278255360;
		};

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
		};

	public:
		int friend_count = 0;
		int player_count = 0;

		debug debug{};
		tunables tunables{};
		notifications notifications{};
		player player{};
		protections protections{};
		rgb rgb{};
		self self{};
		session session{};
		settings settings{};
		spawn spawn{};
		clone_pv clone_pv{};
		spoofing spoofing{};
		vehicle vehicle{};
		weapons weapons{};
		window window{};
		context_menu context_menu{};
		esp esp{};

		menu_settings(file save_file)
			: m_save_file(std::move(save_file))
		{
			g = this;
		}

		~menu_settings()
		{
			g = nullptr;
		}

		void from_json(const nlohmann::json& j)
		{
			this->debug.script_event_logging = j["debug"]["script_event_logging"];

			g->notifications.gta_thread_kill.log = j["notifications"]["gta_thread_kill"]["log"];
			g->notifications.gta_thread_kill.notify = j["notifications"]["gta_thread_kill"]["notify"];
			g->notifications.gta_thread_start.log = j["notifications"]["gta_thread_start"]["log"];
			g->notifications.gta_thread_start.notify = j["notifications"]["gta_thread_start"]["notify"];

			g->notifications.net_array_error.log = j["notifications"]["net_array_error"]["log"];
			g->notifications.net_array_error.notify = j["notifications"]["net_array_error"]["notify"];

			g->notifications.network_player_mgr_init.log = j["notifications"]["network_player_mgr_init"]["log"];
			g->notifications.network_player_mgr_init.notify = j["notifications"]["network_player_mgr_init"]["notify"];
			g->notifications.network_player_mgr_shutdown.log = j["notifications"]["network_player_mgr_shutdown"]["log"];
			g->notifications.network_player_mgr_shutdown.notify = j["notifications"]["network_player_mgr_shutdown"]["notify"];

			g->notifications.player_join.above_map = j["notifications"]["player_join"]["above_map"];
			g->notifications.player_join.log = j["notifications"]["player_join"]["log"];
			g->notifications.player_join.notify = j["notifications"]["player_join"]["notify"];

			g->notifications.player_leave.log = j["notifications"]["player_leave"]["log"];
			g->notifications.player_leave.notify = j["notifications"]["player_leave"]["notify"];

			g->notifications.received_event.clear_ped_task.log = j["notifications"]["received_event"]["clear_ped_task"]["log"];
			g->notifications.received_event.clear_ped_task.notify = j["notifications"]["received_event"]["clear_ped_task"]["notify"];
			g->notifications.received_event.modder_detect.log = j["notifications"]["received_event"]["modder_detect"]["log"];
			g->notifications.received_event.modder_detect.notify = j["notifications"]["received_event"]["modder_detect"]["notify"];
			g->notifications.received_event.request_control_event.log = j["notifications"]["received_event"]["request_control_event"]["log"];
			g->notifications.received_event.request_control_event.notify = j["notifications"]["received_event"]["request_control_event"]["notify"];
			g->notifications.received_event.report_cash_spawn.log = j["notifications"]["received_event"]["report_cash_spawn"]["log"];
			g->notifications.received_event.report_cash_spawn.notify = j["notifications"]["received_event"]["report_cash_spawn"]["notify"];
			g->notifications.received_event.vehicle_temp_action.log = j["notifications"]["received_event"]["vehicle_temp_action"]["log"];
			g->notifications.received_event.vehicle_temp_action.notify = j["notifications"]["received_event"]["vehicle_temp_action"]["notify"];

			g->notifications.reports.log = j["notifications"]["reports"]["log"];
			g->notifications.reports.notify = j["notifications"]["reports"]["notify"];

			g->notifications.invalid_sync.notify = j["notifications"]["invalid_sync"]["notify"];
			g->notifications.invalid_sync.log = j["notifications"]["invalid_sync"]["log"];

			{
				const auto& script_handler_j = j["notifications"]["script_event_handler"];
				auto& script_handler = this->notifications.script_event_handler;

				script_handler.bounty.log = script_handler_j["bounty"]["log"];
				script_handler.bounty.notify = script_handler_j["bounty"]["notify"];
				script_handler.ceo_ban.log = script_handler_j["ceo_ban"]["log"];
				script_handler.ceo_ban.notify = script_handler_j["ceo_ban"]["notify"];
				script_handler.ceo_kick.log = script_handler_j["ceo_kick"]["log"];
				script_handler.ceo_kick.notify = script_handler_j["ceo_kick"]["notify"];
				script_handler.ceo_money.log = script_handler_j["ceo_money"]["log"];
				script_handler.ceo_money.notify = script_handler_j["ceo_money"]["notify"];
				script_handler.clear_wanted_level.log = script_handler_j["clear_wanted_level"]["log"];
				script_handler.clear_wanted_level.notify = script_handler_j["clear_wanted_level"]["notify"];
				script_handler.crash.log = script_handler_j["crash"]["log"];
				script_handler.crash.notify = script_handler_j["crash"]["notify"];
				script_handler.fake_deposit.log = script_handler_j["fake_deposit"]["log"];
				script_handler.fake_deposit.notify = script_handler_j["fake_deposit"]["notify"];
				script_handler.force_mission.log = script_handler_j["force_mission"]["log"];
				script_handler.force_mission.notify = script_handler_j["force_mission"]["notify"];
				script_handler.force_teleport.log = script_handler_j["force_teleport"]["log"];
				script_handler.force_teleport.notify = script_handler_j["force_teleport"]["notify"];
				script_handler.gta_banner.log = script_handler_j["gta_banner"]["log"];
				script_handler.gta_banner.notify = script_handler_j["gta_banner"]["notify"];
				script_handler.mc_teleport.log = script_handler_j["mc_teleport"]["log"];
				script_handler.mc_teleport.notify = script_handler_j["mc_teleport"]["notify"];
				script_handler.network_bail.log = script_handler_j["network_bail"]["log"];
				script_handler.network_bail.notify = script_handler_j["network_bail"]["notify"];
				script_handler.personal_vehicle_destroyed.log = script_handler_j["personal_vehicle_destroyed"]["log"];
				script_handler.personal_vehicle_destroyed.notify = script_handler_j["personal_vehicle_destroyed"]["notify"];
				script_handler.remote_off_radar.log = script_handler_j["remote_off_radar"]["log"];
				script_handler.remote_off_radar.notify = script_handler_j["remote_off_radar"]["notify"];
				script_handler.rotate_cam.log = script_handler_j["rotate_cam"]["log"];
				script_handler.rotate_cam.notify = script_handler_j["rotate_cam"]["notify"];
				script_handler.send_to_cutscene.log = script_handler_j["send_to_cutscene"]["log"];
				script_handler.send_to_cutscene.notify = script_handler_j["send_to_cutscene"]["notify"];
				script_handler.send_to_island.log = script_handler_j["send_to_island"]["log"];
				script_handler.send_to_island.notify = script_handler_j["send_to_island"]["notify"];
				script_handler.sound_spam.log = script_handler_j["sound_spam"]["log"];
				script_handler.sound_spam.notify = script_handler_j["sound_spam"]["notify"];
				script_handler.spectate.log = script_handler_j["spectate"]["log"];
				script_handler.spectate.notify = script_handler_j["spectate"]["notify"];
				script_handler.transaction_error.log = script_handler_j["transaction_error"]["log"];
				script_handler.transaction_error.notify = script_handler_j["transaction_error"]["notify"];
				script_handler.tse_freeze.log = script_handler_j["tse_freeze"]["log"];
				script_handler.tse_freeze.notify = script_handler_j["tse_freeze"]["notify"];
				script_handler.vehicle_kick.log = script_handler_j["vehicle_kick"]["log"];
				script_handler.vehicle_kick.notify = script_handler_j["vehicle_kick"]["notify"];
			}

			g->notifications.send_net_info_to_lobby.log = j["notifications"]["send_net_info_to_lobby"]["log"];
			g->notifications.send_net_info_to_lobby.notify = j["notifications"]["send_net_info_to_lobby"]["notify"];

			g->notifications.transaction_rate_limit.log = j["notifications"]["transaction_rate_limit"]["log"];
			g->notifications.transaction_rate_limit.notify = j["notifications"]["transaction_rate_limit"]["notify"];

			{
				const auto& script_handler_j = j["protections"]["script_events"];
				auto& script_handler = this->protections.script_events;

				script_handler.bounty = script_handler_j["bounty"];
				script_handler.ceo_ban = script_handler_j["ceo_ban"];
				script_handler.ceo_kick = script_handler_j["ceo_kick"];
				script_handler.ceo_money = script_handler_j["ceo_money"];
				script_handler.clear_wanted_level = script_handler_j["clear_wanted_level"];
				script_handler.crash = script_handler_j["crash"];
				script_handler.fake_deposit = script_handler_j["fake_deposit"];
				script_handler.force_mission = script_handler_j["force_mission"];
				script_handler.force_teleport = script_handler_j["force_teleport"];
				script_handler.gta_banner = script_handler_j["gta_banner"];
				script_handler.mc_teleport = script_handler_j["mc_teleport"];
				script_handler.network_bail = script_handler_j["network_bail"];
				script_handler.personal_vehicle_destroyed = script_handler_j["personal_vehicle_destroyed"];
				script_handler.remote_off_radar = script_handler_j["remote_off_radar"];
				script_handler.rotate_cam = script_handler_j["rotate_cam"];
				script_handler.send_to_cutscene = script_handler_j["send_to_cutscene"];
				script_handler.send_to_island = script_handler_j["send_to_island"];
				script_handler.sound_spam = script_handler_j["sound_spam"];
				script_handler.spectate = script_handler_j["spectate"];
				script_handler.transaction_error = script_handler_j["transaction_error"];
				script_handler.vehicle_kick = script_handler_j["vehicle_kick"];
			}

			this->rgb.fade = j["rgb"]["fade"];
			this->rgb.spasm = j["rgb"]["spasm"];
			this->rgb.r = j["rgb"]["r"];
			this->rgb.g = j["rgb"]["g"];
			this->rgb.b = j["rgb"]["b"];
			this->rgb.speed = j["rgb"]["speed"];

			this->tunables.disable_phone = j["tunables"]["disable_phone"];
			this->tunables.no_idle_kick = j["tunables"]["no_idle_kick"];

			this->self.god_mode = j["self"]["god_mode"];
			this->self.proof_bullet = j["self"]["proof_bullet"];
			this->self.proof_fire = j["self"]["proof_fire"];
			this->self.proof_collision = j["self"]["proof_collision"];
			this->self.proof_melee = j["self"]["proof_melee"];
			this->self.proof_explosion = j["self"]["proof_explosion"];
			this->self.proof_steam = j["self"]["proof_steam"];
			this->self.proof_drown = j["self"]["proof_drown"];
			this->self.proof_water = j["self"]["proof_water"];
			this->self.proof_mask = j["self"]["proof_mask"];
			this->self.clean_player = j["self"]["clean_player"];
			this->self.invisibility = j["self"]["invisibility"];
			this->self.local_visibility = j["self"]["local_visibility"];
			this->self.never_wanted = j["self"]["never_wanted"];
			this->self.no_ragdoll = j["self"]["no_ragdoll"];
			this->self.off_radar = j["self"]["off_radar"];
			this->self.super_run = j["self"]["super_run"];
			this->self.proof_bullet = j["self"]["proof_bullet"];
			this->self.proof_fire = j["self"]["proof_fire"];
			this->self.proof_collision = j["self"]["proof_collision"];
			this->self.proof_melee = j["self"]["proof_melee"];
			this->self.proof_explosion = j["self"]["proof_explosion"];
			this->self.proof_steam = j["self"]["proof_steam"];
			this->self.proof_drown = j["self"]["proof_drown"];
			this->self.proof_water = j["self"]["proof_water"];
			this->self.proof_mask = j["self"]["proof_mask"];

			this->settings.hotkeys.menu_toggle = j["settings"]["hotkeys"]["menu_toggle"];

			this->spawn.preview_vehicle = j["spawn"]["preview_vehicle"];
			this->spawn.spawn_inside = j["spawn"]["spawn_inside"];
			this->spawn.spawn_maxed = j["spawn"]["spawn_maxed"];
			this->spawn.plate = j["spawn"]["plate"];

			this->clone_pv.preview_vehicle = j["clone_pv"]["preview_vehicle"];
			this->clone_pv.spawn_inside = j["clone_pv"]["spawn_inside"];
			this->clone_pv.spawn_clone = j["clone_pv"]["spawn_clone"];
			this->clone_pv.spawn_maxed = j["clone_pv"]["spawn_maxed"];
			this->clone_pv.clone_plate = j["clone_pv"]["clone_plate"];
			this->clone_pv.plate = j["clone_pv"]["plate"];

			this->spoofing.spoof_ip = j["spoofing"]["spoof_ip"];
			this->spoofing.spoof_rockstar_id = j["spoofing"]["spoof_rockstar_id"];
			this->spoofing.spoof_username = j["spoofing"]["spoof_username"];

			for (int i = 0; i < 4; i++)
				this->spoofing.ip_address[i] = j["spoofing"]["ip_address"].at(i);
			this->spoofing.rockstar_id = j["spoofing"]["rockstar_id"];
			this->spoofing.username = j["spoofing"]["username"];

			this->vehicle.god_mode = j["vehicle"]["god_mode"];
			this->vehicle.proof_bullet = j["vehicle"]["proof_bullet"];
			this->vehicle.proof_fire = j["vehicle"]["proof_fire"];
			this->vehicle.proof_collision = j["vehicle"]["proof_collision"];
			this->vehicle.proof_melee = j["vehicle"]["proof_melee"];
			this->vehicle.proof_explosion = j["vehicle"]["proof_explosion"];
			this->vehicle.proof_steam = j["vehicle"]["proof_steam"];
			this->vehicle.proof_water = j["vehicle"]["proof_water"];
			this->vehicle.proof_mask = j["vehicle"]["proof_mask"];
			this->vehicle.auto_drive_speed = j["vehicle"]["auto_drive_speed"];
			this->vehicle.auto_drive_to_waypoint = j["vehicle"]["auto_drive_to_waypoint"];
			this->vehicle.auto_drive_wander = j["vehicle"]["auto_drive_wander"];
			this->vehicle.auto_turn_signals = j["vehicle"]["auto_turn_signals"];
			this->vehicle.drive_on_water = j["vehicle"]["drive_on_water"];
			this->vehicle.driving_style_id = j["vehicle"]["driving_style"];
			this->vehicle.horn_boost = j["vehicle"]["horn_boost"];
			this->vehicle.vehicle_jump = j["vehicle"]["vehicle_jump"];
			this->vehicle.instant_brake = j["vehicle"]["instant_brake"];
			this->vehicle.is_targetable = j["vehicle"]["is_targetable"];
			this->vehicle.rainbow_paint = j["vehicle"]["rainbow_paint"];
			this->vehicle.seatbelt = j["vehicle"]["seatbelt"];
			this->vehicle.turn_signals = j["vehicle"]["turn_signals"];

			this->vehicle.speedo_meter.type = (SpeedoMeter)j["vehicle"]["speedo_meter"]["type"];
			this->vehicle.speedo_meter.left_side = j["vehicle"]["speedo_meter"]["left_side"];
			this->vehicle.speedo_meter.x = j["vehicle"]["speedo_meter"]["position_x"];
			this->vehicle.speedo_meter.y = j["vehicle"]["speedo_meter"]["position_y"];

			this->vehicle.fly.dont_stop = j["vehicle"]["fly"]["dont_stop"];
			this->vehicle.fly.enabled = j["vehicle"]["fly"]["enabled"];
			this->vehicle.fly.no_collision = j["vehicle"]["fly"]["no_collision"];
			this->vehicle.fly.speed = j["vehicle"]["fly"]["speed"];
			this->vehicle.fly.stop_on_exit = j["vehicle"]["fly"]["stop_on_exit"];

			this->weapons.custom_weapon = (CustomWeapon)j["weapons"]["custom_weapon"];
			this->weapons.force_crosshairs = j["weapons"]["force_crosshairs"];
			this->weapons.infinite_ammo = j["weapons"]["infinite_ammo"];
			this->weapons.increased_damage = j["weapons"]["increased_damage"];
			this->weapons.infinite_mag = j["weapons"]["infinite_mag"];
			this->weapons.no_recoil = j["weapons"]["no_recoil"];
			this->weapons.no_spread = j["weapons"]["no_spread"];

			this->weapons.ammo_special.type = (eAmmoSpecialType)j["weapons"]["ammo_special"]["type"];
			this->weapons.ammo_special.toggle = j["weapons"]["ammo_special"]["toggle"];

			this->window.color = j["window"]["color"];
			this->window.debug = j["window"]["debug"];
			this->window.handling = j["window"]["handling"];
			this->window.log = j["window"]["log"];
			this->window.main = j["window"]["main"];
			this->window.users = j["window"]["users"];

			this->context_menu.enabled = j["context_menu"]["enabled"];
			this->context_menu.allowed_entity_types = j["context_menu"]["allowed_entity_types"];
			this->context_menu.selected_option_color = j["context_menu"]["selected_option_color"];
			this->context_menu.bounding_box_enabled = j["context_menu"]["bounding_box_enabled"];
			this->context_menu.bounding_box_color = j["context_menu"]["bounding_box_color"];

			this->esp.enabled = j["esp"]["enabled"];
			this->esp.hide_self = j["esp"]["hide_self"];
			this->esp.enemy_color = j["esp"]["enemy_color"];
			this->esp.enemy_near_color = j["esp"]["enemy_near_color"];
			this->esp.default_color = j["esp"]["default_color"];
			this->esp.friend_color = j["esp"]["friend_color"];
			this->esp.box = j["esp"]["box"];
			this->esp.distance = j["esp"]["distance"];
			this->esp.god = j["esp"]["god"];
			this->esp.health = j["esp"]["health"];
			this->esp.armor = j["esp"]["armor"];
			this->esp.name = j["esp"]["name"];
			this->esp.change_esp_color_from_dist = j["esp"]["change_esp_color_from_dist"];
			this->esp.scale_health_from_dist = j["esp"]["scale_health_from_dist"];
			this->esp.scale_armor_from_dist = j["esp"]["scale_armor_from_dist"];
			for (int i = 0; i < 2; i++)
				this->esp.global_render_distance[i] = j["esp"]["global_render_distance"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.tracer_render_distance[i] = j["esp"]["tracer_render_distance"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.box_render_distance[i] = j["esp"]["box_render_distance"].at(i);
			this->esp.tracer = j["esp"]["tracer"];
			for (int i = 0; i < 2; i++)
				this->esp.tracer_draw_position[i] = j["esp"]["tracer_draw_position"].at(i);
			for (int i = 0; i < 2; i++)
				this->esp.distance_threshold[i] = j["esp"]["distance_threshold"].at(i);
		}

		nlohmann::json to_json()
		{
			constexpr auto return_notify_pair = [](const notifications::pair& notify_pair) -> auto
			{
				return nlohmann::json{
					{ "log", notify_pair.log },
					{ "notify", notify_pair.notify }
				};
			};

			const auto& script_handler_notifications = this->notifications.script_event_handler;
			const auto& script_handler_protections = this->protections.script_events;

			return nlohmann::json{
				{
					"debug",
					{
						{ "script_event_logging", this->debug.script_event_logging }
					}
				},
				{
					"notifications", {
						{ "gta_thread_kill", return_notify_pair(g->notifications.gta_thread_kill) },
						{ "gta_thread_start", return_notify_pair(g->notifications.gta_thread_start) },
						{ "net_array_error", return_notify_pair(g->notifications.net_array_error) },
						{ "network_player_mgr_init", return_notify_pair(g->notifications.network_player_mgr_init) },
						{ "network_player_mgr_shutdown", return_notify_pair(g->notifications.network_player_mgr_shutdown) },
						{ "player_join", {
								{ "above_map", g->notifications.player_join.above_map },
								{ "log", g->notifications.player_join.log },
								{ "notify", g->notifications.player_join.notify }
							}
						},
						{ "player_leave", return_notify_pair(g->notifications.player_leave) },
						{
							"received_event", {
								{ "clear_ped_task", return_notify_pair(g->notifications.received_event.clear_ped_task) },
								{ "modder_detect", return_notify_pair(g->notifications.received_event.modder_detect) },
								{ "report_cash_spawn", return_notify_pair(g->notifications.received_event.report_cash_spawn) },
								{ "request_control_event", return_notify_pair(g->notifications.received_event.request_control_event) },
								{ "vehicle_temp_action", return_notify_pair(g->notifications.received_event.vehicle_temp_action) }
							}
						},
						{ "reports", return_notify_pair(g->notifications.reports) },
						{ "script_event_handler", {
								{ "bounty", return_notify_pair(script_handler_notifications.bounty) },
								{ "ceo_ban", return_notify_pair(script_handler_notifications.ceo_ban) },
								{ "ceo_kick", return_notify_pair(script_handler_notifications.ceo_kick) },
								{ "ceo_money", return_notify_pair(script_handler_notifications.ceo_money) },
								{ "clear_wanted_level", return_notify_pair(script_handler_notifications.clear_wanted_level) },
								{ "crash", return_notify_pair(script_handler_notifications.crash) },
								{ "fake_deposit", return_notify_pair(script_handler_notifications.fake_deposit) },
								{ "force_mission", return_notify_pair(script_handler_notifications.force_mission) },
								{ "force_teleport", return_notify_pair(script_handler_notifications.force_teleport) },
								{ "gta_banner", return_notify_pair(script_handler_notifications.gta_banner) },
								{ "mc_teleport", return_notify_pair(script_handler_notifications.mc_teleport) },
								{ "network_bail", return_notify_pair(script_handler_notifications.network_bail) },
								{ "personal_vehicle_destroyed", return_notify_pair(script_handler_notifications.personal_vehicle_destroyed) },
								{ "remote_off_radar", return_notify_pair(script_handler_notifications.remote_off_radar) },
								{ "rotate_cam", return_notify_pair(script_handler_notifications.rotate_cam) },
								{ "send_to_cutscene", return_notify_pair(script_handler_notifications.send_to_cutscene) },
								{ "send_to_island", return_notify_pair(script_handler_notifications.send_to_island) },
								{ "sound_spam", return_notify_pair(script_handler_notifications.sound_spam) },
								{ "spectate", return_notify_pair(script_handler_notifications.spectate) },
								{ "transaction_error", return_notify_pair(script_handler_notifications.transaction_error) },
								{ "tse_freeze", return_notify_pair(script_handler_notifications.tse_freeze) },
								{ "vehicle_kick", return_notify_pair(script_handler_notifications.vehicle_kick) }
							}
						},
						{ "send_net_info_to_lobby", return_notify_pair(g->notifications.send_net_info_to_lobby) },
						{ "transaction_rate_limit", return_notify_pair(g->notifications.transaction_rate_limit) },
						{ "invalid_sync", return_notify_pair(g->notifications.invalid_sync) }
					}
				},
				{
					"protections",
					{
						{
							"script_events", {
								{ "bounty", script_handler_protections.bounty },
								{ "ceo_ban", script_handler_protections.ceo_ban },
								{ "ceo_kick", script_handler_protections.ceo_kick },
								{ "ceo_money", script_handler_protections.ceo_money },
								{ "clear_wanted_level", script_handler_protections.clear_wanted_level },
								{ "crash", script_handler_protections.crash },
								{ "fake_deposit", script_handler_protections.fake_deposit },
								{ "force_mission", script_handler_protections.force_mission },
								{ "force_teleport", script_handler_protections.force_teleport },
								{ "gta_banner", script_handler_protections.gta_banner },
								{ "mc_teleport", script_handler_protections.mc_teleport },
								{ "network_bail", script_handler_protections.network_bail },
								{ "personal_vehicle_destroyed", script_handler_protections.personal_vehicle_destroyed },
								{ "remote_off_radar", script_handler_protections.remote_off_radar },
								{ "rotate_cam", script_handler_protections.rotate_cam },
								{ "send_to_cutscene", script_handler_protections.send_to_cutscene },
								{ "send_to_island", script_handler_protections.send_to_island },
								{ "sound_spam", script_handler_protections.sound_spam },
								{ "spectate", script_handler_protections.spectate },
								{ "transaction_error", script_handler_protections.transaction_error },
								{ "vehicle_kick", script_handler_protections.vehicle_kick }
							}
						}
					}
				},
				{
					"rgb", {
					{ "fade", this->rgb.fade },
					{ "spasm", this->rgb.spasm },
					{ "r", this->rgb.r },
					{ "g", this->rgb.g },
					{ "b", this->rgb.b },
					{ "speed", this->rgb.speed }
					}
				},
				{
					"tunables", {
						{ "disable_phone", this->tunables.disable_phone },
						{ "no_idle_kick", this->tunables.no_idle_kick }
					}
				},
				{
					"self", {
						{ "god_mode", this->self.god_mode },
						{ "proof_bullet", this->self.proof_bullet },
						{ "proof_fire", this->self.proof_fire },
						{ "proof_collision", this->self.proof_collision },
						{ "proof_melee", this->self.proof_melee },
						{ "proof_explosion", this->self.proof_explosion },
						{ "proof_steam", this->self.proof_steam },
						{ "proof_drown", this->self.proof_drown },
						{ "proof_water", this->self.proof_water },
						{ "proof_mask", this->self.proof_mask },
						{ "clean_player", this->self.clean_player },
						{ "invisibility", this->self.invisibility },
						{ "local_visibility", this->self.local_visibility },
						{ "never_wanted", this->self.never_wanted },
						{ "no_ragdoll", this->self.no_ragdoll },
						{ "off_radar", this->self.off_radar },
						{ "super_run", this->self.super_run },

						{ "proof_bullet", this->self.proof_bullet },
						{ "proof_fire", this->self.proof_fire },
						{ "proof_collision", this->self.proof_collision },
						{ "proof_melee", this->self.proof_melee },
						{ "proof_explosion", this->self.proof_explosion },
						{ "proof_steam", this->self.proof_steam },
						{ "proof_drown", this->self.proof_drown },
						{ "proof_water", this->self.proof_water },
						{ "proof_mask", this->self.proof_mask }
					}
				},
				{
					"settings", {
						{ "hotkeys", {
								{ "menu_toggle", this->settings.hotkeys.menu_toggle }
							}
						}
					}
				},
				{
					"clone_pv", {
						{ "preview_vehicle", this->clone_pv.preview_vehicle },
						{ "spawn_inside", this->clone_pv.spawn_inside },
						{ "spawn_clone", this->clone_pv.spawn_clone },
						{ "spawn_maxed", this->clone_pv.spawn_maxed },
						{ "clone_plate", this->clone_pv.clone_plate },
						{ "plate", this->clone_pv.plate }
					}
				},
				{
					"spawn", {
						{ "preview_vehicle", this->spawn.preview_vehicle },
						{ "spawn_inside", this->spawn.spawn_inside },
						{ "spawn_maxed", this->spawn.spawn_maxed},
						{ "plate", this->spawn.plate }
					}
				},
				{
					"spoofing", {
						{ "spoof_ip", this->spoofing.spoof_ip },
						{ "spoof_rockstar_id", this->spoofing.spoof_rockstar_id },
						{ "spoof_username", this->spoofing.spoof_username },
						{ "ip_address", nlohmann::json::array({
							this->spoofing.ip_address[0],
							this->spoofing.ip_address[1],
							this->spoofing.ip_address[2],
							this->spoofing.ip_address[3] })
						},
						{ "rockstar_id", this->spoofing.rockstar_id },
						{ "username", this->spoofing.username }
					}
				},
				{
					"vehicle", {
						{ "god_mode", this->vehicle.god_mode },
						{ "proof_bullet", this->vehicle.proof_bullet },
						{ "proof_fire", this->vehicle.proof_fire },
						{ "proof_collision", this->vehicle.proof_collision },
						{ "proof_melee", this->vehicle.proof_melee },
						{ "proof_explosion", this->vehicle.proof_explosion },
						{ "proof_steam", this->vehicle.proof_steam },
						{ "proof_water", this->vehicle.proof_water },
						{ "proof_mask", this->vehicle.proof_mask },
						{ "auto_drive_speed", this->vehicle.auto_drive_speed },
						{ "auto_drive_to_waypoint", this->vehicle.auto_drive_to_waypoint },
						{ "auto_drive_wander", this->vehicle.auto_drive_wander },
						{ "auto_turn_signals", this->vehicle.auto_turn_signals },
						{ "drive_on_water", this->vehicle.drive_on_water },
						{ "driving_style", this->vehicle.driving_style_id },
						{ "horn_boost", this->vehicle.horn_boost },
						{ "vehicle_jump", this->vehicle.vehicle_jump },
						{ "instant_brake", this->vehicle.instant_brake },
						{ "is_targetable", this->vehicle.is_targetable },
						{ "rainbow_paint", this->vehicle.rainbow_paint },
						{ "turn_signals", this->vehicle.turn_signals },
						{ "seatbelt", this->vehicle.seatbelt },
						{
							"speedo_meter", {
								{ "type", (int)this->vehicle.speedo_meter.type },
								{ "left_side", this->vehicle.speedo_meter.left_side },
								{ "position_x", this->vehicle.speedo_meter.x },
								{ "position_y", this->vehicle.speedo_meter.y },
							}
						},
						{
							"fly",
							{
								{ "no_collision", this->vehicle.fly.no_collision },
								{ "dont_stop", this->vehicle.fly.dont_stop },
								{ "enabled", this->vehicle.fly.enabled },
								{ "stop_on_exit", this->vehicle.fly.stop_on_exit },
								{ "speed", this->vehicle.fly.speed },
							}
						}
					}
				},
				{
					"weapons", {
						{ "ammo_special", {
							{ "toggle", this->weapons.ammo_special.toggle },
							{ "type", (int)this->weapons.ammo_special.type },
							}
						},
						{ "custom_weapon", (int)this->weapons.custom_weapon },
						{ "force_crosshairs", this->weapons.force_crosshairs },
						{ "increased_damage", this->weapons.increased_damage },
						{ "infinite_ammo", this->weapons.infinite_ammo },
						{ "infinite_mag", this->weapons.infinite_mag },
						{ "no_recoil", this->weapons.no_recoil },
						{ "no_spread", this->weapons.no_spread }
					}
				},
				{
					"window", {
						{ "color", this->window.color },
						{ "debug", this->window.debug },
						{ "handling", this->window.handling },
						{ "log", this->window.log },
						{ "main", this->window.main },
						{ "users", this->window.users }
					}
				},
				{
					"context_menu", {
						{"enabled", this->context_menu.enabled},
						{ "allowed_entity_types", this->context_menu.allowed_entity_types },
						{ "selected_option_color", this->context_menu.selected_option_color },
						{ "bounding_box_enabled", this->context_menu.bounding_box_enabled },
						{ "bounding_box_color", this->context_menu.bounding_box_color },
					}
				},
				{
					"esp", {
						{ "enabled", this->esp.enabled },
						{ "hide_self", this->esp.hide_self },
						{ "global_render_distance", nlohmann::json::array({
						this->esp.global_render_distance[0],
						this->esp.global_render_distance[1] })
						},
						{ "tracer_render_distance", nlohmann::json::array({
						this->esp.tracer_render_distance[0],
						this->esp.tracer_render_distance[1] })
						},
						{ "box_render_distance", nlohmann::json::array({
						this->esp.box_render_distance[0],
						this->esp.box_render_distance[1] })
						},
						{ "enemy_color", this->esp.enemy_color },
						{ "enemy_near_color", this->esp.enemy_near_color },
						{ "default_color", this->esp.default_color },
						{ "friend_color", this->esp.friend_color },
						{ "distance", this->esp.distance },
						{ "box", this->esp.box },
						{ "god", this->esp.god },
						{ "health", this->esp.health },
						{ "armor", this->esp.armor },
						{ "name", this->esp.name },
						{ "tracer", this->esp.tracer },
						{ "change_esp_color_from_dist", this->esp.change_esp_color_from_dist },
						{ "scale_health_from_dist", this->esp.scale_health_from_dist },
						{ "scale_armor_from_dist", this->esp.scale_armor_from_dist },
						{ "tracer_draw_position", nlohmann::json::array({
						this->esp.tracer_draw_position[0],
						this->esp.tracer_draw_position[1] })
						},
						{ "distance_threshold", nlohmann::json::array({
						this->esp.distance_threshold[0],
						this->esp.distance_threshold[1] })
						}
					}
				}
			};
		}

		void attempt_save()
		{
			const nlohmann::json& j = this->to_json();

			if (deep_compare(this->options, j, true))
				this->save();
		}

		bool load()
		{
			this->default_options = this->to_json();

			std::ifstream file(m_save_file.get_path());

			if (!file.is_open())
			{
				this->write_default_config();

				file.open(m_save_file.get_path());
			}

			try
			{
				file >> this->options;

				file.close();
			}
			catch (const std::exception&)
			{
				file.close();

				LOG(WARNING) << "Detected corrupt settings, writing default config...";

				this->write_default_config();

				return this->load();
			}

			const bool should_save = this->deep_compare(this->options, this->default_options);

			this->from_json(this->options);

			if (should_save)
			{
				LOG(INFO) << "Updating settings.";
				save();
			}

			return true;
		}

	private:
		file m_save_file;

		bool deep_compare(nlohmann::json& current_settings, const nlohmann::json& default_settings, bool compare_value = false)
		{
			bool should_save = false;

			for (auto& e : default_settings.items())
			{
				const std::string& key = e.key();

				if (current_settings.count(key) == 0 || (compare_value && current_settings[key] != e.value()))
				{
					current_settings[key] = e.value();

					should_save = true;
				}
				else if (current_settings[key].is_object() && e.value().is_object())
				{
					if (deep_compare(current_settings[key], e.value(), compare_value))
						should_save = true;
				}
				else if (!current_settings[key].is_object() && e.value().is_object()) {
					current_settings[key] = e.value();

					should_save = true;
				}
			}

			return should_save;
		}

		bool save()
		{
			std::ofstream file(m_save_file.get_path(), std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}

		bool write_default_config()
		{
			std::ofstream file(m_save_file.get_path(), std::ios::out | std::ios::trunc);
			file << this->to_json().dump(4);
			file.close();

			return true;
		}
	};
}

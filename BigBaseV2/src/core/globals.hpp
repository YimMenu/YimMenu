#pragma once
#include "enums.hpp"
#include "file_manager.hpp"
#include "imgui.h"

namespace big
{
	class menu_settings;
	inline menu_settings* g{};

	class menu_settings {
		nlohmann::json default_options;
		nlohmann::json options;

		struct debug {
			bool script_event_logging = false;
		};

		struct tunables {
			bool disable_phone = false;
			bool no_idle_kick = false;
		};

		struct player {
			int character_slot = 1;
			bool player_never_wanted = false;
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
				bool fake_deposit = true;
				bool force_mission = true;
				bool force_teleport = true;
				bool gta_banner = true;
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

			bool freemode_terminated = false;

			script_events script_events{};
		};

		struct self {
			struct frame_flags {
				bool explosive_ammo = false;
				bool explosive_melee = false;
				bool fire_ammo = false;
				bool super_jump = false;
			};

			bool clean_player = false;
			bool force_wanted_level = false;
			bool free_cam = false;
			bool godmode = false;
			bool invisibility = false;
			bool never_wanted = false;
			bool noclip = false;
			bool no_ragdoll = false;
			bool off_radar = false;
			bool super_run = false;
			int wanted_level = 0;

			frame_flags frame_flags{};
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

		struct spoofing
		{
			bool spoof_username = false;
			std::string username = "";

			bool spoof_ip = true;
			int ip_address[4] = { 42, 42, 42, 42 };

			bool spoof_rockstar_id = false;
			uint64_t rockstar_id = 0;
		};

		struct vehicle {
			struct speedo_meter {
				SpeedoMeter type = SpeedoMeter::DISABLED;

				float x = .9f;
				float y = .72f;

				bool left_side = false;
			};

			bool god_mode = false;
			bool horn_boost = false;
			bool is_targetable = true;
			bool ls_customs = false; // don't save this to disk
			bool pv_teleport_into = false;
			speedo_meter speedo_meter{};
		};

		struct weapons {
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

			ImFont* font_title = nullptr;
			ImFont* font_sub_title = nullptr;
			ImFont* font_small = nullptr;

			bool switched_view = true;

			int x;
			int y;
		};

	public:
		int friend_count = 0;
		int player_count = 0;

		debug debug{};
		tunables tunables{};
		player player{};
		protections protections{};
		self self{};
		settings settings{};
		spoofing spoofing{};
		vehicle vehicle{};
		weapons weapons{};
		window window{};

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

			this->protections.script_events.bounty = j["protections"]["script_events"]["bounty"];
			this->protections.script_events.ceo_ban = j["protections"]["script_events"]["ceo_ban"];
			this->protections.script_events.ceo_kick = j["protections"]["script_events"]["ceo_kick"];
			this->protections.script_events.ceo_money = j["protections"]["script_events"]["ceo_money"];
			this->protections.script_events.clear_wanted_level = j["protections"]["script_events"]["clear_wanted_level"];
			this->protections.script_events.fake_deposit = j["protections"]["script_events"]["fake_deposit"];
			this->protections.script_events.force_mission = j["protections"]["script_events"]["force_mission"];
			this->protections.script_events.force_teleport = j["protections"]["script_events"]["force_teleport"];
			this->protections.script_events.gta_banner = j["protections"]["script_events"]["gta_banner"];
			this->protections.script_events.network_bail = j["protections"]["script_events"]["network_bail"];
			this->protections.script_events.personal_vehicle_destroyed = j["protections"]["script_events"]["personal_vehicle_destroyed"];
			this->protections.script_events.remote_off_radar = j["protections"]["script_events"]["remote_off_radar"];
			this->protections.script_events.rotate_cam = j["protections"]["script_events"]["rotate_cam"];
			this->protections.script_events.send_to_cutscene = j["protections"]["script_events"]["send_to_cutscene"];
			this->protections.script_events.send_to_island = j["protections"]["script_events"]["send_to_island"];
			this->protections.script_events.sound_spam = j["protections"]["script_events"]["sound_spam"];
			this->protections.script_events.spectate = j["protections"]["script_events"]["spectate"];
			this->protections.script_events.transaction_error = j["protections"]["script_events"]["transaction_error"];
			this->protections.script_events.vehicle_kick = j["protections"]["script_events"]["vehicle_kick"];

			this->tunables.disable_phone = j["tunables"]["disable_phone"];
			this->tunables.no_idle_kick = j["tunables"]["no_idle_kick"];

			this->self.clean_player = j["self"]["clean_player"];
			this->self.godmode = j["self"]["godmode"];
			this->self.invisibility = j["self"]["invisibility"];
			this->self.no_ragdoll = j["self"]["no_ragdoll"];
			this->self.never_wanted = j["self"]["never_wanted"];
			this->self.off_radar = j["self"]["off_radar"];
			this->self.super_run = j["self"]["super_run"];

			this->self.frame_flags.explosive_ammo = j["self"]["frame_flags"]["explosive_ammo"];
			this->self.frame_flags.explosive_melee = j["self"]["frame_flags"]["explosive_melee"];
			this->self.frame_flags.fire_ammo = j["self"]["frame_flags"]["fire_ammo"];
			this->self.frame_flags.super_jump = j["self"]["frame_flags"]["super_jump"];

			this->settings.hotkeys.menu_toggle = j["settings"]["hotkeys"]["menu_toggle"];

			this->spoofing.spoof_ip = j["spoofing"]["spoof_ip"];
			this->spoofing.spoof_rockstar_id = j["spoofing"]["spoof_rockstar_id"];
			this->spoofing.spoof_username = j["spoofing"]["spoof_username"];

			for (int i = 0; i < 4; i++)
				this->spoofing.ip_address[i] = j["spoofing"]["ip_address"].at(i);
			this->spoofing.rockstar_id = j["spoofing"]["rockstar_id"];
			this->spoofing.username = j["spoofing"]["username"];

			this->vehicle.god_mode = j["vehicle"]["god_mode"];
			this->vehicle.horn_boost = j["vehicle"]["horn_boost"];
			this->vehicle.is_targetable = j["vehicle"]["is_targetable"];
			this->vehicle.pv_teleport_into = j["vehicle"]["pv_teleport_into"];

			this->vehicle.speedo_meter.type = (SpeedoMeter)j["vehicle"]["speedo_meter"]["type"];
			this->vehicle.speedo_meter.left_side = j["vehicle"]["speedo_meter"]["left_side"];
			this->vehicle.speedo_meter.x = j["vehicle"]["speedo_meter"]["position_x"];
			this->vehicle.speedo_meter.y = j["vehicle"]["speedo_meter"]["position_y"];

			this->weapons.custom_weapon = (CustomWeapon)j["weapons"]["custom_weapon"];
			this->weapons.force_crosshairs = j["weapons"]["force_crosshairs"];
			this->weapons.infinite_ammo = j["weapons"]["infinite_ammo"];
			this->weapons.increased_damage = j["weapons"]["increased_damage"];
			this->weapons.infinite_mag = j["weapons"]["infinite_mag"];
			this->weapons.no_recoil = j["weapons"]["no_recoil"];
			this->weapons.no_spread = j["weapons"]["no_spread"];

			this->window.debug = j["window"]["debug"];
			this->window.handling = j["window"]["handling"];
			this->window.log = j["window"]["log"];
			this->window.main = j["window"]["main"];
			this->window.users = j["window"]["users"];
		}

		nlohmann::json to_json()
		{
			return nlohmann::json{
				{
					"debug",
					{
						{ "script_event_logging", this->debug.script_event_logging }
					}
				},
				{
					"protections",
					{
						{
							"script_events", {
								{ "bounty", this->protections.script_events.bounty },
								{ "ceo_ban", this->protections.script_events.ceo_ban },
								{ "ceo_kick", this->protections.script_events.ceo_kick },
								{ "ceo_money", this->protections.script_events.ceo_money },
								{ "clear_wanted_level", this->protections.script_events.clear_wanted_level },
								{ "fake_deposit", this->protections.script_events.fake_deposit },
								{ "force_mission", this->protections.script_events.force_mission },
								{ "force_teleport", this->protections.script_events.force_teleport },
								{ "gta_banner", this->protections.script_events.gta_banner },
								{ "network_bail", this->protections.script_events.network_bail },
								{ "personal_vehicle_destroyed", this->protections.script_events.personal_vehicle_destroyed },
								{ "remote_off_radar", this->protections.script_events.remote_off_radar },
								{ "rotate_cam", this->protections.script_events.rotate_cam },
								{ "send_to_cutscene", this->protections.script_events.send_to_cutscene },
								{ "send_to_island", this->protections.script_events.send_to_island },
								{ "sound_spam", this->protections.script_events.sound_spam },
								{ "spectate", this->protections.script_events.spectate },
								{ "transaction_error", this->protections.script_events.transaction_error },
								{ "vehicle_kick", this->protections.script_events.vehicle_kick }
							}
						}
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
						{ "clean_player", this->self.clean_player },
						{ "godmode", this->self.godmode },
						{ "invisibility", this->self.invisibility },
						{ "never_wanted", this->self.never_wanted },
						{ "no_ragdoll", this->self.no_ragdoll },
						{ "off_radar", this->self.off_radar },
						{ "super_run", this->self.super_run },

						{
							"frame_flags", {
								{ "explosive_ammo", this->self.frame_flags.explosive_ammo },
								{ "explosive_melee", this->self.frame_flags.explosive_melee },
								{ "fire_ammo", this->self.frame_flags.fire_ammo },
								{ "super_jump", this->self.frame_flags.super_jump }
							}
						}
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
						{ "horn_boost", this->vehicle.horn_boost },
						{ "is_targetable", this->vehicle.is_targetable },
						{ "pv_teleport_into", this->vehicle.pv_teleport_into },
						{
							"speedo_meter", {
								{ "type", (int)this->vehicle.speedo_meter.type },
								{ "left_side", this->vehicle.speedo_meter.left_side },
								{ "position_x", this->vehicle.speedo_meter.x },
								{ "position_y", this->vehicle.speedo_meter.y }
							}
						}
					}
				},
				{
					"weapons", {
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
						{ "debug", this->window.debug },
						{ "handling", this->window.handling },
						{ "log", this->window.log },
						{ "main", this->window.main },
						{ "users", this->window.users }
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

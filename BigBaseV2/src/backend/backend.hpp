#pragma once
#include "common.hpp"
#include "looped/looped.hpp"
#include "script.hpp"

namespace big
{
	class backend {
	public:
		static void loop();

		static void self_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::self_clean_player();
					looped::self_free_cam();
					looped::self_godmode();
					looped::self_invisibility();
					looped::self_no_ragdoll();
					looped::self_off_radar();
					looped::self_police();
					looped::self_super_run();
				}

				script::get_current()->yield();
			}


		}
		static void weapons_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::weapons_ammo_special_type();
					looped::weapons_cage_gun();
					looped::weapons_delete_gun();
					looped::weapons_force_crosshairs();
					looped::weapons_gravity_gun();
					looped::weapons_increased_damage();
					looped::weapons_infinite_ammo();
					looped::weapons_infinite_mag();
					looped::weapons_no_recoil();
					looped::weapons_no_spread();
					looped::weapons_repair_gun();
					looped::weapons_steal_vehicle_gun();
					looped::weapons_vehicle_gun();
				}

				script::get_current()->yield();
			}

		}
		static void vehicles_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::vehicle_auto_drive();
					looped::vehicle_despawn_bypass();
					looped::vehicle_drive_on_water();
					looped::vehicle_god_mode();
					looped::vehicle_horn_boost();
					looped::vehicle_instant_brake();
					looped::vehicle_is_targetable();
					looped::vehicle_rainbow_paint();
					looped::vehicle_seatbelt();
					looped::vehicle_speedo_meter();
				}
				

				script::get_current()->yield();
			}

		}

		static void turnsignal_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::vehicle_turn_signals();
				}
				script::get_current()->yield();
			}

		}

		static void rgbrandomizer_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::rgb_synced_fade();
					looped::rgb_synced_spasm();
				}

				script::get_current()->yield();
			}

		}

		static void misc_loop() {

			while (g_running) {
				
				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::hud_transition_state();
					looped::tunables_disable_phone();
					looped::tunables_no_idle_kick();
					looped::session_local_time();
				}

				script::get_current()->yield();
			}

		}

		static void remote_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::player_never_wanted();
					looped::player_spectate();
				}

				script::get_current()->yield();
			}

		}

		static void noclip_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::self_noclip();
				}

				script::get_current()->yield();
			}

		}

		static void lscustoms_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::vehicle_ls_customs();
				}

				script::get_current()->yield();
			}

		}

		static void vehiclefly_loop() {

			while (g_running) {

				if (script::get_current()->get_enabled_pointer() == nullptr || *script::get_current()->get_enabled_pointer()) {
					looped::vehicle_fly();
				}

				script::get_current()->yield();
			}

		}

	};
}
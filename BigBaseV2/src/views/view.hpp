#pragma once
#include "imgui.h"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/animator.hpp"
#include "gui/components/components.hpp"
#include "script.hpp"
#include "services/player_service.hpp"
#include "views/esp/view_esp.hpp"


namespace big
{
	class view
	{
		enum class tabs {
			DEBUG,
			MOBILE,
			NONE,
			PLAYER,
			SELF,
			SESSION,
			SETTINGS,
			SPAWN,
			SPOOFING,
			TELEPORT,
			VEHICLE,
			WEAPONS,
		};

		struct navigation_struct
		{
			tabs tab = tabs::NONE;
			const char name[32] = "";
			std::function<void()> func = nullptr;
		};

		static void active_view();
		static void debug();
		static void mobile();
		static void navigation();
		static void notifications();
		static void self();
		static void session();
		static void settings();
		static void spawn();
		static void spoofing();
		static void teleport();
		static void vehicle();
		static void view_player();
		static void weapons();

		inline static animator window_animator = animator();

		inline static navigation_struct initial_tab{};

		inline static navigation_struct* current_tab = &initial_tab;

		inline static navigation_struct nav[] = {
			{ tabs::SELF, "Self", view::self },
			{ tabs::MOBILE, "Mobile", view::mobile },
			{ tabs::SPAWN, "Spawn", view::spawn },
			{ tabs::TELEPORT, "Teleport", view::teleport },
			{ tabs::VEHICLE, "Vehicle", view::vehicle },
			{ tabs::WEAPONS, "Weapons", view::weapons },
			{ tabs::SPOOFING, "Spoofing", view::spoofing },
			{ tabs::SESSION, "Session", view::session },
			{ tabs::SETTINGS, "Settings", view::settings },
			{ tabs::DEBUG, "Debug", view::debug },
			{ tabs::PLAYER, "Players", view::view_player },
		};

	public:
		static void root()
		{
			active_view();
			navigation();
		}

		static void always()
		{
			esp::draw();
			notifications();
		}
	};
}
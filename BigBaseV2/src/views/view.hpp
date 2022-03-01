#pragma once
#include "imgui.h"
#include "natives.hpp"
#include "util/animator.hpp"
#include "gui/components/components.hpp"

namespace big
{
	class view
	{
		enum class tabs {
			NONE,
			SELF,
			MOBILE,
			SPAWN,
			WEAPONS,
			SPOOFING,
			SETTINGS,
			TELEPORT,
			VEHICLE,
			PLAYER,
			DEBUG,
		};

		struct navigation_struct
		{
			tabs tab = tabs::NONE;
			const char name[32] = "";
			std::function<void()> func = nullptr;
		};

		static void self();
		static void vehicle();
		static void debug();
		static void view_player();
		static void weapons();
		static void mobile();
		static void teleport();
		static void spawn();
		static void settings();
		static void spoofing();
		static void navigation();
		static void notifications();
		static void active_view();

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
			notifications();
		}
	};
}
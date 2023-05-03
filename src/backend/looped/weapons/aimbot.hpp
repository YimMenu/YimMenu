#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class aimbot : public looped_command
	{
		using looped_command::looped_command;

		Vector3 aim_lock;
		Vector2 mouse_movement;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline aimbot g_aimbot("aimbot", "Aimbot", "lock on and kill", g.weapons.aimbot.enable);

		inline bool_command
		    g_smoothing("smoothing", "Smoothing", "Controls the snappiness of your lock on", g.weapons.aimbot.smoothing);

		inline bool_command
		    g_aimbot_on_player("aimatplayer", "Player", "If you suck at pvp this is for you.", g.weapons.aimbot.on_player);

		inline bool_command g_aimbot_on_npc("aimatnpc", "NPC", "Generally kills normal NPCs", g.weapons.aimbot.on_npc);

		inline bool_command g_aimbot_on_police("aimatpolice", "Police", "Locks onto cops to kill", g.weapons.aimbot.on_police);

		inline bool_command
		    g_aimbot_on_enemy("aimatenemy", "Enemy", "Eliminate your enemies, and win your missions", g.weapons.aimbot.on_enemy);
	}
}

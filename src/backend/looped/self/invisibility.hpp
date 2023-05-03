#pragma once

#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"

namespace big
{
	class invisibility : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline invisibility g_invisibility("invis", "Invisiblity", "Makes you invisible", g.self.invisibility);

		inline bool_command g_local_visibility("localvis", "Visible Locally", "Makes you visible to yourself, but other players would still not be able to see you",
		    g.self.local_visibility);
	}
}

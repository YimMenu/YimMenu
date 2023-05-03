#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class clean_player_looped : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;
	};

	namespace cmd
	{
		inline clean_player_looped g_clean_player_looped("keepclean", "Keep Player Clean", "Prevents wetness and decals from being applied on you",
		    g.self.clean_player);
	}
}

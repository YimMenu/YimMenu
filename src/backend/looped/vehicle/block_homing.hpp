#pragma once

#include "backend/looped_command.hpp"

namespace big
{
	class block_homing : public looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override;

		virtual void on_disable() override;
	};

	namespace cmd
	{
		inline block_homing g_block_homing("blockhoming", "Block Homing Missiles", "Prevents homing missiles from locking on to your vehicle",
		    g.vehicle.block_homing);
	}
}

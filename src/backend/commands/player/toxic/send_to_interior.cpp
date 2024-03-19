#include "backend/player_command.hpp"
#include "natives.hpp"
#include "pointers.hpp"

namespace big
{
	class send_to_interior : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			float max   = 1e+38f;
			auto coords = ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(player->id()), FALSE);
			const size_t arg_count  = 16;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::InteriorControl,
			    (int64_t)self::id,
			    1 << player->id(),
			    (int64_t)_args.get<int>(0),
			    (int64_t)self::id,
			    (int64_t) false,
			    (int64_t) true, // true means enter sender interior
			    (int64_t) * (uint32_t*)&coords.x,
			    (int64_t) * (uint32_t*)&coords.y,
			    (int64_t) * (uint32_t*)&coords.z,
			    0,
			    0,
			    1,
			    (int64_t) * (uint32_t*)&max,
			    (int64_t) true,
			    -1};

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << player->id(), (int)eRemoteEvent::InteriorControl);
		}
	};

	send_to_interior g_send_to_interior("interiortp", "TP_TO_INTERIOR", "TP_TO_INTERIOR_DESC", 1);
}
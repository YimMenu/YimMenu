#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "util/misc.hpp"

#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class enter_interior : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const std::vector<std::uint64_t>& _args, const std::shared_ptr<command_context> ctx)
		{
			int id = player->id();
			if (scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PropertyData.Index != -1)
			{
				const size_t arg_count  = 9;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::Teleport,
				    self::id,
				    (int64_t)player->id(),
				    (int64_t)(int)-1,
				    1,
				    (int64_t)scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PropertyData.Index,
				    1,
				    0,
				    1};

				g_pointers->m_trigger_script_event(1, args, arg_count, 1 << self::id);
			}
			else if (scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Index != eSimpleInteriorIndex::SIMPLE_INTERIOR_INVALID)
			{
				*script_global(1950108).at(3346).as<Player*>() =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Owner;
				*script_global(1950108).at(3683).as<eSimpleInteriorIndex*>() =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Index;
				*script_global(1950108).at(3682).as<bool*>() = true;
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].SimpleInteriorData.InteriorSubtype =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.InteriorSubtype;
			}
			else
			{
				ctx->report_error("Player does not appear to be in an interior");
			}
		}
	};

	enter_interior g_enter_interior("enterint", "Enter Interior", "Enters the player's interior", 0, false);
}
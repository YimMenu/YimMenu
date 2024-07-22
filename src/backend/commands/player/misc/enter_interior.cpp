#include "backend/player_command.hpp"
#include "core/scr_globals.hpp"
#include "pointers.hpp"

#include <script/globals/GPBD_FM.hpp>
#include <script/globals/GlobalPlayerBD.hpp>

namespace big
{
	class enter_interior : player_command
	{
		using player_command::player_command;

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			int id = player->id();
			if (scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PropertyData.Index != -1)
			{
				const size_t arg_count  = 10;
				int64_t args[arg_count] = {(int64_t)eRemoteEvent::Teleport,
				    self::id,
				    1 << self::id,
				    (int64_t)player->id(),
				    (int64_t)(int)-1,
				    1,
				    (int64_t)scr_globals::gpbd_fm_1.as<GPBD_FM*>()->Entries[id].PropertyData.Index,
				    1,
				    0,
				    1};

				g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << self::id, (int)eRemoteEvent::Teleport);
			}
			else if (scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Index != eSimpleInteriorIndex::SIMPLE_INTERIOR_INVALID)
			{
				*scr_globals::interiors.at(3347).as<Player*>() =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Owner;
				*scr_globals::interiors.at(3684).as<eSimpleInteriorIndex*>() =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.Index;
				*scr_globals::interiors.at(3683).as<bool*>() = true;
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].SimpleInteriorData.InteriorSubtype =
				    scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[id].SimpleInteriorData.InteriorSubtype;
			}
			else
			{
				ctx->report_error("BACKEND_ENTER_INTERIOR_NOT_IN_INTERIOR"_T.data());
			}
		}
	};

	enter_interior g_enter_interior("enterint", "ENTER_INTERIOR", "ENTER_INTERIOR_DESC", 0, false);
}
#include "core/scr_globals.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "services/script_patcher/script_patcher_service.hpp"

#include <script/globals/GlobalPlayerBD.hpp>
#include <script/scrProgram.hpp>

static int old_cayo_flags;
static int old_shop_index;

namespace big
{
	class script_vm_guard
	{
		rage::scrProgram* m_program;
		uint8_t** m_orig_bytecode;

	public:
		script_vm_guard(rage::scrProgram* program) :
		    m_program(program)
		{
			m_orig_bytecode = program->m_code_blocks;

			if (auto bytecode = g_script_patcher_service->get_script_bytecode(program->m_name_hash))
				program->m_code_blocks = bytecode;

			if (g_pointers->m_script_globals[0xA])
			{
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CurrentShopIndex = old_shop_index;
				scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CayoPericoFlags  = old_cayo_flags;
			}
		}

		~script_vm_guard()
		{
			m_program->m_code_blocks = m_orig_bytecode;

			if (g_pointers->m_script_globals[0xA])
			{
				old_shop_index = scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CurrentShopIndex;
				old_cayo_flags = scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CayoPericoFlags;

				if (g.spoofing.hide_from_player_list)
				{
					scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CurrentShopIndex = -1;
					scr_globals::globalplayer_bd.as<GlobalPlayerBD*>()->Entries[self::id].CayoPericoFlags  = 1;
				}
			}
		}
	};

	rage::eThreadState hooks::script_vm(uint64_t* start_stack, uint64_t** scr_globals, rage::scrProgram* program, rage::scrThreadContext* ctx)
	{
		script_vm_guard guard(program);
		return g_hooking->get_original<hooks::script_vm>()(start_stack, scr_globals, program, ctx);
	}
}
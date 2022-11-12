#include "native_hooks.hpp"
#include "all_scripts.hpp"
#include "carmod_shop.hpp"
#include "freemode.hpp"
#include "gta_util.hpp"
#include "shop_controller.hpp"
#include "network_session_host.hpp"

#include <script/scrProgram.hpp>
#include <script/scrProgramTable.hpp>

namespace big
{
    constexpr auto ALL_SCRIPT_HASH = RAGE_JOAAT("ALL_SCRIPTS");

    native_hooks::native_hooks()
    {
        add_native_detour(0x812595A0644CE1DE, all_scripts::IS_DLC_PRESENT);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x34E710FF01247C5A, carmod_shop::SET_VEHICLE_LIGHTS);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x767FBC2AC802EF3D, carmod_shop::STAT_GET_INT);
        add_native_detour(RAGE_JOAAT("freemode"), 0x95914459A87EBA28, freemode::NETWORK_BAIL);
        add_native_detour(RAGE_JOAAT("freemode"), 0x5E9564D8246B909A, freemode::IS_PLAYER_PLAYING);
        add_native_detour(RAGE_JOAAT("shop_controller"), 0xDC38CC1E35B6A5D7, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);
        add_native_detour(RAGE_JOAAT("maintransition"), 0x6F3D4ED9BEE4E61D, network::NETWORK_SESSION_HOST);

        for (auto& entry : *g_pointers->m_script_program_table)
            if (entry.m_program)
                hook_program(entry.m_program);

        g_native_hooks = this;
    }

    native_hooks::~native_hooks()
    {
        g_native_hooks = nullptr;
    }

    void native_hooks::add_native_detour(rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
        add_native_detour(ALL_SCRIPT_HASH, hash, detour);
	}

	void native_hooks::add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
	{
		if (const auto& it = m_native_registrations.find(script_hash); it != m_native_registrations.end())
		{
			it->second.emplace_back(hash, detour);
			return;
		}

		m_native_registrations.emplace(script_hash, std::vector<native_detour>({ { hash, detour } }));
	}

    void native_hooks::hook_program(rage::scrProgram* program)
    {
        std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
        const auto script_hash = program->m_name_hash;

        // Functions that need to be detoured for all scripts
        if (const auto& pair = m_native_registrations.find(ALL_SCRIPT_HASH); pair != m_native_registrations.end())
            for (const auto& native_hook_reg : pair->second)
                native_replacements.insert(native_hook_reg);

        // Functions that only need to be detoured for a specific script
        if (const auto& pair = m_native_registrations.find(script_hash); pair != m_native_registrations.end())
            for (const auto& native_hook_reg : pair->second)
                native_replacements.insert(native_hook_reg);

        if (!native_replacements.empty())
        {
            m_script_hooks.emplace(
                program,
                std::make_unique<script_hook>(program, native_replacements)
            );
        }
    }

    void native_hooks::unhook_program(rage::scrProgram* program)
    {
        m_script_hooks.erase(program);
    }
}

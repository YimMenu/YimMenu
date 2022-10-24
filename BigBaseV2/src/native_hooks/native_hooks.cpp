#include "native_hooks.hpp"
#include "all_scripts.hpp"
#include "carmod_shop.hpp"
#include "freemode.hpp"
#include "maintransition.hpp"
#include "gta_util.hpp"
#include "shop_controller.hpp"
#include "ingamehud.hpp"

namespace big
{
    constexpr auto ALL_SCRIPT_HASH = RAGE_JOAAT("ALL_SCRIPTS");

    native_hooks::native_hooks()
    {
        add_native_detour(0x812595A0644CE1DE, all_scripts::IS_DLC_PRESENT);
        add_native_detour(0x5D10B3795F3FC886, all_scripts::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA); // From https://github.com/YimMenu/YimMenu/discussions/143
        add_native_detour(0x95914459A87EBA28, all_scripts::NETWORK_BAIL);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x34E710FF01247C5A, carmod_shop::SET_VEHICLE_LIGHTS);
        add_native_detour(RAGE_JOAAT("carmod_shop"), 0x767FBC2AC802EF3D, carmod_shop::STAT_GET_INT);
        add_native_detour(RAGE_JOAAT("maintransition"), 0x6F3D4ED9BEE4E61D, maintransition::NETWORK_SESSION_HOST); // RID Joiner from https://github.com/YimMenu/YimMenu/issues/172
        add_native_detour(RAGE_JOAAT("maintransition"), 0x933BBEEB8C61B5F4, maintransition::IS_SWITCH_TO_MULTI_FIRSTPART_FINISHED); // This hook lets you stop player-switch in "Pre-HUD Checks"
        add_native_detour(RAGE_JOAAT("maintransition"), 0x06843DA7060A026B, maintransition::SET_ENTITY_COORDS);  // Prevents the game from teleporting you
        add_native_detour(RAGE_JOAAT("maintransition"), 0x1A9205C1B9EE827F, maintransition::SET_ENTITY_COLLISION); // Prevents you from falling
        add_native_detour(RAGE_JOAAT("maintransition"), 0xEA1C610A04DB6BBB, maintransition::SET_ENTITY_VISIBLE);  // Makes you visible
        add_native_detour(RAGE_JOAAT("maintransition"), 0x8D32347D6D4C40A2, maintransition::SET_PLAYER_CONTROL); // Allows controll in session switch
        add_native_detour(RAGE_JOAAT("maintransition"), 0x428CA6DBD1094446, maintransition::FREEZE_ENTITY_POSITION); // Allows controll in session switch
        add_native_detour(RAGE_JOAAT("ingamegud"), 0x6BFB12CE158E3DD4, ingamehud::SC_TRANSITION_NEWS_SHOW); // Stops news. Does this actualy work?
        add_native_detour(RAGE_JOAAT("ingamegud"), 0xFE4C1D0D3B9CC17E, ingamehud::SC_TRANSITION_NEWS_SHOW_TIMED); // Stops news. Does this actualy work?
        add_native_detour(RAGE_JOAAT("shop_controller"), 0xDC38CC1E35B6A5D7, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);

        for (const auto& native_detours_for_script : m_native_registrations)
            if (const auto thread = gta_util::find_script_thread(native_detours_for_script.first); thread != nullptr && thread->m_context.m_state == rage::eThreadState::running)
                this->check_for_thread(thread);

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

    bool native_hooks::check_for_thread(const GtaThread* gta_thread)
    {
        std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
        const auto script_hash = gta_thread->m_script_hash;

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
            if (m_script_hooks.find(gta_thread->m_script_hash) != m_script_hooks.end())
            {
                // this should never happen but if it does we catch it
                LOG_IF(G3LOG_DEBUG, g->debug.logs.script_hook_logs) << "Dynamic native script hook still active for script, cleaning up...";

                m_script_hooks.erase(gta_thread->m_script_hash);
            }

            m_script_hooks.emplace(
                gta_thread->m_script_hash,
                std::make_unique<script_hook>(gta_thread->m_script_hash, native_replacements)
            );

            return true;
        }
        return false;
    }

    void native_hooks::do_cleanup_for_thread(const GtaThread* gta_thread)
    {
        if (m_script_hooks.erase(gta_thread->m_script_hash))
        {
            LOG_IF(G3LOG_DEBUG, g->debug.logs.script_hook_logs) << gta_thread->m_name << " script terminated, cleaning up native hooks";
        }
    }
}
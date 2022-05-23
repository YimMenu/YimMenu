#pragma once
#include "gta_util.hpp"
#include "gta/joaat.hpp"
#include "gta/script_thread.hpp"
#include "native_hooks/carmod_shop.hpp"
#include "native_hooks/freemode.hpp"
#include "native_hooks/shop_controller.hpp"
#include "script_hook.hpp"

namespace big
{
	class native_hooks;
	inline native_hooks* g_native_hooks{};

	class native_hooks final
	{
		typedef std::pair<rage::scrNativeHash, rage::scrNativeHandler> native_detour;

		std::map<rage::joaat_t, std::vector<native_detour>> m_native_registrations;

		std::map<rage::joaat_t, std::unique_ptr<script_hook>> m_script_hooks;

	public:
		native_hooks()
		{
			add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
			add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
			add_native_detour(RAGE_JOAAT("carmod_shop"), 0x34E710FF01247C5A, carmod_shop::SET_VEHICLE_LIGHTS);
			add_native_detour(RAGE_JOAAT("carmod_shop"), 0x767FBC2AC802EF3D, carmod_shop::STAT_GET_INT);
			add_native_detour(RAGE_JOAAT("freemode"), 0x95914459A87EBA28, freemode::NETWORK_BAIL);
			add_native_detour(RAGE_JOAAT("shop_controller"), 0xDC38CC1E35B6A5D7, shop_controller::SET_WARNING_MESSAGE_WITH_HEADER);

			for (const auto& native_detours_for_script : m_native_registrations)
				if (const GtaThread* thread = gta_util::find_script_thread(native_detours_for_script.first); thread != nullptr && thread->m_context.m_state == rage::eThreadState::running)
					this->check_for_thread(thread);

			g_native_hooks = this;
		}
		~native_hooks()
		{
			g_native_hooks = nullptr;
		}

		native_hooks(const native_hooks&) = delete;
		native_hooks(native_hooks&&) noexcept = delete;
		native_hooks& operator=(const native_hooks&) = delete;
		native_hooks& operator=(native_hooks&&) noexcept = delete;

		void add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
		{
			if (const auto& it = m_native_registrations.find(script_hash); it != m_native_registrations.end())
			{
				it->second.emplace_back(hash, detour);

				return;
			}

			m_native_registrations.emplace(script_hash, std::vector<native_detour>({ { hash, detour } }));
		}

		bool check_for_thread(const GtaThread* gta_thread)
		{
			std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
			const auto script_hash = gta_thread->m_script_hash;

			const auto& pair = m_native_registrations.find(script_hash);
			if (pair == m_native_registrations.end())
				return false;

			for (const auto& native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

			if (!native_replacements.empty())
			{
				if (m_script_hooks.find(gta_thread->m_script_hash) != m_script_hooks.end())
				{
					// this should never happen but if it does we catch it
					LOG(INFO) << "Dynamic native script hook still active for script, cleaning up...";

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

		void do_cleanup_for_thread(const GtaThread* gta_thread)
		{
			if (m_script_hooks.erase(gta_thread->m_script_hash))
			{
				LOG(INFO) << gta_thread->m_name << " script terminated, cleaning up native hooks";
			}
		}

	};
}
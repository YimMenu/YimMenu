#pragma once
#include "gta/joaat.hpp"
#include "gta/script_thread.hpp"
#include "native_hooks/carmod_shop.hpp"
#include "native_hooks/freemode.hpp"
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
			this->add_native_detour(RAGE_JOAAT("carmod_shop"), 0x06843DA7060A026B, carmod_shop::SET_ENTITY_COORDS);
			this->add_native_detour(RAGE_JOAAT("carmod_shop"), 0x8E2530AA8ADA980E, carmod_shop::SET_ENTITY_HEADING);
			this->add_native_detour(RAGE_JOAAT("freemode"), 0x580CE4438479CC61, freemode::NETWORK_CAN_BAIL);

			g_native_hooks = this;
		}
		~native_hooks()
		{
			g_native_hooks = nullptr;
		}

		void add_native_detour(rage::joaat_t script_hash, rage::scrNativeHash hash, rage::scrNativeHandler detour)
		{
			if (auto it = m_native_registrations.find(script_hash); it != m_native_registrations.end())
				return it->second.push_back({ hash, detour });

			m_native_registrations.emplace(script_hash, std::vector<native_detour>({ { hash, detour } }));
		}

		bool check_for_thread(GtaThread* gta_thread)
		{
			std::unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements;
			rage::joaat_t script_hash = gta_thread->m_script_hash;

			std::map<rage::joaat_t, std::vector<native_detour>>::iterator pair = m_native_registrations.find(script_hash);
			if (pair == m_native_registrations.end())
				return false;

			for (native_detour native_hook_reg : pair->second)
				native_replacements.insert(native_hook_reg);

			if (native_replacements.size())
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

		void do_cleanup_for_thread(GtaThread* gta_thread)
		{
			if (m_script_hooks.erase(gta_thread->m_script_hash))
			{
				LOG(INFO) << gta_thread->m_name << " script terminated, cleaning up native hooks";
			}
		}

	};
}
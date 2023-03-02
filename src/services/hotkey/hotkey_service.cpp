#include "hotkey_service.hpp"

#include "fiber_pool.hpp"
#include "gui.hpp"
#include "network/ChatData.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "util/teleport.hpp"

namespace big
{
	hotkey_service::hotkey_service()
	{
		register_hotkey("waypoint", g.settings.hotkeys.teleport_waypoint, RAGE_JOAAT("waypointtp"));
		register_hotkey("objective", g.settings.hotkeys.teleport_objective, RAGE_JOAAT("objectivetp"));
		register_hotkey("noclip", g.settings.hotkeys.noclip, RAGE_JOAAT("noclip"));
		register_hotkey("bringpv", g.settings.hotkeys.bringvehicle, RAGE_JOAAT("bringpv"));
		register_hotkey("invis", g.settings.hotkeys.invis, RAGE_JOAAT("invis"));
		register_hotkey("heal", g.settings.hotkeys.heal, RAGE_JOAAT("heal"));
		register_hotkey("fillsnacks", g.settings.hotkeys.fill_inventory, RAGE_JOAAT("fillsnacks"));
		register_hotkey("skipcutscene", g.settings.hotkeys.skip_cutscene, RAGE_JOAAT("skipcutscene"));
		register_hotkey("superjump", g.settings.hotkeys.superjump, RAGE_JOAAT("superjump"));
		register_hotkey("beastjump", g.settings.hotkeys.beastjump, RAGE_JOAAT("beastjump"));
		register_hotkey("invisveh", g.settings.hotkeys.invisveh, RAGE_JOAAT("invisveh"));
		register_hotkey("localinvisveh", g.settings.hotkeys.localinvisveh, RAGE_JOAAT("localinvisveh"));
		register_hotkey("fastquit", g.settings.hotkeys.fast_quit, RAGE_JOAAT("fastquit"));
		register_hotkey("quicksearch", g.settings.hotkeys.cmd_excecutor, RAGE_JOAAT("cmdexecutor"));


		g_renderer->add_wndproc_callback([this](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
			wndproc(static_cast<eKeyState>(msg), wparam);
		});

		g_hotkey_service = this;
	}

	hotkey_service::~hotkey_service()
	{
		g_hotkey_service = nullptr;
	}

	void hotkey_service::register_hotkey(const std::string_view name, key_t key, rage::joaat_t command_hash, eKeyState state, std::optional<std::chrono::high_resolution_clock::duration> cooldown)
	{
		m_hotkeys[state == eKeyState::RELEASE].emplace(key, hotkey(rage::joaat(name), key, command_hash, cooldown));
	}

	bool hotkey_service::update_hotkey(const std::string_view name, const key_t key)
	{
		static auto update_hotkey_map = [](hotkey_map& hotkey_map, rage::joaat_t name_hash, key_t new_key) -> bool {
			for (auto it = hotkey_map.begin(); it != hotkey_map.end(); ++it)
			{
				auto hotkey = it->second;
				if (hotkey.name_hash() != name_hash)
					continue;

				hotkey_map.erase(it);
				hotkey.set_key(new_key);
				hotkey_map.emplace(new_key, hotkey);

				return true;
			}
			return false;
		};

		const auto name_hash = rage::joaat(name);
		return update_hotkey_map(m_hotkeys[1], name_hash, key)  // released
		    && update_hotkey_map(m_hotkeys[0], name_hash, key); // down
	}

	void hotkey_service::wndproc(eKeyState state, key_t key)
	{
		if (const auto chat_data = *g_pointers->m_chat_data; chat_data && (chat_data->m_chat_open || chat_data->m_timer_two))
			return;

		//command executer is opened
		if (g.cmd_executor.enabled)
			return;

		if (g_gui->is_open())
			return;

		if (state == eKeyState::RELEASE || state == eKeyState::DOWN)
		{
			auto& hotkey_map = m_hotkeys[state == eKeyState::RELEASE];
			if (const auto& it = hotkey_map.find(key); it != hotkey_map.end())
			{
				if (auto& hotkey = it->second; hotkey.can_exec())
				{
					g_fiber_pool->queue_job([&hotkey] {
						hotkey.exec();
					});
				}
			}
		}
	}
}
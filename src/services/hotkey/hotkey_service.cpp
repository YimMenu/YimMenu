#include "hotkey_service.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

namespace big
{
    hotkey_service::hotkey_service()
    {
        register_hotkey("waypoint", g->settings.hotkeys.teleport_waypoint, teleport::to_waypoint);
        register_hotkey("objective", g->settings.hotkeys.teleport_objective, teleport::to_objective);

        g_hotkey_service = this;
    }

    hotkey_service::~hotkey_service()
    {
        g_hotkey_service = nullptr;
    }

    void hotkey_service::register_hotkey(const std::string_view name, key_t key, hotkey_func func, eKeyState state, std::optional<std::chrono::high_resolution_clock::duration> cooldown)
    {
        m_hotkeys[state == eKeyState::RELEASE].emplace(key, hotkey(rage::joaat(name), key, func, cooldown));
    }

    bool hotkey_service::update_hotkey(const std::string_view name, const key_t key)
    {
        static auto update_hotkey_map = [key](hotkey_map& hotkey_map, rage::joaat_t name_hash) -> bool
        {
            if (const auto &it = std::find_if(hotkey_map.begin(), hotkey_map.end(), [name_hash](std::pair<key_t, hotkey> pair) -> bool
                {
                    return pair.second.name_hash() == name_hash;
                }); it != hotkey_map.end())
            {
                auto hotkey = it->second;
                hotkey.set_key(key);

                hotkey_map.emplace(key, hotkey);
                hotkey_map.erase(it);

                return true;
            }
            return false;
        };

        const auto name_hash = rage::joaat(name);
        return update_hotkey_map(m_hotkeys[1], name_hash) // released
            && update_hotkey_map(m_hotkeys[0], name_hash); // down
    }

    void hotkey_service::wndproc(eKeyState state, key_t key)
    {
        if (state == eKeyState::RELEASE || state == eKeyState::DOWN)
        {
            auto &hotkey_map = m_hotkeys[state == eKeyState::RELEASE];
            if (const auto &it = hotkey_map.find(key); it != hotkey_map.end())
            {
                if (auto &hotkey = it->second; hotkey.can_exec())
                {
                    g_fiber_pool->queue_job([&hotkey]
                    {
                        hotkey.exec();
                    });
                }
            }
        }
    }
}
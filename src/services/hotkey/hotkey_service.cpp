#include "hotkey_service.hpp"
#include "fiber_pool.hpp"
#include "util/teleport.hpp"

using namespace big;

hotkey_service::hotkey_service()
{
    g_hotkey_service = this;
    add({&g->settings.hotkeys.teleport_waypoint, []{ teleport::to_waypoint(); }});
    add({&g->settings.hotkeys.teleport_objective, []{ teleport::to_objective(); }});
}

hotkey_service::~hotkey_service()
{
    g_hotkey_service = nullptr;
}

void hotkey_service::add(Hotkey key)
{
    m_keys.push_back(key);
}

void hotkey_service::check_keys()
{
    if(GetForegroundWindow() != g_pointers->m_hwnd)
        return;
    static const ImGuiKey key_first = (ImGuiKey)0;
    static bool keys_pressed[ImGuiKey_COUNT] = {};
    static bool keys_released[ImGuiKey_COUNT] = {};
    for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key = (ImGuiKey)(key + 1))
    {
        if (GetAsyncKeyState(key) & 0x8000)
            keys_pressed[key] = true;
        if (keys_pressed[key] && !(GetAsyncKeyState(key) & 0x8000))
        {
            keys_pressed[key] = false;
            keys_released[key] = true;
        }
    }

    for(auto& key : m_keys)
        if (keys_released[*key.m_key])
            g_fiber_pool->queue_job(key.m_cb);

    for (ImGuiKey key = key_first; key < ImGuiKey_COUNT; key = (ImGuiKey)(key + 1))
        keys_released[key] = false;
}
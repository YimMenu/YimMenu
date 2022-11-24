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
    for(auto& key : m_keys)
        if(is_key_released(*key.m_key))
            g_fiber_pool->queue_job(key.m_cb);
}

bool hotkey_service::is_key_released(int key)
{
    static bool keys[260] = {};
    if(GetAsyncKeyState(key) & 0x8000)
        keys[key] = true;
    if(keys[key] && !(GetAsyncKeyState(key) & 0x8000))
    {
        keys[key] = false;
        return true;
    }
    return false;
}
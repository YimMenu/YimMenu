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

void hotkey_service::refresh(int key_released)
{
    for (auto& key : m_keys)
        if (*key.m_key == key_released)
            g_fiber_pool->queue_job(key.m_cb);
}
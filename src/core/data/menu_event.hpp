#pragma once

enum class menu_event
{
    PlayerLeave,
    PlayerJoin,
    PlayerMgrInit,
    PlayerMgrShutdown,
    ChatMessageReceived,
    ScriptedGameEventReceived,
};
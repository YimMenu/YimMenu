#include "hooking.hpp"
#include "pointers.hpp"
#include "services/chat/chat_service.hpp"

namespace big
{
    __int64* hooks::chat_receive(__int64 a1, __int64 a2, __int64 sender, const char* msg, char is_team)
    {
        CNetGamePlayer* Player = g_pointers->m_get_net_player_from_unk(sender);

        if (Player != nullptr)
        {
            g_chat_service->add_msg(Player, msg, (bool)is_team);
            LOG(INFO) << Player->get_name() << ((bool)is_team ? " [LOCAL] " : " [ALL] ") << msg;
        }

        return g_hooking->m_chat_message_received_hook.get_original<decltype(&chat_receive)>()(a1, a2, sender, msg, is_team);
    }
}


/*
48 89 5c 24 08 48 89 54 24 10 57 48 83 ec 20 48 83 61

undefined8 * FUN_7ff7e59cac08(undefined8 *param_1,undefined8 param_2,undefined8 param_3)

{
  char cVar1;
  undefined8 local_res10 [3];

  param_1[1] = 0;
  *(undefined4 *)(param_1 + 2) = 0;
  *(byte *)((longlong)param_1 + 0x14) = *(byte *)((longlong)param_1 + 0x14) & 0xf8;
  *param_1 = CEventNetworkTextMessageReceived::vftable;
  local_res10[0] = param_2;
  cVar1 = FUN_7ff7e5c67d74(param_3);
  if (cVar1 != '\0') {
    FUN_7ff7e5c5b280(param_3,param_1 + 0x13,0x68);
  }
  FUN_7ff7e4883194(param_1 + 3,local_res10,0x80);
  return param_1;
}

*/
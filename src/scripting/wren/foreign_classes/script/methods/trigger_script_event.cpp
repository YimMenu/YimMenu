#include "scripting/wren/foreign_classes/script/wren_script.hpp"
#include "pointers.hpp"

namespace big
{
    void wren_script::trigger_script_event(WrenVM* vm)
    {
        constexpr int event_group = 1;

        constexpr int player_bits_slot = 1;
        int player_bits = (int)wrenGetSlotDouble(vm, player_bits_slot);
        constexpr int send_to_everyone = -1;
        if (player_bits != send_to_everyone)
        {
            player_bits = 1 << player_bits;
        }

        constexpr int args_slot = 2;
        const int arg_count = wrenGetListCount(vm, args_slot);
        std::vector<int64_t> args(arg_count);
        for (int i = 0; i < arg_count; i++)
        {
            constexpr int get_el_slot = 0;
            wrenGetListElement(vm, args_slot, i, get_el_slot);
            args.push_back((int64_t)wrenGetSlotDouble(vm, get_el_slot));
        }

        constexpr size_t args_sender_index = 1;
        if (args.size() > args_sender_index)
            args[args_sender_index] = self::id; // prevent detection from AC
        g_pointers->m_trigger_script_event(event_group, args.data(), arg_count, player_bits);
    }
}

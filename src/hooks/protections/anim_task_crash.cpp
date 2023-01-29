#include "hooking.hpp"
#include "util/misc.hpp"

namespace big
{
    bool hooks::anim_task_crash(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5)
    {
        if (!misc::is_valid_ptr(a2))
            return 0;
        return g_hooking->get_original<hooks::anim_task_crash>()(a1, a2, a3, a4, a5);
    }
}
#include "hooking.hpp"

namespace big
{
    char hooks::indecent_exposure_crash_patch(int64_t a1, int64_t a2)
    {
        __try
        {
            return g_hooking->get_original<indecent_exposure_crash_patch>()(a1, a2);
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return 0;
        }
    }
}

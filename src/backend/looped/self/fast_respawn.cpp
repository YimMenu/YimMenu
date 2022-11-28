#include "backend/looped/looped.hpp"
#include "natives.hpp"

namespace big
{
    void looped::self_fast_respawn()
    {
        if (g->self.fast_respawn)
        {
            if(PED::IS_PED_DEAD_OR_DYING(self::ped, true))
            {
                PED::RESURRECT_PED(self::ped);
                ENTITY::SET_ENTITY_COORDS_NO_OFFSET(self::ped, self::pos.x, self::pos.y, self::pos.z, 0, 0, 0);
            }
        }
    }
}
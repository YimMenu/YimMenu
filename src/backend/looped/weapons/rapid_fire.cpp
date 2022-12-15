#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "gta/enums.hpp"
#include "util/math.hpp"
#include "gui.hpp"

namespace big
{
    void looped::weapons_rapid_fire()
    {
        if (g->weapons.rapid_fire)
        {
            if(!HUD::IS_PAUSE_MENU_ACTIVE() && !g_gui->is_open() && !PED::IS_PED_DEAD_OR_DYING(self::ped, true))
            {
                if (PAD::IS_DISABLED_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_ATTACK))
                {
                    Vector3 direction = math::rotation_to_direction(CAM::GET_GAMEPLAY_CAM_ROT(0));
                    Vector3 start = CAM::GET_GAMEPLAY_CAM_COORD() + direction;
                    Vector3 end = start + direction * 200.0;
                    Hash weapon_hash;
                    WEAPON::GET_CURRENT_PED_WEAPON(self::ped, &weapon_hash, false);
                    MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(start.x, start.y, start.z, end.x, end.y, end.z, WEAPON::GET_WEAPON_DAMAGE(weapon_hash, 0), true, weapon_hash, self::ped, true, false, -1.0);
                }
            }
        }
    }
}
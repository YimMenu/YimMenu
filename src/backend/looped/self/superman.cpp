#include "gta/enums.hpp"
#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "util/is_key_pressed.hpp"

namespace big
{
    class superman : looped_command
    {
        using looped_command::looped_command;

        void apply_force(float x, float y, float z)
        {
            ENTITY::APPLY_FORCE_TO_ENTITY(self::ped, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);
        }

        virtual void on_tick() override
        {
            if(is_key_pressed(VK_SPACE))
                apply_force(0, 0, 10);

            WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, rage::joaat("GADGET_PARACHUTE"), 1, 1);
            if (!ENTITY::IS_ENTITY_IN_AIR(self::ped) || PED::IS_PED_RAGDOLL(self::ped))
                return;
			
            if (is_key_pressed(0x57)) // W key
                apply_force(3, 0, 0);
				
            if (is_key_pressed(0x53)) // S key
                apply_force(3, 6, 0);
			
            if (is_key_pressed(VK_SHIFT))
                apply_force(6, 0, 0);
        }

        virtual void on_enable() override
        {
            g_notification_service->push("Superman Controls", "Use the following keys to control the Superman mode:\n'W' / 'S' / 'SPACE' / 'SHIFT'.");
        }
    };

    superman g_superman("superman", "Superman", "Fly like a superman..", g.self.superman);
}

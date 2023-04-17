#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
namespace big
{
	class superman : looped_command
	{
		using looped_command::looped_command;

		void apply_force(float x, float y, float z)
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(self::ped, 1, x, y, z, 0, 0, 0, 0, true, true, true, false, true);
		}

		virtual void on_tick() override
		{
			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_JUMP))
				apply_force(0, 0, 10);

			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, rage::joaat("GADGET_PARACHUTE"), 1, 1);
			if (!ENTITY::IS_ENTITY_IN_AIR(self::ped) || PED::IS_PED_RAGDOLL(self::ped))
				return;

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_UP_ONLY))
				apply_force(3, 0, 0);

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_MOVE_DOWN_ONLY))
				apply_force(3, 6, 0);

			if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_SPRINT))
				apply_force(6, 0, 0);
		}

		virtual void on_enable() override
		{
			g_notification_service->push("Superman Controls", "Use the following keys to control the Superman mode:\n'W' / 'S' / 'SPACE' / 'SHIFT'.");
		}
	};

	superman g_superman("superman", "Superman", "Fly like a superman", g.self.superman);
}

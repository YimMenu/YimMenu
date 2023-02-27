#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"

namespace big
{
	class no_ragdoll : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			PED::SET_PED_CAN_RAGDOLL(self::ped, false);
		}

		virtual void on_disable() override
		{
			PED::SET_PED_CAN_RAGDOLL(self::ped, true);
		}
	};

	no_ragdoll g_no_ragdoll("noragdoll", "No Ragdoll", "Prevents you from ragdolling", g.self.no_ragdoll);
}

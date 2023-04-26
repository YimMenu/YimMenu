#include "backend/looped_command.hpp"
#include "core/enums.hpp"
#include "natives.hpp"
#include "vehicle/CVehicleModelInfo.hpp"
#include "gta/enums.hpp"

namespace big
{
	class ability_selector : looped_command
	{
		using looped_command::looped_command;

		uint16_t og_ability = 0;
		int byte0;
		int byte1;
		bool edited = false;

		virtual void on_tick() override
		{

			if (g_local_player && g_local_player->m_vehicle && self::veh)
			{
				CVehicleModelInfo* modelinfo = (CVehicleModelInfo*)g_local_player->m_vehicle->m_model_info;

				if (!edited)
					og_ability = modelinfo->m_ability_flag;

				if (PED::IS_PED_DEAD_OR_DYING(self::ped, 0) || PAD::IS_CONTROL_JUST_PRESSED(0, (int)ControllerInputs::INPUT_VEH_EXIT))
				{
					g.vehicle.abilities.boost = false;
					g.vehicle.abilities.jump = false;
					g.vehicle.abilities.parachute = false;
					g.vehicle.abilities.rampbuggy = false;
					modelinfo->m_ability_flag = og_ability;
					edited                    = false;
				}

				if (!g.vehicle.abilities.boost&& !g.vehicle.abilities.jump&& !g.vehicle.abilities.parachute && !g.vehicle.abilities.rampbuggy)
				{
					modelinfo->m_ability_flag = og_ability;
					edited                    = false;
				}

				if (g.vehicle.abilities.jump && !g.vehicle.abilities.boost){edited = true; byte0 = 32;}
				if (g.vehicle.abilities.boost && !g.vehicle.abilities.jump){edited = true; byte0= 64;}
				if (g.vehicle.abilities.boost && g.vehicle.abilities.jump){edited = true; byte0 = 96;}
				if (g.vehicle.abilities.parachute && !g.vehicle.abilities.rampbuggy){edited = true; byte1 = 1;}
				if (g.vehicle.abilities.rampbuggy && !g.vehicle.abilities.parachute){edited = true; byte1 = 2;}
				if (g.vehicle.abilities.rampbuggy && g.vehicle.abilities.parachute){edited = true; byte1 = 3;}

				uint16_t value            = modelinfo->m_ability_flag;
				uint8_t* bytes            = reinterpret_cast<uint8_t*>(&value);
				bytes[0]                  = byte0;
				bytes[1]                  = byte1;
				modelinfo->m_ability_flag = value;
			}
		}
	};

	ability_selector g_ability_selector("vehabilities", "Override Ability", "Allows you to override your vehicle's ability with whatever you've choosen.",
	    g.vehicle.ability_toggle);
}
#include "backend/looped_command.hpp"
#include "util/vehicle.hpp"
#include "util/misc.hpp"
#include "gta/enums.hpp"

#include <vehicle/CVehicleModelInfo.hpp>

namespace big
{
	const std::vector<int16_t> bits = {
		static_cast<int16_t>(eVehicleAbilities::JUMP), 
		static_cast<int16_t>(eVehicleAbilities::ROCKET), 
		static_cast<int16_t>(eVehicleAbilities::PARACHUTE), 
		static_cast<int16_t>(eVehicleAbilities::RAMP_BUGGY)
	};

	bool dont_disable[4]         = {};
	static CVehicle* current_veh = nullptr;

	class vehicle_ability : looped_command
	{
		using looped_command::looped_command;

		virtual void on_enable() override
		{
			CVehicle* vehicle_ptr = static_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(self::veh));

			if (vehicle_ptr == nullptr) 
				memset(dont_disable, 0, 4);
			else
			{
				CVehicleModelInfo* vehicle_model_info = static_cast<CVehicleModelInfo*>(vehicle_ptr->m_model_info);

				for (int i = 0; i < 4; i++)
					dont_disable[i] = misc::has_bits_set((int*)vehicle_model_info->m_ability_flag, bits[i]);
			}

			g.vehicle.ability_jump      = dont_disable[0];
			g.vehicle.ability_rocket    = dont_disable[1];
			g.vehicle.ability_parachute = dont_disable[2];
			g.vehicle.ability_ramp      = dont_disable[3];
		}

		virtual void on_tick() override
		{
			CVehicle* vehicle_ptr = static_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(self::veh));

			if (vehicle_ptr == nullptr || (current_veh && vehicle_ptr != current_veh))
			{
				current_veh                      = nullptr;
				g.vehicle.modify_vehicle_ability = false;
				return;
			}
			current_veh = vehicle_ptr;

			CVehicleModelInfo* vehicle_model_info = static_cast<CVehicleModelInfo*>(vehicle_ptr->m_model_info);

			if (g.vehicle.ability_jump)
				misc::set_bits((int*)vehicle_model_info->m_ability_flag, bits[0]);
			else
				misc::clear_bits((int*)vehicle_model_info->m_ability_flag, bits[0]);

			if (g.vehicle.ability_rocket)
				misc::set_bits((int*)vehicle_model_info->m_ability_flag, bits[1]);
			else
				misc::clear_bits((int*)vehicle_model_info->m_ability_flag, bits[1]);

			if (g.vehicle.ability_parachute)
				misc::set_bits((int*)vehicle_model_info->m_ability_flag, bits[2]);
			else
				misc::clear_bits((int*)vehicle_model_info->m_ability_flag, bits[2]);
			
			if (g.vehicle.ability_ramp)
				misc::set_bits((int*)vehicle_model_info->m_ability_flag, bits[3]);
			else
				misc::clear_bits((int*)vehicle_model_info->m_ability_flag, bits[3]);
		}

		virtual void on_disable() override
		{
			current_veh = nullptr;

			CVehicle* vehicle_ptr = static_cast<CVehicle*>(g_pointers->m_gta.m_handle_to_ptr(self::veh));

			if (vehicle_ptr == nullptr)
				return;

			CVehicleModelInfo* vehicle_model_info = static_cast<CVehicleModelInfo*>(vehicle_ptr->m_model_info);

			for (int i = 0; i < 4; i++)
			{
				if (!dont_disable[i]) {
					misc::clear_bits((int*)vehicle_model_info->m_ability_flag, bits[i]);
					continue;
				}

				if (!misc::has_bits_set((int*)vehicle_model_info->m_ability_flag, bits[i]))
					misc::set_bits((int*)vehicle_model_info->m_ability_flag, bits[i]); // e.g the user disables the rocket on a rocket vehicle, re-apply the bit
			}
		}
	};

	vehicle_ability g_vehicle_ability("modifyvehicleability", "MODIFY_VEHICLE_ABILITY", "MODIFY_VEHICLE_ABILITY_DESC", g.vehicle.modify_vehicle_ability);

	bool_command g_jump_ability("jumpability", "BACKEND_LOOPED_VEHICLE_ABILITY_JUMP", "BACKEND_LOOPED_VEHICLE_ABILITY_JUMP_DESC", g.vehicle.ability_jump);
	bool_command g_rocket_ability("rocketability", "BACKEND_LOOPED_VEHICLE_ABILITY_ROCKET", "BACKEND_LOOPED_VEHICLE_ABILITY_ROCKET_DESC", g.vehicle.ability_rocket);
	bool_command g_parachute_ability("parachuteability", "BACKEND_LOOPED_VEHICLE_ABILITY_PARACHUTE", "BACKEND_LOOPED_VEHICLE_ABILITY_PARACHUTE_DESC", g.vehicle.ability_parachute);
	bool_command g_ramp_ability("rampability", "BACKEND_LOOPED_VEHICLE_ABILITY_RAMP", "BACKEND_LOOPED_VEHICLE_ABILITY_RAMP_DESC", g.vehicle.ability_ramp);
}
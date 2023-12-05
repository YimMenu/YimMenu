#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "util/misc.hpp"
#include "util/vehicle.hpp"

#include <vehicle/CVehicleModelInfo.hpp>

namespace big
{
	class vehicle_ability : looped_command
	{
		using looped_command::looped_command;

		class vehicle_ability_helper
		{
		private:
			static constexpr std::array<eVehicleAbilities, 4> m_abilities = {
				eVehicleAbilities::JUMP,
				eVehicleAbilities::ROCKET,
				eVehicleAbilities::PARACHUTE,
				eVehicleAbilities::RAMP_BUGGY,
			};

		private:
			std::unordered_set<eVehicleAbilities> m_stock_abilities;
			CVehicle* m_vehicle = nullptr;
			uint16_t m_original_abilities;

		public:
			vehicle_ability_helper() = default;
			vehicle_ability_helper(CVehicle* vehicle)
			{
				if (vehicle == nullptr || vehicle->m_model_info == nullptr)
					return;
				m_vehicle = vehicle;

				const auto model_info = reinterpret_cast<CVehicleModelInfo*>(vehicle->m_model_info);
				m_original_abilities = model_info->m_ability_flag;

				for (const auto ability : m_abilities)
				{
					if (m_original_abilities >> (uint16_t)ability & 1)
					{
						m_stock_abilities.insert(ability);
					}
				}
			}

			/**
			 * @brief Gets the initial ability value of the vehicle.
			 * 
			 * @param ability 
			 * @return true 
			 * @return false 
			 */
			bool get_ability_default(eVehicleAbilities ability)
			{
				return m_stock_abilities.contains(ability);
			}

			/**
			 * @brief Checks if the currently bound CVehicle ptr has the flag enabled.
			 * 
			 * @param ability 
			 * @return true 
			 * @return false 
			 */
			bool has_ability(eVehicleAbilities ability)
			{
				return m_vehicle && m_vehicle->m_model_info && reinterpret_cast<CVehicleModelInfo*>(m_vehicle->m_model_info)->m_ability_flag >> (uint16_t)ability & 1;
			}

			/**
			 * @brief Resets the vehicle to its defaults safely!
			 */
			void reset_defaults()
			{
				if (m_vehicle && m_vehicle->m_model_info)
				{
					const auto model_info = reinterpret_cast<CVehicleModelInfo*>(m_vehicle->m_model_info);

					model_info->m_ability_flag = m_original_abilities;
				}
			}

			/**
			 * @brief Safely set the ability state of a vehicle.
			 * 
			 * @param ability 
			 * @param toggle 
			 */
			void toggle_ability(eVehicleAbilities ability, bool toggle)
			{
				if (m_vehicle && m_vehicle->m_model_info)
				{
					const auto model_info = reinterpret_cast<CVehicleModelInfo*>(m_vehicle->m_model_info);
					if (toggle)
						misc::set_bits(&model_info->m_ability_flag, (uint16_t)ability);
					else
						misc::clear_bits(&model_info->m_ability_flag, (uint16_t)ability);
				}
			}

			bool operator ==(const CVehicle* vehicle) const
			{
				return m_vehicle == vehicle;
			}

		} m_vehicle_ability_helper {};

		virtual void on_enable() override
		{
			reset(g_local_player->m_vehicle);
		}

		virtual void on_tick() override
		{
			const auto curr_veh = g_local_player->m_vehicle;
			if (curr_veh && !(g_local_player->m_ped_task_flag & (int)ePedTask::TASK_DRIVING))
			{
				m_vehicle_ability_helper.reset_defaults();
				return;
			}

			if (m_vehicle_ability_helper != curr_veh)
			{
				reset(curr_veh);
			}

			m_vehicle_ability_helper.toggle_ability(eVehicleAbilities::JUMP, g.vehicle.abilities.jump);
			m_vehicle_ability_helper.toggle_ability(eVehicleAbilities::ROCKET, g.vehicle.abilities.rocket);
			m_vehicle_ability_helper.toggle_ability(eVehicleAbilities::PARACHUTE, g.vehicle.abilities.parachute);
			m_vehicle_ability_helper.toggle_ability(eVehicleAbilities::RAMP_BUGGY, g.vehicle.abilities.ramp);
		}

		virtual void on_disable() override
		{
			reset(nullptr);
		}

		void reset(CVehicle* vehicle)
		{
			if (vehicle == nullptr)
			{
				m_vehicle_ability_helper = {};
				g.vehicle.abilities = {};

				return;
			}

			m_vehicle_ability_helper.reset_defaults();
			m_vehicle_ability_helper = { vehicle };

			// currently I'd keep overwriting the display values for what is default for the current vehicle
			// should we always persist the user's choice onto the vehicle? or only the ones that are enabled?
			// doesn't sound like too great of an idea for vehicles that have abilities by default and then suddenly they're disabled
			g.vehicle.abilities.jump      = m_vehicle_ability_helper.get_ability_default(eVehicleAbilities::JUMP);
			g.vehicle.abilities.rocket    = m_vehicle_ability_helper.get_ability_default(eVehicleAbilities::ROCKET);
			g.vehicle.abilities.parachute = m_vehicle_ability_helper.get_ability_default(eVehicleAbilities::PARACHUTE);
			g.vehicle.abilities.ramp      = m_vehicle_ability_helper.get_ability_default(eVehicleAbilities::RAMP_BUGGY);
		}
	};

	vehicle_ability
	    g_vehicle_ability("modifyvehicleability", "MODIFY_VEHICLE_ABILITY", "MODIFY_VEHICLE_ABILITY_DESC", g.vehicle.abilities.enabled);

	bool_command g_jump_ability("jumpability", "BACKEND_LOOPED_VEHICLE_ABILITY_JUMP", "BACKEND_LOOPED_VEHICLE_ABILITY_JUMP_DESC",
	    g.vehicle.abilities.jump);
	bool_command g_rocket_ability("rocketability", "BACKEND_LOOPED_VEHICLE_ABILITY_ROCKET", "BACKEND_LOOPED_VEHICLE_ABILITY_ROCKET_DESC",
	    g.vehicle.abilities.rocket);
	bool_command g_parachute_ability("parachuteability", "BACKEND_LOOPED_VEHICLE_ABILITY_PARACHUTE", "BACKEND_LOOPED_VEHICLE_ABILITY_PARACHUTE_DESC",
	    g.vehicle.abilities.parachute);
	bool_command g_ramp_ability("rampability", "BACKEND_LOOPED_VEHICLE_ABILITY_RAMP", "BACKEND_LOOPED_VEHICLE_ABILITY_RAMP_DESC",
	    g.vehicle.abilities.ramp);
}
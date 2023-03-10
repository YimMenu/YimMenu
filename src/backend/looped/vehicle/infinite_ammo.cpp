#include "backend/looped_command.hpp"
#include "natives.hpp"

namespace big
{
	class infinite_vehicle_ammo : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			auto model = ENTITY::GET_ENTITY_MODEL(self::veh);
			std::array<uint32_t, 12> weaponHashes = {0x7CBE304C, 0x44A56189, 0xA247D03E, 0xB4F96934, 0x753A78F1, 0x8BB7C63E, 0x6C88E47D, 0xBCE908DB, 0x504DA665, 0x1EF01D8A, 0x9E5840A2, 0x3C83C410};

			for (auto hash : weaponHashes)
			{
				VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(model, hash, -1);
			} // Setting to -1 will disable the used missiles count
		}

		virtual void on_disable() override
		{
			auto model = ENTITY::GET_ENTITY_MODEL(self::veh);
			std::array<uint32_t, 12> weaponHashes = {0x7CBE304C, 0x44A56189, 0xA247D03E, 0xB4F96934, 0x753A78F1, 0x8BB7C63E, 0x6C88E47D, 0xBCE908DB, 0x504DA665, 0x1EF01D8A, 0x9E5840A2, 0x3C83C410};

			for (auto hash : weaponHashes)
			{
				VEHICLE::SET_VEHICLE_WEAPON_RESTRICTED_AMMO(model, hash, NULL);
			}
		}
	};

	infinite_vehicle_ammo g_infinite_vehicle_ammo("vehinfammo", "Infinite Vehicle Ammo", "Never run out of vehicle ammo again", g.vehicle.unlimited_ammo);
}

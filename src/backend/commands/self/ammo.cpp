#include "ammo.hpp"

#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	void fill_ammo::execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
	{
		for (const auto& [_, weapon] : g_gta_data_service->weapons())
		{
			int ammo_in;
			WEAPON::GET_MAX_AMMO(self::ped, weapon.m_hash, &ammo_in);
			WEAPON::SET_PED_AMMO(self::ped, weapon.m_hash, ammo_in, 0);
		}
	}
}

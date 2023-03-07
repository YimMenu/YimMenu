#include "backend/command.hpp"
#include "natives.hpp"
#include "services/gta_data/gta_data_service.hpp"

namespace big
{
	class fill_ammo : command
	{
		using command::command;

		virtual void execute(const std::vector<std::uint64_t>&, const std::shared_ptr<command_context> ctx)
		{
			for (const auto& [_, weapon] : g_gta_data_service->weapons())
			{
				int ammo_in;
				WEAPON::GET_MAX_AMMO(self::ped, weapon.m_hash, &ammo_in);
				WEAPON::SET_PED_AMMO(self::ped, weapon.m_hash, ammo_in, 0);
			}
		}
	};
	fill_ammo g_fill_ammo("fillammo", "Fill Ammo", "Fills all of your ammo.", 0);
}
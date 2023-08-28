#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "services/tunables/tunables_service.hpp"
#include "pointers.hpp"

namespace big
{
	static bool initalized_backup = false;
	static std::map<Hash, BOOL> backup_map{};
	static constexpr auto list_of_hashes = {RAGE_JOAAT("GR_BLOCK_APC_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_ARDENT_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_NIGHTSHARK_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_INSURGENT3_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_TECHNICAL3_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_HALFTRACK_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_TRAILERSMALL_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_TAMPA3_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_DUNE3_IN_HEISTS"), RAGE_JOAAT("GR_BLOCK_OPPRESSOR_IN_HEISTS"), RAGE_JOAAT("SMUG_BLOCK_VIGILANTE_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_THRUSTER_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_DELUXO_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_STROMBERG_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_RCV_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_CHERNOBOG_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_BARRAGE_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_KHANJALI_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_SAFARI_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_SAVESTRA_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_AVENGER_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_VOLATOL_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_AKULA_IN_HEISTS"), RAGE_JOAAT("BB_BLOCK_OPPRESSOR2_IN_HEISTS"), RAGE_JOAAT("BB_BLOCK_SCRAMJET_IN_HEISTS"), RAGE_JOAAT("BLOCK_HYDRA_IN_HEISTS"), RAGE_JOAAT("BLOCK_TOREADOR_IN_HEISTS"), RAGE_JOAAT("H2_BLOCK_VISERIS_IN_HEISTS")};

	class allvehsinheists : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			if (*g_pointers->m_gta.m_is_session_started)
			{
				if (initalized_backup == false)
				{
					for (Hash tunable_hash : list_of_hashes)
					{
						if (auto tunable_ptr = g_tunables_service->get_tunable<PBOOL>(tunable_hash))
						{
							backup_map[tunable_hash] = *tunable_ptr;
							initalized_backup        = true;
						}
					}
				}
				else
				{
					for (Hash tunable_hash : list_of_hashes)
					{
						if (auto tunable_ptr = g_tunables_service->get_tunable<PBOOL>(tunable_hash))
						{
							*tunable_ptr = FALSE;
						}
					}
				}
			}
		}

		virtual void on_disable() override
		{
			if (*g_pointers->m_gta.m_is_session_started && initalized_backup)
			{
				for (Hash tunable_hash : list_of_hashes)
				{
					if (auto tunable_ptr = g_tunables_service->get_tunable<PBOOL>(tunable_hash)) //Sanity check in case of tunables_service failure.
					{
						*tunable_ptr = backup_map[tunable_hash];
					}
				}
			}
		}
	};

	allvehsinheists g_allvehsinheists("allvehsinheists", "VEHICLE_ALLOW_ALL_IN_HEISTS", "VEHICLE_ALLOW_ALL_IN_HEISTS_DESC", g.vehicle.all_vehs_in_heists);
}
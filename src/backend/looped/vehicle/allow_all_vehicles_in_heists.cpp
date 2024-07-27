#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "services/tunables/tunables_service.hpp"
#include "pointers.hpp"

namespace big
{
	constexpr auto list_of_hashes = {"GR_BLOCK_APC_IN_HEISTS"_J, "GR_BLOCK_ARDENT_IN_HEISTS"_J, "GR_BLOCK_NIGHTSHARK_IN_HEISTS"_J, "GR_BLOCK_INSURGENT3_IN_HEISTS"_J, "GR_BLOCK_TECHNICAL3_IN_HEISTS"_J, "GR_BLOCK_HALFTRACK_IN_HEISTS"_J, "GR_BLOCK_TRAILERSMALL_IN_HEISTS"_J, "GR_BLOCK_TAMPA3_IN_HEISTS"_J, "GR_BLOCK_DUNE3_IN_HEISTS"_J, "GR_BLOCK_OPPRESSOR_IN_HEISTS"_J, "SMUG_BLOCK_VIGILANTE_IN_HEISTS"_J, "H2_BLOCK_THRUSTER_IN_HEISTS"_J, "H2_BLOCK_DELUXO_IN_HEISTS"_J, "H2_BLOCK_STROMBERG_IN_HEISTS"_J, "H2_BLOCK_RCV_IN_HEISTS"_J, "H2_BLOCK_CHERNOBOG_IN_HEISTS"_J, "H2_BLOCK_BARRAGE_IN_HEISTS"_J, "H2_BLOCK_KHANJALI_IN_HEISTS"_J, "H2_BLOCK_SAFARI_IN_HEISTS"_J, "H2_BLOCK_SAVESTRA_IN_HEISTS"_J, "H2_BLOCK_AVENGER_IN_HEISTS"_J, "H2_BLOCK_VOLATOL_IN_HEISTS"_J, "H2_BLOCK_AKULA_IN_HEISTS"_J, "BB_BLOCK_OPPRESSOR2_IN_HEISTS"_J, "BB_BLOCK_SCRAMJET_IN_HEISTS"_J, "BLOCK_HYDRA_IN_HEISTS"_J, "BLOCK_TOREADOR_IN_HEISTS"_J, "H2_BLOCK_VISERIS_IN_HEISTS"_J};

	class allvehsinheists : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			for (Hash tunable_hash : list_of_hashes)
			{
				if (auto tunable_ptr = g_tunables_service->get_tunable<PBOOL>(tunable_hash)) [[likely]]
				{
					if (*tunable_ptr != FALSE) [[unlikely]]
						*tunable_ptr = FALSE;
				}
			}
		}
	};

	allvehsinheists g_allvehsinheists("allvehsinheists", "VEHICLE_ALLOW_ALL_IN_HEISTS", "VEHICLE_ALLOW_ALL_IN_HEISTS_DESC", g.vehicle.all_vehs_in_heists);
}

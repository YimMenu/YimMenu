#include "backend/looped/looped.hpp"
#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class allvehsinheists : looped_command
	{
		using looped_command::looped_command;

		virtual void on_tick() override
		{
			*scr_globals::tuneables.at(21911).as<PBOOL>() = FALSE; //APC
			*scr_globals::tuneables.at(21912).as<PBOOL>() = FALSE; //ARDENT
			*scr_globals::tuneables.at(21913).as<PBOOL>() = FALSE; //NIGHTSHARK
			*scr_globals::tuneables.at(21914).as<PBOOL>() = FALSE; //INSURGENT3
			*scr_globals::tuneables.at(21915).as<PBOOL>() = FALSE; //TECHNICAL3
			*scr_globals::tuneables.at(21916).as<PBOOL>() = FALSE; //HALFTRACK
			*scr_globals::tuneables.at(21917).as<PBOOL>() = FALSE; //TRAILERSMALL
			*scr_globals::tuneables.at(21918).as<PBOOL>() = FALSE; //TAMPA3
			*scr_globals::tuneables.at(21919).as<PBOOL>() = FALSE; //DUNE3
			*scr_globals::tuneables.at(21920).as<PBOOL>() = FALSE; //OPPRESSOR
			*scr_globals::tuneables.at(23026).as<PBOOL>() = FALSE; //VIGILANTE
			*scr_globals::tuneables.at(23597).as<PBOOL>() = FALSE; //THRUSTER
			*scr_globals::tuneables.at(23598).as<PBOOL>() = FALSE; //DELUXO
			*scr_globals::tuneables.at(23599).as<PBOOL>() = FALSE; //STROMBERG
			*scr_globals::tuneables.at(23600).as<PBOOL>() = FALSE; //RCV
			*scr_globals::tuneables.at(23601).as<PBOOL>() = FALSE; //CHERNOBOG
			*scr_globals::tuneables.at(23602).as<PBOOL>() = FALSE; //BARRAGE
			*scr_globals::tuneables.at(23603).as<PBOOL>() = FALSE; //KHANJALI
			*scr_globals::tuneables.at(23604).as<PBOOL>() = FALSE; //SAFARI
			*scr_globals::tuneables.at(23605).as<PBOOL>() = FALSE; //SAVESTRA
			*scr_globals::tuneables.at(23607).as<PBOOL>() = FALSE; //REVOLTER
			*scr_globals::tuneables.at(23608).as<PBOOL>() = FALSE; //AVENGER
			*scr_globals::tuneables.at(23609).as<PBOOL>() = FALSE; //VOLATOL
			*scr_globals::tuneables.at(23610).as<PBOOL>() = FALSE; //AKULA
			*scr_globals::tuneables.at(23611).as<PBOOL>() = FALSE; //OPPRESSOR2
			*scr_globals::tuneables.at(23612).as<PBOOL>() = FALSE; //SCRAMJET
			*scr_globals::tuneables.at(23613).as<PBOOL>() = FALSE; //HYDRA
			*scr_globals::tuneables.at(25952).as<PBOOL>() = FALSE; //TOREADOR
			*scr_globals::tuneables.at(23606).as<PBOOL>() = FALSE; //VISERIS
		}

		virtual void on_disable() override
		{
			*scr_globals::tuneables.at(21911).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_APC_IN_HEISTS"));
			*scr_globals::tuneables.at(21912).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_ARDENT_IN_HEISTS"));
			*scr_globals::tuneables.at(21913).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_NIGHTSHARK_IN_HEISTS"));
			*scr_globals::tuneables.at(21914).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_INSURGENT3_IN_HEISTS"));
			*scr_globals::tuneables.at(21915).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_TECHNICAL3_IN_HEISTS"));
			*scr_globals::tuneables.at(21916).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_HALFTRACK_IN_HEISTS"));
			*scr_globals::tuneables.at(21917).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_TRAILERSMALL_IN_HEISTS"));
			*scr_globals::tuneables.at(21918).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_TAMPA3_IN_HEISTS"));
			*scr_globals::tuneables.at(21919).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_DUNE3_IN_HEISTS"));
			*scr_globals::tuneables.at(21920).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("GR_BLOCK_OPPRESSOR_IN_HEISTS"));
			*scr_globals::tuneables.at(23026).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("SMUG_BLOCK_VIGILANTE_IN_HEISTS"));
			*scr_globals::tuneables.at(23597).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_THRUSTER_IN_HEISTS"));
			*scr_globals::tuneables.at(23598).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_DELUXO_IN_HEISTS"));
			*scr_globals::tuneables.at(23599).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_STROMBERG_IN_HEISTS"));
			*scr_globals::tuneables.at(23600).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_RCV_IN_HEISTS"));
			*scr_globals::tuneables.at(23601).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_CHERNOBOG_IN_HEISTS"));
			*scr_globals::tuneables.at(23602).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_BARRAGE_IN_HEISTS"));
			*scr_globals::tuneables.at(23603).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_KHANJALI_IN_HEISTS"));
			*scr_globals::tuneables.at(23604).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_SAFARI_IN_HEISTS")); 
			*scr_globals::tuneables.at(23605).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_SAVESTRA_IN_HEISTS"));
			*scr_globals::tuneables.at(23607).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_REVOLTER_IN_HEISTS"));
			*scr_globals::tuneables.at(23608).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_AVENGER_IN_HEISTS"));
			*scr_globals::tuneables.at(23609).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_VOLATOL_IN_HEISTS"));
			*scr_globals::tuneables.at(23610).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_AKULA_IN_HEISTS"));
			*scr_globals::tuneables.at(23611).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("BB_BLOCK_OPPRESSOR2_IN_HEISTS"));
			*scr_globals::tuneables.at(23612).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("BB_BLOCK_SCRAMJET_IN_HEISTS"));
			*scr_globals::tuneables.at(23613).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("BLOCK_HYDRA_IN_HEISTS"));
			*scr_globals::tuneables.at(25952).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("BLOCK_TOREADOR_IN_HEISTS"));
			*scr_globals::tuneables.at(23606).as<PBOOL>() = *g_tunables_service->get_tunable<PBOOL>(RAGE_JOAAT("H2_BLOCK_VISERIS_IN_HEISTS"));
		}
	};

	allvehsinheists g_allvehsinheists("allvehsinheists", "VEHICLE_ALLOW_ALL_IN_HEISTS", "VEHICLE_ALLOW_ALL_IN_HEISTS_DESC", g.vehicle.all_vehs_in_heists);
}
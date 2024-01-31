#include "vehicle_helper.hpp"

#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

#include <util/gxt_label.hpp>

namespace big
{
	void vehicle_helper::add_clan_logo_to_vehicle(Vehicle vehicle, Ped ped)
	{
		rage::fvector3 x, y, z;
		float scale;
		Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
		if (GetVehicleInfoForClanLogo(modelHash, x, y, z, scale))
		{
			int alpha = 200;
			if (modelHash == VEHICLE_WINDSOR || modelHash == VEHICLE_COMET4)
				alpha = 255;

			GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
			if (y.z >= 0.0f)
				GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "chassis_dummy"), x.x * -1.0f, x.y, x.z, y.x * -1.0f, y.y, y.z, z.x * -1.0f, z.y * -1.0f, z.z, scale, 1, alpha);
		}
	}

	const char* vehicle_helper::get_mod_slot_name(Hash model, Vehicle vehicle, int mod_slot)
	{
		switch (mod_slot)
		{
		case MOD_HOOD: return get_gxt_label("CMOD_MOD_HOD").c_str();
		case MOD_ARMOR: return get_gxt_label("CMOD_MOD_ARM").c_str();
		case MOD_BRAKES: return get_gxt_label("CMOD_MOD_BRA").c_str();
		case MOD_ENGINE: return get_gxt_label("CMOD_MOD_ENG").c_str();
		case MOD_SUSPENSION: return get_gxt_label("CMOD_MOD_SUS").c_str();
		case MOD_TRANSMISSION: return get_gxt_label("CMOD_MOD_TRN").c_str();
		case MOD_HORNS: return get_gxt_label("CMOD_MOD_HRN").c_str();
		case MOD_FRONTWHEEL:
		{
			if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
				return get_gxt_label("CMOD_MOD_WHEM").c_str();
			return get_gxt_label("CMOD_WHE0_0").c_str();
		}
		case MOD_REARWHEEL:
			return get_gxt_label("CMOD_WHE0_1").c_str();
			//Bennys
		case MOD_PLATEHOLDER: return get_gxt_label("CMM_MOD_S0").c_str();
		case MOD_VANITYPLATES: return get_gxt_label("CMM_MOD_S1").c_str();
		case MOD_TRIMDESIGN:
		{
			if (model == VEHICLE_SULTANRS)
				return get_gxt_label("CMM_MOD_S2b").c_str();
			return get_gxt_label("CMM_MOD_S2").c_str();
		}
		case MOD_ORNAMENTS: return get_gxt_label("CMM_MOD_S3").c_str();
		case MOD_DASHBOARD: return get_gxt_label("CMM_MOD_S4").c_str();
		case MOD_DIALDESIGN: return get_gxt_label("CMM_MOD_S5").c_str();
		case MOD_DOORSPEAKERS: return get_gxt_label("CMM_MOD_S6").c_str();
		case MOD_SEATS: return get_gxt_label("CMM_MOD_S7").c_str();
		case MOD_STEERINGWHEELS: return get_gxt_label("CMM_MOD_S8").c_str();
		case MOD_COLUMNSHIFTERLEVERS: return get_gxt_label("CMM_MOD_S9").c_str();
		case MOD_PLAQUES: return get_gxt_label("CMM_MOD_S10").c_str();
		case MOD_SPEAKERS: return get_gxt_label("CMM_MOD_S11").c_str();
		case MOD_TRUNK: return get_gxt_label("CMM_MOD_S12").c_str();
		case MOD_HYDRO: return get_gxt_label("CMM_MOD_S13").c_str();
		case MOD_ENGINEBLOCK: return get_gxt_label("CMM_MOD_S14").c_str();
		case MOD_AIRFILTER:
		{
			if (model == VEHICLE_SULTANRS)
				return get_gxt_label("CMM_MOD_S15b").c_str();
			return get_gxt_label("CMM_MOD_S15").c_str();
		}
		case MOD_STRUTS:
		{
			if (model == VEHICLE_SULTANRS || model == VEHICLE_BANSHEE2)
				return get_gxt_label("CMM_MOD_S16b").c_str();
			return get_gxt_label("CMM_MOD_S16").c_str();
		}
		case MOD_ARCHCOVER:
		{
			if (model == VEHICLE_SULTANRS)
				return get_gxt_label("CMM_MOD_S17b").c_str();
			return get_gxt_label("CMM_MOD_S17").c_str();
		}
		case MOD_AERIALS:
		{
			if (model == VEHICLE_SULTANRS)
				return get_gxt_label("CMM_MOD_S18b").c_str();
			if (model == VEHICLE_BTYPE3)
				return get_gxt_label("CMM_MOD_S18c").c_str();
			return get_gxt_label("CMM_MOD_S18").c_str();
		}
		case MOD_TRIM:
		{
			if (model == VEHICLE_SULTANRS)
				return get_gxt_label("CMM_MOD_S19b").c_str();
			if (model == VEHICLE_BTYPE3)
				return get_gxt_label("CMM_MOD_S19c").c_str();
			if (model == VEHICLE_VIRGO2)
				return get_gxt_label("CMM_MOD_S19d").c_str();
			return get_gxt_label("CMM_MOD_S19").c_str();
		}
		case MOD_TANK:
		{
			if (model == VEHICLE_SLAMVAN3)
				return get_gxt_label("CMM_MOD_S27").c_str();
			return get_gxt_label("CMM_MOD_S20").c_str();
		}
		case MOD_WINDOWS:
		{
			if (model == VEHICLE_BTYPE3)
				return get_gxt_label("CMM_MOD_S21b").c_str();
			return get_gxt_label("CMM_MOD_S21").c_str();
		}
		case MOD_DOORS:
		{
			if (model == VEHICLE_SLAMVAN3)
				return get_gxt_label("SLVAN3_RDOOR").c_str();
			return get_gxt_label("CMM_MOD_S22").c_str();
		}
		case MOD_LIVERY: return get_gxt_label("CMM_MOD_S23").c_str();
		default:
			auto name = VEHICLE::GET_MOD_SLOT_NAME(vehicle, mod_slot);
			if (name == nullptr)
				return "";
			if (strstr(name, "_"))
				return get_gxt_label(name).c_str();
			return name;
		}
	}

	static const std::map<int, const char*> horn_map = {{-1, "CMOD_HRN_0"},
	    {0, "CMOD_HRN_TRK"},
	    {1, "CMOD_HRN_COP"},
	    {2, "CMOD_HRN_CLO"},
	    {3, "CMOD_HRN_MUS1"},
	    {4, "CMOD_HRN_MUS2"},
	    {5, "CMOD_HRN_MUS3"},
	    {6, "CMOD_HRN_MUS4"},
	    {7, "CMOD_HRN_MUS5"},
	    {8, "CMOD_HRN_SAD"},
	    {9, "HORN_CLAS1"},
	    {10, "HORN_CLAS2"},
	    {11, "HORN_CLAS3"},
	    {12, "HORN_CLAS4"},
	    {13, "HORN_CLAS5"},
	    {14, "HORN_CLAS6"},
	    {15, "HORN_CLAS7"},
	    {16, "HORN_CNOTE_C0"},
	    {17, "HORN_CNOTE_D0"},
	    {18, "HORN_CNOTE_E0"},
	    {19, "HORN_CNOTE_F0"},
	    {20, "HORN_CNOTE_G0"},
	    {21, "HORN_CNOTE_A0"},
	    {22, "HORN_CNOTE_B0"},
	    {23, "HORN_CNOTE_C1"},
	    {24, "HORN_HIPS1"},
	    {25, "HORN_HIPS2"},
	    {26, "HORN_HIPS3"},
	    {27, "HORN_HIPS4"},
	    {28, "HORN_INDI_1"},
	    {29, "HORN_INDI_2"},
	    {30, "HORN_INDI_3"},
	    {31, "HORN_INDI_4"},
	    {32, "HORN_LUXE2"},
	    {33, "HORN_LUXE1"},
	    {34, "HORN_LUXE3"}, /*{35, "HORN_LUXE2"},
		{36, "HORN_LUXE1"}, {37, "HORN_LUXE3"},*/
	    {38, "HORN_HWEEN1"},
	    /*{39, "HORN_HWEEN1"},*/ {40, "HORN_HWEEN2"},
	    /*{41, "HORN_HWEEN2"},*/ {42, "HORN_LOWRDER1"},
	    /*{43, "HORN_LOWRDER1"},*/ {44, "HORN_LOWRDER2"}, /*{45, "HORN_LOWRDER2"},*/
	    {46, "HORN_XM15_1"},
	    {47, "HORN_XM15_2"},
	    {48, "HORN_XM15_3"}};

	const char* vehicle_helper::get_mod_name(Hash model, Vehicle vehicle, int mod_slot, int mod, int mod_count)
	{
		if (mod_count == 0)
			return "";
		if (mod < -1 || mod >= mod_count)
			return "";
		if (mod_slot == MOD_HORNS)
		{
			if (horn_map.contains(mod))
			{
				return get_gxt_label(horn_map.find(mod)->second).c_str();
			}
			return "";
		}

		if (mod_slot == MOD_FRONTWHEEL || mod_slot == MOD_REARWHEEL)
		{
			if (mod == -1)
			{
				if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
					return get_gxt_label("CMOD_WHE_0").c_str();
				return get_gxt_label("CMOD_WHE_B_0").c_str();
			}
			if (mod >= mod_count / 2)
				//return std::format("{} {}", get_gxt_label("CHROME"), get_gxt_label(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str(); //Bug with FMT library? Returns Chrome Chrome...
				return std::format("Chrome {}", get_gxt_label(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str();
			return get_gxt_label(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod)).c_str();
		}

		switch (mod_slot)
		{
		case MOD_ARMOR: return get_gxt_label(std::format("CMOD_ARM_{}", mod + 1)).c_str();
		case MOD_BRAKES: return get_gxt_label(std::format("CMOD_BRA_{}", mod + 1)).c_str();
		case MOD_ENGINE:
			if (mod == -1)
				return get_gxt_label("CMOD_ARM_0").c_str();
			return get_gxt_label(std::format("CMOD_ENG_{}", mod + 1)).c_str();
		case MOD_SUSPENSION: return get_gxt_label(std::format("CMOD_SUS_{}", mod + 1)).c_str();
		case MOD_TRANSMISSION: return get_gxt_label(std::format("CMOD_GBX_{}", mod + 1)).c_str();
		}


		if (mod > -1)
		{
			if (mod_slot == MOD_SIDESKIRT && VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT) < 2)
			{
				return get_gxt_label("CMOD_SKI_1").c_str();
			}
			auto label = VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod);
			if (label == nullptr || strlen(label) == 0)
				return "MISSING_LABEL";
			return get_gxt_label(label).c_str();
		}
		switch (mod_slot)
		{
		case MOD_AIRFILTER: break;
		case MOD_STRUTS:
			switch (model)
			{
			case VEHICLE_BANSHEE:
			case VEHICLE_BANSHEE2:
			case VEHICLE_SULTANRS: return get_gxt_label("CMOD_COL5_41").c_str();
			}
			break;
		}
		return get_gxt_label("CMOD_DEF_0").c_str();
	}


	static const std::map<Hash, std::map<int, std::vector<int32_t>>> mod_blacklists = {{VEHICLE_BANSHEE, {{MOD_SPOILERS, {3, 4}}, {MOD_COLUMNSHIFTERLEVERS, {0, 1, 2, 3}}, {MOD_SPEAKERS, {0}}, {MOD_LIVERY, {15, 16}}}}, {VEHICLE_SENTINEL, {{MOD_SPOILERS, {4, 5}}, {MOD_COLUMNSHIFTERLEVERS, {0, 1, 2, 3}}, {MOD_SPEAKERS, {0}}, {MOD_LIVERY, {0, 1}}}}};

	bool vehicle_helper::check_mod_blacklist(Hash model, int mod_slot, int mod)
	{
		if (!mod_blacklists.contains(model))
		{
			return false;
		}

		auto veh_slot_blacklist = mod_blacklists.find(model)->second;
		if (!veh_slot_blacklist.contains(mod_slot))
		{
			return false;
		}

		auto veh_mod_blacklist = veh_slot_blacklist.find(mod_slot)->second;
		if (std::ranges::find(veh_mod_blacklist, mod) != veh_mod_blacklist.end())
		{
			return true;
		}

		return false;
	}
}

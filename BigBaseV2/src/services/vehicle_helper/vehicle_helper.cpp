#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "vehicle_helper.hpp"

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

	void vehicle_helper::set_mp_parameters_for_vehicle(Vehicle vehicle)
	{
		DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
		auto networkId = NETWORK::VEH_TO_NET(vehicle);
		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(vehicle))
			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
		VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE);
	}

	Vehicle vehicle_helper::create_vehicle(Hash modelHash, float x, float y, float z, float heading)
	{
		while (!STREAMING::HAS_MODEL_LOADED(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			script::get_current()->yield();
		}
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x9090;
		Vehicle vehicle = VEHICLE::CREATE_VEHICLE(modelHash, x, y, z, heading, TRUE, FALSE, FALSE);
		*(unsigned short*)big::g_pointers->m_model_spawn_bypass = 0x0574;
		script::get_current()->yield(); //This allows the car to initalize so when we write things like radio station, it will overwrite.
		ENTITY::SET_ENTITY_CLEANUP_BY_ENGINE_(vehicle, TRUE);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(modelHash);
		if (*big::g_pointers->m_is_session_started)
			set_mp_parameters_for_vehicle(vehicle);
		return vehicle;
	}

	const char* vehicle_helper::get_mod_slot_name(int mod_slot, Vehicle vehicle)
	{
		Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
		switch (mod_slot)
		{
		case MOD_HOOD:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_HOD");
		case MOD_ARMOR:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_ARM");
		case MOD_BRAKES:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_BRA");
		case MOD_ENGINE:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_ENG");
		case MOD_SUSPENSION:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_SUS");
		case MOD_TRANSMISSION:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_TRN");
		case MOD_HORNS:
			return HUD::GET_LABEL_TEXT_("CMOD_MOD_HRN");
		case MOD_FRONTWHEEL:
			if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
				return HUD::GET_LABEL_TEXT_("CMOD_MOD_WHEM");
			else
				return HUD::GET_LABEL_TEXT_("CMOD_WHE0_0");
		case MOD_REARWHEEL:
			return HUD::GET_LABEL_TEXT_("CMOD_WHE0_1");
			//Bennys
		case MOD_PLATEHOLDER:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S0");
		case MOD_VANITYPLATES:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S1");
		case MOD_TRIMDESIGN:
			if (model == VEHICLE_SULTANRS)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S2b");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S2");
		case MOD_ORNAMENTS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S3");
		case MOD_DASHBOARD:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S4");
		case MOD_DIALDESIGN:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S5");
		case MOD_DOORSPEAKERS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S6");
		case MOD_SEATS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S7");
		case MOD_STEERINGWHEELS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S8");
		case MOD_COLUMNSHIFTERLEVERS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S9");
		case MOD_PLAQUES:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S10");
		case MOD_SPEAKERS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S11");
		case MOD_TRUNK:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S12");
		case MOD_HYDRAULICS:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S13");
		case MOD_ENGINEBLOCK:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S14");
		case MOD_AIRFILTER:
			if (model == VEHICLE_SULTANRS)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S15b");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S15");
		case MOD_STRUTS:
			if (model == VEHICLE_SULTANRS || model == VEHICLE_BANSHEE2)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S16b");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S16");
		case MOD_ARCHCOVER:
			if (model == VEHICLE_SULTANRS)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S17b");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S17");
		case MOD_AERIALS:
			if (model == VEHICLE_SULTANRS)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S18b");
			else if (model == VEHICLE_BTYPE3)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S18c");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S18");
		case MOD_TRIM:
			if (model == VEHICLE_SULTANRS)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S19b");
			else if (model == VEHICLE_BTYPE3)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S19c");
			else if (model == VEHICLE_VIRGO2)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S19d");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S19");
		case MOD_TANK:
			if (model == VEHICLE_SLAMVAN3)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S27");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S20");
		case MOD_WINDOWS:
			if (model == VEHICLE_BTYPE3)
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S21b");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S21");
		case MOD_DOORS:
			if (model == VEHICLE_SLAMVAN3)
				return HUD::GET_LABEL_TEXT_("SLVAN3_RDOOR");
			else
				return HUD::GET_LABEL_TEXT_("CMM_MOD_S22");
		case MOD_LIVERY:
			return HUD::GET_LABEL_TEXT_("CMM_MOD_S23");
		default:
			auto name = VEHICLE::GET_MOD_SLOT_NAME(vehicle, mod_slot);
			if (name == nullptr)
				return "";
			if (strstr(name, "_"))
				return HUD::GET_LABEL_TEXT_(name);
			return name;
		}
	}

	static const std::map<int, const char*> horn_map = {
		{-1, "CMOD_HRN_0"}, {0, "CMOD_HRN_TRK"}, {1, "CMOD_HRN_COP"}, {2, "CMOD_HRN_CLO"}, {3, "CMOD_HRN_MUS1"}, {4, "CMOD_HRN_MUS2"}, {5, "CMOD_HRN_MUS3"},
		{6, "CMOD_HRN_MUS4"}, {7, "CMOD_HRN_MUS5"}, {8, "CMOD_HRN_SAD"}, {9, "HORN_CLAS1"}, {10, "HORN_CLAS2"},
		{11, "HORN_CLAS3"}, {12, "HORN_CLAS4"}, {13, "HORN_CLAS5"}, {14, "HORN_CLAS6"}, {15, "HORN_CLAS7"},
		{16, "HORN_CNOTE_C0"}, {17, "HORN_CNOTE_D0"}, {18, "HORN_CNOTE_E0"}, {19, "HORN_CNOTE_F0"}, {20, "HORN_CNOTE_G0"},
		{21, "HORN_CNOTE_A0"}, {22, "HORN_CNOTE_B0"}, {23, "HORN_CNOTE_C1"}, {24, "HORN_HIPS1"}, {25, "HORN_HIPS2"},
		{26, "HORN_HIPS3"}, {27, "HORN_HIPS4"}, {28, "HORN_INDI_1"}, {29, "HORN_INDI_2"}, {30, "HORN_INDI_3"},
		{31, "HORN_INDI_4"}, {32, "HORN_LUXE2"}, {33, "HORN_LUXE1"}, {34, "HORN_LUXE3"}, /*{35, "HORN_LUXE2"},
		{36, "HORN_LUXE1"}, {37, "HORN_LUXE3"},*/ {38, "HORN_HWEEN1"}, /*{39, "HORN_HWEEN1"},*/ {40, "HORN_HWEEN2"},
		/*{41, "HORN_HWEEN2"},*/ {42, "HORN_LOWRDER1"}, /*{43, "HORN_LOWRDER1"},*/ {44, "HORN_LOWRDER2"}, /*{45, "HORN_LOWRDER2"},*/
		{46, "HORN_XM15_1"}, {47, "HORN_XM15_2"}, {48, "HORN_XM15_3"}
	};

	const char* vehicle_helper::get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle)
	{
		if (mod_count == 0)
			return "";
		if (mod < -1 || mod >= mod_count)
			return "";
		if (mod_slot == MOD_HORNS)
		{
			if (horn_map.find(mod) != horn_map.end())
			{
				return HUD::GET_LABEL_TEXT_(horn_map.find(mod)->second);
			}
			return "";
		}
		Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
		if (mod_slot == MOD_FRONTWHEEL || mod_slot == MOD_REARWHEEL)
		{
			if (mod == -1)
			{
				if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
					return HUD::GET_LABEL_TEXT_("CMOD_WHE_0");
				else
					return HUD::GET_LABEL_TEXT_("CMOD_WHE_B_0");
			}
			if (mod >= mod_count / 2)
				//return fmt::format("{} {}", HUD::GET_LABEL_TEXT_("CHROME"), HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str(); //Bug with FMT library? Returns Chrome Chrome...
				return fmt::format("Chrome {}", HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str();
			else
				return HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod));
		}

		switch (mod_slot)
		{
		case MOD_ARMOR:
			return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_ARM_{}", (mod + 1)).c_str());
		case MOD_BRAKES:
			return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_BRA_{}", (mod + 1)).c_str());
		case MOD_ENGINE:
			if (mod == -1)
				return HUD::GET_LABEL_TEXT_("CMOD_ARM_0");
			return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_ENG_{}", (mod + 1)).c_str());
		case MOD_SUSPENSION:
			return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_SUS_{}", (mod + 1)).c_str());
		case MOD_TRANSMISSION:
			return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_GBX_{}", (mod + 1)).c_str());
		}
		if (mod > -1)
		{
			if (mod_slot == MOD_SIDESKIRT && VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT) < 2)
			{
				return HUD::GET_LABEL_TEXT_("CMOD_SKI_1");
			}
			auto label = VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod);
			if (label == nullptr || strlen(label) == 0)
				return "MISSING_LABEL";
			return HUD::GET_LABEL_TEXT_(label);
		}
		else
		{
			switch (mod_slot)
			{
			case MOD_AIRFILTER:
				break;
			case MOD_STRUTS:
				switch (model)
				{
				case VEHICLE_BANSHEE:
				case VEHICLE_BANSHEE2:
				case VEHICLE_SULTANRS:
					return HUD::GET_LABEL_TEXT_("CMOD_COL5_41");
				}
				break;

			}
			return HUD::GET_LABEL_TEXT_("CMOD_DEF_0");
		}
	}
}

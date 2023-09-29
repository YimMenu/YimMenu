#include "protection.hpp"

#include "model_info.hpp"

namespace big::protection
{
	constexpr auto crash_objects = {RAGE_JOAAT("prop_dummy_01"), RAGE_JOAAT("prop_dummy_car"), RAGE_JOAAT("prop_dummy_light"), RAGE_JOAAT("prop_dummy_plane"), RAGE_JOAAT("prop_distantcar_night"), RAGE_JOAAT("prop_distantcar_day"), RAGE_JOAAT("hei_bh1_08_details4_em_night"), RAGE_JOAAT("dt1_18_sq_night_slod"), RAGE_JOAAT("ss1_12_night_slod"), RAGE_JOAAT("hash_b334b5e2_qyquzxq_collision"), RAGE_JOAAT("h4_prop_bush_bgnvla_med_01"), RAGE_JOAAT("h4_prop_bush_bgnvla_lrg_01"), RAGE_JOAAT("h4_prop_bush_buddleia_low_01"), RAGE_JOAAT("h4_prop_bush_ear_aa"), RAGE_JOAAT("h4_prop_bush_ear_ab"), RAGE_JOAAT("h4_prop_bush_fern_low_01"), RAGE_JOAAT("h4_prop_bush_fern_tall_cc"), RAGE_JOAAT("h4_prop_bush_mang_ad"), RAGE_JOAAT("h4_prop_bush_mang_low_aa"), RAGE_JOAAT("h4_prop_bush_mang_low_ab"), RAGE_JOAAT("h4_prop_bush_seagrape_low_01"), RAGE_JOAAT("prop_h4_ground_cover"), RAGE_JOAAT("h4_prop_weed_groundcover_01"), RAGE_JOAAT("h4_prop_grass_med_01"), RAGE_JOAAT("h4_prop_grass_tropical_lush_01"), RAGE_JOAAT("h4_prop_grass_wiregrass_01"), RAGE_JOAAT("h4_prop_weed_01_plant"), RAGE_JOAAT("h4_prop_weed_01_row"), RAGE_JOAAT("urbanweeds02_l1"), RAGE_JOAAT("proc_forest_grass01"), RAGE_JOAAT("prop_small_bushyba"), RAGE_JOAAT("v_res_d_dildo_a"), RAGE_JOAAT("v_res_d_dildo_b"), RAGE_JOAAT("v_res_d_dildo_c"), RAGE_JOAAT("v_res_d_dildo_d"), RAGE_JOAAT("v_res_d_dildo_e"), RAGE_JOAAT("v_res_d_dildo_f"), RAGE_JOAAT("v_res_skateboard"), RAGE_JOAAT("prop_battery_01"), RAGE_JOAAT("prop_barbell_01"), RAGE_JOAAT("prop_barbell_02"), RAGE_JOAAT("prop_bandsaw_01"), RAGE_JOAAT("prop_bbq_3"), RAGE_JOAAT("v_med_curtainsnewcloth2"), RAGE_JOAAT("bh1_07_flagpoles"), RAGE_JOAAT("hash_058a7eb5_deihiws_collision"), RAGE_JOAAT("proc_dry_plants_01"), RAGE_JOAAT("proc_leafyplant_01"), RAGE_JOAAT("proc_grassplantmix_02"), RAGE_JOAAT("proc_dryplantsgrass_01"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_dryplantsgrass_02"), RAGE_JOAAT("proc_grasses01"), RAGE_JOAAT("prop_dryweed_002_a"), RAGE_JOAAT("prop_fernba"), RAGE_JOAAT("prop_weed_001_aa"), RAGE_JOAAT("urbangrnfrnds_01"), RAGE_JOAAT("urbanweeds01"), RAGE_JOAAT("prop_dandy_b"), RAGE_JOAAT("v_proc2_temp"), RAGE_JOAAT("prop_fernbb"), RAGE_JOAAT("proc_drygrassfronds01"), RAGE_JOAAT("prop_log_ae"), RAGE_JOAAT("prop_grass_da"), RAGE_JOAAT("prop_fragtest_cnst_04")};
	bool is_crash_object(rage::joaat_t model)
	{
		if (!model_info::get_model(model))
			return false;
		if (!model_info::is_model_of_type(model, eModelType::Object, eModelType::Time, eModelType::Weapon, eModelType::Destructable, eModelType::WorldObject, eModelType::Sprinkler, eModelType::Unk65, eModelType::Plant, eModelType::LOD, eModelType::Unk132, eModelType::Building))
			return true;
		for (auto iterator : crash_objects)
			if (iterator == model)
				return true;
		return false;
	}

	constexpr auto crash_peds = {RAGE_JOAAT("slod_human"), RAGE_JOAAT("slod_small_quadped"), RAGE_JOAAT("slod_large_quadped")};
	bool is_crash_ped(rage::joaat_t model)
	{
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		if (!model_info::is_model_of_type(model, eModelType::Ped, eModelType::OnlineOnlyPed))
			return true;
		return false;
	}

	constexpr auto crash_vehicles = {RAGE_JOAAT("arbitergt"), RAGE_JOAAT("astron2"), RAGE_JOAAT("cyclone2"), RAGE_JOAAT("ignus2"), RAGE_JOAAT("s95")};
	bool is_crash_vehicle(rage::joaat_t model)
	{
		for (auto iterator : crash_vehicles)
			if (iterator == model)
				return true;
		if (!model_info::is_model_of_type(model, eModelType::Vehicle, eModelType::Unk133))
			return true;
		return false;
	}

	constexpr auto valid_player_models = {
	    RAGE_JOAAT("mp_m_freemode_01"),
	    RAGE_JOAAT("mp_f_freemode_01"),
	    RAGE_JOAAT("u_m_m_filmdirector"),
	    RAGE_JOAAT("player_zero"),
	    RAGE_JOAAT("player_one"),
	    RAGE_JOAAT("player_two"),
	    // peyote
	    RAGE_JOAAT("A_C_Boar"),
	    RAGE_JOAAT("A_C_Cat_01"),
	    RAGE_JOAAT("A_C_Cow"),
	    RAGE_JOAAT("A_C_Coyote"),
	    RAGE_JOAAT("A_C_Deer"),
	    RAGE_JOAAT("A_C_Husky"),
	    RAGE_JOAAT("A_C_MtLion"),
	    RAGE_JOAAT("A_C_Pig"),
	    RAGE_JOAAT("A_C_Poodle"),
	    RAGE_JOAAT("A_C_Pug"),
	    RAGE_JOAAT("A_C_Rabbit_01"),
	    RAGE_JOAAT("A_C_Retriever"),
	    RAGE_JOAAT("A_C_Rottweiler"),
	    RAGE_JOAAT("A_C_shepherd"),
	    RAGE_JOAAT("A_C_Westy"),
	    RAGE_JOAAT("A_C_Chickenhawk"),
	    RAGE_JOAAT("A_C_Cormorant"),
	    RAGE_JOAAT("A_C_Crow"),
	    RAGE_JOAAT("A_C_Hen"),
	    RAGE_JOAAT("A_C_Pigeon"),
	    RAGE_JOAAT("A_C_Seagull"),
	    RAGE_JOAAT("A_C_Dolphin"),
	    RAGE_JOAAT("A_C_Fish"),
	    RAGE_JOAAT("A_C_KillerWhale"),
	    RAGE_JOAAT("A_C_SharkHammer"),
	    RAGE_JOAAT("A_C_SharkTiger"),
	    RAGE_JOAAT("A_C_Stingray"),
	    RAGE_JOAAT("IG_Orleans"),
	    RAGE_JOAAT("A_C_Chop"),
	    RAGE_JOAAT("A_C_HumpBack"),
	};
	bool is_valid_player_model(rage::joaat_t model)
	{
		for (auto iterator : valid_player_models)
			if (iterator == model)
				return true;
		return false;
	}
}
#include "protection.hpp"

#include "model_info.hpp"

namespace big::protection
{
	constexpr auto crash_objects = {"prop_dummy_01"_J, "prop_dummy_car"_J, "prop_dummy_light"_J, "prop_dummy_plane"_J, "prop_distantcar_night"_J, "prop_distantcar_day"_J, "hei_bh1_08_details4_em_night"_J, "dt1_18_sq_night_slod"_J, "ss1_12_night_slod"_J, "hash_b334b5e2_qyquzxq_collision"_J, "h4_prop_bush_bgnvla_med_01"_J, "h4_prop_bush_bgnvla_lrg_01"_J, "h4_prop_bush_buddleia_low_01"_J, "h4_prop_bush_ear_aa"_J, "h4_prop_bush_ear_ab"_J, "h4_prop_bush_fern_low_01"_J, "h4_prop_bush_fern_tall_cc"_J, "h4_prop_bush_mang_ad"_J, "h4_prop_bush_mang_low_aa"_J, "h4_prop_bush_mang_low_ab"_J, "h4_prop_bush_seagrape_low_01"_J, "prop_h4_ground_cover"_J, "h4_prop_weed_groundcover_01"_J, "h4_prop_grass_med_01"_J, "h4_prop_grass_tropical_lush_01"_J, "h4_prop_grass_wiregrass_01"_J, "h4_prop_weed_01_plant"_J, "h4_prop_weed_01_row"_J, "urbanweeds02_l1"_J, "proc_forest_grass01"_J, "prop_small_bushyba"_J, "v_res_d_dildo_a"_J, "v_res_d_dildo_b"_J, "v_res_d_dildo_c"_J, "v_res_d_dildo_d"_J, "v_res_d_dildo_e"_J, "v_res_d_dildo_f"_J, "v_res_skateboard"_J, "prop_battery_01"_J, "prop_barbell_01"_J, "prop_barbell_02"_J, "prop_bandsaw_01"_J, "prop_bbq_3"_J, "v_med_curtainsnewcloth2"_J, "bh1_07_flagpoles"_J, "hash_058a7eb5_deihiws_collision"_J, "proc_dry_plants_01"_J, "proc_leafyplant_01"_J, "proc_grassplantmix_02"_J, "proc_dryplantsgrass_01"_J, "proc_dryplantsgrass_02"_J, "proc_dryplantsgrass_02"_J, "proc_grasses01"_J, "prop_dryweed_002_a"_J, "prop_fernba"_J, "prop_weed_001_aa"_J, "urbangrnfrnds_01"_J, "urbanweeds01"_J, "prop_dandy_b"_J, "v_proc2_temp"_J, "prop_fernbb"_J, "proc_drygrassfronds01"_J, "prop_log_ae"_J, "prop_grass_da"_J, "prop_fragtest_cnst_04"_J};
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

	constexpr auto crash_peds = {"slod_human"_J, "slod_small_quadped"_J, "slod_large_quadped"_J};
	bool is_crash_ped(rage::joaat_t model)
	{
		for (auto iterator : crash_peds)
			if (iterator == model)
				return true;
		if (!model_info::is_model_of_type(model, eModelType::Ped, eModelType::OnlineOnlyPed))
			return true;
		return false;
	}

	constexpr auto crash_vehicles = {"arbitergt"_J, "astron2"_J, "cyclone2"_J, "ignus2"_J, "s95"_J};
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
	    "mp_m_freemode_01"_J,
	    "mp_f_freemode_01"_J,
	    "u_m_m_filmdirector"_J,
	    "player_zero"_J,
	    "player_one"_J,
	    "player_two"_J,
	    // peyote
	    "A_C_Boar"_J,
	    "A_C_Cat_01"_J,
	    "A_C_Cow"_J,
	    "A_C_Coyote"_J,
	    "A_C_Deer"_J,
	    "A_C_Husky"_J,
	    "A_C_MtLion"_J,
	    "A_C_Pig"_J,
	    "A_C_Poodle"_J,
	    "A_C_Pug"_J,
	    "A_C_Rabbit_01"_J,
	    "A_C_Retriever"_J,
	    "A_C_Rottweiler"_J,
	    "A_C_shepherd"_J,
	    "A_C_Westy"_J,
	    "A_C_Chickenhawk"_J,
	    "A_C_Cormorant"_J,
	    "A_C_Crow"_J,
	    "A_C_Hen"_J,
	    "A_C_Pigeon"_J,
	    "A_C_Seagull"_J,
	    "A_C_Dolphin"_J,
	    "A_C_Fish"_J,
	    "A_C_KillerWhale"_J,
	    "A_C_SharkHammer"_J,
	    "A_C_SharkTiger"_J,
	    "A_C_Stingray"_J,
	    "IG_Orleans"_J,
	    "A_C_Chop"_J,
	    "A_C_HumpBack"_J,
	};
	bool is_valid_player_model(rage::joaat_t model)
	{
		for (auto iterator : valid_player_models)
			if (iterator == model)
				return true;
		return false;
	}
}

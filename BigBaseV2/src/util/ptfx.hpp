#pragma once
#include "gta/joaat.hpp"
#include "gta/replay.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/math.hpp"

//https://www.youtube.com/watch?v=k6z4Y5DBb-g  <- All Effects
namespace big::ptfx
{
	inline void supermanPTFX()
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("scr_rcbarry2");
		//STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("scr_rcbarry2"))
		{
			//Foot
			auto const LeftF = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_L_Foot, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("sp_clown_appear_trails", LeftF.x, LeftF.y, LeftF.z, 0, 0, 0, 2, false, false, false, false);

			auto const RightF = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_R_Foot, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("scr_rcbarry2");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("sp_clown_appear_trails", RightF.x, RightF.y, RightF.z, 0, 0, 0, 2, false, false, false, false);

			//HELP FINDING A GOOD PTFX!!!
			/*/Hand
			auto const LeftH = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_L_Hand, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("muz_buzzard", LeftH.x, LeftH.y, LeftH.z, 0, 0, 0, 2, false, false, false, false);

			auto const RightH = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_R_Hand, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("muz_buzzard", RightH.x, RightH.y, RightH.z, 0, 0, 0, 2, false, false, false, false);*/
		}
	}

	inline void flashrunPTFX()
	{
		STREAMING::REQUEST_NAMED_PTFX_ASSET("core");
		if (STREAMING::HAS_NAMED_PTFX_ASSET_LOADED("core"))
		{
			//Foot
			auto const LeftF = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_L_Foot, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("ent_ray_prologue_elec_crackle_sp", LeftF.x, LeftF.y, LeftF.z, 0, 0, 0, 2, false, false, false, false);

			auto const RightF = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_R_Foot, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("ent_ray_prologue_elec_crackle_sp", RightF.x, RightF.y, RightF.z, 0, 0, 0, 2, false, false, false, false);

			//Hand
			auto const LeftH = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_R_Hand, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("ent_ray_prologue_elec_crackle_sp", LeftH.x, LeftH.y, LeftH.z, 0, 0, 0, 2, false, false, false, false);

			auto const RightH = PED::GET_PED_BONE_COORDS(self::ped, (int)PedBones::SKEL_L_Hand, 0, 0, 0);
			GRAPHICS::USE_PARTICLE_FX_ASSET("core");
			GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD("ent_ray_prologue_elec_crackle_sp", RightH.x, RightH.y, RightH.z, 0, 0, 0, 2, false, false, false, false);
		}
	}
}
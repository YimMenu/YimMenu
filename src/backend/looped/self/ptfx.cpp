#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"

namespace big
{

	class ptfx_looped : looped_command
	{
		using looped_command::looped_command;

		PedBones ptfx_ped_bones[5] = {PedBones::SKEL_Head, PedBones::SKEL_L_Hand, PedBones::SKEL_R_Hand, PedBones::SKEL_L_Foot, PedBones::SKEL_R_Foot};

		const char* ptfx_vehicle_pos[4] = {"wheel_lf", "wheel_lr", "wheel_rf", "wheel_rr"};

		void show_player_ptfx_effect(const char* fx_name, const char* name)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(fx_name);
			for (const auto& ptfx_bone : ptfx_ped_bones)
			{
				GRAPHICS::USE_PARTICLE_FX_ASSET(fx_name);
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name,
				    self::ped,
				    0.f,
				    0.f,
				    0.f,
				    0.f,
				    0.f,
				    0.f,
				    (int)ptfx_bone,
				    g.self.ptfx_effects.size,
				    1,
				    1,
				    1);
			}
		}

		void show_vehicle_ptfx_effect(const char* fx_name, const char* name)
		{
			STREAMING::REQUEST_NAMED_PTFX_ASSET(fx_name);
			for (const auto& ptfx_bone : ptfx_vehicle_pos)
			{
				GRAPHICS::USE_PARTICLE_FX_ASSET(fx_name);
				Vector3 bone_pos = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(self::veh, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(self::veh, ptfx_bone));
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(name,
				    bone_pos.x,
				    bone_pos.y,
				    bone_pos.z,
				    0.f,
				    0.f,
				    0.f,
				    g.self.ptfx_effects.size,
				    0.f,
				    0.f,
				    0.f,
				    0);
			}
		}

		virtual void on_tick() override
		{
			if (self::veh == 0)
				show_player_ptfx_effect(g.self.ptfx_effects.asset, g.self.ptfx_effects.effect);
			else
				show_vehicle_ptfx_effect(g.self.ptfx_effects.asset, g.self.ptfx_effects.effect);
		}

		virtual void on_disable() override
		{
			STREAMING::REMOVE_PTFX_ASSET();
		}
	};

	ptfx_looped g_ptfx_looped("ptfx", "PTFX_CMD", "PTFX_CMD_DESC", g.self.ptfx_effects.show);
}
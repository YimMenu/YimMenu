#include "natives.hpp"
#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "core/data/ptfx_effects.hpp"

namespace big
{

	class ptfx_looped : looped_command
	{
		using looped_command::looped_command;

		PedBones ptfx_bones[5] = {
			PedBones::SKEL_Head,
			PedBones::SKEL_L_Hand,
			PedBones::SKEL_R_Hand,
			PedBones::SKEL_L_Foot,
			PedBones::SKEL_R_Foot
		};

		void show_ptfx_effect(const char* fx_name, const char* name)
		{
			for (const auto& ptfx_bone : ptfx_bones)
			{
				STREAMING::REQUEST_NAMED_PTFX_ASSET(fx_name);
				GRAPHICS::USE_PARTICLE_FX_ASSET(fx_name);
				GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name, self::ped, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, (int)ptfx_bone, g.self.ptfx_effects.size, 1, 1, 1);
				STREAMING::REMOVE_PTFX_ASSET();
			}
		}

		virtual void on_tick() override
		{
			show_ptfx_effect(g.self.ptfx_effects.asset, g.self.ptfx_effects.effect);			
		}
	};

	ptfx_looped g_ptfx_looped("ptfx", "Enable PTFX", "Show nice PTFX Effects on your character", g.self.ptfx_effects.show);
}
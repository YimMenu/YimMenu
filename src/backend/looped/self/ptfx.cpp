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

        void show_ptfx_effect(const std::string fx_name, const std::string name)
        {
            for (const auto& ptfx_bone : ptfx_bones)
			{
                STREAMING::REQUEST_NAMED_PTFX_ASSET(fx_name.c_str());
		        GRAPHICS::USE_PARTICLE_FX_ASSET(fx_name.c_str());
		        GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(name.c_str(), self::ped, 0.00f, 0.00f, 0.00f, 0.00f, 0.00f, 0.0f, (int)ptfx_bone, g.self.ptfx_effects.size, 1, 1, 1);
		        STREAMING::REMOVE_PTFX_ASSET();
            }
        }

		virtual void on_tick() override
		{
            switch (g.self.ptfx_effects.type)
            {
                case PTFXEffects::Lighting:
                    show_ptfx_effect("scr_rcbarry2", "scr_clown_death");
                    break;
                case PTFXEffects::Clown:
                    show_ptfx_effect("scr_rcbarry2", "scr_clown_appears");
                    break;
                case PTFXEffects::Firework:
                    show_ptfx_effect("scr_indep_fireworks", "scr_indep_firework_trailburst");
                    break;
			    case PTFXEffects::Alien1:
				    show_ptfx_effect("scr_rcbarry1", "scr_alien_disintegrate");
				    break;
			    case PTFXEffects::Alien2:
			    	show_ptfx_effect("scr_rcbarry1", "scr_alien_teleport");
				    break;
			    case PTFXEffects::Electric:
				    show_ptfx_effect("scr_agencyheistb", "scr_agency3b_elec_box");
				    break;
			    case PTFXEffects::Electric_Boosh:
			        show_ptfx_effect("scr_trevor1", "scr_trev1_trailer_boosh");
				    break;
			    case PTFXEffects::Smoke:
				    show_ptfx_effect("scr_familyscenem", "scr_meth_pipe_smoke");
				    break;
			    case PTFXEffects::Water_Splash:
				    show_ptfx_effect("scr_fbi5a", "scr_fbi5_ped_water_splash");
				    break;
			    case PTFXEffects::Ghost_Rider:
				    show_ptfx_effect("scr_agencyheist", "scr_fbi_dd_breach_smoke");
				    break;
            }
		}
	};

	ptfx_looped g_ptfx_looped("ptfx", "Enable PTFX", "Show nice PTFX Effects on your character", g.self.ptfx_effects.show);
}
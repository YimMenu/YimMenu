#pragma once

struct ptfx_library
{
	const char* friendly_name;
	const char* asset_name;
	std::vector<const char*> effect_names;
};

const ptfx_library ptfx_named[] = {
    {"Agency Heist",
        "scr_agencyheist",
        {
            {"scr_fbi_mop_drips"},
            {"scr_agency3a_door_hvy_trig"},
            {"scr_fbi_dd_breach_smoke"},
        }},
    {"Alien",
        "scr_rcbarry1",
        {
            {"scr_alien_teleport"},
            {"scr_alien_disintegrate"},
        }},
    {"Clown",
        "scr_rcbarry2",
        {
            {"scr_clown_death"},
            {"eject_clown"},
            {"scr_exp_clown"},
            {"scr_clown_appears"},
            {"sp_clown_appear_trails"},
            {"scr_clown_bul"},// this one makes noise? lol
            {"muz_clown"},
        }},
    {"Firework",
        "scr_indep_fireworks",
        {
            {"scr_indep_firework_sparkle_spawn"},
            {"scr_indep_firework_trailburst_spawn"},// add seizure warning
            {"scr_indep_firework_burst_spawn"},
            {"scr_indep_firework_trail_spawn"},
        }},
};

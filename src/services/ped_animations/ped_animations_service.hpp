#pragma once
#include "file_manager.hpp"

namespace big
{
    struct ped_animation
    {
        std::string name;
        std::string dict;
        std::string anim;
        float blendin = 4.f;
        float blendout = -4.f;
        int time_to_play = -1;
        int flags = 0;
        float start_phase = 0;
        bool ambient = false;
        float pos[3] = {};
        float rot[3] = {};
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ped_animation, name, dict, anim, blendin, blendout, time_to_play, flags, start_phase, ambient, pos, rot);

    class ped_animation_service
    {
    public:
        std::map<std::string, std::vector<ped_animation>> all_saved_animations;
        ped_animation current_animation;
        
        bool fetch_saved_animations();
        bool save_new_animation(const std::string& category, ped_animation);
        bool delete_saved_animation(const std::string& category, ped_animation);
        ped_animation* get_animation_by_name(std::string name);
        std::vector<ped_animation> saved_animations_filtered_list(std::string filter);
        std::vector<ped_animation> saved_animations_ambient_list();

        void play_saved_ped_animation(ped_animation p, Ped ped);
        void ambient_animations_prompt_tick();
    
    private:
        std::filesystem::path get_ped_animations_file_path();
    };

    inline ped_animation_service g_ped_animation_service;
}
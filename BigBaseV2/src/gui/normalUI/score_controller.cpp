#include "views/view.hpp"
#include "natives.hpp"

namespace big
{
    void view::score_controller()
    {
        if (g->window.score_controller)
        {
            if (ImGui::Begin("Score Controller"))
            {
				
				components::input_text_with_hint("###Score_track", "Score Track", g->tunables.music_event, 64, ImGuiInputTextFlags_EnterReturnsTrue, []
				{
					AUDIO::TRIGGER_MUSIC_EVENT(g->tunables.music_event);

					AUDIO::TRIGGER_MUSIC_EVENT(g->tunables.supportingevent);
				});

				components::input_text_with_hint("###Score_support_track", "Support Track", g->tunables.supportingevent, 64, ImGuiInputTextFlags_EnterReturnsTrue, []
				{
					AUDIO::TRIGGER_MUSIC_EVENT(g->tunables.supportingevent);
				});
				
				components::input_text_with_hint("###Score_Intansity_track", "Intensity Track", g->tunables.intensity, 64, ImGuiInputTextFlags_EnterReturnsTrue, []
				{
					AUDIO::TRIGGER_MUSIC_EVENT(g->tunables.intensity);
				});
				
				components::button("Stop Score", []
				{
					AUDIO::TRIGGER_MUSIC_EVENT("GTA_ONLINE_STOP_SCORE");
				});
                ImGui::End();
            }
        }
    }
}

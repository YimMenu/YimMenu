#include "views/view.hpp"
#include "backend/looped/self/part_water.hpp"

namespace big
{
    void view::world()
    {
        components::sub_title("GUI_TAB_TIME_N_WEATHER"_T);
        {
            view::time_and_weather();
        }

        ImGui::Separator();

        components::sub_title("GUI_TAB_WATER"_T);
        {
		    components::command_checkbox(&cmd::g_partwater);
        }
    }
}

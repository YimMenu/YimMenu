#include "views/view.hpp"

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
		    components::command_checkbox<"partwater">();
        }
    }
}
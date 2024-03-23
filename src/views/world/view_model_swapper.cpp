#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	void view::model_swapper()
	{
		ImGui::Text("VIEW_MODEL_SWAPPER_LINE1"_T.data());
		ImGui::Text("VIEW_MODEL_SWAPPER_LINE2"_T.data());
		ImGui::Text("VIEW_MODEL_SWAPPER_LINE3"_T.data());

		static char dst_text[256];
		static char src_text[256];
		static size_t selected_index = -1;
		static float width           = *g_pointers->m_gta.m_resolution_x / 5.0;

		ImGui::SetNextItemWidth(width);
		ImGui::InputText("VIEW_MODEL_SWAPPER_DEST"_T.data(), dst_text, IM_ARRAYSIZE(dst_text));
		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		ImGui::SameLine();
		ImGui::SetNextItemWidth(width);
		ImGui::InputText("VIEW_MODEL_SWAPPER_SRC"_T.data(), src_text, IM_ARRAYSIZE(src_text));
		if (ImGui::IsItemActive())
			g.self.hud.typing = TYPING_TICKS;
		ImGui::SameLine();

		if (ImGui::Button("ADD"_T.data()))
		{
			std::lock_guard lock(g.world.model_swapper.m);
			if (dst_text[0] == '\0' || src_text[0] == '\0')
			{
				g_notification_service.push_error("GUI_TAB_MODEL_SWAPPER"_T.data(), "VIEW_MODEL_SWAPPER_WRONG_INPUT"_T.data());
				return;
			}
			std::string str = dst_text;
			transform(str.begin(), str.end(), str.begin(), ::tolower);
			size_t i = 0;
			for (; i < g.world.model_swapper.models.size(); i++)
			{
				std::string tmp = g.world.model_swapper.models[i].first;
				transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
				if (str == tmp)
				{
					g.world.model_swapper.models[i].first  = dst_text;
					g.world.model_swapper.models[i].second = src_text;
					break;
				}
			}
			if (i == g.world.model_swapper.models.size())
				g.world.model_swapper.models.push_back(std::make_pair(dst_text, src_text));
			g.world.model_swapper.update = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("DELETE"_T.data()))
		{
			std::lock_guard lock(g.world.model_swapper.m);
			if (!g.world.model_swapper.models.size() || selected_index < 0
			    || selected_index >= g.world.model_swapper.models.size())
			{
				g_notification_service.push_error("GUI_TAB_MODEL_SWAPPER"_T.data(), "VIEW_MODEL_SWAPPER_INVALID_INDEX"_T.data());
				return;
			}
			g.world.model_swapper.models.erase(std::begin(g.world.model_swapper.models) + selected_index);
			g.world.model_swapper.update = true;
		}
		ImGui::SameLine();
		if (ImGui::Button("VIEW_DEBUG_GLOBAL_CLEAR"_T.data()))
		{
			std::lock_guard lock(g.world.model_swapper.m);
			g.world.model_swapper.models.clear();
			g.world.model_swapper.update = true;
		}

		ImGui::SetNextItemWidth(width);
		ImGui::PushID(2);
		if (ImGui::BeginListBox("VIEW_MODEL_SWAPPER_DEST"_T.data()))
		{
			for (size_t i = 0; i < g.world.model_swapper.models.size(); i++)
			{
				if (ImGui::Selectable(g.world.model_swapper.models[i].first.c_str(), selected_index == i))
				{
					selected_index = i;
					strcpy_s(dst_text, sizeof(dst_text), g.world.model_swapper.models[i].first.c_str());
					strcpy_s(src_text, sizeof(src_text), g.world.model_swapper.models[i].second.c_str());
				}

				if (selected_index == i)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(width);
		if (ImGui::BeginListBox("VIEW_MODEL_SWAPPER_SRC"_T.data()))
		{
			for (size_t i = 0; i < g.world.model_swapper.models.size(); i++)
			{
				if (ImGui::Selectable(g.world.model_swapper.models[i].second.c_str(), selected_index == i))
				{
					selected_index = i;
					strcpy_s(dst_text, sizeof(dst_text), g.world.model_swapper.models[i].first.c_str());
					strcpy_s(src_text, sizeof(src_text), g.world.model_swapper.models[i].second.c_str());
				}

				if (selected_index == i)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndListBox();
		}
		ImGui::PopID();
	}
}

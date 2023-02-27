#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	float draw_notification(float start_pos, ImDrawList* dl, std::string title, std::string message, ImVec4 color)
	{
		ImColor textCol   = ImGui::ColorConvertFloat4ToU32({1.f, 1.f, 1.f, 1.f});
		color.w           = 0.5f;
		ImColor fadeBegin = ImGui::ColorConvertFloat4ToU32(color);
		color.w           = 0.f;
		ImColor fadeEnd   = ImGui::ColorConvertFloat4ToU32(color);

		int j            = 0;
		int prevSpace    = 0;
		float total_size = 0.f;
		std::vector<std::string> split_points;
		for (int i = 0; i <= message.size(); i++)
		{
			std::string current_message = message.substr(j, i - j);

			if (message.substr(i, 1) == " ")
			{
				prevSpace = i;
			}

			ImVec2 size = ImGui::CalcTextSize(current_message.c_str());

			if (i == message.size())
			{
				total_size = total_size + size.y;
				split_points.push_back(message.substr(j, i));
			}
			else if (size.x >= 330.f)
			{
				total_size = total_size + size.y;
				split_points.push_back(message.substr(j, prevSpace - j));
				j = prevSpace + 1;
				i = prevSpace;
			}
		}

		dl->AddRectFilled({(float)*g_pointers->m_resolution_x - 360.f, 10.f + start_pos},
		    {(float)*g_pointers->m_resolution_x - 10.f, start_pos + 45.f + total_size},
		    g.window.color);
		dl->AddRectFilledMultiColor({(float)*g_pointers->m_resolution_x - 360.f, 10.f + start_pos}, {(float)*g_pointers->m_resolution_x - 255.f, start_pos + 45.f + total_size}, fadeBegin, fadeEnd, fadeEnd, fadeBegin);

		dl->AddText(g.window.font_sub_title,
		    22.f,
		    {(float)*g_pointers->m_resolution_x - 350.f, 15.f + start_pos},
		    textCol,
		    title.c_str());
		int i = 0;
		for (std::string txt : split_points)
		{
			dl->AddText({(float)*g_pointers->m_resolution_x - 350.f, 40.f + (i * 20.f) + start_pos}, textCol, txt.c_str());
			i++;
		}

		return start_pos + 45.f + total_size;
	}

	void view::notifications()
	{
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();

		std::vector<notification> notifications = g_notification_service->get();

		float prev_pos = 0.f;
		for (int i = 0; i < notifications.size(); i++)
		{
			notification& n = notifications[i];

			prev_pos =
			    draw_notification(prev_pos, draw_list, n.title, n.message, g_notification_service->notification_colors.at(n.type));
		}

		/*ImGui::SetNextWindowSize({ (float)g.window.x * 0.2f, (float)g.window.y });
		ImGui::SetNextWindowPos({ (float)g.window.x - (float)g.window.x * 0.2f, 0 });
		if (ImGui::Begin("notifications", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus))
		{
			std::vector<notification> notifications = g_notification_service->get();

			for (int i = 0; i < notifications.size(); i++)
			{
				notification& n = notifications[i];
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, n.alpha);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.10f, 0.09f, 0.12f, 1.00f));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.10f, 0.09f, 0.12f, 1.00f));
				ImGui::SetNextWindowBgAlpha(n.alpha);
				ImGui::BeginChildFrame(i, ImVec2(0, 75.f + (float)(20 * (int)(n.message.size() / 28) + 20 * (float)std::count(n.message.begin(), n.message.end(), '\n'))), ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs);
				ImGui::Text(n.title.c_str());
				ImGui::PushStyleColor(ImGuiCol_Text, g_notification_service->notification_colors.at(n.type));
				ImGui::TextWrapped(n.message.c_str());
				ImGui::PopStyleColor();
				ImGui::EndChildFrame();
				ImGui::PopStyleColor(2);
				ImGui::PopStyleVar();
			}
			ImGui::End();
		} */
	}
}
#include "pointers.hpp"
#include "views/view.hpp"

namespace big
{
	// developer made, developer left, new developer too scared to touch
	float draw_notification(float start_pos, ImDrawList* dl, const notification& notif)
	{
		auto color = notif.color();

		ImColor textCol   = ImGui::ColorConvertFloat4ToU32({1.f, 1.f, 1.f, 1.f});
		color.w           = 0.5f;
		ImColor fadeBegin = ImGui::ColorConvertFloat4ToU32(color);
		color.w           = 0.f;
		ImColor fadeEnd   = ImGui::ColorConvertFloat4ToU32(color);

		const auto alpha = notif.alpha();
		// actually make use of the fadeout
		textCol.Value.w *= alpha;
		fadeBegin.Value.w *= alpha;
		fadeEnd.Value.w *= alpha;

		int j            = 0;
		int prevSpace    = -1;
		float total_size = 0.f;
		std::vector<std::string> split_points;

		auto message = notif.message();
		for (int i = 0; i <= message.size(); i++)
		{
			const auto current_message = message.substr(j, i - j);
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
				if (prevSpace != -1)
				{
					total_size = total_size + size.y;
					split_points.push_back(message.substr(j, prevSpace - j));
					j = prevSpace + 1;
					i = prevSpace;
				}
				else
				{
					total_size = total_size + size.y;
					split_points.push_back(message.substr(j, i - j));
					j = i;
				}
			}
		}

		dl->AddRectFilled({(float)*g_pointers->m_gta.m_resolution_x - 360.f, 10.f + start_pos},
		    {(float)*g_pointers->m_gta.m_resolution_x - 10.f, start_pos + 45.f + total_size},
		    g.window.background_color);
		dl->AddRectFilledMultiColor({(float)*g_pointers->m_gta.m_resolution_x - 360.f, 10.f + start_pos},
		    {(float)*g_pointers->m_gta.m_resolution_x - 255.f, start_pos + 45.f + total_size},
		    fadeBegin,
		    fadeEnd,
		    fadeEnd,
		    fadeBegin);

		const auto count = notif.counter();
		auto title = count > 1 ? std::format("{} ({})", notif.title(), count < 100 ? std::to_string(count) : "+99") : notif.title();
		dl->AddText(g.window.font_sub_title,
		    22.f,
		    {(float)*g_pointers->m_gta.m_resolution_x - 350.f, 15.f + start_pos},
		    textCol,
		    title.c_str());
		int i = 0;
		for (std::string txt : split_points)
		{
			dl->AddText({(float)*g_pointers->m_gta.m_resolution_x - 350.f, 40.f + (i * 20.f) + start_pos}, textCol, txt.c_str());
			i++;
		}

		return start_pos + 45.f + total_size;
	}

	void view::notifications()
	{
		const auto draw_list = ImGui::GetBackgroundDrawList();
		const auto notifications = g_notification_service.get();

		float prev_pos = 0.f;
		for (const auto& notif : notifications)
		{
			prev_pos = draw_notification(prev_pos, draw_list, notif);
		}
	}
}

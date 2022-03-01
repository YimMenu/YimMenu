#include "view.hpp"
#include "services/notification_service.hpp"

namespace big
{
	void view::notifications()
	{
		ImGui::SetNextWindowSize({ (float)g->window.x * 0.2f, (float)g->window.y });
		ImGui::SetNextWindowPos({ (float)g->window.x - (float)g->window.x * 0.2f, 0 });
		if (ImGui::Begin("notifications", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBackground))
		{
			std::vector<notification> notifications = g_notification_service->get();

			for (int i = 0; i < notifications.size(); i++)
			{
				notification& n = notifications[i];
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, n.alpha);
				ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.10f, 0.09f, 0.12f, 1.00f));
				ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.10f, 0.09f, 0.12f, 1.00f));
				ImGui::SetNextWindowBgAlpha(n.alpha);
				ImGui::BeginChild(i, ImVec2(0, 75.f + (float)(20 * (int)(n.message.size() / 28) + 20 * (float)std::count(n.message.begin(), n.message.end(), '\n'))), true, ImGuiWindowFlags_NoScrollbar);
				ImGui::Text(n.title.c_str());
				ImGui::PushStyleColor(ImGuiCol_Text, g_notification_service->notification_colors.at(n.type));
				ImGui::TextWrapped(n.message.c_str());
				ImGui::PopStyleColor();
				ImGui::EndChild();
				ImGui::PopStyleVar();
				ImGui::PopStyleColor(2);
			}
		}
	}
}
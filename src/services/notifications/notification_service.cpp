#include "notification_service.hpp"

#include "widgets/imgui_hotkey.hpp"

namespace big
{
	notification_service::notification_service()
	{
		push("NOTIFICATION_WELCOME_TITLE"_T.data(),
		    std::vformat("NOTIFICATION_WELCOME_TEXT"_T, std::make_format_args(ImGui::key_names[g.settings.hotkeys.menu_toggle])));

		g_notification_service = this;
	}

	notification_service::~notification_service()
	{
		g_notification_service = nullptr;
	}

	void notification_service::push(notification n)
	{
		this->notifications.emplace(std::hash<std::string>{}(n.message + n.title), n);
	}

	void notification_service::push(std::string title, std::string message)
	{
		this->push({NotificationType::INFO, title, message, std::chrono::system_clock::now(), 5000.f, 1.f});
	}

	void notification_service::push_warning(std::string title, std::string message)
	{
		this->push({NotificationType::WARNING, title, message, std::chrono::system_clock::now(), 7000.f, 1.f});
	}

	void notification_service::push_error(std::string title, std::string message)
	{
		this->push({NotificationType::DANGER, title, message, std::chrono::system_clock::now(), 7000.f, 1.f});
	}

	std::vector<notification> notification_service::get()
	{
		std::vector<notification> notifications_to_sent;
		std::vector<std::size_t> to_remove;
		for (auto& n : this->notifications)
		{
			std::chrono::time_point<std::chrono::system_clock> curTime = std::chrono::system_clock::now();
			const float time_diff =
			    (float)std::chrono::duration_cast<std::chrono::milliseconds>(curTime - n.second.created_on).count();
			n.second.alpha = 1;
			if (n.second.destroy_in <= time_diff)
			{
				n.second.alpha = 1.f - ((time_diff - n.second.destroy_in) / 600);
				n.second.alpha = n.second.alpha < 0.f ? 0.f : n.second.alpha;
			}

			if (n.second.alpha > 0.f)
				notifications_to_sent.push_back(n.second);
			else
				to_remove.push_back(n.first);
		}
		for (std::size_t k : to_remove)
			this->notifications.erase(k);

		return notifications_to_sent;
	}

}
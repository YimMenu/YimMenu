#include "notification.hpp"

namespace big
{
	notification::notification(const std::string title, const std::string message, NotificationType type, const std::chrono::high_resolution_clock::duration lifetime) :
	    m_title(title),
	    m_message(message),
	    m_identifier(std::hash<std::string>{}(title + message)),
	    m_type(type),
	    m_lifetime(lifetime),
	    m_destroy_time(std::chrono::high_resolution_clock::now() + lifetime),
	    m_counter(1)
	{
		switch (type)
		{
		case NotificationType::DANGER: m_color = ImVec4(0.69f, 0.29f, 0.29f, 1.00f); break;
		case NotificationType::WARNING: m_color = ImVec4(0.69f, 0.49f, 0.29f, 1.00f); break;
		case NotificationType::SUCCESS: m_color = ImVec4(0.29f, 0.69f, 0.34f, 1.00f); break;
		default:
		case NotificationType::INFO: m_color = ImVec4(0.80f, 0.80f, 0.83f, 1.00f); break;
		}
	}

	// linear fade out in the last 600ms
	const float notification::alpha() const
	{
		const auto remaining_time = std::chrono::duration_cast<std::chrono::milliseconds>(m_destroy_time - std::chrono::high_resolution_clock::now());
		if (remaining_time < 300ms)
		{
			return (float)remaining_time.count() / 300.f;
		}
		return 1.0f;
	}

	void notification::reset()
	{
		++m_counter;

		m_destroy_time = std::chrono::high_resolution_clock::now() + m_lifetime;
	}

	bool notification::should_be_destroyed() const
	{
		return m_destroy_time < std::chrono::high_resolution_clock::now();
	}
}

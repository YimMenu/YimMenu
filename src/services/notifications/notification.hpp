#pragma once

namespace big
{
	enum class NotificationType
	{
		INFO,
		SUCCESS,
		WARNING,
		DANGER,
	};

	class notification
	{
	private:
		std::string m_title;
		std::string m_message;
		std::size_t m_identifier;

		NotificationType m_type;

		std::chrono::high_resolution_clock::duration m_lifetime;
		std::chrono::steady_clock::time_point m_destroy_time;

		ImVec4 m_color;
		std::size_t m_counter;

	public:
		notification()                                   = default;
		virtual ~notification()                          = default;
		notification(const notification&)                = default;
		notification(notification&&) noexcept            = default;
		notification& operator=(const notification&)     = default;
		notification& operator=(notification&&) noexcept = default;

		notification(const std::string title, const std::string message, NotificationType type, const std::chrono::high_resolution_clock::duration lifetime = std::chrono::seconds(5));

		const std::string& title() const
		{
			return m_title;
		}
		const std::string& message() const
		{
			return m_message;
		}
		const std::size_t identifier() const
		{
			return m_identifier;
		}

		const NotificationType type() const
		{
			return m_type;
		}

		const std::chrono::steady_clock::time_point destroy_time() const
		{
			return m_destroy_time;
		}

		const float alpha() const;
		const ImVec4 color() const
		{
			return m_color;
		}

		/**
         * @brief Returns the amount of times the notification was refreshed because the same notification was pushed.
         * 
         * @return const std::size_t 
         */
		const std::size_t counter() const
		{
			return m_counter;
		}

		/**
         * @brief Resets the destroy timer on a notification, extending its lifetime and incrementing the show counter.
         */
		void reset();
		/**
         * @brief Indicates if the notification is ready to be destroyed (it has gone past its lifetime).
         * 
         * @return true 
         * @return false 
         */
		bool should_be_destroyed() const;
	};
}

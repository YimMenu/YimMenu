#pragma once

namespace big
{
	class rate_limiter
	{
		uint32_t m_attempts_allowed_in_time_period;
		std::chrono::milliseconds m_time_period;
		std::chrono::system_clock::time_point m_last_event_time{};
		uint32_t m_num_attempts_allowed = 0;

	public:
		rate_limiter(std::chrono::milliseconds time_period, uint32_t num_allowed_attempts) :
		    m_attempts_allowed_in_time_period(num_allowed_attempts),
		    m_time_period(time_period)
		{
		}

		// Returns true if the rate limit has been exceeded
		bool process()
		{
			if (std::chrono::system_clock::now() - m_last_event_time < m_time_period)
			{
				if (++m_num_attempts_allowed > m_attempts_allowed_in_time_period)
					return true;
			}
			else
			{
				m_last_event_time      = std::chrono::system_clock::now();
				m_num_attempts_allowed = 1;
			}
			return false;
		}

		// Check if the rate limit was exceeded by the last process() call. Use this to prevent the player from being flooded with notifications
		bool exceeded_last_process()
		{
			return (m_num_attempts_allowed - 1) == m_attempts_allowed_in_time_period;
		}
	};
}
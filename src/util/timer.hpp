#pragma once
#include <chrono>

namespace big
{
	class timer
	{
	public:
		explicit timer(std::chrono::milliseconds delay) :
		    m_timer(std::chrono::steady_clock::now()),
		    m_delay(delay)
		{
		}

		bool updated()
		{
			auto now = std::chrono::steady_clock::now();
			if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_timer) >= m_delay)
			{
				m_timer = now;
				return true;
			}

			return false;
		}

		void set_delay(std::chrono::milliseconds delay)
		{
			m_delay = delay;
		}

	private:
		std::chrono::steady_clock::time_point m_timer;
		std::chrono::milliseconds m_delay;
	};
}

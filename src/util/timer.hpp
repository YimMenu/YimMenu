#pragma once
#include <chrono>

class timer
{
public:
	explicit timer(std::chrono::nanoseconds delay) :
	    m_timer(std::chrono::high_resolution_clock::now()),
		m_delay(std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(delay))
	{
	}

	bool updated()
	{
		auto now = std::chrono::high_resolution_clock::now();
		if ((now.time_since_epoch() - m_timer.time_since_epoch()).count() >= m_delay.count())
		{
			m_timer = now;
			return true;
		}

		return false;
	}

	void set_delay(std::chrono::nanoseconds delay) {
		m_delay = delay;
	}
private:
	std::chrono::high_resolution_clock::time_point m_timer;
	std::chrono::high_resolution_clock::duration m_delay;
};

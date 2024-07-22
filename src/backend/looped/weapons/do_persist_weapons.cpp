#include "backend/looped/looped.hpp"
#include "services/persist_weapons/persist_weapons.hpp"

namespace big
{
	static auto last_time = std::chrono::steady_clock::now();

	void looped::weapons_do_persist_weapons()
	{
		const auto time_now = std::chrono::steady_clock::now();

		const auto elapsed_time_in_ms = std::chrono::duration_cast<std::chrono::milliseconds>(time_now - last_time);

		if (elapsed_time_in_ms >= 500ms) [[unlikely]]
		{
			last_time = time_now;

			persist_weapons::check_player_has_weapons();
		}
	}
}

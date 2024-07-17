#include "backend/looped_command.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"
#include "services/tunables/tunables_service.hpp"

namespace big
{
	class no_idle_kick : looped_command
	{
		using looped_command::looped_command;

		std::array<int, 8> m_restore;
		bool m_backed_up;

		const std::vector<Hash> m_tunable_hashes = {"IDLEKICK_WARNING1"_J, "IDLEKICK_WARNING2"_J, "IDLEKICK_WARNING3"_J, "IDLEKICK_KICK"_J, "ConstrainedKick_Warning1"_J, "ConstrainedKick_Warning2"_J, "ConstrainedKick_Warning3"_J, "ConstrainedKick_Kick"_J};

		virtual void on_tick() override
		{
			if (!m_backed_up) [[unlikely]]
			{
				bool did_fail = false;
				for (int i = 0; i < m_restore.size(); i++)
				{
					if (auto tunable = g_tunables_service->get_tunable<int*>(m_tunable_hashes[i]))
					{
						m_restore[i] = *tunable;
					}
					else
					{
						did_fail = true;
					}
				}
				m_backed_up = !did_fail;
			}
			else
			{
				for (Hash hash_iter : m_tunable_hashes)
				{
					if (auto tunable_ptr = g_tunables_service->get_tunable<int*>(hash_iter))
					{
						*tunable_ptr = INT_MAX;
					}
				}
			}
		}

		virtual void on_disable() override
		{
			if (m_backed_up)
			{
				for (int i = 0; i < m_restore.size(); ++i)
					*g_tunables_service->get_tunable<int*>(m_tunable_hashes[i]) = m_restore[i];
			}
		}
	};

	no_idle_kick g_no_idle_kick("noidlekick", "NO_IDLE_KICK", "NO_IDLE_KICK_DESC", g.tunables.no_idle_kick);
}

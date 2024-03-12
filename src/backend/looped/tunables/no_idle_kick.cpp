#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	class no_idle_kick : looped_command
	{
		using looped_command::looped_command;

		std::array<int*, 8> m_tunables = {nullptr};
		std::array<int, 8> m_restore;
		bool m_ready_to_use;

		virtual void on_tick() override
		{
			if (!m_ready_to_use)
			{
				m_tunables[0] = g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING1"_J);
				m_tunables[1] = g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING2"_J);
				m_tunables[2] = g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING3"_J);
				m_tunables[3] = g_tunables_service->get_tunable<int*>("IDLEKICK_KICK"_J);
				m_tunables[4] = g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning1"_J);
				m_tunables[5] = g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning2"_J);
				m_tunables[6] = g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning3"_J);
				m_tunables[7] = g_tunables_service->get_tunable<int*>("ConstrainedKick_Kick"_J);

				// create backup of tunables
				m_ready_to_use = true;
				for (int i = 0; i < m_restore.size(); ++i)
				{
					if (m_ready_to_use = m_tunables[i]; !m_ready_to_use)
						break;
					m_restore[i] = *m_tunables[i];
				}
			}
			else
			{
				for (const auto& tunable : m_tunables)
				{
					if (tunable)
						*tunable = INT_MAX;
				}
			}
		}

		virtual void on_disable() override
		{
			for (int i = 0; m_ready_to_use && i < m_restore.size(); ++i)
			{
				if (m_tunables[i])
					*m_tunables[i] = m_restore[i];
			}
		}
	};

	no_idle_kick g_no_idle_kick("noidlekick", "NO_IDLE_KICK", "NO_IDLE_KICK_DESC", g.tunables.no_idle_kick);
}

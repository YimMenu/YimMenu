#include "backend/looped_command.hpp"
#include "services/tunables/tunables_service.hpp"
#include "core/scr_globals.hpp"
#include "natives.hpp"

namespace big
{
	class no_idle_kick : looped_command
	{
		using looped_command::looped_command;

		std::array<int, 8> m_restore;
		bool m_backed_up;

		virtual void on_tick() override
		{
			if (!m_backed_up) [[unlikely]]
			{
				m_restore[0] = *g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING1"_J);
				m_restore[1] = *g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING2"_J);
				m_restore[2] = *g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING3"_J);
				m_restore[3] = *g_tunables_service->get_tunable<int*>("IDLEKICK_KICK"_J);
				m_restore[4] = *g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning1"_J);
				m_restore[5] = *g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning2"_J);
				m_restore[6] = *g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning3"_J);
				m_restore[7] = *g_tunables_service->get_tunable<int*>("ConstrainedKick_Kick"_J);
				m_backed_up  = true;
			}
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING1"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING2"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING3"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("IDLEKICK_KICK"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning1"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning2"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning3"_J) = INT_MAX;
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Kick"_J) = INT_MAX;
		}

		virtual void on_disable() override
		{
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING1"_J) = m_restore[0];
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING2"_J) = m_restore[1];
			*g_tunables_service->get_tunable<int*>("IDLEKICK_WARNING3"_J) = m_restore[2];
			*g_tunables_service->get_tunable<int*>("IDLEKICK_KICK"_J) = m_restore[3];
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning1"_J) = m_restore[4];
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning2"_J) = m_restore[5];
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Warning3"_J) = m_restore[6];
			*g_tunables_service->get_tunable<int*>("ConstrainedKick_Kick"_J) = m_restore[7];
		}
	};

	no_idle_kick g_no_idle_kick("noidlekick", "NO_IDLE_KICK", "NO_IDLE_KICK_DESC", g.tunables.no_idle_kick);
}

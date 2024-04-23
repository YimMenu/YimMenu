#include "script_connection.hpp"

#include "gta_util.hpp"
#include "natives.hpp"
#include "script.hpp"
#include "util/scripts.hpp"

#include <script/globals/GPBD_FM_3.hpp>

namespace big
{
	bool script_connection::does_remote_script_exist()
	{
		return NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(m_target->get()->id(), m_script_name.data(), -1);
	}

	bool script_connection::start_script_on_local()
	{
		while (!SCRIPT::HAS_SCRIPT_WITH_NAME_HASH_LOADED(m_script_hash))
		{
			SCRIPT::REQUEST_SCRIPT_WITH_NAME_HASH(m_script_hash);
			script::get_current()->yield();
		}

		auto program = gta_util::find_script_program(m_script_hash);

		int count              = program->m_local_count;
		program->m_local_count = 2;
		int id                 = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(m_script_hash, DEFAULT_STACK_SIZE);
		program->m_local_count = count;


		SCRIPT::SET_SCRIPT_WITH_NAME_HASH_AS_NO_LONGER_NEEDED(m_script_hash);
		m_thread = gta_util::find_script_thread_by_id(id);

		if (!m_thread)
			return false;

		m_thread->m_context.m_state = rage::eThreadState::unk_3;
		return true;
	}

	void script_connection::start_script_on_remote()
	{
		if (!m_target)
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Starting " << m_script_name << " using am_launcher";

			scripts::start_launcher_script(scripts::launcher_index_from_hash(m_script_hash));
		}
		else
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Starting " << m_script_name << " using TSEs";

			const size_t arg_count = 26;
			int64_t args[arg_count] = {(int64_t)eRemoteEvent::StartScriptBegin, (int64_t)self::id, 1 << m_target->get()->id()};

			args[3] = scripts::launcher_index_from_hash(m_script_hash);
			strcpy((char*)&args[3 + 3], "0");
			args[3 + 16] = -1;
			args[3 + 17] = 1337;
			args[25] = scr_globals::gpbd_fm_3.as<GPBD_FM_3*>()->Entries[m_target->get()->id()].ScriptEventReplayProtectionCounter;

			g_pointers->m_gta.m_trigger_script_event(1, args, arg_count, 1 << m_target->get()->id(), (int)eRemoteEvent::StartScriptBegin);

			for (int i = 0; i < 2; i++)
			{
				const size_t arg_count_2    = 26;
				int64_t args_2[arg_count_2] = {(int64_t)eRemoteEvent::StartScriptProceed, (int64_t)self::id, 1 << m_target->get()->id()};
				args_2[3 + 17]              = 1337;
				g_pointers->m_gta.m_trigger_script_event(1, args_2, arg_count_2, 1 << m_target->get()->id(), (int)eRemoteEvent::StartScriptProceed);

				script::get_current()->yield(20ms);
			}
		}
	}

	bool script_connection::populate_instance_id()
	{
		for (int i = 0; i < 0x100; i++)
		{
			if (NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(m_target->get()->id(), m_script_name.data(), i))
			{
				m_instance_id = i;
				break;
			}
		}

		return m_instance_id != -1;
	}

	bool script_connection::set_script_as_networked()
	{
		gta_util::execute_as_script(m_thread, [this] {
			NETWORK::NETWORK_SET_THIS_SCRIPT_IS_NETWORK_SCRIPT(32, true, m_instance_id);
		});

		for (int i = 0; i < 100; i++)
		{
			int status = 0;
			gta_util::execute_as_script(m_thread, [&status] {
				status = NETWORK::NETWORK_GET_SCRIPT_STATUS();
			});

			if (status == 2)
				return true;

			if (status > 2)
			{
				break;
			}

			script::get_current()->yield(50ms);
		}

		return false;
	}

	void script_connection::setup_broadcast_data()
	{
		auto locals = gta_util::find_script_program(m_script_hash)->m_local_data;

		if (m_host_broadcast_size)
		{
			m_host_broadcast_data = new uint64_t[m_host_broadcast_size];

			if (m_host_broadcast_default_data_address.has_value())
				memcpy(m_host_broadcast_data, &locals[m_host_broadcast_default_data_address.value()], m_host_broadcast_size * sizeof(uint64_t));
			else
				memset(m_host_broadcast_data, 0, m_host_broadcast_size * sizeof(uint64_t));
		}

		if (m_player_broadcast_data)
		{
			m_player_broadcast_data = new uint64_t[m_player_broadcast_size];

			if (m_player_broadcast_default_data_address.has_value())
			{
				memcpy(m_player_broadcast_data, &locals[m_player_broadcast_default_data_address.value()], m_player_broadcast_size * sizeof(uint64_t));
			}
			else
			{
				memset(m_player_broadcast_data, 0, m_player_broadcast_size * sizeof(uint64_t));
				m_player_broadcast_data[0] = 32;
			}
		}

		if (m_broadcast_setup_callback)
			m_broadcast_setup_callback(m_thread, m_host_broadcast_data, m_player_broadcast_data);
	}

	void script_connection::register_broadcast_data()
	{
		gta_util::execute_as_script(m_thread, [this] {
			if (m_host_broadcast_size)
				NETWORK::NETWORK_REGISTER_HOST_BROADCAST_VARIABLES((int*)m_host_broadcast_data, m_host_broadcast_size, 0);

			if (m_player_broadcast_size)
				NETWORK::NETWORK_REGISTER_PLAYER_BROADCAST_VARIABLES((int*)m_player_broadcast_data, m_player_broadcast_size, 0);
		});
	}

	bool script_connection::force_host_of_script()
	{
		if (m_thread && m_thread->m_net_component)
		{
			for (int i = 0; !((CGameScriptHandlerNetComponent*)m_thread->m_net_component)->is_local_player_host(); i++)
			{
				if (i > 200)
					return false;

				((CGameScriptHandlerNetComponent*)m_thread->m_net_component)
				    ->send_host_migration_event(g_player_service->get_self()->get_net_game_player());
				script::get_current()->yield(10ms);

				if (!m_thread->m_stack || !m_thread->m_net_component)
					return false;
			}

			((CGameScriptHandlerNetComponent*)m_thread->m_net_component)->block_host_migration(true);
		}

		return true;
	}

	bool script_connection::wait_for_host_broadcast_data()
	{
		for (int i = 0; i < 3600; i++)
		{
			bool received = false;
			gta_util::execute_as_script(m_thread, [&received] {
				received = NETWORK::NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA();
			});

			if (received)
				return true;

			script::get_current()->yield();
		}

		return false;
	}

	bool script_connection::wait_for_connection_to_remote()
	{
		for (int i = 0; i < 100; i++)
		{
			bool is_a_participant = false;
			gta_util::execute_as_script(m_thread, [&is_a_participant, this] {
				is_a_participant = NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT(m_target->get()->id());
			});

			if (is_a_participant)
				return true;

			script::get_current()->yield(25ms);
		}

		return false;
	}

	bool script_connection::start_impl()
	{
		auto need_to_create = !m_target || !populate_instance_id();

		if (need_to_create && m_no_remote_start)
		{
			if (m_debug_logging)
				LOG(FATAL) << "Script must be started on remote, but script starting is disabled";

			return false;
		}

		if (!start_script_on_local())
		{
			if (m_debug_logging)
				LOG(FATAL) << "Failed to start script locally";

			return false;
		}

		if (!set_script_as_networked())
		{
			if (m_debug_logging)
				LOG(FATAL) << "Failed to set script as networked";

			return false;
		}

		setup_broadcast_data();
		register_broadcast_data();

		if (!need_to_create && (!m_target || !m_target->get()->is_valid() || !wait_for_connection_to_remote()))
		{
			if (m_debug_logging)
				LOG(FATAL) << "Remote no longer a participant";

			return false;
		}

		if (m_wait_for_host_broadcast_data && !wait_for_host_broadcast_data())
		{
			if (m_debug_logging)
				LOG(FATAL) << "Failed to receive host broadcast data";

			return false;
		}

		if (!force_host_of_script())
		{
			if (m_debug_logging)
				LOG(FATAL) << "Failed to get script host";

			return false;
		}

		if (need_to_create)
			start_script_on_remote();

		if (need_to_create && m_target && !wait_for_connection_to_remote())
		{
			if (m_debug_logging)
				LOG(FATAL) << "Failed to connect to remote";

			return false;
		}

		if (m_broadcast_modify_callback)
			m_broadcast_modify_callback(m_thread, m_host_broadcast_data, m_player_broadcast_data);

		m_startup_done          = true;
		m_startup_complete_time = std::chrono::system_clock::now();

		return true;
	}

	script_connection::script_connection(const std::string& script_name, std::optional<player_ptr> target) :
	    m_script_name(script_name),
	    m_script_hash(rage::joaat(script_name)),
	    m_target(target)
	{
	}

	void script_connection::start()
	{
		if (m_startup_done && m_thread && m_broadcast_modify_callback)
			m_broadcast_modify_callback(m_thread, m_host_broadcast_data, m_player_broadcast_data);

		if (m_startup_done || m_startup_failed)
			return;

		if (!start_impl())
			m_startup_failed = true;
	}

	void script_connection::cleanup()
	{
		if (m_thread)
		{
			m_thread->kill();
			m_thread = nullptr;
		}

		if (m_host_broadcast_data)
		{
			delete[] m_host_broadcast_data;
			m_host_broadcast_data = nullptr;
		}

		if (m_player_broadcast_data)
		{
			delete[] m_player_broadcast_data;
			m_player_broadcast_data = nullptr;
		}
	}

	bool script_connection::should_cleanup()
	{
		if (m_startup_failed)
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Startup has failed, cleaning up";

			return true;
		}

		if (m_startup_done && (!m_thread || m_thread->m_stack == nullptr || m_thread->m_context.m_state == rage::eThreadState::killed))
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Local thread has been terminated, cleaning up";

			return true;
		}

		if (m_startup_done && m_target && !m_target->get()->is_valid())
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Target has left, cleaning up";

			return true;
		}

#if 0
		if (m_target && m_target->get()->is_valid())
		{
			bool is_a_participant = false;

			gta_util::execute_as_script(m_thread, [&is_a_participant, this] {
				is_a_participant = NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT(m_target->get()->id());
			});

			if (!is_a_participant)
			{
				if (m_debug_logging)
					LOG(VERBOSE) << "Target no longer a participant, cleaning up";

				return true;
			}
		}
#endif

		bool might_cleanup = m_quick_cleanup || MISC::GET_NUMBER_OF_FREE_STACKS_OF_THIS_SIZE(DEFAULT_STACK_SIZE) < 5;

		if (might_cleanup && m_startup_complete_time.has_value()
		    && std::chrono::system_clock::now() - m_startup_complete_time.value() > 5s)
		{
			if (m_debug_logging)
				LOG(VERBOSE) << "Cleaning up";

			return true;
		}

		return false;
	}
}
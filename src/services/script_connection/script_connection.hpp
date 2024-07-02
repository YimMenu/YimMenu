#pragma once
#include "services/players/player_service.hpp"

namespace big
{
	constexpr int DEFAULT_STACK_SIZE = 1424;

	class script_connection
	{
		std::string m_script_name;
		rage::joaat_t m_script_hash;
		std::optional<player_ptr> m_target;
		int m_instance_id                                          = -1;
		rage::scrThread* m_thread                                  = nullptr;
		bool m_startup_done                                        = false;
		bool m_startup_failed                                      = false;
		int m_host_broadcast_size                                  = 0;
		int m_player_broadcast_size                                = 0;
		bool m_debug_logging                                       = false;
		bool m_wait_for_host_broadcast_data                        = false;
		bool m_no_remote_start                                     = false;
		bool m_quick_cleanup                                       = false;
		std::optional<int> m_host_broadcast_default_data_address   = std::nullopt;
		std::optional<int> m_player_broadcast_default_data_address = std::nullopt;
		int m_max_players                                          = 32;

		std::function<void(rage::scrThread*, uint64_t*, uint64_t*)> m_broadcast_setup_callback{};
		std::function<void(rage::scrThread*, uint64_t*, uint64_t*)> m_broadcast_modify_callback{};

		uint64_t* m_host_broadcast_data                                         = nullptr;
		uint64_t* m_player_broadcast_data                                       = nullptr;
		std::optional<std::chrono::system_clock::time_point> m_startup_complete_time = std::nullopt;

		bool does_remote_script_exist();
		bool start_script_on_local();
		void start_script_on_remote();
		bool populate_instance_id();
		bool set_script_as_networked();
		void setup_broadcast_data();
		void register_broadcast_data();
		bool force_host_of_script();
		bool wait_for_host_broadcast_data();
		bool wait_for_connection_to_remote();

		bool start_impl();

	public:
		script_connection(const std::string& script_name, std::optional<player_ptr> target = std::nullopt);
		void start();
		void cleanup();
		bool should_cleanup();
		void give_host();

		// clang-format off

		inline rage::joaat_t get_script_hash() { return m_script_hash; }
		inline std::optional<player_ptr> get_target() { return m_target; }
		inline rage::scrThread* get_script_thread() { return m_thread; }

		inline void set_host_broadcast_size(int size) { m_host_broadcast_size = size; }
		inline void set_player_broadcast_size(int size) { m_player_broadcast_size = size; }
		inline void set_debug_logging(bool enabled) { m_debug_logging = enabled; }
		inline void set_wait_for_host_broadcast_data(bool enabled) { m_wait_for_host_broadcast_data = enabled; }
		inline void set_no_remote_start(bool enabled) { m_no_remote_start = enabled; }
		inline void set_quick_cleanup(bool enabled) { m_quick_cleanup = enabled; }
		inline void set_host_broadcast_default_data_address(int data_address) { m_host_broadcast_default_data_address = data_address; }
		inline void set_player_broadcast_default_data_address(int data_address) { m_player_broadcast_default_data_address = data_address; }
		inline void set_max_players(int num) { m_max_players = num; }

		// thread, host_broadcast_data, player_broadcast_data
		inline void set_broadcast_setup_callback(std::function<void(rage::scrThread*, uint64_t*, uint64_t*)> cb) { m_broadcast_setup_callback = std::move(cb); }
		inline void set_broadcast_modify_callback(std::function<void(rage::scrThread*, uint64_t*, uint64_t*)> cb) { m_broadcast_modify_callback = std::move(cb); }

		inline void invalidate_script_thread() { m_thread = nullptr; }

		// clang-format on
	};
}
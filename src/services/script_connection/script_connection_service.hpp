#pragma once
#include "script_connection.hpp"

namespace big
{
	class script_connection_service
	{
		std::vector<std::unique_ptr<script_connection>> m_script_connections;
		script_connection* get_connection(const std::string& script_name, std::optional<player_ptr> target);

	public:
		script_connection_service();
		~script_connection_service();

		script_connection* create_connection(const std::string& script_name, std::optional<player_ptr> target);
		void on_tick();
	};

	inline script_connection_service* g_script_connection_service;
}
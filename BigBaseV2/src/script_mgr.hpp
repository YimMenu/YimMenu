#pragma once
#include "common.hpp"
#include "script.hpp"

namespace big
{

	inline bool g_script_self = true;
	inline bool g_script_weapons = true;
	inline bool g_script_vehicles = true;
	inline bool g_script_misc = true;
	inline bool g_script_remote = true;
	inline bool g_script_noclip = true;
	inline bool g_script_lscustoms = true;
	inline bool g_script_vehiclefly = true;
	inline bool g_script_rgbrandomizer = true;
	inline bool g_script_contextmenu = true;
	inline bool g_script_turnsignal = true;

	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void add_script(std::unique_ptr<script> script);
		void remove_all_scripts();
		void tick();
		std::vector<script*> get_scripts_data() {
			std::vector<script*> retvalue{};
			for (auto& s : m_scripts) { 
				if(s->get_enabled_pointer())
					retvalue.push_back(s.get());
			}
			return retvalue;
		}
	private:
		void tick_internal();
	private:
		std::recursive_mutex m_mutex;
		std::vector<std::unique_ptr<script>> m_scripts;
	};

	inline script_mgr g_script_mgr;
}

#pragma once
#include "gta/joaat.hpp"
#include "memory/pattern.hpp"

namespace big
{
	// a lightweight script function wrapper inspired by https://github.com/Parik27/V.Rainbomizer/blob/master/src/mission/missions_YscUtils.hh
	class script_function
	{
		rage::joaat_t m_script;
		const memory::pattern m_pattern;
		int32_t m_offset;
		int32_t m_ip;
		std::string m_name;

	public:
		script_function(const std::string& name, const rage::joaat_t script, const std::string& pattern, int32_t offset);
		void populate_ip();
		void call(rage::scrThread* thread, rage::scrProgram* program, std::initializer_list<std::uint64_t> args);

		// for pure functions that do not need access to thread stack
		void static_call(std::initializer_list<std::uint64_t> args);

		void operator()(std::initializer_list<std::uint64_t> args);
	};

	namespace scr_functions
	{
		static inline script_function join_ceo("JC", RAGE_JOAAT("freemode"), "2D 04 1D 00 00 5D", 0);
		static inline script_function set_freemode_session_active("SFSA", RAGE_JOAAT("freemode"), "2D 00 02 00 00 75 5D ? ? ? 50", 0);
		static inline script_function dance_loop("DL", RAGE_JOAAT("am_mp_nightclub"), "2D 00 14 00 00 4F ? ? 47 ? ? 5D ? ? ? 56", 0);
		static inline script_function init_nightclub_script("INS", RAGE_JOAAT("am_mp_nightclub"), "2D 00 11 00 00 4F", 0);

		static inline script_function save_to_datafile("STD", RAGE_JOAAT("fm_race_creator"), "2D 01 03 00 00 71 2C", 0);
		static inline script_function load_from_datafile("LFD", RAGE_JOAAT("fm_race_creator"), "2D 04 0D 00 00 71 2C", 0);
	}
}
#pragma once
#include "gta_util.hpp"
#include "natives.hpp"
#include "script_local.hpp"
#include "local_player.hpp"

namespace lua_script
{
	static Hash stat_text_to_hash(std::string& text)
	{
		if (text[0] == '$')
		{
			text = text.substr(1);
		}

		std::transform(text.begin(), text.end(), text.begin(), ::toupper);

		if (text.substr(0, 3) == "MPX")
			text[2] = big::local_player::get_active_character_slot() + '0';

		return rage::joaat(text);
	}

	namespace stats
	{
		static inline int get_int(Hash stat_hash)
		{
			int out_value;
			STATS::STAT_GET_INT(stat_hash, &out_value, -1);

			return out_value;
		}
		static inline int get_int(std::string stat_name)
		{
			return get_int(stat_text_to_hash(stat_name));
		}
		static inline bool set_int(Hash stat_hash, int value, bool save = true)
		{
			return STATS::STAT_SET_INT(stat_hash, value, save);
		}
		static inline bool set_int(std::string stat_name, int value, bool save = true)
		{
			return set_int(stat_text_to_hash(stat_name), value, save);
		}
	}
	namespace locals
	{
		template<typename T>
		inline T get(const std::string& script, int index)
		{
			static std::remove_pointer_t<T> null{};
			auto thread = big::gta_util::find_script_thread(rage::joaat(script));
			if (thread)
				return big::script_local(thread->m_stack, index).as<T>();

			return &null;
		}
		static inline int get_int(const std::string& script, int index)
		{
			return *get<int*>(script, index);
		}

		static inline void set_int(const std::string& script, int index, int val)
		{
			*get<int*>(script, index) = val;
		}

		static inline int get_float(const std::string& script, int index)
		{
			return *get<float*>(script, index);
		}

		static inline void set_float(const std::string& script, int index, float val)
		{
			*get<float*>(script, index) = val;
		}
	}
}
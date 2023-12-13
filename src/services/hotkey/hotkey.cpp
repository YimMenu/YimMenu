#include "hotkey.hpp"

namespace big
{
	hotkey::hotkey(rage::joaat_t name_hash, key_t key, rage::joaat_t command_hash, std::optional<std::chrono::high_resolution_clock::duration> cooldown) :
	    m_name_hash(name_hash),
	    m_key(key),
	    m_command_hash(command_hash),
	    m_cooldown(cooldown),
	    m_wakeup()
	{
	}

	bool hotkey::can_exec() const
	{
		return !m_cooldown.has_value() || std::chrono::high_resolution_clock::now() >= m_wakeup;
	}

	void hotkey::exec()
	{
		if (m_cooldown.has_value())
			m_wakeup = std::chrono::high_resolution_clock::now() + m_cooldown.value();

		command::get(m_command_hash)->call({});
	}

	rage::joaat_t hotkey::name_hash() const
	{
		return m_name_hash;
	}

	void hotkey::set_key(key_t new_key)
	{
		m_key = new_key;
	}
}
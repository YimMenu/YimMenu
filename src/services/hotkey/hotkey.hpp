#pragma once
#include "backend/command.hpp"
#include "common.hpp"
#include "rage/joaat.hpp"

namespace big
{
	using key_t = unsigned int;

	class hotkey final
	{
	public:
		hotkey(rage::joaat_t name_hash, key_t key, rage::joaat_t command_hash, std::optional<std::chrono::high_resolution_clock::duration> cooldown = std::nullopt);
		virtual ~hotkey() = default;

		bool can_exec() const;
		void exec();

		rage::joaat_t name_hash() const;
		void set_key(key_t new_key);

	private:
		rage::joaat_t m_name_hash;
		key_t m_key;

		rage::joaat_t m_command_hash;
		std::optional<std::chrono::high_resolution_clock::duration> m_cooldown;
		std::chrono::high_resolution_clock::time_point m_wakeup;
	};
}
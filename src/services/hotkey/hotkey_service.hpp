#pragma once
#include "common.hpp"
#include "core/enums.hpp"
#include "hotkey.hpp"

namespace big
{
	using hotkey_map = std::multimap<key_t, hotkey>;

	class hotkey_service final
	{
	public:
		hotkey_service();
		virtual ~hotkey_service();
		hotkey_service(const hotkey_service&)                = delete;
		hotkey_service(hotkey_service&&) noexcept            = delete;
		hotkey_service& operator=(const hotkey_service&)     = delete;
		hotkey_service& operator=(hotkey_service&&) noexcept = delete;


		void register_hotkey(const std::string_view name, const key_t initial_key, const rage::joaat_t command_hash, const eKeyState state = eKeyState::RELEASE, std::optional<std::chrono::high_resolution_clock::duration> cooldown = std::nullopt);
		bool update_hotkey(const std::string_view name, const key_t new_key);
		void wndproc(eKeyState state, key_t key);

	private:
		// yes curse me
		std::array<hotkey_map, 2> m_hotkeys;
	};

	inline hotkey_service* g_hotkey_service{};
}

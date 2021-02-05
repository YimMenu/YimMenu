#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <D3D11.h>
#include <wrl/client.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>

#include <chrono>
#include <ctime>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <atomic>
#include <mutex>
#include <thread>

#include <memory>
#include <new>

#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <functional>
#include <utility>

#include <stack>
#include <vector>

#include <typeinfo>
#include <type_traits>

#include <exception>
#include <stdexcept>

#include <any>
#include <optional>
#include <variant>

#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "logger.hpp"
#include "settings.h"

#include "gta/ped_factory.hpp"
#include "structs/lists.hpp"
#include "structs/player.hpp"
#include "structs/temp.hpp"

namespace big
{
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ true };

	// Global Variables
	inline player g_player;
	inline player g_selectedPlayer;
	inline std::unordered_map<Player, player> g_players;
	
	inline CAutomobile* g_vehicle;

	inline temp g_temp = temp{};

	// screen width and height
	inline int x, y;
}

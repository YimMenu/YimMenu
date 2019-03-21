#pragma once

#define NOMINMAX
#define _CRT_SECURE_NO_WARNINGS

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0601

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

#define FMT_HEADER_ONLY
#include <cpptoml/cpptoml.h>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <StackWalker/StackWalker.h>

#include "logger.hpp"

namespace big
{
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ true };
	
	struct stackwalker : public StackWalker
	{
		using StackWalker::StackWalker;

		void OnOutput(LPCSTR szText) override
		{
			g_logger->raw(log_color::red, szText);
		}
	};

	inline stackwalker g_stackwalker;
}

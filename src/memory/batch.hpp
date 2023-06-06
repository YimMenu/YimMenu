#pragma once
#include "pattern.hpp"
#include "range.hpp"
#include "signature.hpp"

#include <future>

namespace memory
{
	template<size_t N>
	struct batch
	{
		std::array<signature, N> m_entries;

		constexpr batch(std::array<signature, N> entries)
		{
			m_entries = entries;
		}
	};

	template<size_t N>
	struct batch_and_hash
	{
		batch<N> m_batch;
		uint32_t m_hash;
	};

	struct signature_hasher
	{
		static inline constexpr uint32_t FNV_PRIME_32  = 16777619u;
		static inline constexpr uint32_t FNV_OFFSET_32 = 2166136261u;

		static inline constexpr uint32_t fnv1a_32(const char* str, uint32_t hash = FNV_OFFSET_32) noexcept
		{
			return (str[0] == '\0') ? hash : fnv1a_32(&str[1], (hash ^ static_cast<uint32_t>(str[0])) * FNV_PRIME_32);
		}

		template<signature sig>
		static inline constexpr uint32_t compute_hash(uint32_t hash)
		{
			hash = fnv1a_32(sig.m_ida, hash);

			return hash;
		}

		template<signature sig, signature... rest_sigs>
		static inline constexpr uint32_t add(uint32_t hash = FNV_OFFSET_32)
		{
			hash = compute_hash<sig>(hash);

			if constexpr (sizeof...(rest_sigs) > 0)
			{
				hash = add<rest_sigs...>(hash);
			}

			return hash;
		}
	};

	template<signature... args>
	static inline constexpr auto make_batch(uint32_t hash = signature_hasher::FNV_OFFSET_32)
	{
		constexpr std::array<signature, sizeof...(args)> a1 = {args...};

		constexpr memory::batch<a1.size()> h(a1);

		return batch_and_hash<a1.size()>{h, signature_hasher::add<args...>()};
	}

	struct batch_runner
	{
		inline static std::mutex s_entry_mutex;
		inline static std::vector<std::future<bool>> g_futures;

		template<size_t N>
		inline static bool run(const memory::batch<N> batch, range region)
		{
			for (auto& entry : batch.m_entries)
			{
				g_futures.emplace_back(std::async(&scan_pattern_and_execute_callback, region, entry));
			}

			bool found_all_patterns = true;
			for (auto& future : g_futures)
			{
				future.wait();

				if (!future.get())
					found_all_patterns = false;
			}

			g_futures.clear();

			return found_all_patterns;
		}

		inline static bool scan_pattern_and_execute_callback(range region, signature entry)
		{
			if (auto result = region.scan(entry.m_ida); result.has_value())
			{
				if (entry.m_on_signature_found)
				{
					std::lock_guard<std::mutex> lock(s_entry_mutex); // Acquire a lock on the mutex to synchronize access.

					std::invoke(std::move(entry.m_on_signature_found), result.value());
					LOG(INFO) << "Found '" << entry.m_name << "' GTA5.exe+"
					          << HEX_TO_UPPER(result.value().as<DWORD64>() - region.begin().as<DWORD64>());

					return true;
				}
			}

			LOG(WARNING) << "Failed to find '" << entry.m_name << "'.";

			return false;
		}
	};
}

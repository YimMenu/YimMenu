#pragma once

namespace big
{
	enum class MouseButton : uint8_t
	{
		Left,
		Middle,
		Right
	};

	class cef_helper
	{
	public:
		static inline LARGE_INTEGER qi_freq_;

		static inline uint64_t time_now()
		{
			if (!qi_freq_.HighPart && !qi_freq_.LowPart)
			{
				QueryPerformanceFrequency(&qi_freq_);
			}
			LARGE_INTEGER t = {};
			QueryPerformanceCounter(&t);
			return static_cast<uint64_t>((t.QuadPart / double(qi_freq_.QuadPart)) * 1000000);
		}

		template<class T>
		static std::shared_ptr<T> to_shared_ptr(T* obj)
		{
			return std::shared_ptr<T>(obj, [](T* p) {
				if (p)
					p->Release();
			});
		}
	};
}

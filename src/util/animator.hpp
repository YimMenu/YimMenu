#pragma once

namespace big
{
	class animator
	{
		std::chrono::time_point<std::chrono::system_clock> animation_start_time;
		std::chrono::time_point<std::chrono::system_clock> animation_current_time;
		float animation_curve(float t)
		{
			return 3 * pow(1.f - t, 2.f) * t + 3 * (1.f - t) * pow(t, 2.f) + pow(t, 3.f);
		}

	public:
		void animate(int milliseconds, std::function<void(float&)> cb)
		{
			animation_current_time = std::chrono::system_clock::now();
			float timeDiff = (float)std::chrono::duration_cast<std::chrono::milliseconds>(animation_current_time - animation_start_time)
			                     .count();
			float t = timeDiff / milliseconds;

			if (t > 1)
			{
				t = 1;
			}

			float progress = animation_curve(t);
			cb(progress);
		}

		void reset()
		{
			animation_start_time = std::chrono::system_clock::now();
		}
	};
}
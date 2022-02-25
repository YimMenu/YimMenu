#pragma once
#include "imgui.h"

namespace big
{
	class components
	{
	public:
		static bool nav_button(const char*);
		static bool button(const char*);
		static void title(const char*);
		static void button(const char*, std::function<void()>);
	};
}
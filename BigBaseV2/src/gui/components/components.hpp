#pragma once
#include "imgui.h"

namespace big
{
	class components
	{
		static void custom_text(const char*, ImFont*);
	public:
		static bool nav_button(const char*);
		static bool button(const char*);
		static void small_text(const char*);
		static void sub_title(const char*);
		static void title(const char*);
		static void button(const char*, std::function<void()>);
	};
}
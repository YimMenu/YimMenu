#pragma once
#include "imgui.h"

namespace big
{
	class components
	{
		static void custom_text(const std::string_view, ImFont*);
	public:
		static bool nav_button(const std::string_view);
		static bool button(const std::string_view);
		static void small_text(const std::string_view);
		static void sub_title(const std::string_view);
		static void title(const std::string_view);
		static void button(const std::string_view, std::function<void()>);
	};
}
#pragma once
#include "core/enums.hpp"
#include <imgui.h>

namespace big
{
	inline struct g_context_menu_t
	{
		bool enabled = false;

		uint8_t allowed_entity_types = static_cast<uint8_t>(ContextEntityType::PED) | static_cast<uint8_t>(ContextEntityType::PLAYER) | static_cast<uint8_t>(ContextEntityType::VEHICLE) | static_cast<uint8_t>(ContextEntityType::OBJECT);

		ImU32 selected_option_color = 4278255360;

		bool bounding_box_enabled = true;
		ImU32 bounding_box_color  = 4278255360;

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_context_menu_t, allowed_entity_types, selected_option_color, bounding_box_enabled, bounding_box_color)
	} g_context_menu{};
}
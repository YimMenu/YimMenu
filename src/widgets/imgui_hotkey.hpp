#pragma once
#include <imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui_internal.h>

namespace ImGui
{
	const char* const key_names[] = {"Unknown", "VK_LBUTTON", "VK_RBUTTON", "VK_CANCEL", "VK_MBUTTON", "VK_XBUTTON1", "VK_XBUTTON2", "Unknown", "VK_BACK", "VK_TAB", "Unknown", "Unknown", "VK_CLEAR", "VK_RETURN", "Unknown", "Unknown", "VK_SHIFT", "VK_CONTROL", "VK_MENU", "VK_PAUSE", "VK_CAPITAL", "VK_KANA", "Unknown", "VK_JUNJA", "VK_FINAL", "VK_KANJI", "Unknown", "VK_ESCAPE", "VK_CONVERT", "VK_NONCONVERT", "VK_ACCEPT", "VK_MODECHANGE", "VK_SPACE", "VK_PRIOR", "VK_NEXT", "VK_END", "VK_HOME", "VK_LEFT", "VK_UP", "VK_RIGHT", "VK_DOWN", "VK_SELECT", "VK_PRINT", "VK_EXECUTE", "VK_SNAPSHOT", "VK_INSERT", "VK_DELETE", "VK_HELP", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "VK_LWIN", "VK_RWIN", "VK_APPS", "Unknown", "VK_SLEEP", "VK_NUMPAD0", "VK_NUMPAD1", "VK_NUMPAD2", "VK_NUMPAD3", "VK_NUMPAD4", "VK_NUMPAD5", "VK_NUMPAD6", "VK_NUMPAD7", "VK_NUMPAD8", "VK_NUMPAD9", "VK_MULTIPLY", "VK_ADD", "VK_SEPARATOR", "VK_SUBTRACT", "VK_DECIMAL", "VK_DIVIDE", "VK_F1", "VK_F2", "VK_F3", "VK_F4", "VK_F5", "VK_F6", "VK_F7", "VK_F8", "VK_F9", "VK_F10", "VK_F11", "VK_F12", "VK_F13", "VK_F14", "VK_F15", "VK_F16", "VK_F17", "VK_F18", "VK_F19", "VK_F20", "VK_F21", "VK_F22", "VK_F23", "VK_F24", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "VK_NUMLOCK", "VK_SCROLL", "VK_OEM_NEC_EQUAL", "VK_OEM_FJ_MASSHOU", "VK_OEM_FJ_TOUROKU", "VK_OEM_FJ_LOYA", "VK_OEM_FJ_ROYA", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "VK_LSHIFT", "VK_RSHIFT", "VK_LCONTROL", "VK_RCONTROL", "VK_LMENU", "VK_RMENU"};

	inline bool Hotkey(const char* label, int* k, const ImVec2& size_arg = {})
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g         = *GImGui;
		ImGuiIO& io             = g.IO;
		const ImGuiStyle& style = g.Style;

		const ImGuiID id        = window->GetID(label);
		const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
		ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
		const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
		const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

		ImGui::ItemSize(total_bb, style.FramePadding.y);
		if (!ImGui::ItemAdd(total_bb, id, 0, ImGuiItemFlags_Inputable))
			return false;

		const bool focus_requested = (ImGui::GetItemStatusFlags() & ImGuiItemStatusFlags_FocusedByTabbing) || g.ActiveId == id;
		//const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id, false);
		//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);

		const bool hovered = ImGui::ItemHoverable(frame_bb, id);

		if (hovered)
		{
			ImGui::SetHoveredID(id);
			g.MouseCursor = ImGuiMouseCursor_TextInput;
		}

		const bool user_clicked = hovered && io.MouseClicked[0];

		if (focus_requested || user_clicked)
		{
			if (g.ActiveId != id)
			{
				// Start edition
				memset(io.MouseDown, 0, sizeof(io.MouseDown));
				memset(io.KeysDown, 0, sizeof(io.KeysDown));
				*k = 0;
			}
			ImGui::SetActiveID(id, window);
			ImGui::FocusWindow(window);
		}
		else if (io.MouseClicked[0])
		{
			// Release focus when we click outside
			if (g.ActiveId == id)
				ImGui::ClearActiveID();
		}

		bool value_changed = false;
		int key            = *k;

		if (g.ActiveId == id)
		{
			for (auto i = 0; i < 5; i++)
			{
				if (io.MouseDown[i])
				{
					switch (i)
					{
					case 0: key = VK_LBUTTON; break;
					case 1: key = VK_RBUTTON; break;
					case 2: key = VK_MBUTTON; break;
					case 3: key = VK_XBUTTON1; break;
					case 4: key = VK_XBUTTON2; break;
					}
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
			if (!value_changed)
			{
				for (auto i = VK_BACK; i <= VK_RMENU; i++)
				{
					if (io.KeysDown[i])
					{
						key           = i;
						value_changed = true;
						ImGui::ClearActiveID();
					}
				}
			}

			if (IsKeyPressedMap(ImGuiKey_Escape))
			{
				*k = 0;
				ImGui::ClearActiveID();
			}
			else
			{
				*k = key;
			}
		}

		// Render
		// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

		char buf_display[64] = "None";

		ImGui::RenderFrame(frame_bb.Min,
		    frame_bb.Max,
		    ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)),
		    true,
		    style.FrameRounding);

		if (*k != 0 && g.ActiveId != id)
		{
			strcpy_s(buf_display, key_names[*k]);
		}
		else if (g.ActiveId == id)
		{
			strcpy_s(buf_display, "<Press a key>");
		}

		const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y);// Not using frame_bb.Max because we have adjusted size
		ImVec2 render_pos = frame_bb.Min + style.FramePadding;
		ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding,
		    frame_bb.Max - style.FramePadding,
		    buf_display,
		    NULL,
		    NULL,
		    style.ButtonTextAlign,
		    &clip_rect);
		//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
		//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

		if (label_size.x > 0)
			ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

		return value_changed;
	}
}
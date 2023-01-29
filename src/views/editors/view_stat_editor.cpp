#include "views/view.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "util/local_player.hpp"
#include "util/misc.hpp"

namespace big
{
	static int year, month, day, hour, minute, second, millisecond;

	static char stat_int_read_result[256] = {};
	static char stat_int_text[256] = {};
	static char stat_int_value[256] = {};

	static char stat_bool_read_result[256] = {};
	static char stat_bool_text[256] = {};
	static char stat_bool_value[256] = {};

	static char stat_float_read_result[256] = {};
	static char stat_float_text[256] = {};
	static char stat_float_value[256] = {};

	static char stat_increment_text[256] = {};
	static char stat_increment_value[256] = {};

	static char stat_date_read_result[256] = {};
	static char stat_date_text[256] = {};
	static char stat_date_value[256] = {};

	static char stat_string_read_result[256] = {};
	static char stat_string_text[256] = {};
	static char stat_string_value[256] = {};

	static char stat_label_text[256] = {};
	static char stat_label_value[256] = {};

	static char stat_user_id_read_result[256] = {};
	static char stat_user_id_text[256] = {};
	static char stat_user_id_value[256] = {};

	static char packed_stat_int_read_result[256] = {};
	static char packed_stat_int_text[256] = {};
	static char packed_stat_int_value[256] = {};

	static char packed_stat_bool_read_result[256] = {};
	static char packed_stat_bool_text[256] = {};
	static char packed_stat_bool_value[256] = {};

	static void tab_item_stat()
	{
		if (ImGui::BeginTabItem("Stat"))
		{
			ImGui::Text("Stat: prefix with $ for string ($MPX_CHAR_SET_RP_GIFT_ADMIN)");

			enum Mode
			{
				INT,
				BOOLEAN,
				FLOAT,
				INCREMENT,
				DATE,
				STRING,
				LABEL,
				USER_ID,
				IMPORT
			};

			ImGui::RadioButton("Int", &g.stat_editor.stat.radio_button_index, INT); ImGui::SameLine();
			ImGui::RadioButton("Bool", &g.stat_editor.stat.radio_button_index, BOOLEAN); ImGui::SameLine();
			ImGui::RadioButton("Float", &g.stat_editor.stat.radio_button_index, FLOAT); ImGui::SameLine();
			ImGui::RadioButton("Increment", &g.stat_editor.stat.radio_button_index, INCREMENT); ImGui::SameLine();
			ImGui::RadioButton("Date", &g.stat_editor.stat.radio_button_index, DATE); ImGui::SameLine();
			ImGui::RadioButton("String", &g.stat_editor.stat.radio_button_index, STRING); ImGui::SameLine();
			ImGui::RadioButton("Label", &g.stat_editor.stat.radio_button_index, LABEL); ImGui::SameLine();
			ImGui::RadioButton("User Id", &g.stat_editor.stat.radio_button_index, USER_ID); ImGui::SameLine();
			ImGui::RadioButton("Import", &g.stat_editor.stat.radio_button_index, IMPORT);

			switch (g.stat_editor.stat.radio_button_index)
			{
			case INT:
			{
				components::input_text("Stat", stat_int_text, sizeof(stat_int_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.int_text = stat_int_text; });
				components::input_text("Value", stat_int_value, sizeof(stat_int_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.int_value = stat_int_value; });
				components::button("Apply", [] { local_player::stat_set_int(stat_int_text, stat_int_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.int_read);
				components::input_text("##read_result", stat_int_read_result, sizeof(stat_int_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case BOOLEAN:
			{
				components::input_text("Stat", stat_bool_text, sizeof(stat_bool_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.bool_text = stat_bool_text; });
				components::input_text("Value", stat_bool_value, sizeof(stat_bool_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.bool_value = stat_bool_value; });
				components::button("Apply", [] { local_player::stat_set_bool(stat_bool_text, stat_bool_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.bool_read);
				components::input_text("##read_result", stat_bool_read_result, sizeof(stat_bool_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case FLOAT:
			{
				components::input_text("Stat", stat_float_text, sizeof(stat_float_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.float_text = stat_float_text; });
				components::input_text("Value", stat_float_value, sizeof(stat_float_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.float_value = stat_float_value; });
				components::button("Apply", [] { local_player::stat_set_float(stat_float_text, stat_float_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.float_read);
				components::input_text("##read_result", stat_float_read_result, sizeof(stat_float_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case INCREMENT:
			{
				components::input_text("Stat", stat_increment_text, sizeof(stat_increment_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.increment_text = stat_increment_text; });
				components::input_text("Value", stat_increment_value, sizeof(stat_increment_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.increment_value = stat_increment_value; });	
				components::button("Apply", [] { local_player::stat_increment(stat_increment_text, stat_increment_value); }); ImGui::SameLine();
				ImGui::SameLine();
				ImGui::Checkbox("Loop Write", &g.stat_editor.stat.increment_loop_write);
			}
				break;
			case DATE:
			{
				components::input_text("Stat", stat_date_text, sizeof(stat_date_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.date_text = stat_date_text; });
				components::input_text("Value", stat_date_value, sizeof(stat_date_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.date_value = stat_date_value; });
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("year month day hour minute second millisecond\nexample: 2022 1 17 21 34 55");
				components::button("Apply", [] { local_player::stat_set_date(stat_date_text, stat_date_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.date_read);
				components::input_text("##read_result", stat_date_read_result, sizeof(stat_date_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case STRING:
			{
				components::input_text("Stat", stat_string_text, sizeof(stat_string_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.string_text = stat_string_text; });
				components::input_text("Value", stat_string_value, sizeof(stat_string_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.string_value = stat_string_value; });
				components::button("Apply", [] { local_player::stat_set_string(stat_string_text, stat_string_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.string_read);
				components::input_text("##read_result", stat_string_read_result, sizeof(stat_string_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case LABEL:
			{
				components::input_text("Stat", stat_label_text, sizeof(stat_label_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.label_text = stat_label_text; });
				components::input_text("Value", stat_label_value, sizeof(stat_label_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.label_value = stat_label_value; });
				components::button("Apply", [] { local_player::stat_set_label(stat_label_text, stat_label_value); }); ImGui::SameLine();
			}
				break;
			case USER_ID:
			{
				components::input_text("Stat", stat_user_id_text, sizeof(stat_user_id_text), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.user_id_text = stat_user_id_text; });
				components::input_text("Value", stat_user_id_value, sizeof(stat_user_id_value), ImGuiInputTextFlags_None, [] { g.stat_editor.stat.user_id_value = stat_user_id_value; });
				components::button("Apply", [] { local_player::stat_set_user_id(stat_user_id_text, stat_user_id_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.user_id_read);
				components::input_text("##read_result", stat_user_id_read_result, sizeof(stat_user_id_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case IMPORT:
			{
				ImGui::Text("0:Int\n1:Bool\n2:Float\n3:Increment\n4:Date\n5:String\n6:Label\n7:User Id");
				ImGui::Text("Example:\n$MPX_CHAR_NAME\n5:name\n$MPX_DEFAULT_STATS_SET\n1:0");
				components::button("Import From Clipboard", []
				{
					std::string clipboard_text = ImGui::GetClipboardText();
					std::vector<std::string> lines = misc::split(clipboard_text, '\n');
					if (!lines.size() || lines.size() % 2)
						return;
					for (size_t i = 0; i < lines.size(); i += 2)
					{
						if (lines[i + 1] == "")
							continue;
						std::vector<std::string> strs = misc::split(lines[i + 1], ':');
						if (strs.size() == 1)
							strs.push_back(""); //In case the string is to set a ""
						int type = misc::get_text_value<int>(strs[0]);
						switch (type)
						{
						case INT:
							local_player::stat_set_int(lines[i], strs[1]);
							break;
						case BOOLEAN:
							local_player::stat_set_bool(lines[i], strs[1]);
							break;
						case FLOAT:
							local_player::stat_set_float(lines[i], strs[1]);
							break;
						case INCREMENT:
							local_player::stat_increment(lines[i], strs[1]);
							break;
						case DATE:
							local_player::stat_set_date(lines[i], strs[1]);
							break;
						case STRING:
							local_player::stat_set_string(lines[i], strs[1]);
							break;
						case LABEL:
							local_player::stat_set_label(lines[i], strs[1]);
							break;
						case USER_ID:
							local_player::stat_set_user_id(lines[i], strs[1]);
							break;
						default:
							break;
						}
					}
				});
			}
				break;
			default:
				break;
			}

			ImGui::EndTabItem();
		}
	}

	static void tab_item_packed_stat()
	{
		if (ImGui::BeginTabItem("Packed Stat"))
		{
			ImGui::Text("Index: enter two numbers to represent a range (31786 32786)");

			enum Mode
			{
				INT,
				BOOLEAN,
				IMPORT
			};

			ImGui::RadioButton("Int", &g.stat_editor.packed_stat.radio_button_index, INT); ImGui::SameLine();
			ImGui::RadioButton("Bool", &g.stat_editor.packed_stat.radio_button_index, BOOLEAN); ImGui::SameLine();
			ImGui::RadioButton("Import", &g.stat_editor.packed_stat.radio_button_index, IMPORT);

			switch (g.stat_editor.packed_stat.radio_button_index)
			{
			case INT:
			{
				components::input_text("Index", packed_stat_int_text, sizeof(packed_stat_int_text), ImGuiInputTextFlags_None, [] { g.stat_editor.packed_stat.int_text = packed_stat_int_text; });
				components::input_text("Value", packed_stat_int_value, sizeof(packed_stat_int_value), ImGuiInputTextFlags_None, [] { g.stat_editor.packed_stat.int_value = packed_stat_int_value; });
				components::button("Apply", [] { local_player::packed_stat_set_int(packed_stat_int_text, packed_stat_int_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.packed_stat.int_read);
				components::input_text("##read_result", packed_stat_int_read_result, sizeof(packed_stat_int_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case BOOLEAN:
			{
				components::input_text("Index", packed_stat_bool_text, sizeof(packed_stat_bool_text), ImGuiInputTextFlags_None, [] { g.stat_editor.packed_stat.bool_text = packed_stat_bool_text; });
				components::input_text("Value", packed_stat_bool_value, sizeof(packed_stat_bool_value), ImGuiInputTextFlags_None, [] { g.stat_editor.packed_stat.bool_value = packed_stat_bool_value; });
				components::button("Apply", [] { local_player::packed_stat_set_bool(packed_stat_bool_text, packed_stat_bool_value); }); ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.packed_stat.bool_read);
				components::input_text("##read_result", packed_stat_bool_read_result, sizeof(packed_stat_bool_read_result), ImGuiInputTextFlags_ReadOnly);
			}
				break;
			case IMPORT:
			{
				ImGui::Text("0:Int\n1:Bool");
				ImGui::Text("Example:\n31786\n0:123\n31786 32786\n1:1");
				components::button("Import From Clipboard", []
				{
					std::string clipboard_text = ImGui::GetClipboardText();
					std::vector<std::string> lines = misc::split(clipboard_text, '\n');
					if (!lines.size() || lines.size() % 2)
						return;
					for (size_t i = 0; i < lines.size(); i += 2)
					{
						if (lines[i + 1] == "")
							continue;
						std::vector<std::string> strs = misc::split(lines[i + 1], ':');
						if (strs.size() == 1)
							continue;
						int type = misc::get_text_value<int>(strs[0]);
						switch (type)
						{
						case INT:
							local_player::packed_stat_set_int(lines[i], strs[1]);
							break;
						case BOOLEAN:
							local_player::packed_stat_set_bool(lines[i], strs[1]);
							break;
						default:
							break;
						}
					}
				});
			}
				break;
			default:
				break;
			}

			ImGui::EndTabItem();
		}
	}

	void view::stat_editor()
	{
		static bool init = ([]()
		{
			strcpy_s(stat_int_text, sizeof(stat_int_text), g.stat_editor.stat.int_text.c_str());
			strcpy_s(stat_int_value, sizeof(stat_int_value), g.stat_editor.stat.int_value.c_str());
			strcpy_s(stat_bool_text, sizeof(stat_bool_text), g.stat_editor.stat.bool_text.c_str());
			strcpy_s(stat_bool_value, sizeof(stat_bool_value), g.stat_editor.stat.bool_value.c_str());
			strcpy_s(stat_float_text, sizeof(stat_float_text), g.stat_editor.stat.float_text.c_str());
			strcpy_s(stat_float_value, sizeof(stat_float_value), g.stat_editor.stat.float_value.c_str());
			strcpy_s(stat_increment_text, sizeof(stat_increment_text), g.stat_editor.stat.increment_text.c_str());
			strcpy_s(stat_increment_value, sizeof(stat_increment_value), g.stat_editor.stat.increment_value.c_str());
			strcpy_s(stat_date_text, sizeof(stat_date_text), g.stat_editor.stat.date_text.c_str());
			strcpy_s(stat_date_value, sizeof(stat_date_value), g.stat_editor.stat.date_value.c_str());
			strcpy_s(stat_string_text, sizeof(stat_string_text), g.stat_editor.stat.string_text.c_str());
			strcpy_s(stat_string_value, sizeof(stat_string_value), g.stat_editor.stat.string_value.c_str());
			strcpy_s(stat_label_text, sizeof(stat_label_text), g.stat_editor.stat.label_text.c_str());
			strcpy_s(stat_label_value, sizeof(stat_label_value), g.stat_editor.stat.label_value.c_str());
			strcpy_s(stat_user_id_text, sizeof(stat_user_id_text), g.stat_editor.stat.user_id_text.c_str());
			strcpy_s(stat_user_id_value, sizeof(stat_user_id_value), g.stat_editor.stat.user_id_value.c_str());

			strcpy_s(packed_stat_int_text, sizeof(packed_stat_int_text), g.stat_editor.packed_stat.int_text.c_str());
			strcpy_s(packed_stat_int_value, sizeof(packed_stat_int_value), g.stat_editor.packed_stat.int_value.c_str());
			strcpy_s(packed_stat_bool_text, sizeof(packed_stat_bool_text), g.stat_editor.packed_stat.bool_text.c_str());
			strcpy_s(packed_stat_bool_value, sizeof(packed_stat_bool_value), g.stat_editor.packed_stat.bool_value.c_str());
		}(), true);

		g_fiber_pool->queue_job([] 
		{
			STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), &g.player.character_slot, -1);
			CLOCK::GET_POSIX_TIME(&year, &month, &day, &hour, &minute, &second);
			if (g.stat_editor.stat.int_read)
				strcpy_s(stat_int_read_result, sizeof(stat_int_read_result), std::to_string(local_player::stat_get_int(stat_int_text)).c_str());
			if (g.stat_editor.stat.bool_read)
				strcpy_s(stat_bool_read_result, sizeof(stat_bool_read_result), std::to_string(local_player::stat_get_bool(stat_bool_text)).c_str());
			if (g.stat_editor.stat.float_read)
				strcpy_s(stat_float_read_result, sizeof(stat_float_read_result), std::to_string(local_player::stat_get_float(stat_float_text)).c_str());
			if (g.stat_editor.stat.increment_loop_write)
				local_player::stat_increment(stat_increment_text, stat_increment_value);
			if (g.stat_editor.stat.date_read)
				strcpy_s(stat_date_read_result, sizeof(stat_date_read_result), local_player::stat_get_date(stat_date_text).c_str());
			if (g.stat_editor.stat.string_read)
				strcpy_s(stat_string_read_result, sizeof(stat_string_read_result), local_player::stat_get_string(stat_string_text).c_str());
			if (g.stat_editor.stat.user_id_read)
				strcpy_s(stat_user_id_read_result, sizeof(stat_user_id_read_result), local_player::stat_get_user_id(stat_user_id_text).c_str());
			if(g.stat_editor.packed_stat.int_read)
				strcpy_s(packed_stat_int_read_result, sizeof(packed_stat_int_read_result), std::to_string(local_player::packed_stat_get_int(packed_stat_int_text)).c_str());
			if (g.stat_editor.packed_stat.bool_read)
				strcpy_s(packed_stat_bool_read_result, sizeof(packed_stat_bool_read_result), std::to_string(local_player::packed_stat_get_bool(packed_stat_bool_text)).c_str());
		});

		components::sub_title(std::format("Posix Time: {}-{}-{} {}:{}:{}", year, month, day, hour, minute, second));
		components::sub_title(std::format("Character Index: {}", g.player.character_slot));
		components::sub_title("Be aware of stat limits, use with caution, modifying some stats are risky.");

		if (ImGui::BeginTabBar("##stat_editor_tab_bar"))
		{
			tab_item_stat();
			tab_item_packed_stat();
			ImGui::EndTabBar();
		}
	}
}
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "views/view.hpp"

namespace big::helper
{
	static void stat_set_int(std::string stat, std::string value);
	static void stat_set_bool(std::string stat, std::string value);
	static void stat_set_float(std::string stat, std::string value);
	static void stat_increment(std::string stat, std::string value);
	static void stat_set_date(std::string stat, std::string value);
	static void stat_set_string(std::string stat, std::string value);
	static void stat_set_label(std::string stat, std::string value);
	static void stat_set_user_id(std::string stat, std::string value);
	static std::string stat_get_int(std::string stat);
	static std::string stat_get_bool(std::string stat);
	static std::string stat_get_float(std::string stat);
	static std::string stat_get_date(std::string stat);
	static std::string stat_get_string(std::string stat);
	static std::string stat_get_user_id(std::string stat);

	static void packed_stat_set_int(std::string index, std::string value);
	static void packed_stat_set_bool(std::string index, std::string value);
	static std::string packed_stat_get_int(std::string index);
	static std::string packed_stat_get_bool(std::string index);
}

namespace big
{
	static int character_index = 0;
	static int year, month, day, hour, minute, second, millisecond;

	static char stat_int_read_result[256] = {};
	static char stat_int_text[256]        = {};
	static char stat_int_value[256]       = {};

	static char stat_bool_read_result[256] = {};
	static char stat_bool_text[256]        = {};
	static char stat_bool_value[256]       = {};

	static char stat_float_read_result[256] = {};
	static char stat_float_text[256]        = {};
	static char stat_float_value[256]       = {};

	static char stat_increment_text[256]  = {};
	static char stat_increment_value[256] = {};

	static char stat_date_read_result[256] = {};
	static char stat_date_text[256]        = {};
	static char stat_date_value[256]       = {};

	static char stat_string_read_result[256] = {};
	static char stat_string_text[256]        = {};
	static char stat_string_value[256]       = {};

	static char stat_label_text[256]  = {};
	static char stat_label_value[256] = {};

	static char stat_user_id_read_result[256] = {};
	static char stat_user_id_text[256]        = {};
	static char stat_user_id_value[256]       = {};

	static char packed_stat_int_read_result[256] = {};
	static char packed_stat_int_text[256]        = {};
	static char packed_stat_int_value[256]       = {};

	static char packed_stat_bool_read_result[256] = {};
	static char packed_stat_bool_text[256]        = {};
	static char packed_stat_bool_value[256]       = {};

	template<typename T>
	static std::enable_if_t<std::is_same_v<T, std::string>, T> get_text_value(std::string text)
	{
		return text;
	}

	template<typename T>
	static std::enable_if_t<!std::is_same_v<T, std::string>, T> get_text_value(std::string text)
	{
		T value = (T)0;
		std::stringstream(text) >> value;
		return value;
	}

	template<typename T = std::string>
	static std::vector<T> split(std::string text, const char delim)
	{
		std::vector<T> result;
		std::string str;
		std::stringstream ss(text);
		while (std::getline(ss, str, delim))
			result.push_back(get_text_value<T>(str));
		return result;
	}

	static Hash get_text_stat_hash(std::string text)
	{
		std::transform(text.begin(), text.end(), text.begin(), ::tolower);
		if (text[0] == '$')
		{
			auto substr = text.substr(1);
			if (substr.substr(0, 3) == "mpx")
				substr[2] = character_index + '0';
			return rage::joaat(substr);
		}
		return get_text_value<Hash>(text);
	}

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

			ImGui::RadioButton("Int", &g.stat_editor.stat.radio_button_index, INT);
			ImGui::SameLine();
			ImGui::RadioButton("Bool", &g.stat_editor.stat.radio_button_index, BOOLEAN);
			ImGui::SameLine();
			ImGui::RadioButton("Float", &g.stat_editor.stat.radio_button_index, FLOAT);
			ImGui::SameLine();
			ImGui::RadioButton("Increment", &g.stat_editor.stat.radio_button_index, INCREMENT);
			ImGui::SameLine();
			ImGui::RadioButton("Date", &g.stat_editor.stat.radio_button_index, DATE);
			ImGui::SameLine();
			ImGui::RadioButton("String", &g.stat_editor.stat.radio_button_index, STRING);
			ImGui::SameLine();
			ImGui::RadioButton("Label", &g.stat_editor.stat.radio_button_index, LABEL);
			ImGui::SameLine();
			ImGui::RadioButton("User Id", &g.stat_editor.stat.radio_button_index, USER_ID);
			ImGui::SameLine();
			ImGui::RadioButton("Import", &g.stat_editor.stat.radio_button_index, IMPORT);

			switch (g.stat_editor.stat.radio_button_index)
			{
			case INT:
			{
				components::input_text("Stat", stat_int_text, sizeof(stat_int_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.int_text = stat_int_text;
				});
				components::input_text("Value", stat_int_value, sizeof(stat_int_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.int_value = stat_int_value;
				});
				components::button("Apply", [] {
					helper::stat_set_int(stat_int_text, stat_int_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.int_read);
				components::input_text("##read_result", stat_int_read_result, sizeof(stat_int_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case BOOLEAN:
			{
				components::input_text("Stat", stat_bool_text, sizeof(stat_bool_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.bool_text = stat_bool_text;
				});
				components::input_text("Value", stat_bool_value, sizeof(stat_bool_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.bool_value = stat_bool_value;
				});
				components::button("Apply", [] {
					helper::stat_set_bool(stat_bool_text, stat_bool_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.bool_read);
				components::input_text("##read_result", stat_bool_read_result, sizeof(stat_bool_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case FLOAT:
			{
				components::input_text("Stat", stat_float_text, sizeof(stat_float_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.float_text = stat_float_text;
				});
				components::input_text("Value", stat_float_value, sizeof(stat_float_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.float_value = stat_float_value;
				});
				components::button("Apply", [] {
					helper::stat_set_float(stat_float_text, stat_float_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.float_read);
				components::input_text("##read_result", stat_float_read_result, sizeof(stat_float_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case INCREMENT:
			{
				components::input_text("Stat", stat_increment_text, sizeof(stat_increment_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.increment_text = stat_increment_text;
				});
				components::input_text("Value", stat_increment_value, sizeof(stat_increment_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.increment_value = stat_increment_value;
				});
				components::button("Apply", [] {
					helper::stat_increment(stat_increment_text, stat_increment_value);
				});
				ImGui::SameLine();
				ImGui::SameLine();
				ImGui::Checkbox("Loop Write", &g.stat_editor.stat.increment_loop_write);
			}
			break;
			case DATE:
			{
				components::input_text("Stat", stat_date_text, sizeof(stat_date_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.date_text = stat_date_text;
				});
				components::input_text("Value", stat_date_value, sizeof(stat_date_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.date_value = stat_date_value;
				});
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("year month day hour minute second millisecond\nexample: 2022 1 17 21 34 55");
				components::button("Apply", [] {
					helper::stat_set_date(stat_date_text, stat_date_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.date_read);
				components::input_text("##read_result", stat_date_read_result, sizeof(stat_date_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case STRING:
			{
				components::input_text("Stat", stat_string_text, sizeof(stat_string_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.string_text = stat_string_text;
				});
				components::input_text("Value", stat_string_value, sizeof(stat_string_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.string_value = stat_string_value;
				});
				components::button("Apply", [] {
					helper::stat_set_string(stat_string_text, stat_string_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.string_read);
				components::input_text("##read_result", stat_string_read_result, sizeof(stat_string_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case LABEL:
			{
				components::input_text("Stat", stat_label_text, sizeof(stat_label_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.label_text = stat_label_text;
				});
				components::input_text("Value", stat_label_value, sizeof(stat_label_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.label_value = stat_label_value;
				});
				components::button("Apply", [] {
					helper::stat_set_label(stat_label_text, stat_label_value);
				});
				ImGui::SameLine();
			}
			break;
			case USER_ID:
			{
				components::input_text("Stat", stat_user_id_text, sizeof(stat_user_id_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.user_id_text = stat_user_id_text;
				});
				components::input_text("Value", stat_user_id_value, sizeof(stat_user_id_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.stat.user_id_value = stat_user_id_value;
				});
				components::button("Apply", [] {
					helper::stat_set_user_id(stat_user_id_text, stat_user_id_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.stat.user_id_read);
				components::input_text("##read_result", stat_user_id_read_result, sizeof(stat_user_id_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case IMPORT:
			{
				ImGui::Text("0:Int\n1:Bool\n2:Float\n3:Increment\n4:Date\n5:String\n6:Label\n7:User Id");
				ImGui::Text("Example:\n$MPX_CHAR_NAME\n5:name\n$MPX_DEFAULT_STATS_SET\n1:0");
				components::button("Import From Clipboard", [] {
					std::string clipboard_text     = ImGui::GetClipboardText();
					std::vector<std::string> lines = split(clipboard_text, '\n');
					if (!lines.size() || lines.size() % 2)
						return;
					for (size_t i = 0; i < lines.size(); i += 2)
					{
						if (lines[i + 1] == "")
							continue;
						std::vector<std::string> strs = split(lines[i + 1], ':');
						if (strs.size() == 1)
							strs.push_back("");//In case the string is to set a ""
						int type = get_text_value<int>(strs[0]);
						switch (type)
						{
						case INT: helper::stat_set_int(lines[i], strs[1]); break;
						case BOOLEAN: helper::stat_set_bool(lines[i], strs[1]); break;
						case FLOAT: helper::stat_set_float(lines[i], strs[1]); break;
						case INCREMENT: helper::stat_increment(lines[i], strs[1]); break;
						case DATE: helper::stat_set_date(lines[i], strs[1]); break;
						case STRING: helper::stat_set_string(lines[i], strs[1]); break;
						case LABEL: helper::stat_set_label(lines[i], strs[1]); break;
						case USER_ID: helper::stat_set_user_id(lines[i], strs[1]); break;
						default: break;
						}
					}
				});
			}
			break;
			default: break;
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

			ImGui::RadioButton("Int", &g.stat_editor.packed_stat.radio_button_index, INT);
			ImGui::SameLine();
			ImGui::RadioButton("Bool", &g.stat_editor.packed_stat.radio_button_index, BOOLEAN);
			ImGui::SameLine();
			ImGui::RadioButton("Import", &g.stat_editor.packed_stat.radio_button_index, IMPORT);

			switch (g.stat_editor.packed_stat.radio_button_index)
			{
			case INT:
			{
				components::input_text("Index", packed_stat_int_text, sizeof(packed_stat_int_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.packed_stat.int_text = packed_stat_int_text;
				});
				components::input_text("Value", packed_stat_int_value, sizeof(packed_stat_int_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.packed_stat.int_value = packed_stat_int_value;
				});
				components::button("Apply", [] {
					helper::packed_stat_set_int(packed_stat_int_text, packed_stat_int_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.packed_stat.int_read);
				components::input_text("##read_result", packed_stat_int_read_result, sizeof(packed_stat_int_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case BOOLEAN:
			{
				components::input_text("Index", packed_stat_bool_text, sizeof(packed_stat_bool_text), ImGuiInputTextFlags_None, [] {
					g.stat_editor.packed_stat.bool_text = packed_stat_bool_text;
				});
				components::input_text("Value", packed_stat_bool_value, sizeof(packed_stat_bool_value), ImGuiInputTextFlags_None, [] {
					g.stat_editor.packed_stat.bool_value = packed_stat_bool_value;
				});
				components::button("Apply", [] {
					helper::packed_stat_set_bool(packed_stat_bool_text, packed_stat_bool_value);
				});
				ImGui::SameLine();
				ImGui::Checkbox("Read", &g.stat_editor.packed_stat.bool_read);
				components::input_text("##read_result", packed_stat_bool_read_result, sizeof(packed_stat_bool_read_result), ImGuiInputTextFlags_ReadOnly);
			}
			break;
			case IMPORT:
			{
				ImGui::Text("0:Int\n1:Bool");
				ImGui::Text("Example:\n31786\n0:123\n31786 32786\n1:1");
				components::button("Import From Clipboard", [] {
					std::string clipboard_text     = ImGui::GetClipboardText();
					std::vector<std::string> lines = split(clipboard_text, '\n');
					if (!lines.size() || lines.size() % 2)
						return;
					for (size_t i = 0; i < lines.size(); i += 2)
					{
						if (lines[i + 1] == "")
							continue;
						std::vector<std::string> strs = split(lines[i + 1], ':');
						if (strs.size() == 1)
							continue;
						int type = get_text_value<int>(strs[0]);
						switch (type)
						{
						case INT: helper::packed_stat_set_int(lines[i], strs[1]); break;
						case BOOLEAN: helper::packed_stat_set_bool(lines[i], strs[1]); break;
						default: break;
						}
					}
				});
			}
			break;
			default: break;
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

		g_fiber_pool->queue_job([] {
			STATS::STAT_GET_INT(RAGE_JOAAT("MPPLY_LAST_MP_CHAR"), &character_index, -1);
			CLOCK::GET_POSIX_TIME(&year, &month, &day, &hour, &minute, &second);
			if (g.stat_editor.stat.int_read)
				strcpy_s(stat_int_read_result, sizeof(stat_int_read_result), helper::stat_get_int(stat_int_text).c_str());
			if (g.stat_editor.stat.bool_read)
				strcpy_s(stat_bool_read_result, sizeof(stat_bool_read_result), helper::stat_get_bool(stat_bool_text).c_str());
			if (g.stat_editor.stat.float_read)
				strcpy_s(stat_float_read_result, sizeof(stat_float_read_result), helper::stat_get_float(stat_float_text).c_str());
			if (g.stat_editor.stat.increment_loop_write)
				helper::stat_increment(stat_increment_text, stat_increment_value);
			if (g.stat_editor.stat.date_read)
				strcpy_s(stat_date_read_result, sizeof(stat_date_read_result), helper::stat_get_date(stat_date_text).c_str());
			if (g.stat_editor.stat.string_read)
				strcpy_s(stat_string_read_result,
				    sizeof(stat_string_read_result),
				    helper::stat_get_string(stat_string_text).c_str());
			if (g.stat_editor.stat.user_id_read)
				strcpy_s(stat_user_id_read_result,
				    sizeof(stat_user_id_read_result),
				    helper::stat_get_user_id(stat_user_id_text).c_str());
			if (g.stat_editor.packed_stat.int_read)
				strcpy_s(packed_stat_int_read_result,
				    sizeof(packed_stat_int_read_result),
				    helper::packed_stat_get_int(packed_stat_int_text).c_str());
			if (g.stat_editor.packed_stat.bool_read)
				strcpy_s(packed_stat_bool_read_result,
				    sizeof(packed_stat_bool_read_result),
				    helper::packed_stat_get_bool(packed_stat_bool_text).c_str());
		});

		components::sub_title(std::format("Posix Time: {}-{}-{} {}:{}:{}", year, month, day, hour, minute, second));
		components::sub_title(std::format("Character Index: {}", character_index));
		components::sub_title("Be aware of stat limits, use with caution, modifying some stats are risky.");

		if (ImGui::BeginTabBar("##stat_editor_tab_bar"))
		{
			tab_item_stat();
			tab_item_packed_stat();
			ImGui::EndTabBar();
		}
	}
}

namespace big::helper
{
	void stat_set_int(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_INT(get_text_stat_hash(stat), get_text_value<int>(value), TRUE);
	}

	void stat_set_bool(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_BOOL(get_text_stat_hash(stat), get_text_value<bool>(value), TRUE);
	}

	void stat_set_float(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_SET_FLOAT(get_text_stat_hash(stat), get_text_value<float>(value), TRUE);
	}

	void stat_increment(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		STATS::STAT_INCREMENT(get_text_stat_hash(stat), get_text_value<float>(value));
	}

	void stat_set_date(std::string stat, std::string value)
	{
		if (stat == "" || value == "")
			return;
		std::vector<int64_t> strs = split<int64_t>(value, ' ');
		int64_t dates[7]{};
		STATS::STAT_GET_DATE(get_text_stat_hash(stat), (Any*)dates, 7, -1);
		while (strs.size() < 7)//Writing will succeed only when size is greater than or equal to 7
			strs.push_back(dates[strs.size()]);
		STATS::STAT_SET_DATE(get_text_stat_hash(stat), (Any*)strs.data(), strs.size(), TRUE);
	}

	void stat_set_string(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_STRING(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	void stat_set_label(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_GXT_LABEL(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	void stat_set_user_id(std::string stat, std::string value)
	{
		if (stat == "")
			return;
		STATS::STAT_SET_USER_ID(get_text_stat_hash(stat), value.c_str(), TRUE);
	}

	std::string stat_get_int(std::string stat)
	{
		int result = 0;
		if (stat != "")
			STATS::STAT_GET_INT(get_text_stat_hash(stat), &result, -1);
		return std::to_string(result);
	}

	std::string stat_get_bool(std::string stat)
	{
		int result = 0;
		if (stat != "")
			STATS::STAT_GET_BOOL(get_text_stat_hash(stat), &result, -1);
		return std::to_string(result);
	}

	std::string stat_get_float(std::string stat)
	{
		float result = 0;
		if (stat != "")
			STATS::STAT_GET_FLOAT(get_text_stat_hash(stat), &result, -1);
		return std::to_string(result);
	}

	std::string stat_get_date(std::string stat)
	{
		int64_t result[7]{};
		if (stat != "")
			STATS::STAT_GET_DATE(get_text_stat_hash(stat), (Any*)&result, 7, -1);
		return std::format("{} {} {} {} {} {} {}", result[0], result[1], result[2], result[3], result[4], result[5], result[6]);
	}

	std::string stat_get_string(std::string stat)
	{
		std::string result = "";
		if (stat != "")
			result = STATS::STAT_GET_STRING(get_text_stat_hash(stat), -1);
		return result;
	}

	std::string stat_get_user_id(std::string stat)
	{
		std::string result = "";
		if (stat != "")
			result = STATS::STAT_GET_USER_ID(get_text_stat_hash(stat));
		return result;
	}

	void packed_stat_set_int(std::string index, std::string value)
	{
		if (index == "" || value == "")
			return;
		std::vector<int> index_v = split<int>(index, ' ');
		int index_min            = index_v[0];
		int index_max            = index_min;
		if (index_v.size() >= 2)
			index_max = index_v[1];
		int value_n = get_text_value<int>(value);
		for (int i = index_min; i <= index_max; i++)
			STATS::SET_PACKED_STAT_INT_CODE(i, value_n, character_index);
	}

	void packed_stat_set_bool(std::string index, std::string value)
	{
		if (index == "" || value == "")
			return;
		std::vector<int> index_v = split<int>(index, ' ');
		int index_min            = index_v[0];
		int index_max            = index_min;
		if (index_v.size() >= 2)
			index_max = index_v[1];
		int value_b = get_text_value<bool>(value);
		for (int i = index_min; i <= index_max; i++)
			STATS::SET_PACKED_STAT_BOOL_CODE(i, value_b, character_index);
	}

	std::string packed_stat_get_int(std::string index)
	{
		int result = 0;
		std::string str;
		std::stringstream ss(index);
		std::getline(ss, str, ' ');
		if (str != "")
			result = STATS::GET_PACKED_STAT_INT_CODE(get_text_value<int>(str), character_index);
		return std::to_string(result);
	}

	std::string packed_stat_get_bool(std::string index)
	{
		int result = 0;
		std::string str;
		std::stringstream ss(index);
		std::getline(ss, str, ' ');
		if (str != "")
			result = STATS::GET_PACKED_STAT_BOOL_CODE(get_text_value<int>(str), character_index);
		return std::to_string(result);
	}
}
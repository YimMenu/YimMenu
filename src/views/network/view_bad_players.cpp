#include "pointers.hpp"
#include "services/bad_players/bad_players.hpp"
#include "services/notifications/notification_service.hpp"
#include "thread_pool.hpp"
#include "util/strings.hpp"
#include "views/view.hpp"

inline std::map<uint64_t, bad_players_nm::bad_player> filter_bad_players(const std::map<uint64_t, bad_players_nm::bad_player>& inputMap, const std::string& searchString)
{
	std::map<uint64_t, bad_players_nm::bad_player> filteredMap;
	std::string lowercaseSearchString = toLowercase(searchString);
	for (auto pair : inputMap)
		if (std::string lowercaseStr = toLowercase(pair.second.name); lowercaseStr.find(lowercaseSearchString) != std::string::npos)
			filteredMap[pair.first] = pair.second;
	return filteredMap;
}

namespace big
{
	void view::bad_players()
	{
		static char player_name[64];
		static uint64_t selected_id, rockstar_id;
		static std::string search_blocked_player_name;
		static bool save_as_spammer;
		static std::map<uint64_t, bad_players_nm::bad_player> searched_blocked_players;

		ImGui::PushItemWidth(300);
		components::input_text("Player Name", player_name, sizeof(player_name));

		ImGui::InputScalar("Rockstar Id", ImGuiDataType_U64, &rockstar_id);
		ImGui::PopItemWidth();

		ImGui::Checkbox("Save as spammer", &save_as_spammer);

		ImGui::Spacing();

		if (components::button("Add to block list"))
		{
			std::string name = player_name;
			if (trimString(name).length() && rockstar_id)
				g_thread_pool->push([] {
					bad_players_nm::add_player({player_name, rockstar_id, true, save_as_spammer});
					save_as_spammer = false;
					strcpy(player_name, "");
					rockstar_id = 0;
				});
			else
				g_notification_service->push_error("New Player Entry", "Player Name or Rockstar Id is missing.");
		}

		ImGui::Spacing();

		ImGui::SetNextItemWidth(300);
		if (components::input_text_with_hint("###searched_blocked_players", "search blocked player", search_blocked_player_name))
			searched_blocked_players.clear();

		ImGui::Spacing();

		ImGui::BeginGroup();
		{
			ImGui::Text("Joins Not blocked -");
			if (ImGui::BeginListBox("##bad_players", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.3)}))
			{
				for (auto& pair : bad_players_nm::bad_players_list)
					if (!pair.second.block_join && ImGui::Selectable(pair.second.name.c_str(), selected_id && selected_id == pair.first))
						selected_id = pair.first;

				ImGui::EndListBox();
			}
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		{
			ImGui::Text("Joins blocked -");
			if (ImGui::BeginListBox("##bad_players_blocked", {300, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.3)}))
			{
				std::map<uint64_t, bad_players_nm::bad_player> temp_objs;

				if (searched_blocked_players.size())
					temp_objs = searched_blocked_players;
				else if (search_blocked_player_name.length() > 0)
					temp_objs = searched_blocked_players = filter_bad_players(bad_players_nm::bad_players_list, search_blocked_player_name);

				for (auto& pair : (search_blocked_player_name.length() > 0 ? temp_objs : bad_players_nm::bad_players_list))
					if (pair.second.block_join && ImGui::Selectable(pair.second.name.c_str(), selected_id && selected_id == pair.first))
						selected_id = pair.first;

				ImGui::EndListBox();
			}
		}
		ImGui::EndGroup();

		components::button("Reset Non Blocked List", [] {
			selected_id = 0;
			for (auto it = bad_players_nm::bad_players_list.begin(); it != bad_players_nm::bad_players_list.end();)
				if (!it->second.block_join)
					it = bad_players_nm::bad_players_list.erase(it);
				else
					++it;
		});
		ImGui::SameLine();
		components::button("Reset All", [] {
			selected_id = 0;
			bad_players_nm::load_blocked_list();
		});

		ImGui::Spacing();

		if (selected_id)
		{
			ImGui::Spacing();

			components::sub_title("Selected Player");

			ImGui::Spacing();

			ImGui::BeginGroup();
			{
				ImGui::Text(bad_players_nm::bad_players_list[selected_id].name.c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton("Copy##copyname"))
					ImGui::SetClipboardText(bad_players_nm::bad_players_list[selected_id].name.c_str());

				ImGui::Spacing();

				ImGui::Text(std::to_string(selected_id).c_str());
				ImGui::SameLine();
				if (ImGui::SmallButton("Copy##copyrid"))
					ImGui::SetClipboardText(std::to_string(selected_id).c_str());
			}
			ImGui::EndGroup();
			ImGui::SameLine(0, 2.0f * ImGui::GetTextLineHeight());
			ImGui::BeginGroup();
			{
				auto block_join = bad_players_nm::bad_players_list[selected_id].block_join;
				auto is_spammer = bad_players_nm::bad_players_list[selected_id].is_spammer;

				if (ImGui::Checkbox("Block Join", &block_join))
					g_thread_pool->push([block_join] {
						bad_players_nm::toggle_block(selected_id, block_join);
						searched_blocked_players.clear();
					});

				if (ImGui::Checkbox("Is Spammer", &is_spammer))
					g_thread_pool->push([is_spammer] {
						bad_players_nm::set_spammer(selected_id, is_spammer);
					});
			}
			ImGui::EndGroup();
		}
	}
}
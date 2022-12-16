#include "fiber_pool.hpp"
#include "script.hpp"
#include "views/view.hpp"
#include "services/creator_storage/creator_storage_service.hpp"
#include "util/scripts.hpp"

static bool cached_creator_files = false;
static std::vector<std::string> creator_files;

namespace big
{
	void view::creator()
	{
		static std::string selected_creator_file = "";
		if (!cached_creator_files)
		{
			creator_files = creator_storage_service::list_files();
			cached_creator_files = true;
		}

		ImGui::PushItemWidth(250);
		components::sub_title("Saved Jobs");

		if (ImGui::ListBoxHeader("##empty", ImVec2(200, 200)))
		{
			for (const auto& pair : creator_files)
			{
				if (ImGui::Selectable(pair.c_str(), selected_creator_file == pair))
					selected_creator_file = pair;
			}

			ImGui::ListBoxFooter();
		}

		ImGui::SameLine();

		ImGui::BeginGroup();

		if (!selected_creator_file.empty())
		{
			components::button("Save To File", []
			{
				creator_storage_service::save_file(selected_creator_file);
			});

			ImGui::SameLine();

			components::button("Load From File", []
			{
				creator_storage_service::load_file(selected_creator_file);
			});
		}

		static char job_file_name_input[50]{};

		ImGui::PushItemWidth(250);
		components::input_text_with_hint(
			"Job Name",
			"Ex: My Cool Job",
			job_file_name_input, IM_ARRAYSIZE(job_file_name_input));

		components::button("Create Job File", []
		{
			cached_creator_files = false;
			creator_storage_service::create_file(std::string(job_file_name_input) + ".json");
		});

		ImGui::SameLine();

		components::button("Refresh", []
		{
			cached_creator_files = false;
		});

		ImGui::EndGroup();

		components::sub_title("Launch Creator");
		ImGui::BeginGroup();
		components::button("Race", [] { scripts::start_creator_script(RAGE_JOAAT("fm_race_creator")); }); ImGui::SameLine();
		components::button("Capture", [] { scripts::start_creator_script(RAGE_JOAAT("fm_capture_creator")); }); ImGui::SameLine();
		components::button("Deathmatch", [] { scripts::start_creator_script(RAGE_JOAAT("fm_deathmatch_creator")); }); ImGui::SameLine();
		components::button("LTS", [] { scripts::start_creator_script(RAGE_JOAAT("fm_lts_creator")); });
		ImGui::EndGroup();
	}
}

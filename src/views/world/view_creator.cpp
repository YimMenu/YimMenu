#include "fiber_pool.hpp"
#include "script.hpp"
#include "services/api/api_service.hpp"
#include "services/creator_storage/creator_storage_service.hpp"
#include "thread_pool.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

static bool cached_creator_files = false;
static std::vector<std::string> creator_files;

namespace big
{
	void view::creator()
	{
		static std::string selected_creator_file = "";
		if (!cached_creator_files)
		{
			creator_files        = creator_storage_service::list_files();
			cached_creator_files = true;
		}

		ImGui::PushItemWidth(250);
		components::sub_title("CREATOR_SAVED_JOBS"_T);

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
			components::button("CREATOR_SAVE_TO_FILE"_T, [] {
				creator_storage_service::save_file(selected_creator_file);
			});

			ImGui::SameLine();

			components::button("CREATOR_LOAD_FROM_FILE"_T, [] {
				creator_storage_service::load_file(selected_creator_file);
			});
		}

		static char job_file_name_input[50]{};

		ImGui::PushItemWidth(250);
		components::input_text_with_hint("CREATOR_JOB_FILENAME"_T, "CREATOR_JOB_FILENAME_HINT"_T, job_file_name_input, IM_ARRAYSIZE(job_file_name_input));

		components::button("CREATOR_JOB_CREATE_FILE"_T, [] {
			cached_creator_files = false;
			creator_storage_service::create_file(std::string(job_file_name_input) + ".json");
		});

		ImGui::SameLine();

		components::button("REFRESH"_T, [] {
			cached_creator_files = false;
		});

		ImGui::Separator();

		static char job_link[69]{};
		components::input_text("CREATOR_JOB_LINK"_T, job_link, sizeof(job_link));

		components::button("CREATOR_JOB_IMPORT"_T, [] {
			g_thread_pool->push([] {
				std::string content_id = job_link;
				nlohmann::json job_details;
				if (content_id.starts_with("https://"))
					content_id = content_id.substr(46);

				g_fiber_pool->queue_job([content_id] {
					if (NETWORK::UGC_QUERY_BY_CONTENT_ID(content_id.c_str(), false, "gta5mission"))
					{
						while (NETWORK::UGC_IS_GETTING())
							script::get_current()->yield();

						int f1 = NETWORK::UGC_GET_CONTENT_FILE_VERSION(0, 1);
						int f0 = NETWORK::UGC_GET_CONTENT_FILE_VERSION(0, 0);

						if (g_api_service->download_job_metadata(content_id, f1 < 0 ? 0 : f1, f0 < 0 ? 0 : f0, NETWORK::UGC_GET_CONTENT_LANGUAGE(0)))
						{
							cached_creator_files = false;
							g_notification_service->push("CREATOR_JOB_IMPORT_NOTIFICATION"_T.data(),
							    "CREATOR_JOB_IMPORT_SUCCESS"_T.data());
						}
						else
						{
							g_notification_service->push_error("CREATOR_JOB_IMPORT_NOTIFICATION"_T.data(),
							    "CREATOR_JOB_FAILED_METADATA_FETCH"_T.data());
						}
					}
					else
					{
						g_notification_service->push_error("CREATOR_JOB_IMPORT_NOTIFICATION"_T.data(),
						    "CREATOR_JOB_UGC_QUERY_FAILED"_T.data());
					}
				});
			});
		});

		ImGui::EndGroup();

		components::sub_title("CREATOR_LAUNCH"_T);
		ImGui::BeginGroup();
		components::button("RACE"_T, [] {
			scripts::start_creator_script(RAGE_JOAAT("fm_race_creator"));
		});
		ImGui::SameLine();
		components::button("CAPTURE"_T, [] {
			scripts::start_creator_script(RAGE_JOAAT("fm_capture_creator"));
		});
		ImGui::SameLine();
		components::button("DEATHMATCH"_T, [] {
			scripts::start_creator_script(RAGE_JOAAT("fm_deathmatch_creator"));
		});
		ImGui::SameLine();
		components::button("LTS"_T, [] {
			scripts::start_creator_script(RAGE_JOAAT("fm_lts_creator"));
		});
		ImGui::EndGroup();

		components::sub_title("CREATOR_OPTIONS"_T);
		ImGui::BeginGroup();
		ImGui::Checkbox("CREATOR_INFINITE_MEMORY"_T.data(), &g.ugc.infinite_model_memory);
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("CREATOR_INFINITE_MEMORY_DESCRIPTION"_T.data());

		ImGui::EndGroup();
	}
}

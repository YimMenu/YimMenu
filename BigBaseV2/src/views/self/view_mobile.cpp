#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "util/player.hpp"
#include "views/view.hpp"
#include "services/players/ped_list_service.hpp"

namespace big
{
	void view::ped_model() {
		//ImGui::SetWindowSize({ 0.f, (float)*g_pointers->m_resolution_y }, ImGuiCond_Always);

		static char model[32];
		/*components::input_text_with_hint("Model Name###player_ped_model", "Player Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, [] {
			g_fiber_pool->queue_job([] {
				const Hash hash = rage::joaat(model);

				for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
				{
					STREAMING::REQUEST_MODEL(hash);

					script::get_current()->yield();
				}
				if (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model ? ");

					return;
				}

				PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
				script::get_current()->yield();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
				});
			});*/
		static int selected_class = -1;
		auto class_arr = g_ped_list_service->get_pedtype_arr();

		//ImGui::SetNextItemWidth(300.f);
		if (ImGui::BeginCombo("Pedtype", selected_class == -1 ? "ALL" : class_arr[selected_class].c_str()))
		{
			if (ImGui::Selectable("ALL", selected_class == -1))
			{
				selected_class = -1;
			}

			for (int i = 0; i < class_arr.size(); i++)
			{
				if (ImGui::Selectable(class_arr[i].c_str(), selected_class == i))
				{
					selected_class = i;
				}

				if (selected_class == i)
				{
					ImGui::SetItemDefaultFocus();
				}
			}

			ImGui::EndCombo();
		}


		components::input_text_with_hint("Model Name###player_ped_model", "Search", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, []
			{
				const Hash hash = rage::joaat(model);

				for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
				{
					STREAMING::REQUEST_MODEL(hash);

					script::get_current()->yield();
				}
				if (!STREAMING::HAS_MODEL_LOADED(hash))
				{
					g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model ? ");

					return;
				}

				PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
				PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
				script::get_current()->yield();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
			});
		if (ImGui::ListBoxHeader("###peds"))
		{
			if (!g_ped_list_service->get_ped_list().is_null())
			{
				for (auto& item : g_ped_list_service->get_ped_list())
				{
					if (item["Name"].is_null())
						continue;

					std::string name = item["Name"];
					std::string pedtype = item["Pedtype"];

					std::string search = model;
					std::transform(search.begin(), search.end(), search.begin(), ::tolower);

					if ((selected_class == -1 || class_arr[selected_class] == pedtype)
						&&
						(search.empty() ||
							does_search_match(name, search)))
					{
						components::selectable(item["Name"], item["Name"] == search, [&item]
							{
								const Hash hash = item["Hash"];

								for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
								{
									STREAMING::REQUEST_MODEL(hash);

									script::get_current()->yield();
								}
								if (!STREAMING::HAS_MODEL_LOADED(hash))
								{
									g_notification_service->push_error("Self", "Failed to spawn model, did you give an incorrect model ? ");

									return;
								}

								PLAYER::SET_PLAYER_MODEL(PLAYER::GET_PLAYER_INDEX(), hash);
								PED::SET_PED_DEFAULT_COMPONENT_VARIATION(self::ped);
								script::get_current()->yield();
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);
							});
					}
				}
			}
			else ImGui::Text("No peds in registry.");
			ImGui::ListBoxFooter();
		}		
	}
}

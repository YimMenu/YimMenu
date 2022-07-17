#include "fiber_pool.hpp"
#include "util/entity.hpp"
#include "util/player.hpp"
#include "views/view.hpp"
#include "services/players/ped_list_service.hpp"
#include "gta/Weapons.h"

namespace big
{
	void view::ped_model() {

		static char model[32];
		static int selected_class = -1;
		auto class_arr = g_ped_list_service->get_pedtype_arr();

		ImGui::Checkbox("Give All Weapon", &g->self.give_all_weapon);

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

		const auto SET_PLAYER_MODEL = [](Ped ped, Hash hash)
		{
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
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(ped);
			script::get_current()->yield();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			script::get_current()->yield();

			if (g->self.give_all_weapon)
			{
				if (PED::GET_PED_TYPE(self::ped) != ePedType::PED_TYPE_ANIMAL) {
					for (auto const& weapon : weapon_list) {
						WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, weapon, 9999, false);
					}
					WEAPON::GIVE_DELAYED_WEAPON_TO_PED(self::ped, -72657034, 0, true);
				}
			}
		};
		components::input_text_with_hint("Model Name###player_ped_model", "Search", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue, [=] {
			const Hash hash = rage::joaat(model);

			SET_PLAYER_MODEL(self::ped, hash);
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

					if ((selected_class == -1 || class_arr[selected_class] == pedtype) && (search.empty() || does_search_match(name, search)))
					{
						components::selectable(item["Name"], item["Name"] == search, [=] {
							const Hash hash = item["Hash"];

							SET_PLAYER_MODEL(self::ped, hash);
						});
					}
				}
			}
			else ImGui::Text("No peds in registry.");
			ImGui::ListBoxFooter();
		}
	}
}
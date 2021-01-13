#include "tab_bar.hpp"
#include "pointers.hpp"

namespace big
{
	static char model[64];

	void tabbar::render_spawn()
	{
		if (ImGui::BeginTabItem("Spawn"))
		{
			if (
				ImGui::InputText("Model Name", model, sizeof(model), ImGuiInputTextFlags_EnterReturnsTrue) ||
				ImGui::Button("Spawn")
			)
			{
				QUEUE_JOB_BEGIN_CLAUSE(= )
				{
					Hash hash = MISC::GET_HASH_KEY((const char*)model);

					if (hash)
					{
						for (uint8_t i = 0; !STREAMING::HAS_MODEL_LOADED(hash) && i < 100; i++)
						{
							STREAMING::REQUEST_MODEL(hash);

							script::get_current()->yield();
						}
						if (!STREAMING::HAS_MODEL_LOADED(hash))
						{
							features::notify::above_map("~r~Failed to spawn model, did you give an incorrect model?");

							return;
						}

						Ped player = PLAYER::PLAYER_PED_ID();

						Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(player, .0, 8.0, .5);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x9090;
						Vehicle veh = VEHICLE::CREATE_VEHICLE(hash, location.x, location.y, location.z, ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()) + 90.f, true, false, false);
						*(unsigned short*)g_pointers->m_model_spawn_bypass = 0x0574;

						script::get_current()->yield();

						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

						if (*g_pointers->m_is_session_started)
						{
							DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
							ENTITY::_SET_ENTITY_SOMETHING(veh, true);
							int networkId = NETWORK::VEH_TO_NET(veh);
							if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
								NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
							VEHICLE::SET_VEHICLE_IS_STOLEN(veh, false);
						}
					}
				}QUEUE_JOB_END_CLAUSE
			}

			ImGui::EndTabItem();
		}
	}
}
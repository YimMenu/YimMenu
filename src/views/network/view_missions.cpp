#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "gta_util.hpp"
#include "script_local.hpp"
#include "util/scripts.hpp"
#include "views/view.hpp"

namespace big
{
	static bool mission_found = false;

	inline rage::scrThread* check_script(rage::joaat_t hash)
	{
		if (auto thread = gta_util::find_script_thread(hash))
		{
			mission_found = true;
			return thread;
		}

		return nullptr;
	}

	void view::missions()
	{
		mission_found = false;

		components::sub_title("Event Starter");

		ImGui::BeginGroup();
		components::button("Hot Target", [] {
			scripts::start_launcher_script(36);
		});
		components::button("Kill List", [] {
			scripts::start_launcher_script(37);
		});
		components::button("Checkpoints", [] {
			scripts::start_launcher_script(39);
		});
		components::button("Challenges", [] {
			scripts::start_launcher_script(40);
		});
		components::button("Penned In", [] {
			scripts::start_launcher_script(41);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Hot Property", [] {
			scripts::start_launcher_script(43);
		});
		components::button("King Of The Castle", [] {
			scripts::start_launcher_script(45);
		});
		components::button("Criminal Damage", [] {
			scripts::start_launcher_script(46);
		});
		components::button("Hunt The Beast", [] {
			scripts::start_launcher_script(47);
		});
		components::button("Business Battles", [] {
			scripts::start_launcher_script(114);
		});
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("One-On-One Deathmatch", [] {
			scripts::start_launcher_script(197);
		});
		components::button("Impromptu Race", [] {
			scripts::start_launcher_script(16);
		});
		components::button("Flight School", [] {
			scripts::start_launcher_script(196);
		});
		components::button("Golf", [] {
			scripts::start_launcher_script(193);
		});
		components::button("Tutorial", [] {
			scripts::start_launcher_script(20);
		});
		if (ImGui::IsItemHovered())
			ImGui::SetTooltip("Only works on joining players");
		ImGui::EndGroup();

		ImGui::SameLine();

		ImGui::BeginGroup();
		components::button("Gunslinger", [] {
			scripts::start_launcher_script(211);
		});
		components::button("Space Monkey", [] {
			scripts::start_launcher_script(216);
		});
		components::button("Wizard", [] {
			scripts::start_launcher_script(212);
		});
		components::button("QUB3D", [] {
			scripts::start_launcher_script(217);
		});
		components::button("Camhedz", [] {
			scripts::start_launcher_script(218);
		});
		ImGui::EndGroup();

		ImGui::Separator();

		if (check_script(RAGE_JOAAT("am_criminal_damage")))
		{
			components::sub_title("Criminal Damage");
			components::button("Start Event##criminal_damage", [] {
				if (scripts::force_host(RAGE_JOAAT("am_criminal_damage")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
						*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(43).as<int*>() = 0;
			});
			ImGui::SameLine();
			components::button("Finish Event##criminal_damage", [] {
				if (scripts::force_host(RAGE_JOAAT("am_criminal_damage")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
						*script_local(script->m_stack, scr_locals::am_criminal_damage::broadcast_idx).at(39).as<int*>() = 0;
			});

			components::button("Max Score", [] {
				if (auto criminal_damage = gta_util::find_script_thread(RAGE_JOAAT("am_criminal_damage")))
					*script_local(criminal_damage->m_stack, scr_locals::am_criminal_damage::score_idx).as<int*>() = 999'999'999;
			});
		}

		if (check_script(RAGE_JOAAT("am_cp_collection")))
		{
			components::sub_title("Checkpoints");

			components::button("Start Event##cp_collection", [] {
				if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
						*script_local(script->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(667).as<int*>() = 0;
			});
			ImGui::SameLine();
			components::button("Finish Event##cp_collection", [] {
				if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
						*script_local(script->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(661).as<int*>() = 0;
			});

			components::button("Win Event", [] {
				if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
					*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::player_broadcast_idx)
					     .at(checkpoints->m_net_component->m_local_participant_index, 5)
					     .at(4)
					     .as<int*>() = 999'999'999;

				script::get_current()->yield(1s);

				if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
				{
					if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
					{
						*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::broadcast_idx).at(708).as<int*>() = 0;
					}
				}
			});
			ImGui::SameLine();
			components::button("Scramble Checkpoints", [] {
				std::vector<Vector3> active_player_positions;

				for (auto& plyr : g_player_service->players())
				{
					if (plyr.second->is_valid() && NETWORK::NETWORK_IS_PLAYER_A_PARTICIPANT_ON_SCRIPT(plyr.second->id(), "am_cp_collection", -1))
					{
						active_player_positions.push_back(
						    ENTITY::GET_ENTITY_COORDS(PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(plyr.second->id()), false));
					}
				}

				if (scripts::force_host(RAGE_JOAAT("am_cp_collection")))
				{
					if (auto checkpoints = gta_util::find_script_thread(RAGE_JOAAT("am_cp_collection")))
					{
						for (int i = 0; i < 100; i++)
						{
							*script_local(checkpoints->m_stack, scr_locals::am_cp_collection::broadcast_idx)
							     .at(10)
							     .at(i, 5)
							     .as<Vector3*>() = active_player_positions[i % active_player_positions.size()];
						}
					}
				}
			});
		}

		if (check_script(RAGE_JOAAT("am_king_of_the_castle")))
		{
			components::sub_title("King Of The Castle");
			components::button("Complete Event##kotc", [] {
				if (scripts::force_host(RAGE_JOAAT("am_king_of_the_castle")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_king_of_the_castle")))
						*script_local(script->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx).at(1).at(1).as<int*>() = 0;
			});
			ImGui::SameLine();
			components::button("Expire Event (if possible)##kotc", [] {
				if (scripts::force_host(RAGE_JOAAT("am_king_of_the_castle")))
					if (auto script = gta_util::find_script_thread(RAGE_JOAAT("am_king_of_the_castle")))
						*script_local(script->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx).at(1).at(3).as<int*>() = 0;
			});

			components::button("Become The King##kotc", [] {
				if (scripts::force_host(RAGE_JOAAT("am_king_of_the_castle")))
				{
					if (auto kotc = gta_util::find_script_thread(RAGE_JOAAT("am_king_of_the_castle")))
					{
						*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
						     .at(6)
						     .at(0, 204)
						     .at(74)
						     .at(0, 4)
						     .as<int*>() = 0;
						*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
						     .at(6)
						     .at(0, 204)
						     .at(74)
						     .at(0, 4)
						     .at(1)
						     .as<int*>() = self::id;
						*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
						     .at(6)
						     .at(0, 204)
						     .at(74)
						     .at(0, 4)
						     .at(2)
						     .as<int*>() = self::id;
						*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
						     .at(6)
						     .at(0, 204)
						     .at(74)
						     .at(0, 4)
						     .at(3)
						     .as<float*>() = 999999999.0f;
					}
				}
			});
			ImGui::SameLine();
			components::button("Dethrone Everyone##kotc", [] {
				if (scripts::force_host(RAGE_JOAAT("am_king_of_the_castle")))
				{
					if (auto kotc = gta_util::find_script_thread(RAGE_JOAAT("am_king_of_the_castle")))
					{
						for (int i = 0; i < *script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
						                         .at(6)
						                         .at(0, 204)
						                         .at(74)
						                         .as<int*>();
						     i++)
						{
							*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
							     .at(6)
							     .at(0, 204)
							     .at(74)
							     .at(i, 4)
							     .as<int*>() = -1;
							*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
							     .at(6)
							     .at(0, 204)
							     .at(74)
							     .at(i, 4)
							     .at(1)
							     .as<int*>() = -1;
							*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
							     .at(6)
							     .at(0, 204)
							     .at(74)
							     .at(i, 4)
							     .at(2)
							     .as<int*>() = -1;
							*script_local(kotc->m_stack, scr_locals::am_king_of_the_castle::broadcast_idx)
							     .at(6)
							     .at(0, 204)
							     .at(74)
							     .at(i, 4)
							     .at(3)
							     .as<float*>() = -1.0f;
						}
					}
				}
			});
		}


		if (!mission_found)
		{
			ImGui::Text("No active mission");
		}
	}
}
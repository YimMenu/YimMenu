#include "view_esp.hpp"

#include "gta_util.hpp"
#include "pointers.hpp"
#include "gta/matrix.hpp"
#include "services/players/player_service.hpp"
#include "util/math.hpp"
#include "util/misc.hpp"
#include "gta/enums.hpp"

namespace big
{
	static const ImColor death_bg         = ImColor(0.117f, 0.113f, 0.172f, .75f);
	static const ImColor armor_blue_bg    = ImColor(0.36f, 0.71f, 0.89f, .75f);
	static const ImColor armor_blue       = ImColor(0.36f, 0.71f, 0.89f, 1.f);
	static const ImColor health_green_bg  = ImColor(0.29f, 0.69f, 0.34f, .75f);
	static const ImColor health_green     = ImColor(0.29f, 0.69f, 0.34f, 1.f);
	static const ImColor health_yellow_bg = ImColor(0.69f, 0.49f, 0.29f, .75f);
	static const ImColor health_yellow    = ImColor(0.69f, 0.49f, 0.29f, 1.f);
	static const ImColor health_red_bg    = ImColor(0.69f, 0.29f, 0.29f, .75f);
	static const ImColor health_red       = ImColor(0.69f, 0.29f, 0.29f, 1.f);

	void esp::draw_player(const player_ptr& plyr, ImDrawList* const draw_list)
	{
		if (!plyr->is_valid() || !plyr->get_ped() || !plyr->get_ped()->m_navigation)
			return;

		auto& player_pos = *plyr->get_ped()->m_navigation->get_position();

		float screen_x, screen_y;

		const float distance = math::calculate_distance_from_game_cam(player_pos);
		const float multplr  = distance > g.esp.global_render_distance[1] ? -1.f : 6.17757f / distance;

		if (multplr == -1.f || g.esp.global_render_distance[0] > distance)
			return;

		uint32_t ped_damage_bits = plyr->get_ped()->m_damage_bits;

		Vector3 plyr_coords = {player_pos.x, player_pos.y, player_pos.z};
		if (world_to_screen(plyr_coords, screen_x, screen_y))
		//if (g_pointers->m_gta.m_get_screen_coords_for_world_coords(player_pos.data, &screen_x, &screen_y))
		{
			const auto esp_x = (float)*g_pointers->m_gta.m_resolution_x * screen_x;
			const auto esp_y = (float)*g_pointers->m_gta.m_resolution_y * screen_y;

			std::string name_str;
			ImVec2 name_pos = {esp_x - (62.5f * multplr), esp_y - (175.f * multplr) - 20.f};
			ImU32 esp_color = g.esp.default_color;

			if (plyr->is_friend())
			{
				esp_color = g.esp.friend_color;
			}
			else if (g.esp.change_esp_color_from_dist)
			{
				if (distance <= g.esp.distance_threshold[0])
					esp_color = g.esp.enemy_color;
				else if (distance >= g.esp.distance_threshold[0] && distance < g.esp.distance_threshold[1])
					esp_color = g.esp.enemy_near_color;
			}

			const auto armor_perc  = plyr->get_ped()->m_armor / 50.f;
			const auto health_perc = plyr->get_ped()->m_health / (plyr->get_ped()->m_maxhealth + 0.001f);

			if (distance < g.esp.tracer_render_distance[1] && distance > g.esp.tracer_render_distance[0] && g.esp.tracer)
				draw_list->AddLine({(float)*g_pointers->m_gta.m_resolution_x * g.esp.tracer_draw_position[0],
				                       (float)*g_pointers->m_gta.m_resolution_y * g.esp.tracer_draw_position[1]},
				    {esp_x, esp_y},
				    esp_color);

			if (distance < g.esp.box_render_distance[1] && distance > g.esp.box_render_distance[0] && g.esp.box)
				draw_list->AddRect({esp_x - (62.5f * multplr), esp_y - (175.f * multplr)}, {esp_x - (62.5f * multplr) + (125.f * multplr), esp_y - (175.f * multplr) + (350.f * multplr)}, esp_color);

			if (distance < g.esp.bone_render_distance[1] && distance > g.esp.bone_render_distance[0] && g.esp.bone)
			{
				// Map bone locations to x/y on screen
				ImVec2 head_pos;
				bool head_valid = bone_to_screen(plyr, ePedBoneType::HEAD, head_pos);
				if (head_valid)
				{
					// Draw circle around head
					draw_list->AddCircle(head_pos, 20.f * multplr, esp_color, 0, 2.0f);
				}

				ImVec2 neck_pos;
				bool neck_valid = bone_to_screen(plyr, ePedBoneType::NECK, neck_pos);
				if (head_valid && neck_valid)
				{
					// Head to neck
					draw_list->AddLine(head_pos, neck_pos, esp_color, 2.0f);
				}

				ImVec2 abdomen_pos;
				bool abdomen_valid = bone_to_screen(plyr, ePedBoneType::ABDOMEN, abdomen_pos);
				if (neck_valid && abdomen_valid)
				{
					// Neck to abdomen
					draw_list->AddLine(neck_pos, abdomen_pos, esp_color, 2.0f);
				}

				ImVec2 l_hand_pos;
				bool l_hand_valid = bone_to_screen(plyr, ePedBoneType::L_HAND, l_hand_pos);
				if (neck_valid && l_hand_valid)
				{
					// Neck to left hand
					draw_list->AddLine(neck_pos, l_hand_pos, esp_color, 2.0f);
				}

				ImVec2 r_hand_pos;
				bool r_hand_valid = bone_to_screen(plyr, ePedBoneType::R_HAND, r_hand_pos);
				if (neck_valid && r_hand_valid)
				{
					// Neck to right hand
					draw_list->AddLine(neck_pos, r_hand_pos, esp_color, 2.0f);
				}

				ImVec2 l_ankle_pos;
				bool l_ankle_valid = bone_to_screen(plyr, ePedBoneType::L_ANKLE, l_ankle_pos);
				if (abdomen_valid && l_ankle_valid)
				{
					// Abdomen to left ankle
					draw_list->AddLine(abdomen_pos, l_ankle_pos, esp_color, 2.0f);
				}

				ImVec2 r_ankle_pos;
				bool r_ankle_valid = bone_to_screen(plyr, ePedBoneType::R_ANKLE, r_ankle_pos);
				if (abdomen_valid && r_ankle_valid)
				{
					// Abdomen to right ankle
					draw_list->AddLine(abdomen_pos, r_ankle_pos, esp_color, 2.0f);
				}

				ImVec2 l_foot_pos;
				bool l_foot_valid = bone_to_screen(plyr, ePedBoneType::L_FOOT, l_foot_pos);
				if (l_ankle_valid && l_foot_valid)
				{
					// Left ankle to left foot
					draw_list->AddLine(l_ankle_pos, l_foot_pos, esp_color, 2.0f);
				}

				ImVec2 r_foot_pos;
				bool r_foot_valid = bone_to_screen(plyr, ePedBoneType::R_FOOT, r_foot_pos);
				if (r_ankle_valid && r_foot_valid)
				{
					// Right ankle to right foot
					draw_list->AddLine(r_ankle_pos, r_foot_pos, esp_color, 2.0f);
				}

				/*
				bool head_valid = bone_to_screen(plyr, (int)PedBones::SKEL_Head, head_pos);
				
				if (head_valid)
				{
					// Draw circle around head
					draw_list->AddCircle(head_pos, 20.f * multplr, esp_color, 0, 2.0f);
				}

				// Make sure to validate both bones before drawing a line between them, otherwise off-screen bones will cause long lines across your screen

				ImVec2 neck_pos;
				bool neck_valid = bone_to_screen(plyr, (int)PedBones::SKEL_Neck_1, neck_pos);

				if (head_valid && neck_valid)
				{
					// Head to neck
					draw_list->AddLine(head_pos, neck_pos, esp_color, 2.0f);
				}


				ImVec2 r_shoulder_pos;
				bool r_shoulder_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Clavicle, r_shoulder_pos);
				if (neck_valid && r_shoulder_valid)
				{
					// Neck to right shoulder
					draw_list->AddLine(neck_pos, r_shoulder_pos, esp_color, 2.0f);
				}

				ImVec2 l_shoulder_pos;
				bool l_shoulder_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Clavicle, l_shoulder_pos);
				if (neck_valid && l_shoulder_valid)
				{
					// Neck to left shoulder
					draw_list->AddLine(neck_pos, l_shoulder_pos, esp_color, 2.0f);
				}

				ImVec2 r_elbow_pos;
				bool r_elbow_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_UpperArm, r_elbow_pos);
				if (r_shoulder_valid && r_elbow_valid)
				{
					// Right shoulder to right elbow
					draw_list->AddLine(r_shoulder_pos, r_elbow_pos, esp_color, 2.0f);
				}

				ImVec2 l_elbow_pos;
				bool l_elbow_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_UpperArm, l_elbow_pos);
				if (l_shoulder_valid && l_elbow_valid)
				{
					// Left shoulder to left elbow
					draw_list->AddLine(l_shoulder_pos, l_elbow_pos, esp_color, 2.0f);
				}

				ImVec2 r_upperarm_pos;
				bool r_upperarm_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_UpperArm, r_upperarm_pos);
				if (r_elbow_valid && r_upperarm_valid)
				{
					// Right elbow to right upper arm
					draw_list->AddLine(r_elbow_pos, r_upperarm_pos, esp_color, 2.0f);
				}

				ImVec2 l_upperarm_pos;
				bool l_upperarm_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_UpperArm, l_upperarm_pos);
				if (l_elbow_valid && l_upperarm_valid)
				{
					// Left elbow to left upper arm
					draw_list->AddLine(l_elbow_pos, l_upperarm_pos, esp_color, 2.0f);
				}

				ImVec2 r_forearm_pos;
				bool r_forearm_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Forearm, r_forearm_pos);
				if (r_upperarm_valid && r_forearm_valid)
				{
					// Right upper arm to right forearm
					draw_list->AddLine(r_upperarm_pos, r_forearm_pos, esp_color, 2.0f);
				}

				ImVec2 l_forearm_pos;
				bool l_forearm_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Forearm, l_forearm_pos);
				if (l_upperarm_valid && l_forearm_valid)
				{
					// Left upper arm to left forearm
					draw_list->AddLine(l_upperarm_pos, l_forearm_pos, esp_color, 2.0f);
				}

				ImVec2 r_hand_pos;
				bool r_hand_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Hand, r_hand_pos);
				if (r_forearm_valid && r_hand_valid)
				{
					// Right forearm to right hand
					draw_list->AddLine(r_forearm_pos, r_hand_pos, esp_color, 2.0f);
				}

				ImVec2 l_hand_pos;
				bool l_hand_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Hand, l_hand_pos);
				if (l_forearm_valid && l_hand_valid)
				{
					// Left forearm to left hand
					draw_list->AddLine(l_forearm_pos, l_hand_pos, esp_color, 2.0f);
				}

				ImVec2 spine_pos;
				bool spine_valid = bone_to_screen(plyr, (int)PedBones::SKEL_Spine0, spine_pos);
				if (neck_valid && spine_valid)
				{
					// Neck to spine
					draw_list->AddLine(neck_pos, spine_pos, esp_color, 2.0f);
				}

				ImVec2 r_thigh_pos;
				bool r_thigh_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Thigh, r_thigh_pos);
				if (spine_valid && r_thigh_valid)
				{
					// Spine to right thigh
					draw_list->AddLine(spine_pos, r_thigh_pos, esp_color, 2.0f);
				}

				ImVec2 l_thigh_pos;
				bool l_thigh_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Thigh, l_thigh_pos);
				if (spine_valid && l_thigh_valid)
				{
					// Spine to left thigh
					draw_list->AddLine(spine_pos, l_thigh_pos, esp_color, 2.0f);
				}

				ImVec2 r_calf_pos;
				bool r_calf_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Calf, r_calf_pos);
				if (r_thigh_valid && r_calf_valid)
				{
					// Right thigh to right calf
					draw_list->AddLine(r_thigh_pos, r_calf_pos, esp_color, 2.0f);
				}

				ImVec2 l_calf_pos;
				bool l_calf_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Calf, l_calf_pos);
				if (l_thigh_valid && l_calf_valid)
				{
					// Left thigh to left calf
					draw_list->AddLine(l_thigh_pos, l_calf_pos, esp_color, 2.0f);
				}

				ImVec2 r_foot_pos;
				bool r_foot_valid = bone_to_screen(plyr, (int)PedBones::SKEL_R_Foot, r_foot_pos);
				if (r_calf_valid && r_foot_valid)
				{
					// Right calf to right foot
					draw_list->AddLine(r_calf_pos, r_foot_pos, esp_color, 2.0f);
				}

				ImVec2 l_foot_pos;
				bool l_foot_valid = bone_to_screen(plyr, (int)PedBones::SKEL_L_Foot, l_foot_pos);
				if (l_calf_valid && l_foot_valid)
				{
					// Left calf to left foot
					draw_list->AddLine(l_calf_pos, l_foot_pos, esp_color, 2.0f);
				}
				*/
			}

			if (g.esp.name)
				name_str = plyr->get_name();

			if (g.esp.distance)
			{
				if (g.esp.name)
					name_str += " | ";
				name_str += std::to_string((int)distance);
				name_str += "m";
			}

			draw_list->AddText(name_pos, esp_color, name_str.c_str());
			std::string mode_str = "";
			if (g.esp.god)
			{
				if (ped_damage_bits & (uint32_t)eEntityProofs::GOD)
				{
					mode_str = "ESP_GOD"_T.data();
				}
				else
				{
					if (ped_damage_bits & (uint32_t)eEntityProofs::BULLET)
					{
						mode_str += "ESP_BULLET"_T.data();
					}
					if (ped_damage_bits & (uint32_t)eEntityProofs::EXPLOSION)
					{
						mode_str += "ESP_EXPLOSION"_T.data();
					}
				}
			}

			if (auto player_vehicle = plyr->get_current_vehicle();
				player_vehicle &&
				(plyr->get_ped()->m_ped_task_flag & (uint32_t)ePedTask::TASK_DRIVING) &&
				(player_vehicle->m_damage_bits & (uint32_t)eEntityProofs::GOD))
			{
				mode_str =+ "VEHICLE_GOD"_T.data();
			}

			if (!mode_str.empty())
			{
				draw_list->AddText({esp_x - (62.5f * multplr), esp_y - (175.f * multplr) - 40.f},
				    ImColor(1.f, 0.f, 0.f, 1.f),
				    mode_str.c_str());
			}

			if (!(ped_damage_bits & (uint32_t)eEntityProofs::GOD))
			{
				if (g.esp.health)
				{
					if (g.esp.scale_health_from_dist)
					{
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f},
						    {esp_x - (62.5f * multplr) + (125.f * multplr), esp_y + (175.f * multplr) + 5.f},
						    health_perc == 0.f      ? death_bg :
						        health_perc < 0.25f ? health_red_bg :
						        health_perc < 0.65f ? health_yellow_bg :
						                              health_green_bg,
						    4);
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f},
						    {esp_x - (62.5f * multplr) + (125.f * multplr) * health_perc, esp_y + (175.f * multplr) + 5.f},
						    health_perc < 0.25f     ? health_red :
						        health_perc < 0.65f ? health_yellow :
						                              health_green,
						    4);
					}
					else
					{
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f},
						    {esp_x - (62.5f * multplr) + (100.f), esp_y + (175.f * multplr) + 5.f},
						    health_perc == 0.f      ? death_bg :
						        health_perc < 0.25f ? health_red_bg :
						        health_perc < 0.65f ? health_yellow_bg :
						                              health_green_bg,
						    4);
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + 5.f},
						    {esp_x - (62.5f * multplr) + (100.f * health_perc), esp_y + (175.f * multplr) + 5.f},
						    health_perc < 0.25f     ? health_red :
						        health_perc < 0.65f ? health_yellow :
						                              health_green,
						    4);
					}
				}
				if (g.esp.armor && plyr->get_ped()->m_armor > 0)
				{
					float offset = 5.f;
					offset       = g.esp.health ? 10.f : 5.f;
					if (g.esp.scale_armor_from_dist)
					{
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + offset}, {esp_x - (62.5f * multplr) + (125.f * multplr), esp_y + (175.f * multplr) + offset}, armor_blue_bg, 4);
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + offset}, {esp_x - (62.5f * multplr) + (125.f * multplr) * armor_perc, esp_y + (175.f * multplr) + offset}, armor_blue, 4);
					}
					else
					{
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + offset}, {esp_x - (62.5f * multplr) + (100.f), esp_y + (175.f * multplr) + offset}, armor_blue_bg, 4);
						draw_list->AddLine({esp_x - (62.5f * multplr), esp_y + (175.f * multplr) + offset}, {esp_x - (62.5f * multplr) + (100.f * armor_perc), esp_y + (175.f * multplr) + offset}, armor_blue, 4);
					}
				}
			}
		}
	}
	/*
	bool esp::bone_to_screen(const player_ptr& plyr, int boneID, ImVec2& boneVec)
	{
		bool isSuccess = false;

		if (plyr == nullptr)
			return false;

		float bone_x = 0;
		float bone_y = 0;

		float screenX = (float)*g_pointers->m_gta.m_resolution_x;
		float screenY = (float)*g_pointers->m_gta.m_resolution_y;

		const auto player_ped = g_pointers->m_gta.m_ptr_to_handle(plyr->get_ped());
		const auto bone_data = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(player_ped, PED::GET_PED_BONE_INDEX(player_ped, boneID));

		float f_vec[3] = { bone_data.x, bone_data.y, bone_data.z };
		isSuccess = g_pointers->m_gta.m_get_screen_coords_for_world_coords(f_vec, &bone_x, &bone_y);

		boneVec.x = screenX * bone_x;
		boneVec.y = screenY * bone_y;

		return isSuccess;
	}
	*/

	bool esp::bone_to_screen(const player_ptr& plyr, ePedBoneType boneType, ImVec2& boneVec)
	{
		if (plyr == nullptr)
			return false;

		float screenX = (float)*g_pointers->m_gta.m_resolution_x;
		float screenY = (float)*g_pointers->m_gta.m_resolution_y;

		// Validate stability of get_bone_coords
		const auto player_bones = plyr->get_ped()->get_bone_coords(boneType);

		Vector3 f_vec = {player_bones.x, player_bones.y, player_bones.z};

		if (world_to_screen(f_vec, boneVec.x, boneVec.y))
		{
			boneVec.x = screenX * boneVec.x;
			boneVec.y = screenY * boneVec.y;

			return true;
		}

		return false;
	}

	void esp::draw()
	{
		if (!g.esp.enabled)
			return;

		if (const auto draw_list = ImGui::GetBackgroundDrawList(); draw_list)
		{
			// draw_player(g_player_service->get_self(), draw_list); // Draw ESP on self, useful for debugging

			g_player_service->iterate([draw_list](const player_entry& entry) {
				draw_player(entry.second, draw_list);
			});
		}
	}

    bool esp::world_to_screen(const Vector3 entity_position, float& screenX, float& screenY)
    {
        // Get the viewport matrix
        rage::CViewPort* view_port = g_pointers->m_gta.m_viewport;

        // Apply the transformation matrix to the entity position
        Vector3 transformed_position;
        transformed_position.x = view_port->m_matrix[1] * entity_position.x + view_port->m_matrix[5] * entity_position.y + view_port->m_matrix[9] * entity_position.z + view_port->m_matrix[13]; // Row 2
        transformed_position.y = view_port->m_matrix[2] * entity_position.x + view_port->m_matrix[6] * entity_position.y + view_port->m_matrix[10] * entity_position.z + view_port->m_matrix[14]; // Row 3
        transformed_position.z = view_port->m_matrix[3] * entity_position.x + view_port->m_matrix[7] * entity_position.y + view_port->m_matrix[11] * entity_position.z + view_port->m_matrix[15]; // Row 4

        // Check if the transformed position is behind the camera
        if (transformed_position.z < 0.001f)
            return false;

        // Perform perspective division
        transformed_position.z = 1.0f / transformed_position.z;
        transformed_position.x *= transformed_position.z;
        transformed_position.y *= transformed_position.z;

        // Get the resolution of the game window
        float resolutionX = static_cast<float>(*g_pointers->m_gta.m_resolution_x);
        float resolutionY = static_cast<float>(*g_pointers->m_gta.m_resolution_y);

        // Calculate the screen coordinates
        screenX = ((resolutionX * 0.5f) + (0.5f * transformed_position.x * resolutionX + 1.0f)) / resolutionX;
        screenY = ((resolutionY * 0.5f) - (0.5f * transformed_position.y * resolutionY + 1.0f)) / resolutionY;

        // Check if the screen coordinates are outside the screen boundaries
        if (screenX > 1.0f || screenX < 0.0f || screenY > 1.0f || screenY < 0.0f)
            return false;

        return true;
    }


	/*


	bool esp::world_to_screen(const Vector3 entity_position, float &screenX, float &screenY)
	{
		rage::CViewPort* view_port = g_pointers->m_gta.m_viewport;


		// Viewport is a 16-element (4x4 matrix)
		float cam_matrix[4][4] = {0};

		// Copy the values from the 16-element viewport array to the 4x4 matrix
		for (int i = 0; i < 16; i++)
		{
			cam_matrix[i / 4][i % 4] = view_port->m_matrix[i];
		}

		// LOG(INFO) << "cam_matrix: " << cam_matrix[0][0] << ", " << cam_matrix[0][1] << ", " << cam_matrix[0][2] << ", " << cam_matrix[0][3] << ", " << cam_matrix[1][0] << ", " << cam_matrix[1][1] << ", " << cam_matrix[1][2] << ", " << cam_matrix[1][3] << ", " << cam_matrix[2][0] << ", " << cam_matrix[2][1] << ", " << cam_matrix[2][2] << ", " << cam_matrix[2][3] << ", " << cam_matrix[3][0] << ", " << cam_matrix[3][1] << ", " << cam_matrix[3][2] << ", " << cam_matrix[3][3];

		// Transpose
		float transposed_cam_matrix[4][4] = {0};

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transposed_cam_matrix[j][i] = cam_matrix[i][j];
			}
		}

		Vector4 vecZ = {transposed_cam_matrix[3][0], transposed_cam_matrix[3][1], transposed_cam_matrix[3][2], transposed_cam_matrix[3][3]};
		Vector4 vecX = {transposed_cam_matrix[1][0], transposed_cam_matrix[1][1], transposed_cam_matrix[1][2], transposed_cam_matrix[1][3]};
		Vector4 vecY = {transposed_cam_matrix[2][0], transposed_cam_matrix[2][1], transposed_cam_matrix[2][2], transposed_cam_matrix[2][3]};

		Vector3 screen_position = {0, 0, 0};
		screen_position.z = (vecZ.x * entity_position.x) + (vecZ.y * entity_position.y) + (vecZ.z * entity_position.z) + vecZ.w;
		screen_position.x =	(vecX.x * entity_position.x) + (vecX.y * entity_position.y) + (vecX.z * entity_position.z) + vecX.w;
		screen_position.y = (vecY.x * entity_position.x) + (vecY.y * entity_position.y) + (vecY.z * entity_position.z) + vecY.w;

		if (screen_position.z < 0.001f)
		{
			screenX = 0.0f;
			screenY = 0.0f;
			
			return false;
		}

		float invw = 1.0f / screen_position.z;

		screen_position.x *= invw;
		screen_position.y *= invw;

		LOG(INFO) << "screen_position: " << screen_position.x << ", " << screen_position.y;

		float resX = (float)*g_pointers->m_gta.m_resolution_x;
		float resY = (float)*g_pointers->m_gta.m_resolution_y;

		// Compute res on-screen pixel position
		screen_position.x += (resX / 2.0f) + (int)(0.5f * screen_position.x * resX + 0.5f);
		screen_position.y = (resY / 2.0f) - (int)(0.5f * screen_position.y * resY + 0.5f);

		screenX = screen_position.x;
		screenY = screen_position.y;

		LOG(INFO) << "screenX: " << screenX << ", screenY: " << screenY;

		return true;
	}*/


}
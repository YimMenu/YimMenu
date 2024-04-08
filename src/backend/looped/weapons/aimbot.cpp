#include "backend/looped_command.hpp"
#include "gta/enums.hpp"
#include "natives.hpp"
#include "util/entity.hpp"

#include <numbers>
namespace big
{
	class aimbot : looped_command
	{
		static inline Vector3 prevTargetPosition;
		static inline Vector3 prevPlayerPosition;
		static inline Vector3 curTargetPosition;
		static inline Vector3 curPlayerPosition;

		static inline float playerToPedDistance;

		static inline Entity target_entity = 0;
		static inline float zCorrection; // Define a zCorrection that lets us vertically offset our aim from the bone
		static inline uint32_t aimBone = 0x796E;

		// Stage 1: Target Acquisition
		// Stage 2: Target Tracking
		// Stage 3: Target Reset

		using looped_command::looped_command;
		virtual void on_tick() override
		{
			// Set local versions of configured variables
			float aimbot_fov = g.weapons.aimbot.fov; // FoV in pixels, grabbed from ImGUI slider

			// Correct for unit circle for the actual math
			aimbot_fov = aimbot_fov / (float)*g_pointers->m_gta.m_resolution_x;

			// Only process aim targets while we're actually free aiming
			if (PLAYER::IS_PLAYER_FREE_AIMING(self::id))
			{
				// Stage 1: Target Acquisition
				for (auto ped : entity::get_entities(false, true))
				{
					// Don't trying acquiring a target if we're already locked onto one
					if (target_entity)
						continue;

					// First, filter out all dead peds
					if (ENTITY::IS_ENTITY_DEAD(ped, 0))
						continue;

					Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(self::ped, 0);
					Vehicle pedVehicle    = PED::GET_VEHICLE_PED_IS_IN(ped, 0);

					// Ignore peds that are in the vehicle with the player
					if (playerVehicle && (playerVehicle == pedVehicle))
						continue;

					// Next, filter out peds outside of the scan area
					Vector3 pedWorldPosition    = ENTITY::GET_ENTITY_COORDS(ped, false);
					Vector3 playerWorldPosition = ENTITY::GET_ENTITY_COORDS(self::ped, false);

					playerToPedDistance = SYSTEM::VDIST2(playerWorldPosition.x,
					    playerWorldPosition.y,
					    playerWorldPosition.z,
					    pedWorldPosition.x,
					    pedWorldPosition.y,
					    pedWorldPosition.z);

					// Don't flip out if an enemy is on top of us
					if (playerToPedDistance < 2.0f)
						continue;

					float xScreen, yScreen;
					GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(pedWorldPosition.x, pedWorldPosition.y, pedWorldPosition.z, &xScreen, &yScreen);

					float xDelta = xScreen - 0.5f; // How far from center (crosshair) is X?
					float yDelta = yScreen - 0.5f; // How far from center (crosshair) is Y?

					// Note that the values returned into xScreen and yScreen by the W2S function range from [0,0] (top left) to [1,1] (bottom right)
					// Largest supported magnitude will obviously be sqrt(0.5^2 + 0.5^2) = 0.707 which is what we'll use in the GUI for now
					// TODO: Create a more easily understandable mapping between GUI value and actual implementation (maybe pixels? maybe draw a box on-screen that shows the valid area?)
					float crosshairMag = sqrtf(xDelta * xDelta + yDelta * yDelta);

					if (crosshairMag > aimbot_fov)
						continue;

					// Filter out peds that are alive and in the scan area, but are behind some sort of cover (we don't want to aim through walls)
					if (!ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(self::ped, ped, 17))
						continue;

					// Now that we've filtered out most of what we want to ignore, our remaining peds are all alive, within our scan area, and targetable
					// From this list of potentially valid targets, let's pick one!
					int relation = PED::GET_RELATIONSHIP_BETWEEN_PEDS(self::ped, ped); // relation for enemy check
					int type     = PED::GET_PED_TYPE(ped); // for police check, cop types are 6, swat is 27

					// If target is a player and we're aiming at players
					if (PED::IS_PED_A_PLAYER(ped) && g.weapons.aimbot.on_player)
					{
						goto set_target;
					}
					// If target is an enemy and we're aiming at enemies
					else if ((relation == 4 || relation == 5 || PED::IS_PED_IN_COMBAT(ped, self::ped))
					    && g.weapons.aimbot.on_enemy) // relation 4 and 5 are for enemies
					{
						goto set_target;
					}
					// If target is law enforcement and we're aiming at law enforcement
					else if (((type == 6 && !PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_uscg_01"))) || type == 27 || // s_m_y_uscg_01 = us coast guard 1 (technically military)
					             PED::IS_PED_MODEL(ped, rage::joaat("s_m_y_ranger_01")) || PED::IS_PED_MODEL(ped, rage::joaat("s_f_y_ranger_01"))) // ranger models
					    && g.weapons.aimbot.on_police)
					{
						goto set_target;
					}
					// If target is an NPC and we're aiming at all NPCs
					// TODO: Maybe filter out animals (type 28)?
					else if (g.weapons.aimbot.on_npc && !PED::IS_PED_A_PLAYER(ped) && type != 28)
					{
						goto set_target;
					}

					// Nothing found, keep going
					else
					{
						continue;
					}

				// At this point, we've verified this ped is something we want to aim at
				set_target:
				{
					target_entity = ped;
				}
				}
				// END Target Acquisition

				// Stage 2: Target Tracking
				if (target_entity)
				{
					// We're now actively checking against the target entity each tick, not the entire pedlist
					// So now we need to verify that the target entity is still valid (alive, not behind cover, etc.) and break the lock-on DURING free aim
					if (ENTITY::IS_ENTITY_DEAD(target_entity, 0) || !ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY_ADJUST_FOR_COVER(self::ped, target_entity, 17))
					{
						// Reset the target entity, and don't bother with the camera stuff since next tick we're scanning for a new target
						target_entity = 0;
					}
					else
					{
						// We have a valid ped, now do bone stuff

						// Set the bone to aim at
						// If the target is on a motorcycle or bike, aim at their neck since a headshot is going to be difficult and most shots will miss
						int pedVehicleClass = VEHICLE::GET_VEHICLE_CLASS(PED::GET_VEHICLE_PED_IS_IN(target_entity, 0));
						if (PED::IS_PED_IN_ANY_VEHICLE(target_entity, 0) && (pedVehicleClass == 8 || pedVehicleClass == 13))
						{
							aimBone     = 0x9995; // Neck
							zCorrection = 0.f;
						}
						else if (PED::IS_PED_IN_ANY_VEHICLE(target_entity, 0))
						{
							aimBone     = 0x796E; // Head
							zCorrection = 0.075f;
						}
						else
						{
							aimBone     = 0x796E; // Head
							zCorrection = 0.07f;
						}

						// Aim Prediction
						// Get current position of ourselves and our targets to use for aim prediction
						curTargetPosition = ENTITY::GET_ENTITY_BONE_POSTION(target_entity, PED::GET_PED_BONE_INDEX(target_entity, aimBone));
						curPlayerPosition = ENTITY::GET_ENTITY_COORDS(self::ped, false);

						// Initialize the previous position if it hasn't been (meaning this is the first tick we're aiming at the target)
						if (prevTargetPosition.x == 0 && prevTargetPosition.y == 0 && prevTargetPosition.z == 0)
						{
							prevTargetPosition = curTargetPosition;
						}

						if (prevPlayerPosition.x == 0 && prevPlayerPosition.y == 0 && prevPlayerPosition.z == 0)
						{
							prevPlayerPosition = curPlayerPosition;
						}

						// posChange is the vector between the position this tick and the position last tick (how far the target moved)
						// We apply the vector to the current position to lead the target
						Vector3 tarPosChange    = curTargetPosition - prevTargetPosition;
						Vector3 playerPosChange = curPlayerPosition - prevPlayerPosition;

						// Apply a compensating factor for the position change
						float compFactor = 1.55f;
						tarPosChange     = tarPosChange * compFactor;

						// We use this playerPosChange a little further down when we grab the camera coordinates
						playerPosChange = playerPosChange * compFactor;

						Vector3 compedAimPos = curTargetPosition + tarPosChange;

						// Apply the zCorrection defined above
						compedAimPos.z += zCorrection;

						/*
						// Vector3 playerVelocity;
						float predMult = 0.015f;

						// For prediction, we want the vehicle's velocity if the ped is in one, otherwise we just grab the ped's velocity if they're on foot
						Vehicle pedVehicle = PED::GET_VEHICLE_PED_IS_IN(target_entity, 0);
						if (pedVehicle)
						{
							targetVelocity = ENTITY::GET_ENTITY_SPEED_VECTOR(pedVehicle, 1);
						}
						else
						{
							targetVelocity = ENTITY::GET_ENTITY_SPEED_VECTOR(target_entity, 1);
						}

						// Set up a corrected/predicted target position based on their velocity and the prediction multiplier
						targetVelocityPred = targetVelocity * predMult;
						
						//playerVelocity = ENTITY::GET_ENTITY_SPEED_VECTOR(self::ped, 1);

						aim_lock = PED::GET_PED_BONE_COORDS(target_entity,
						    g.weapons.aimbot.selected_bone,
						    targetVelocityPred.x,
						    targetVelocityPred.y + 0.05f, // Small manual adjustment since the head bone isn't optimal for aimbot
						    targetVelocityPred.z);
						
						*/

						// New aimbot code, credits to xiaoxiao921
						// Do a bit of converting from Vector3 to fvector3
						rage::fvector3 target_position;
						target_position.x = compedAimPos.x;
						target_position.y = compedAimPos.y;
						target_position.z = compedAimPos.z;

						uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;

						// Good info here about the layout of the gameplay camera director
						// https://www.unknowncheats.me/forum/grand-theft-auto-v/144028-grand-theft-auto-reversal-structs-offsets-625.html#post3249805

						uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C0);

						//uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C8);
						//uintptr_t cam_follow_ped_camera2 = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C0);
						//uintptr_t cam_follow_ped_camera3 = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x3'C0);

						rage::fvector3 actualCamPosition = get_camera_position();
						rage::fvector3 compedCamPosition;
						// Do a bit of converting from Vector3 to fvector3, also applying the player position prediction offset here
						compedCamPosition.x = actualCamPosition.x + playerPosChange.x;
						compedCamPosition.y = actualCamPosition.y + playerPosChange.y;
						compedCamPosition.z = actualCamPosition.z + playerPosChange.z;

						// Camera Handling
						// Note we HAVE to normalize this vector
						const auto camera_target = (target_position - compedCamPosition).normalize();

						// Game uses different cameras when on-foot vs. in vehicle, which is why using the gameplay cam is such a PITA, but for the aimbot it's fine to write to both locations
						reset_aim_vectors(cam_follow_ped_camera);
						*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40) = camera_target; // First person & sniper (on foot)
						*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0) = camera_target; // Third person

						/*
						if (!PED::IS_PED_IN_ANY_VEHICLE(self::ped, 0))
						{
							if (CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
							{
								*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40) = camera_target;
							}
							else
							{
								*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0) = camera_target;
							}
						}
						else
						{
							// Setting these vectors allows us to correct aim from inside a vehicle
							reset_aim_vectors(cam_follow_ped_camera);

							*reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0) = camera_target;
						}
						*/
						// Got rid of all the smoothing crap... I don't see any value for it in a game like GTA
						/*
						camera_target = aim_lock - CAM::GET_GAMEPLAY_CAM_COORD();

						constexpr float RADPI = 180.0f / std::numbers::pi;
						float magnitude       = std::hypot(camera_target.x, camera_target.y, camera_target.z);
						float camera_heading  = atan2f(camera_target.x, camera_target.y) * RADPI;

						float camera_pitch = asinf(camera_target.z / magnitude) * RADPI;
						float self_heading = ENTITY::GET_ENTITY_HEADING(self::ped);
						float self_pitch   = ENTITY::GET_ENTITY_PITCH(self::ped);

						if (camera_heading >= 0.0f && camera_heading <= 180.0f)
						{
							camera_heading = 360.0f - camera_heading;
						}
						else if (camera_heading <= -0.0f && camera_heading >= -180.0f)
						{
							camera_heading = -camera_heading;
						}

						if (CAM::GET_FOLLOW_PED_CAM_VIEW_MODE() == CameraMode::FIRST_PERSON)
						{
							CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(camera_heading - self_heading);
							CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(camera_pitch - self_pitch);
						}
						else
						{
							CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(camera_heading - self_heading);
							CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(camera_pitch - self_pitch, 1.0f);
						}
						*/

						// Store the current position for next tick's prediction
						prevTargetPosition = curTargetPosition;
						prevPlayerPosition = curPlayerPosition;
					}
				}
				// END Target Tracking
			}
			else
			{
				// Stage 3: Target Reset
				// If we're not free aiming, clear the target entity in case we were previously locked onto something
				target_entity      = 0;
				prevTargetPosition = {0.f, 0.f, 0.f};
				prevPlayerPosition = {0.f, 0.f, 0.f};
			}
		}

		virtual void on_disable() override
		{
			target_entity      = 0;
			prevTargetPosition = {0.f, 0.f, 0.f};
			prevPlayerPosition = {0.f, 0.f, 0.f};
		}

		static rage::fvector3 get_camera_position()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C0);
			return *reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x60);
		}

		static rage::fvector3 get_camera_aim_direction()
		{
			uintptr_t cam_gameplay_director = *g_pointers->m_gta.m_cam_gameplay_director;
			uintptr_t cam_follow_ped_camera = *reinterpret_cast<uintptr_t*>(cam_gameplay_director + 0x2'C0);

			uintptr_t cam_follow_ped_camera_metadata = *reinterpret_cast<uintptr_t*>(cam_follow_ped_camera + 0x10);
			bool is_first_person = *reinterpret_cast<float*>(cam_follow_ped_camera_metadata + 0x30) == 0.0f;
			// We only use 0x40 in first person on foot
			if (is_first_person)
			{
				// This is our first-person camera direction
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x40)->normalize();
			}
			else
			{
				// This is our third-person camera direction, and yes it is different from the first-person
				return reinterpret_cast<rage::fvector3*>(cam_follow_ped_camera + 0x3'D0)->normalize();
			}
		}

		// This is a total mystery but we need to call it to correct our in-vehicle aim
		static void reset_aim_vectors(uintptr_t camera)
		{
			uintptr_t camera_params = *(uintptr_t*)(camera + 0x10);
			{
				// So far it seems that 0x2AC is only -2.0f when free aiming in a vehicle
				if (*(float*)(camera_params + 0x2'AC) == -2.0f)
				{
					*(float*)(camera_params + 0x2'AC) = 0.0f;
					*(float*)(camera_params + 0x2'B0) = 0.0f;
					*(float*)(camera_params + 0x2'C0) = 111.0f;
					*(float*)(camera_params + 0x2'C4) = 111.0f;
				}

				if (*(float*)(camera_params + 0x1'30) == 8.0f)
				{
					*(float*)(camera_params + 0x1'30) = 111.0f; // def 8.0f
					*(float*)(camera_params + 0x1'34) = 111.0f; // def 10.0f
					*(float*)(camera_params + 0x4'CC) = 0.0f;   // def 4.0f

					if (*(float*)(camera_params + 0x4'9C) == 1.0f)
					{
						*(float*)(camera_params + 0x4'9C) = 0.0f; // def 1.0f
					}

					*(float*)(camera_params + 0x2'AC) = 0.0f; // def -3.0f
					*(float*)(camera_params + 0x2'B0) = 0.0f; // def -8.0f
				}
			}
		}
	};

	aimbot g_aimbot("aimbot", "VIEW_OVERLAY_AIMBOT", "BACKEND_LOOPED_WEAPONS_AIMBOT_DESC", g.weapons.aimbot.enable);

	bool_command
	    g_aimbot_on_player("aimatplayer", "PLAYER", "BACKEND_LOOPED_WEAPONS_AIM_AT_PLAYER_DESC", g.weapons.aimbot.on_player);
	bool_command
		g_aimbot_on_npc("aimatnpc", "NPC", "BACKEND_LOOPED_WEAPONS_AIM_AT_NPC_DESC", g.weapons.aimbot.on_npc);
	bool_command
	    g_aimbot_on_police("aimatpolice", "POLICE", "BACKEND_LOOPED_WEAPONS_AIM_AT_POLICE_DESC", g.weapons.aimbot.on_police);
	bool_command
		g_aimbot_on_enemy("aimatenemy", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY", "BACKEND_LOOPED_WEAPONS_AIM_AT_ENEMY_DESC", g.weapons.aimbot.on_enemy);
}

#pragma once
#include "backend/reactions/reaction.hpp"

namespace big
{
	inline struct g_reactions_t
	{
		reaction end_session_kick{"End Session Kick", "Blocked End Session Kick from {}"};
		reaction network_bail{"Network Bail", "Blocked Network Bail from {}"};
		reaction null_function_kick{"Null Function Kick", "Blocked Null Function Kick from {}"};
		reaction kick_vote{"Kick Vote", "{} is voting to kick you!"};
		reaction oom_kick{"OOM Kick", "Blocked OOM Kick from {}"};
		reaction crash{"Crash", "Blocked Crash from {}"};
		reaction stand_user_crash{"Crash", "Blocked Stand User Crash from {}"};
		reaction report{"Report", "Blocked Report from {}"};

		reaction gta_banner{"GTA Banner", "Blocked GTA Banner from {}"}; // please don't enable this
		reaction tse_freeze{"TSE Freeze", "Blocked TSE Freeze from {}"};
		reaction tse_sender_mismatch{"TSE Sender Mismatch", "Blocked TSE Sender Mismatch from {}"};

		reaction game_anti_cheat_modder_detection{"Anti-Cheat Modder Detection", "{} is detected as a modder by anti-cheat!"};
		reaction modder_detection{"Modder Detection", "{} is detected as a modder!"};

		reaction ceo_kick{"CEO Kick", "Blocked CEO Kick from {}"};
		reaction ceo_money{"CEO Money", "Blocked CEO Money from {}"};
		reaction clear_wanted_level{"Clear Wanted Level", "Blocked Clear Wanted Level from {}"};
		reaction fake_deposit{"Fake Deposit", "Blocked Fake Deposit from {}"};
		reaction force_mission{"Force Mission", "Blocked Force Mission from {}"};
		reaction force_teleport{"Force Teleport", "Blocked Force Teleport from {}"};
		reaction kick_from_interior{"Kick From Interior", "Blocked Kick From Interior from {}"};
		reaction mc_teleport{"MC Teleport", "Blocked MC Teleport from {}"};
		reaction personal_vehicle_destroyed{"Personal Vehicle Destroyed", "Blocked Personal Vehicle Destroyed from {}"};
		reaction destroy_personal_vehicle{"Destroy Personal Vehicle", "Blocked Destroy Personal Vehicle from {}"};
		reaction give_collectible{"Give Collectible", "Blocked Give Collectible from {}"};
		reaction remote_off_radar{"Remote Off Radar", "Blocked Remote Off Radar from {}"};
		reaction rotate_cam{"Rotate Cam", "Blocked Rotate Cam from {}"};
		reaction send_to_cutscene{"Send To Cutscene", "Blocked Send To Cutscene from {}"};
		reaction send_to_location{"Send To Location", "Blocked Send To Location from {}"};
		reaction send_to_interior{"Send To Interior", "Blocked Send To Interior from {}"};
		reaction sound_spam{"Sound Spam", "Blocked Sound Spam from {}"};
		reaction spectate_notification{"Spectate Notification", "Blocked Spectate Notification from {}"};
		reaction transaction_error{"Transaction Error", "Blocked Transaction Error from {}"};
		reaction vehicle_kick{"Vehicle Kick", "Blocked Vehicle Kick from {}"};
		reaction teleport_to_warehouse{"Teleport To Warehouse", "Blocked Teleport To Warehouse from {}"};
		reaction start_activity{"Start Activity", "Blocked Start Activity from {}"};
		reaction start_script{"Start Script", "Blocked Start Script from {}"};
		reaction trigger_business_raid{"Trigger Business Raid", "Blocked Trigger Business Raid from {}"};
		reaction turn_into_beast{"Turn Into Beast", "Blocked Turn Into Beast from {}"};
		reaction remote_wanted_level{"Remote Wanted Level", "Blocked Remote Wanted Level from {}"};
		reaction clear_ped_tasks{"Clear Ped Tasks", "Blocked Clear Ped Tasks from {}"};
		reaction remote_ragdoll{"Remote Ragdoll", "Blocked Remote Ragdoll from {}"};
		reaction report_cash_spawn{"Cash Spawn", "{} is spawning cash!"};
		reaction request_control_event{"Request Control Event", "Blocked Request Control Event from {}"};
		reaction spectate{"Spectate", "{} is spectating you"};

		// not shown in UI settings
		reaction remove_weapon{"Remove Weapon", "Blocked remove weapon from {}"};
		reaction spoofed_host_token{"Spoofed Host token", "{} has spoofed their host token."};
	} g_reactions{};
}

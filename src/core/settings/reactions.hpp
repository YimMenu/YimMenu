#pragma once
#include "backend/reactions/reaction.hpp"

namespace big
{
	inline struct g_reactions_t
	{
		reaction ceo_kick{"CEO Kick", "Blocked CEO Kick from %s", "%s tried to kick me from my CEO!"};
		reaction ceo_money{"CEO Money", "Blocked CEO Money from %s", "%s tried to drop money on me!"};
		reaction clear_wanted_level{"Clear Wanted Level", "Blocked Clear Wanted Level from %s", "%s tried to clear my wanted level!"};
		reaction crash{"Crash", "Blocked Crash from %s", "%s tried to crash me!"};
		reaction end_session_kick{"End Session Kick", "Blocked End Session Kick from %s", "%s tried to kick me out!"};
		reaction fake_deposit{"Fake Deposit", "Blocked Fake Deposit from %s", "%s tried to show me a fake money notification!"};
		reaction force_mission{"Force Mission", "Blocked Force Mission from %s", "%s tried to force me into a mission!"};
		reaction force_teleport{"Force Teleport", "Blocked Force Teleport from %s", "%s tried to teleport me!"};
		reaction gta_banner{"GTA Banner", "Blocked GTA Banner from %s", "Blocked GTA Banner from %s"}; // please don't enable this
		reaction kick_from_interior{"Kick From Interior", "Blocked Kick From Interior from %s", "%s tried to kick me from my interior!"};
		reaction mc_teleport{"MC Teleport", "Blocked MC Teleport from %s", "%s tried to teleport me!"};
		reaction network_bail{"Network Bail", "Blocked Network Bail from %s", "%s tried to kick me out!"};
		reaction personal_vehicle_destroyed{"Personal Vehicle Destroyed", "Blocked Personal Vehicle Destroyed from %s", "%s tried to show me a fake insurance notification!"};
		reaction remote_off_radar{"Remote Off Radar", "Blocked Remote Off Radar from %s", "%s tried to give me off radar!"};
		reaction rotate_cam{"Rotate Cam", "Blocked Rotate Cam from %s", "%s tried to mess with my camera!"};
		reaction send_to_cutscene{"Send To Cutscene", "Blocked Send To Cutscene from %s", "%s tried to force me into a cutscene!"};
		reaction send_to_location{"Send To Location", "Blocked Send To Location from %s", "%s tried to send me to Cayo Perico!"};
		reaction send_to_interior{"Send To Interior", "Blocked Send To Interior from %s", "%s tried to send me to an interior!"};
		reaction sound_spam{"Sound Spam", "Blocked Sound Spam from %s", "%s tried to spam annoying sounds at me!"};
		reaction spectate_notification{"Spectate Notification", "Blocked Spectate Notification from %s", "Blocked Spectate Notification from %s"};
		reaction give_collectible{"Give Collectible", "Blocked Give Collectible from %s", "%s tried to give me a collectible!"};
		reaction transaction_error{"Transaction Error", "Blocked Transaction Error from %s", "%s tried to show me a transaction error!"};
		reaction tse_freeze{"TSE Freeze", "Blocked TSE Freeze from %s", "%s tried to softlock my game!"};
		reaction tse_sender_mismatch{"TSE Sender Mismatch", "Blocked TSE Sender Mismatch from %s", "Blocked TSE Sender Mismatch from %s"};
		reaction vehicle_kick{"Vehicle Kick", "Blocked Vehicle Kick from %s", "%s tried to kick me from my vehicle!"};
		reaction teleport_to_warehouse{"Teleport To Warehouse", "Blocked Teleport To Warehouse from %s", "%s tried to teleport me to a warehouse!"};
		reaction start_activity{"Start Activity", "Blocked Start Activity from %s", "Blocked Start Activity from %s"};
		reaction start_script{"Start Script", "Blocked Start Script from %s", "Blocked Start Script from %s"};
		reaction null_function_kick{"Null Function Kick", "Blocked Null Function Kick from %s", "%s tried to kick me out!"};
		reaction destroy_personal_vehicle{"Destroy Personal Vehicle", "Blocked Destroy Personal Vehicle from %s", "%s tried to destroy my personal vehicle!"};
		reaction trigger_business_raid{"Trigger Business Raid", "Blocked Trigger Business Raid from %s", "%s tried to trigger a business raid!"};
		reaction turn_into_beast{"Turn Into Beast", "Blocked Turn Into Beast from %s", "%s tried to turn me into the beast!"};
		reaction remote_wanted_level{"Remote Wanted Level", "Blocked Remote Wanted Level from %s", "%s tried to give me a wanted level!"};
		reaction clear_ped_tasks{"Clear Ped Tasks", "Blocked Clear Ped Tasks from %s", "%s tried to freeze me!"};
		reaction remote_ragdoll{"Remote Ragdoll", "Blocked Remote Ragdoll from %s", "%s tried to ragdoll me!"};
		reaction kick_vote{"Kick Vote", "%s is voting to kick you!", "%s is voting to kick me!"};
		reaction report_cash_spawn{"Cash Spawn", "%s is spawning cash!", "%s is spawning cash!"};
		reaction modder_detection{"Modder Detection", "%s is detected as a modder!", "%s is detected as a modder!"};
		reaction game_anti_cheat_modder_detection{"Game Anti-Cheat Modder Detection", "%s is detected as a modder by the game anti-cheat!", "%s is detected as a modder by the game anti-cheat!"};
		reaction request_control_event{"Request Control Event", "Blocked Request Control Event from %s", "%s tried to mess with my vehicle!"};
		reaction report{"Report", "Blocked Report from %s", "%s tried to report me!"};
		reaction spectate{"Spectate", "%s is spectating you", "%s is spectating me!"};

		reaction gamer_instruction_kick{"Gamer Instruction Kick", "Blocked Gamer Instruction Kick from %s", "%s tried to kick me out!"};

		NLOHMANN_DEFINE_TYPE_INTRUSIVE(g_reactions_t, ceo_money, ceo_kick, clear_wanted_level, crash, end_session_kick, fake_deposit, force_mission, force_teleport, gta_banner, kick_from_interior, mc_teleport, network_bail, personal_vehicle_destroyed, remote_off_radar, rotate_cam, send_to_cutscene, send_to_location, sound_spam, spectate_notification, give_collectible, transaction_error, tse_freeze, tse_sender_mismatch, vehicle_kick, teleport_to_warehouse, trigger_business_raid, start_activity, start_script, null_function_kick, destroy_personal_vehicle, clear_ped_tasks, turn_into_beast, remote_wanted_level, remote_ragdoll, kick_vote, report_cash_spawn, modder_detection, game_anti_cheat_modder_detection, request_control_event, report, gamer_instruction_kick, send_to_interior, spectate)
	} g_reactions{};
}

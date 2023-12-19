#include "backend/looped/looped.hpp"
#include "util/vehicle.hpp"

#include <vehicle/CVehicleModelInfo.hpp>
#include <vehicle/CVehicleSeatMetadataMgr.hpp>
#include <vehicle/CVehicleDriveByMetadataMgr.hpp>
#include <vehicle/CGetPedSeatReturnClass.hpp>

#include "gta/weapons.hpp"

namespace big
{
	void looped::vehicle_allow_all_weapons()
	{
		CVehicle* vehicle_ptr = (CVehicle*)g_pointers->m_gta.m_handle_to_ptr(self::veh);

		if (vehicle_ptr == nullptr || g_local_player == nullptr)
			return;

		auto seat_info = g_pointers->m_gta.m_get_ped_seat(g_local_player->m_seat_info, g_local_player);

		if (seat_info == nullptr)
			return;

		if (g.vehicle.unlimited_weapons == false)
		{
			if (seat_info->anim_info)
			{
				for (auto drive_by_anim_info : seat_info->anim_info->m_drive_by_anim_infos)
				{
					if (drive_by_anim_info->m_weapon_groups->m_groups.size() == 7 && drive_by_anim_info->m_weapon_groups->m_groups.contains(GROUP_PISTOL))
					{
						drive_by_anim_info->m_weapon_groups->m_groups.clear();
						drive_by_anim_info->m_weapon_groups->m_groups.append({GROUP_PISTOL, GROUP_SMG});
					}
				}
			}
			return;
		}

		if (seat_info->anim_info == nullptr) //Should only occur in the R-88 and similar formula cars, so assume the user is in the driver's seat. Fix later, if other edge cases occur.
		{
			seat_info->anim_info = g_pointers->m_gta.m_vehicle_layout_metadata_mgr->m_drive_by_seat_defaults->m_driveby_standard_front_left;
		}

		for (auto drive_by_anim_info : seat_info->anim_info->m_drive_by_anim_infos)
		{
			if (drive_by_anim_info->m_weapon_groups->m_groups.size() != 7 && drive_by_anim_info->m_weapon_groups->m_groups.contains(GROUP_PISTOL))
			{
				drive_by_anim_info->m_weapon_groups->m_groups.clear();
				drive_by_anim_info->m_weapon_groups->m_groups.append({GROUP_PISTOL, GROUP_MG, GROUP_RIFLE, GROUP_SHOTGUN, GROUP_HEAVY, GROUP_SNIPER, GROUP_SMG});
			}
		}

		CVehicleModelInfo* vehicle_model_info = static_cast<CVehicleModelInfo*>(vehicle_ptr->m_model_info);
		vehicle_model_info->set_vehicle_model_flag(CVehicleModelInfoFlags::DRIVER_NO_DRIVE_BY, false);
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
		{
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE, 1);
		}
	}
}
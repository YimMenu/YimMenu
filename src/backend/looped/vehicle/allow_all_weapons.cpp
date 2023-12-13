#include "backend/looped/looped.hpp"
#include "util/vehicle.hpp"

#include <vehicle/CVehicleModelInfo.hpp>
#include <vehicle/CVehicleSeatMetadataMgr.hpp>
#include <vehicle/CVehicleDriveByMetadataMgr.hpp>

#include "gta/weapons.hpp"

namespace big
{
	void looped::vehicle_allow_all_weapons()
	{
		CVehicle* vehicle_ptr = (CVehicle*)g_pointers->m_gta.m_handle_to_ptr(self::veh);

		if (vehicle_ptr == nullptr)
			return;

		rage::atArray<Hash> one_handed_groups =
		    g_pointers->m_gta.m_driveby_metadata_mgr->m_drive_by_weapon_groups->m_drive_by_default->m_driveby_default_one_handed_weapon_group_names;

		if (g.vehicle.unlimited_weapons == false)
		{
			if (one_handed_groups.size() != 1)
			{
				rage::atArray<Hash> one_handed_groups;
				one_handed_groups.append(GROUP_PISTOL);
				g_pointers->m_gta.m_driveby_metadata_mgr->m_drive_by_weapon_groups->m_drive_by_default->m_driveby_default_one_handed_weapon_group_names = one_handed_groups;
			}
			return;
		}

		CVehicleModelInfo* vehicle_model_info = static_cast<CVehicleModelInfo*>(vehicle_ptr->m_model_info);

		auto num_seats = vehicle_model_info->m_vehicle_layout->m_max_seats;
		auto seat_info = vehicle_model_info->m_vehicle_layout->m_layout_metadata->m_seat_info;
		auto defaults  = g_pointers->m_gta.m_vehicle_layout_metadata_mgr->m_drive_by_seat_defaults;
		if (seat_info->m_front_left->m_drive_by_info != defaults->m_driveby_standard_front_left)
			seat_info->m_front_left->m_drive_by_info = defaults->m_driveby_standard_front_left;
		if (num_seats > 1 && seat_info->m_front_right->m_drive_by_info != defaults->m_driveby_standard_front_right)
			seat_info->m_front_right->m_drive_by_info = defaults->m_driveby_standard_front_right;
		if (num_seats > 2 && seat_info->m_rear_left->m_drive_by_info != defaults->m_driveby_standard_rear_left)
			seat_info->m_rear_left->m_drive_by_info = defaults->m_driveby_standard_rear_left;
		if (num_seats > 3 && seat_info->m_rear_right->m_drive_by_info != defaults->m_driveby_standard_rear_right)
			seat_info->m_rear_right->m_drive_by_info = defaults->m_driveby_standard_rear_right;

		vehicle_model_info->set_vehicle_model_flag(CVehicleModelInfoFlags::DRIVER_NO_DRIVE_BY, false);
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_AIM))
		{
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_FLY_MOUSE_CONTROL_OVERRIDE, 1);
		}

		if (g_pointers->m_gta.m_driveby_metadata_mgr->m_drive_by_weapon_groups->m_drive_by_default
		        ->m_driveby_default_one_handed_weapon_group_names.size() == 1)
		{
			one_handed_groups.append({GROUP_MG, GROUP_RIFLE, GROUP_SHOTGUN, GROUP_HEAVY, GROUP_SNIPER, GROUP_SMG});
			g_pointers->m_gta.m_driveby_metadata_mgr->m_drive_by_weapon_groups->m_drive_by_default->m_driveby_default_one_handed_weapon_group_names = one_handed_groups;
		}
	}
}
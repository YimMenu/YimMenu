#include "api/api.hpp"
#include "backend.hpp"
#include "fiber_pool.hpp"
#include "looped/looped.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "thread_pool.hpp"
#include "features.hpp"
#include "script_local.hpp"
#include "gta_util.hpp"

namespace big
{
	void backend::loop()
	{
		g.attempt_save();
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::system_screen_size();

			looped::system_update_pointers();
		}QUEUE_JOB_END_CLAUSE
		//	if (g_local_player != nullptr && !api::util::signed_in())
		//	{
			//	g_thread_pool->push([]
			//		{
			//			looped::api_login_session();
			//		});
		//	}
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_esp();
			looped::self_aim();
		}QUEUE_JOB_END_CLAUSE
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::tunables_disable_phone();
			looped::tunables_no_idle_kick();
			looped::tunables_casino_rig();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_frame_flags();
			looped::self_free_cam();
			looped::self_godmode();
			looped::self_off_radar();
			looped::self_police();
			looped::self_no_ragdoll();
			looped::self_super_run();
			looped::self_unlimited_ammo();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::player_specate();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_noclip();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::weapons_cage_gun();
			looped::weapons_delete_gun();
			looped::weapons_gravity_gun();
			looped::weapons_steal_vehicle_gun();
			looped::weapons_repair_gun();
			looped::weapons_vehicle_gun();
			looped::weapons_infinite_ammo();
			looped::weapons_infinite_mag();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::vehicle_despawn_bypass();
			looped::vehicle_god_mode();
			looped::vehicle_untargetable();
			looped::vehicle_horn_boost();
			looped::vehicle_speedo_meter();
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::vehicle_ls_customs();
		}QUEUE_JOB_END_CLAUSE
	}
}
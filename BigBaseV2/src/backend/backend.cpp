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
			looped::system_update_players();

			looped::system_update_pointers();
		}QUEUE_JOB_END_CLAUSE

		if (g_local_player != nullptr && !api::util::signed_in())
		{
			g_thread_pool->push([]
			{
				looped::api_login_session();
			});
		}

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::tunables_disable_phone();
			looped::tunables_no_idle_kick();
		}QUEUE_JOB_END_CLAUSE

			if (features::always_jackpot) {
				g_fiber_pool->queue_job([] {

					// Basically, Always win the slots, not worth mentioning it.

					gta_util::execute_as_script(RAGE_JOAAT("CASINO_SLOTS"), [] {
						auto slots_thread = gta_util::find_script_thread(RAGE_JOAAT("CASINO_SLOTS"));
						for (int i = 1; i <= 195; i++) {
							auto local1354 = script_local(slots_thread, 1354).at(1);
							int break_value = *local1354.at(i).as<int*>();
							if (break_value != 64) {
								*local1354.at(i).as<int*>() = 6;
							}
						}
						});
					});
			}

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::self_frame_flags();
			looped::self_free_cam();
			looped::self_godmode();
			looped::self_off_radar();
			looped::self_police();
			looped::self_no_ragdoll();
			looped::self_super_run();
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
		}QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			looped::vehicle_despawn_bypass();
			looped::vehicle_god_mode();
			looped::vehicle_horn_boost();
			looped::vehicle_speedo_meter();
		}QUEUE_JOB_END_CLAUSE
	}
}
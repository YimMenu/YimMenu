#include "backend/looped/looped.hpp"
#include "gta/enums.hpp"
#include "gta_util.hpp"
#include "script_function.hpp"
#include "script_local.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "util/math.hpp"
#include "util/scripts.hpp"

namespace big
{
	static bool bLastLsCustoms = false;
	static bool bModshopReady  = false;

	void looped::vehicle_ls_customs()
	{
		if (g.vehicle.ls_customs && g.vehicle.ls_customs != bLastLsCustoms)
		{
			g_fiber_pool->queue_job([] {
				scripts::request_script(RAGE_JOAAT("carmod_shop"));
				if (scripts::wait_till_loaded(RAGE_JOAAT("carmod_shop")))
				{
					HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 9);

					while (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 9))
						script::get_current()->yield();

					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("CommonMenu", false);
					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("MPShopSale", false);
					GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT("ShopUI_Title_Los_Santos_Car_Meet", false);

					// clang-format off
					while (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("CommonMenu") 
						|| !GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("MPShopSale") 
						|| !GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED("ShopUI_Title_Los_Santos_Car_Meet"))
						script::get_current()->yield();
					// clang-format on

					auto id = SYSTEM::START_NEW_SCRIPT_WITH_NAME_HASH(RAGE_JOAAT("carmod_shop"), 5050);
					if (!id)
						return;

					g.m_modshop_thread = gta_util::find_script_thread_by_id(id);
					if (!g.m_modshop_thread)
						return;

					g.m_modshop_thread->m_context.m_state = rage::eThreadState::unk_3;
					scr_functions::modshop_loop.populate_ip();
					scr_functions::setup_modshop.populate_ip();

					g_script_patcher_service->update();

					scr_functions::setup_modshop.call_latent(g.m_modshop_thread, gta_util::find_script_program(RAGE_JOAAT("carmod_shop")), {45, 0, 18, 0}, bModshopReady);
					*script_local(g.m_modshop_thread->m_stack, 730).at(446).as<int*>() = 2;
					*script_local(g.m_modshop_thread->m_stack, 2237).as<ControllerInputs*>() = ControllerInputs::INPUT_FRONTEND_LT;
				}
			});
			bLastLsCustoms = true;
		}
		else if (!g.vehicle.ls_customs && g.vehicle.ls_customs != bLastLsCustoms)
		{
			if (g.m_modshop_thread)
				g.m_modshop_thread->kill();

			GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED("CommonMenu");
			GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED("MPShopSale");
			GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED("ShopUI_Title_Los_Santos_Car_Meet");

			g.m_modshop_thread = nullptr;
			bLastLsCustoms     = false;
			bModshopReady      = false;
			g_script_patcher_service->update();
		}

		if (self::veh == 0 || SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(RAGE_JOAAT("maintransition")) > 0 || (!g.m_modshop_thread && bModshopReady))
		{
			g.vehicle.ls_customs = false;
			return;
		}

		if (g.vehicle.ls_customs && g.m_modshop_thread)
		{
			PAD::DISABLE_CONTROL_ACTION(0, (int)ControllerInputs::INPUT_VEH_CIN_CAM, true);

			if (*script_local(g.m_modshop_thread->m_stack, 2466).as<bool*>() && PAD::IS_CONTROL_JUST_PRESSED(2, (int)ControllerInputs::INPUT_FRONTEND_ACCEPT))
				g.vehicle.ls_customs = false;
		}

		if (g.vehicle.ls_customs && bModshopReady && g.m_modshop_thread && g.m_modshop_thread->m_stack)
		{
			*script_local(g.m_modshop_thread->m_stack, 2418).as<bool*>()           = false;
			*script_local(g.m_modshop_thread->m_stack, 730).at(638).as<int*>()     = -1;
			*script_local(g.m_modshop_thread->m_stack, 730).at(409).as<Vehicle*>() = self::veh;

			if (*script_local(g.m_modshop_thread->m_stack, 730).at(446).as<int*>() == 0)
				*script_local(g.m_modshop_thread->m_stack, 730).at(446).as<int*>() = 2;

			scr_functions::modshop_loop.call(g.m_modshop_thread, gta_util::find_script_program(RAGE_JOAAT("carmod_shop")), {});
		}
	}
}
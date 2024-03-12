#pragma once
#include "core/scr_globals.hpp"
#include "fiber_pool.hpp"
#include "native_hooks.hpp"
#include "natives.hpp"
#include "util/scripts.hpp"

namespace big
{
	namespace creator
	{
		void GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(rage::scrNativeCallContext* src)
		{
			const auto hash = src->get_arg<rage::joaat_t>(0);

			if (hash == "freemode"_J || hash == "main"_J)
			{
				src->set_return_value(0);
				return;
			}

			src->set_return_value(SCRIPT::GET_NUMBER_OF_THREADS_RUNNING_THE_SCRIPT_WITH_THIS_HASH(hash));
		}

		void GET_ENTITY_MODEL(rage::scrNativeCallContext* src)
		{
			Entity entity = src->get_arg<Entity>(0);
			Hash model    = ENTITY::GET_ENTITY_MODEL(entity);

			if (entity == self::ped)
			{
				if (model != "mp_m_freemode_01"_J && model != "mp_f_freemode_01"_J)
					model = "mp_m_freemode_01"_J;
			}

			src->set_return_value<Hash>(std::move(model));
		}

		void GET_USED_CREATOR_BUDGET(rage::scrNativeCallContext* src)
		{
			if (g.ugc.infinite_model_memory)
				src->set_return_value<float>(0);
			else
				src->set_return_value<float>(STREAMING::GET_USED_CREATOR_BUDGET());
		}
	}
}

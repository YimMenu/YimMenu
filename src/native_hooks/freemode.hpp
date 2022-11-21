#pragma once

namespace big
{
	namespace freemode
	{
		inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
		{
			LOG(INFO) << "NETWORK_BAIL prevented";
		}

		inline void IS_PLAYER_PLAYING(rage::scrNativeCallContext* src)
		{
			// block undead OTR
			if (g->session.decloak_players && src->get_arg<Player>(0) != self::id)
				src->set_return_value<BOOL>(TRUE);
			else
				src->set_return_value<BOOL>(PLAYER::IS_PLAYER_PLAYING(src->get_arg<Player>(0)));
		};

		inline void SET_ENTITY_VISIBLE(rage::scrNativeCallContext* src)
		{
			auto entity = src->get_arg<Entity>(0);
			auto toggle = src->get_arg<bool>(1);
			auto outfit = src->get_arg<bool>(2);

			if (g->self.invisibility && entity == self::ped && toggle)
				return;
			else
				ENTITY::SET_ENTITY_VISIBLE(entity, toggle, outfit);
		}
	}
}
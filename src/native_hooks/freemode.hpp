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

		void SET_BIGMAP_ACTIVE(rage::scrNativeCallContext* src)
		{
			if (!g->m_mission_creator_thread)
				HUD::SET_BIGMAP_ACTIVE(src->get_arg<BOOL>(0), src->get_arg<BOOL>(1));
		};

		void SET_BLIP_DISPLAY(rage::scrNativeCallContext* src)
		{
			if ((!g->m_mission_creator_thread) || src->get_arg<Blip>(0) != HUD::GET_MAIN_PLAYER_BLIP_ID())
				HUD::SET_BLIP_DISPLAY(src->get_arg<Blip>(0), src->get_arg<BOOL>(1));
		};
	}
}
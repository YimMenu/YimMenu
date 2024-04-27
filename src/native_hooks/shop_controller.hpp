#pragma once
#include "native_hooks.hpp"
#include "core/scr_globals.hpp"

namespace big
{
	namespace shop_controller
	{
		static inline std::string format_money(int64_t amount)
		{
			std::stringstream ss;
			ss.imbue(std::locale("en_US.UTF-8"));
			ss << std::put_money(static_cast<long double>(amount) * 100, false);
			std::string money = ss.str();
			return money.substr(0, money.size() - 3);
		}

		void SET_WARNING_MESSAGE_WITH_HEADER(rage::scrNativeCallContext* src)
		{
			if (auto entry_line = src->get_arg<const char*>(1); !strcmp(entry_line, "CTALERT_F_2"))
			{
				if (g.notifications.transaction_rate_limit.log)
					LOG(WARNING) << "Received transaction rate limit";
				if (g.notifications.transaction_rate_limit.notify)
					g_notification_service.push_warning("TRANSACTION_RATE_LIMIT"_T.data(), "TRANSACTION_RATE_LIMIT_MESSAGE"_T.data());

				*scr_globals::transaction_overlimit.as<PBOOL>() = FALSE;

				return;
			}

			HUD::SET_WARNING_MESSAGE_WITH_HEADER(src->get_arg<const char*>(0), src->get_arg<const char*>(1), src->get_arg<int>(2), src->get_arg<const char*>(3), src->get_arg<BOOL>(4), src->get_arg<Any>(5), src->get_arg<Any*>(6), src->get_arg<Any*>(7), src->get_arg<BOOL>(8), src->get_arg<Any>(9));
		}

		void SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(rage::scrNativeCallContext* src)
		{
			if (g.window.gui.format_money)
			{
				auto arg0         = src->get_arg<int>(0);
				Hash casino_chips = self::char_index ? "MP1_CASINO_CHIPS"_J : "MP0_CASINO_CHIPS"_J;
				int player_chips;

				STATS::STAT_GET_INT(casino_chips, &player_chips, -1);
				if (arg0 == player_chips && player_chips >= 1000)
				{
					auto chips_format = format_money(player_chips);
					return GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(chips_format.c_str());
				}
			}

			GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(src->get_arg<int>(0));
		}
	}
}

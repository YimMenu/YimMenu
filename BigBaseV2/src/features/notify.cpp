#include "notify.hpp"

namespace big::features::notify
{
	void above_map(const char* text)
	{
		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}
}
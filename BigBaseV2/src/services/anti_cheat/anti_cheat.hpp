#include "anti_cheat_service.hpp"

namespace big
{
	anti_cheat_service::anti_cheat_service()
	{
		g_anti_cheat_service = this;
	}

	anti_cheat_service::~anti_cheat_service()
	{
		g_anti_cheat_service = nullptr;
	}



	bool anti_cheat_service::is_modder(Player player)
	{

		return false;
	}
}
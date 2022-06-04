#pragma once
#include "player_service.hpp"

namespace big
{
	class friends_service final
	{
	public:
		friends_service();
		virtual ~friends_service();

		static bool is_friend(const player_ptr& plyr);
	};

	inline friends_service* g_friends_service{};
}
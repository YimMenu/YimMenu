#pragma once

namespace big
{
	class friends_service final
	{
	public:
		friends_service();
		~friends_service();

		friends_service(const friends_service&)                = delete;
		friends_service(friends_service&&) noexcept            = delete;
		friends_service& operator=(const friends_service&)     = delete;
		friends_service& operator=(friends_service&&) noexcept = delete;

		[[nodiscard]] static bool is_friend(int64_t rockstar_id);
		[[nodiscard]] static bool is_friend(CNetGamePlayer* net_player);
	};

	inline friends_service* g_friends_service{};
}
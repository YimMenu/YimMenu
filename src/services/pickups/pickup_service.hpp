#pragma once

namespace big
{
	class pickup_service final
	{
	public:
		pickup_service();
		~pickup_service();

		pickup_service(const pickup_service&)                = delete;
		pickup_service(pickup_service&&) noexcept            = delete;
		pickup_service& operator=(const pickup_service&)     = delete;
		pickup_service& operator=(pickup_service&&) noexcept = delete;

		void give_player_ammo(const Player player) const;
		void give_player_armour(const Player player) const;
		void give_player_health(const Player player) const;
		void give_player_weapons(const Player player) const;

		void give_ammo(const int targets) const;
		void give_armour(const int targets) const;
		void give_health(const int targets) const;
		void give_weapons(const int targets) const;
	};

	inline pickup_service* g_pickup_service{};
}
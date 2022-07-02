#include "pickup_service.hpp"
#include "pickup_helper.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	pickup_service::pickup_service()
	{
		g_pickup_service = this;
	}

	pickup_service::~pickup_service()
	{
		g_pickup_service = nullptr;
	}

	void pickup_service::give_player_ammo(const Player player) const
	{
		give_ammo(1 << player);
	}

	void pickup_service::give_player_armour(const Player player) const
	{
		give_armour(1 << player);
	}

	void pickup_service::give_player_health(const Player player) const
	{
		give_health(1 << player);
	}

	void pickup_service::give_player_weapons(const Player player) const
	{
		give_weapons(1 << player);
	}

	void pickup_service::give_ammo(const int targets) const
	{
		for (const auto& [_, hash] : rewards::ammo)
		{
			g_pointers->m_give_pickup_rewards(targets, hash);

			script::get_current()->yield(20ms);
		}
	}

	void pickup_service::give_armour(const int targets) const
	{
		g_pointers->m_give_pickup_rewards(targets, rewards::misc.at("ARMOUR"));
	}

	void pickup_service::give_health(const int targets) const
	{
		g_pointers->m_give_pickup_rewards(targets, rewards::misc.at("HEALTH"));
	}

	void pickup_service::give_weapons(const int targets) const
	{
		for (const auto& [_, hash] : rewards::weapons)
		{
			g_pointers->m_give_pickup_rewards(targets, hash);

			script::get_current()->yield(20ms);
		}
	}
}

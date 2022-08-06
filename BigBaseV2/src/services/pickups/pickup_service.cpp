#include "pickup_service.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/gta_data/gta_data_service.hpp"

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
		for (const auto& weapon : g_gta_data_service->get_weapon_arr())
		{
			if (weapon.reward_ammo_hash != 0 || weapon.throwable)
			{
				g_pointers->m_give_pickup_rewards(targets, weapon.reward_ammo_hash);
				script::get_current()->yield(20ms);
			}
		}
	}

	void pickup_service::give_armour(const int targets) const
	{
		g_pointers->m_give_pickup_rewards(targets, RAGE_JOAAT("REWARD_ARMOUR"));
		script::get_current()->yield(20ms);
	}

	void pickup_service::give_health(const int targets) const
	{
		g_pointers->m_give_pickup_rewards(targets, RAGE_JOAAT("REWARD_HEALTH"));
		script::get_current()->yield(20ms);
		g_pointers->m_give_pickup_rewards(targets, RAGE_JOAAT("REWARD_HEALTH"));
		script::get_current()->yield(20ms);
	}

	void pickup_service::give_weapons(const int targets) const
	{
		for (const auto& weapon : g_gta_data_service->get_weapon_arr())
		{
			if (weapon.reward_hash != 0)
			{
				g_pointers->m_give_pickup_rewards(targets, weapon.reward_hash);
				script::get_current()->yield(20ms);
			}
		}

		g_pointers->m_give_pickup_rewards(targets, RAGE_JOAAT("REWARD_PARACHUTE"));
		script::get_current()->yield(20ms);
	}
}

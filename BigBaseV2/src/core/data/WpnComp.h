#pragma once

struct WpnUpgArrStruct
{
	Hash WeaponHash;
	std::string UpgradeHash;
};

namespace WpnUpg
{
	namespace WpnUpgArrays
	{
		extern const std::vector<WpnUpgArrStruct> MaxUpgradeWeapon;
	}
}
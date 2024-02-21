#pragma once

// https://github.com/Parik27/V.Rainbomizer/blob/0c70868626411a1d30483339003b9985b0ff1c98/lib/CItemInfo.hh#L62
class CWeaponInfoManager
{
public:
	char field_0x0[16][4];
	rage::atArray<CWeaponInfo*> m_item_infos;
};
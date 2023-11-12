#pragma once

class CNetGamePlayer;
enum class eNetObjType;

namespace big
{
	inline CNetGamePlayer* m_syncing_player  = nullptr;
	inline eNetObjType m_syncing_object_type = (eNetObjType)-1;
}
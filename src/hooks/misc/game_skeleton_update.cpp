#include "hooking.hpp"

namespace big
{
#pragma pack(push, 8)
	struct game_skeleton_item
	{
		virtual ~game_skeleton_item() = default;
		virtual void run()                = 0; // 0x08
		
		char m_pad[0x8];            // 0x08
		uint32_t m_hash;            // 0x10
		game_skeleton_item* m_next; // 0x18
	};
	static_assert(sizeof(game_skeleton_item) == 0x20);
#pragma pack(pop)

	void hooks::game_skeleton_update(__int64 update_group)
	{
		for (auto item = *(game_skeleton_item**)(update_group + 0x20); item; item = item->m_next)
			if (item->m_hash != 0xA0F39FB6)
				item->run();
	}
}

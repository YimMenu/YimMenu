#include "hooking.hpp"

// rage::gameSkeleton -> modes (does not derive from updateBase?) -> groups -> items

namespace big
{
	class game_skeleton_update_group;
	class game_skeleton_item;

#pragma pack(push, 8)
	struct game_skeleton_update_mode
	{
		int m_type;                           // 0x00
		game_skeleton_update_group* m_groups; // 0x08
		game_skeleton_update_mode* m_next;    // 0x10
	};
	static_assert(sizeof(game_skeleton_update_mode) == 0x18);

	struct game_skeleton_update_group
	{
		virtual ~game_skeleton_update_group() = default;
		virtual void run()            = 0; // 0x08

		char pad[0x10];                     // 0x08
		game_skeleton_update_group* m_next; // 0x18	
		game_skeleton_item* m_items;        // 0x20
	};
	static_assert(sizeof(game_skeleton_update_group) == 0x28);

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

	void hooks::game_skeleton_update(__int64 skeleton, int type)
	{
		for (auto mode = *(game_skeleton_update_mode**)(skeleton + 0x140); mode; mode = mode->m_next)
		{
			if (mode && mode->m_type == type)
			{
				for (auto group = mode->m_groups; group; group = group->m_next)
				{
					for (auto item = group->m_items; item; item = item->m_next)
					{
						if (item->m_hash != 0xA0F39FB6)
						{
							item->run();
						}
					}
				}

			    break;
			}
		}
	}
}

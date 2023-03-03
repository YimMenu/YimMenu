#pragma once

class CNetGamePlayer;

namespace rage
{
	class netArrayHandlerBase;
}

class CGameArrayMgr
{
public:
	char padding[0x40];
	rage::netArrayHandlerBase* m_start;
};
static_assert(sizeof(CGameArrayMgr) == 0x48);

namespace rage
{
	class netSyncDataUnit_Dynamic
	{
	public:
		virtual ~netSyncDataUnit_Dynamic() = default;// 0x00

		virtual void _0x08() = 0;

		virtual void _0x10() = 0;

		virtual void set_data_counter(int index, uint16_t counter) = 0;// 0x18

		virtual void reset_data_counter(int index) = 0;// 0x20

		// ...

		int m_players_need_ack; // 0x08
		int m_players_need_sync;// 0x0C
	};

	class netSyncData_Dynamic
	{
	public:
		virtual ~netSyncData_Dynamic() = default;// 0x00

		virtual rage::datBitBuffer* _0x08() = 0;

		virtual rage::datBitBuffer* _0x10() = 0;

		virtual int get_num_receivers() = 0;// 0x18

		virtual int _0x20() = 0;

		virtual void _0x28() = 0;// same as get_sync_unit_for_element

		virtual netSyncDataUnit_Dynamic* get_sync_unit_for_element(uint32_t element) = 0;// 0x30

		// ...
	};

	class netArrayHandlerBase
	{
	public:
		virtual ~netArrayHandlerBase() = default;// 0x00

		virtual void _0x08() = 0;

		virtual void _0x10() = 0;

		virtual void _0x18() = 0;

		virtual void _0x20() = 0;

		virtual void _0x28() = 0;

		virtual void _0x30() = 0;

		virtual void _0x38() = 0;//

		virtual void _0x40() = 0;//

		virtual int _0x48(CNetGamePlayer* player, int max_size, uint32_t* a3, uint32_t* a4) = 0;//

		virtual int get_size(CNetGamePlayer* player, int max_size, uint32_t element) = 0;// 0x50

		virtual int pack_array_data(CNetGamePlayer* player, rage::datBitBuffer* bit_buffer, uint16_t counter, uint32_t* elem_start, bool silent) = 0;// 0x58

		virtual void _0x60() = 0;//

		virtual bool _0x68(CNetGamePlayer* player) = 0;// is_player_out_of_scope or something like that

		virtual void _0x70() = 0;//

		virtual bool can_send_update(CNetGamePlayer* player) = 0;// 0x78

		virtual void _0x80() = 0;//

		virtual void _0x88() = 0;//

		virtual void* get_identifier() = 0;// 0x90

		virtual void* _0x98() = 0;// same as get_identifier

		virtual void _0xA0() = 0;//

		virtual bool can_verify_array_data() = 0;// 0xA8

		virtual void _0xB0() = 0;//

		virtual void _0xB8() = 0;//

		virtual void should_sync_element(uint32_t element) = 0;// 0xC0

		virtual void _0xC8() = 0;//

		virtual void _0xD0() = 0;//

		virtual bool are_all_elements_in_scope() = 0;// 0xD8

		virtual void _0xE0() = 0;//

		virtual void verify_array_data() = 0;// 0xE8

		virtual void _0xF0() = 0;//

		virtual char* get_name() = 0;// 0xF8

		virtual bool is_local_player_owner_of_array() = 0;// 0x100

		virtual CNetGamePlayer* get_owner_of_array() = 0;// 0x108

		virtual void _0x110() = 0;

		virtual uint32_t get_array_hash() = 0;

		virtual int _0x120() = 0;// gets array size for hashing

		virtual netSyncData_Dynamic* _0x128() = 0;// same as get_dynamic_sync_data

		virtual netSyncData_Dynamic* get_dynamic_sync_data() = 0;// 0x130

		virtual void _0x138() = 0;

		virtual bool is_element_in_scope(uint32_t element, CNetGamePlayer* player) = 0;// 0x140

		virtual int get_receiver_index_from_player(CNetGamePlayer*) = 0;// 0x148

		virtual void _0x150() = 0;

		virtual void _0x158() = 0;

		// pasted from fivem
		virtual bool is_element_empty(uint32_t element) = 0;// 0x160

		virtual void set_element_empty(uint32_t element) = 0;// 0x168

		virtual void write_element_index(rage::datBitBuffer& buffer, uint32_t) = 0;// 0x170

		virtual void read_element_index(rage::datBitBuffer& buffer, uint32_t&) = 0;// 0x178

		virtual bool is_valid_index(uint32_t) = 0;// 0x180

		virtual void recalculate_dirty_elements() = 0;// 0x188

		virtual void reset_element_sync_data(uint32_t element) = 0;// 0x190

		virtual void do_post_read_processing() = 0;// 0x198

		virtual void do_post_element_read_processing(uint32_t element) = 0;// 0x1A0

		virtual bool can_apply_element_data(uint32_t element, const rage::netPlayer& sender, bool force) = 0;// 0x1A8

		virtual void extract_data_for_serializing(uint32_t elem) = 0;// 0x1B0

		virtual void write_element(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0;// 0x1B8

		virtual void read_element(rage::datBitBuffer& buffer, uint32_t elem, void* logger) = 0;// 0x1C0

		virtual void log_element(uint32_t elem, void* logger) = 0;// 0x1C8

		virtual uint32_t get_current_element_size_in_bits(uint32_t elem) = 0;// 0x1D0

		virtual void apply_element_data(uint32_t element, const rage::netPlayer& sender) = 0;// 0x1D8

		virtual void _0x1E0() = 0;

		virtual void _0x1E8(bool) = 0;// very important! changes send function to use some kind of cached buffer that prevents us from modifing array data per player

		void* m_something;// 0x10

		netArrayHandlerBase* m_next;// 0x18

		uint8_t m_pad[100 - 0x18];// +8
		uint32_t m_hash;
		uint8_t m_pad2[244 - 104];// +8
		uint16_t m_index;         // 244
		uint16_t m_count;         // 246
		uint8_t m_max_elements;   // 248
		uint8_t m_element_size;   // 249
		uint8_t m_element_size_2; // 250
		uint8_t m_pad3[13];       // 251
		void* m_array;            // 264

#if 0
		static inline netArrayHandlerBase* get_by_data(void* data)
		{
			if (auto array_mgr = *big::g_pointers->m_game_array_mgr)
			{
				if (auto handler = array_mgr->m_start)
				{
					do
					{
						if (handler->m_array == data)
							return handler;
					}
					while (handler = handler->m_next);
				}
			}

			return nullptr;
		}
#endif
	};

	static_assert(sizeof(netArrayHandlerBase) == 272);
}
#pragma once
#include <cstdint>
#include "pointers.hpp"
#include "fwddec.hpp"

#pragma pack(push, 1)
namespace rage
{
	class netPlayer;
	class datBitBuffer
	{
	public:
		inline datBitBuffer(void* data, uint32_t size)
		{
			m_data = data;
			m_f8 = 0;
			m_maxBit = size * 8;
			m_unkBit = 0;
			m_curBit = 0;
			m_unk2Bit = 0;
			m_flagBits = 0;
		}

		inline uint32_t GetPosition()
		{
			return m_unkBit;
		}

		inline bool Seek(uint32_t bits)
		{
			if (bits >= 0)
			{
				uint32_t length = (m_flagBits & 1) ? m_maxBit : m_curBit;

				if (bits <= length)
				{
					m_unkBit = bits;
				}
			}

			return false;
		}

		inline int GetDataLength()
		{
			int leftoverBit = (m_curBit % 8) ? 1 : 0;

			return (m_curBit / 8) + leftoverBit;
		}

		inline bool ReadByte(uint8_t* integer, int bits)
		{
			uint32_t read;
			if (big::g_pointers->m_read_bitbuf_dword(this, &read, bits))
			{
				*integer = read;
				return true;
			}
			return false;
		}

		inline bool ReadWord(uint16_t* integer, int bits)
		{
			uint32_t read;
			if (big::g_pointers->m_read_bitbuf_dword(this, &read, bits))
			{
				*integer = read;
				return true;
			}
			return false;
		}

		inline bool ReadDword(uint32_t* integer, int bits)
		{
			return big::g_pointers->m_read_bitbuf_dword(this, integer, bits);
		}

		inline bool ReadInt32(int32_t* integer, int bits)
		{
			int32_t v8;
			int32_t v9;
			if (ReadDword((uint32_t*)&v8, 1u) && ReadDword((uint32_t*)&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -v8);
				return true;
			}
			return false;
		}

		inline bool ReadQWord(uint64_t* integer, int bits)
		{
			if (bits <= 32)
			{
				uint32_t v10{};
				if (ReadDword(&v10, bits))
				{
					*integer = v10;
					return true;
				}
				return false;
			}
			else
			{
				uint32_t v10{}, v11{};
				if (ReadDword(&v11, 32u) && ReadDword(&v10, bits - 32u))
				{
					*integer = v11 | ((uint64_t)v10 << 32);
					return true;
				}
				return false;
			}
		}

		inline bool ReadInt64(int64_t* integer, int bits)
		{
			uint32_t v8;
			uint64_t v9;
			if (ReadDword(&v8, 1u) && ReadQWord(&v9, bits - 1))
			{
				*integer = v8 + (v9 ^ -(int64_t)v8);
				return true;
			}
			return false;
		}

		inline bool ReadArray(PVOID array, int size)
		{
			return big::g_pointers->m_read_bitbuf_array(this, array, size, 0);
		}

	public:
		void* m_data; //0x0000
		uint32_t m_f8; //0x0008
		uint32_t m_maxBit; //0x000C
		uint32_t m_unkBit; //0x0010
		uint32_t m_curBit; //0x0014
		uint32_t m_unk2Bit; //0x0018
		uint8_t m_flagBits; //0x001C
	};

	class netGameEvent
	{
	public:
		virtual ~netGameEvent() = default;

		virtual const char* get_name() { return 0; };
		virtual bool is_in_scope(netPlayer* player) { return 0; };
		virtual bool time_to_resend(std::uint32_t time) { return 0; };
		virtual bool can_change_scope() { return 0; };

		virtual void prepare_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};
		virtual void handle_data(datBitBuffer* buffer, netPlayer* source_player, netPlayer* target_player) {};

		virtual bool decide(netPlayer* source_player, netPlayer* target_player) { return 0; };

		virtual void prepare_reply(datBitBuffer* buffer, netPlayer* reply_player) {};
		virtual void handle_reply(datBitBuffer* buffer, netPlayer* souce_player) {};

		virtual void prepare_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};
		virtual void handle_extra_data(datBitBuffer* buffer, bool is_reply, netPlayer* player, netPlayer* player2) {};

	private:
		virtual void unk_0x60() {};
		virtual void unk_0x68() {};
		virtual void unk_0x70() {};
		virtual void unk_0x78() {};
	public:
		virtual bool operator==(netGameEvent const& other) { return 0; };
		virtual bool operator!=(netGameEvent const& other) { return 0; };

		virtual bool must_persist() { return 0; };
		virtual bool must_persist_when_out_of_scope() { return 0; };
		virtual bool has_timed_out() { return 0; };
	public:
		std::uint16_t m_id;          // 0x08
		bool m_requires_reply;       // 0x0A
	private:
		char m_padding1[0x05];       // 0x0B
	public:
		netPlayer* m_source_player;  // 0x10
		netPlayer* m_target_player;  // 0x18
		std::uint32_t m_resend_time; // 0x20
	private:
		std::uint16_t m_0x24;        // 0x24
		std::uint8_t m_0x26;         // 0x26
		std::uint8_t m_0x27;         // 0x27
		std::uint32_t m_0x28;        // 0x28
		char m_padding2[0x04];
	};
}

class CScriptedGameEvent : public rage::netGameEvent
{
public:
	char m_padding[0x40];      // 0x30
	std::int64_t m_args[54];   // 0x70
	std::uint32_t m_bitset;    // 0x220
	std::uint32_t m_args_size; // 0x224
};

class CNetworkIncrementStatEvent : public rage::netGameEvent
{
public:
	Hash m_stat;    // 0x30
	std::uint32_t m_ammount; // 0x34
};
#pragma pack(pop)
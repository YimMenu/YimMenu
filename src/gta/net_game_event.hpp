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
		datBitBuffer(uint8_t* data, uint32_t size) {
			m_data = data;
			m_bitOffset = 0;
			m_maxBit = size * 8;
			m_bitsRead = 0;
			m_curBit = 0;
			m_highestBitsRead = 0;
			m_flagBits = 0;
		}
		uint32_t GetPosition() {
			return m_bitsRead;
		}
		bool Seek(uint32_t bits) {
			if (bits >= 0) {
				uint32_t length = (m_flagBits & 1) ? m_maxBit : m_curBit;
				if (bits <= length)
					m_bitsRead = bits;
			}
			return false;
		}
		bool WriteBool(bool integer) {
			return big::g_pointers->m_write_bitbuf_bool(this, integer, 1);
		}
		bool ReadBool(bool* integer) {
			return big::g_pointers->m_read_bitbuf_bool(this, integer, 1);
		}
		bool ReadPeerId(uint64_t* integer) {
			return this->ReadQWord(integer, 0x32);
		}
		uint64_t ReadBits(size_t numBits) {
			auto const totalBits = (m_flagBits & 1) ? m_maxBit : m_curBit;
			if ((m_flagBits & 2) || m_bitsRead + numBits > totalBits)
				return 0;
			auto const bufPos = m_bitsRead + m_bitOffset;
			auto const initialBitOffset = bufPos & 0b111;
			auto const start = &m_data[bufPos / 8];
			auto const next = &start[1];
			auto result = (start[0] << initialBitOffset) & 0xff;
			for (auto i = 0; i < ((numBits - 1) / 8); i++) {
				result <<= 8;
				result |= next[i] << initialBitOffset;
			}
			if (initialBitOffset)
				result |= next[0] >> (8 - initialBitOffset);
			m_bitsRead += static_cast<uint32_t>(numBits);
			if (m_bitsRead > m_highestBitsRead)
				m_highestBitsRead = m_bitsRead;
			return result >> ((8 - numBits) % 8);
		}
		int GetDataLength() {
			int leftoverBit = (m_curBit % 8) ? 1 : 0;
			return (m_curBit / 8) + leftoverBit;
		}
		bool ReadString(char* string, int bits) {
			return big::g_pointers->m_read_bitbuf_string(this, string, bits);
		}
		bool WriteByte(uint8_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_dword(this, integer, bits);
		}
		bool ReadByte(uint8_t* integer, int bits) {
			uint32_t read;
			if (big::g_pointers->m_read_bitbuf_dword(this, &read, bits)) {
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteWord(uint16_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_dword(this, integer, bits);
		}
		bool ReadWord(uint16_t* integer, int bits) {
			uint32_t read;
			if (big::g_pointers->m_read_bitbuf_dword(this, &read, bits)) {
				*integer = read;
				return true;
			}
			return false;
		}
		bool WriteDword(uint32_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_dword(this, integer, bits);
		}
		bool ReadDword(uint32_t* integer, int bits) {
			return big::g_pointers->m_read_bitbuf_dword(this, integer, bits);
		}
		bool WriteInt32(int32_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_int32(this, integer, bits);
		}
		bool ReadInt32(int32_t* integer, int bits) {
			int32_t v8;
			int32_t v9;
			if (ReadDword((uint32_t*)&v8, 1u) && ReadDword((uint32_t*)&v9, bits - 1)) {
				*integer = v8 + (v9 ^ -v8);
				return true;
			}
			return false;
		}
		bool WriteQWord(uint64_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_qword(this, integer, bits);
		}
		bool ReadQWord(uint64_t* integer, int bits) {
			if (bits <= 32) {
				uint32_t v10;
				if (ReadDword(&v10, bits)) {
					*integer = v10;
					return true;
				}
			}
			else {
				uint32_t v10, v11;
				if (ReadDword(&v11, 32u) && ReadDword(&v10, bits - 32u)) {
					*integer = v11 | ((uint64_t)v10 << 32);
					return true;
				}
			}
			return false;
		}
		bool WriteInt64(int64_t integer, int bits) {
			return big::g_pointers->m_write_bitbuf_int64(this, integer, bits);
		}
		bool ReadInt64(int64_t* integer, int bits) {
			uint32_t v8;
			uint64_t v9;
			if (ReadDword(&v8, 1u) && ReadQWord(&v9, bits - 1)) {
				*integer = v8 + (v9 ^ -(int64_t)v8);
				return true;
			}
			return false;
		}
		bool WriteArray(uint8_t* array, int size) {
			return big::g_pointers->m_write_bitbuf_array(this, array, size, 0);
		}
		bool ReadArray(PVOID array, int size) {
			return big::g_pointers->m_read_bitbuf_array(this, array, size, 0);
		}
	public:
		uint8_t* m_data; //0x0000
		uint32_t m_bitOffset; //0x0008
		uint32_t m_maxBit; //0x000C
		uint32_t m_bitsRead; //0x0010
		uint32_t m_curBit; //0x0014
		uint32_t m_highestBitsRead; //0x0018
		uint8_t m_flagBits; //0x001C
	};

	enum class eNetMessage : uint32_t {
		CMsgInvalid = 0xFFFFF,
		CMsgSessionAcceptChat = 0x62,
		CMsgStartMatchCmd = 0x2D,
		CMsgSetInvitableCmd = 0x1F,
		CMsgSessionMemberIds = 0x23,
		CMsgRequestGamerInfo = 0x54,
		CMsgRemoveGamersFromSessionCmd = 0x53,
		CMsgNotMigrating = 0x35,
		CMsgMigrateHostResponse = 0x12,
		CMsgMigrateHostRequest = 0x66,
		CMsgJoinResponse = 0x2A,
		CMsgJoinRequest = 0x41,
		CMsgHostLeftWhilstJoiningCmd = 0x58,
		CMsgConfigResponse = 0x5F,
		CMsgConfigRequest = 0x48,
		CMsgChangeSessionAttributesCmd = 0x5A,
		CMsgAddGamerToSessionCmd = 0x64, // this is where send net info to lobby is called, among other things
		CMsgReassignResponse = 0x10,
		CMsgReassignNegotiate = 0x01,
		CMsgReassignConfirm = 0x26,
		CMsgPlayerData = 0x18,
		CMsgPackedReliables = 0x30,
		CMsgPackedCloneSyncACKs = 0x3B,
		CMsgNonPhysicalData = 0x16,
		CMsgNetArrayMgrUpdateAck = 0x5D,
		CMsgNetArrayMgrUpdate = 0x60,
		CMsgNetArrayMgrSplitUpdateAck = 0x25,
		CMsgScriptVerifyHostAck = 0x0B,
		CMsgScriptVerifyHost = 0x3E,
		CMsgScriptNewHost = 0x0E,
		CMsgScriptMigrateHostFailAck = 0x1A,
		CMsgScriptMigrateHost = 0x33,
		CMsgScriptLeaveAck = 0x40,
		CMsgScriptLeave = 0x17,
		CMsgScriptJoinHostAck = 0x4D,
		CMsgScriptJoinAck = 0x43,
		CMsgScriptJoin = 0x5C,
		CMsgScriptHostRequest = 0x67,
		CMsgScriptHandshakeAck = 0x5B,
		CMsgScriptHandshake = 0x57,
		CMsgScriptBotLeave = 0x2B, // unused?
		CMsgScriptBotJoinAck = 0x63, // unused?
		CMsgScriptBotJoin = 0x1C, // unused?
		CMsgScriptBotHandshakeAck = 0x31, // unused?
		CMsgScriptBotHandshake = 0x4B, // unused?
		CMsgPartyLeaveGame = 0x3D,
		CMsgPartyEnterGame = 0x1E,
		CMsgCloneSync = 0x4E, // aka clone_create, clone_sync etc.
		CMsgActivateNetworkBot = 0x65, // unused?
		CMsgRequestObjectIds = 0x29,
		CMsgInformObjectIds = 0x09,
		CMsgTextMessage = 0x24, // this one is for chat
		CMsgPlayerIsTyping = 0x61,
		CMsgPackedEvents = 0x4F, // aka received_event
		CMsgPackedEventReliablesCMsgs = 0x20,
		CMsgRequestKickFromHost = 0x0D,
		CMsgTransitionToGameStart = 0x50,
		CMsgTransitionToGameNotify = 0x02,
		CMsgTransitionToActivityStart = 0x06,
		CMsgTransitionToActivityFinish = 0x36,
		CMsgTransitionParameters = 0x3C,
		CMsgTransitionParameterString = 0x37,
		CMsgTransitionLaunchNotify = 0x1B,
		CMsgTransitionLaunch = 0x19,
		CMsgTransitionGamerInstruction = 0x14,
		CMsgTextMessage2 = 0x0A, // this one is for phone message
		CMsgSessionEstablishedRequest = 0x52,
		CMsgSessionEstablished = 0x07,
		CMsgRequestTransitionParameters = 0x42,
		CMsgRadioStationSyncRequest = 0x47,
		CMsgRadioStationSync = 0x46,
		CMsgPlayerCardSync = 0x3A,
		CMsgPlayerCardRequest = 0x6A,
		CMsgLostConnectionToHost = 0x81,
		CMsgKickPlayer = 0x34, // host kick
		CMsgDebugStall = 0x7E, // unused?
		CMsgCheckQueuedJoinRequestReply = 0x59,
		CMsgCheckQueuedJoinRequest = 0x51,
		CMsgBlacklist = 0x0C,
		CMsgRoamingRequestBubbleRequiredResponse = 0x83,
		CMsgRoamingRequestBubbleRequiredCheck = 0x82,
		CMsgRoamingRequestBubble = 0x2E,
		CMsgRoamingJoinBubble = 0x4C,
		CMsgRoamingJoinBubbleAck = 0x3F,
		CMsgRoamingInitialBubble = 0x32,
		CMsgVoiceStatus = 0x03,
		CMsgTextChatStatus = 0x00,
		CMsgJoinResponse2 = 0x08,
		CMsgJoinRequest2 = 0x68,
		CMsgNetTimeSync = 0x38, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 37
		CMsgNetComplaint = 0x55, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 54
		CMsgNetLagPing = 0x27, // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 26
		CMsgSearchResponse = 0x6B, // unused? ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 6A
		CMsgSearchRequest = 0x05, // unused?
		CMsgQosProbeResponse = 0x2C, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2B
		CMsgQosProbeRequest = 0x1D, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 1C
		CMsgCxnRelayAddressChanged = 0x49, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 48
		CMsgCxnRequestRemoteTimeout = 0x2F, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 2E
		CMsgSessionDetailRequest = 0x22, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 21
		CMsgSessionDetailResponse = 0x13, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 12
		CMsgKeyExchangeOffer = 0x0F, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 0E (last result)
		CMsgKeyExchangeAnswer = 0x44, // ctor 40 53 48 83 EC 20 BA ? ? ? ? 4C 8D 0D ? ? ? ? 48 8B D9 44 8D 42 43
		CMsg_0x87 = 0x87,
		CMsg_0x88 = 0x88,
		CMsg_0x80 = 0x80,
		CMsg_0x28 = 0x28,
		CMsg_0x11 = 0x11,
		CMsg_0x45 = 0x45,
		CMsg_0x89 = 0x89,
		CMsg_0x86 = 0x86,
	};
	namespace netConnection {
		class InFrame
		{
		public:
			enum class EventType
			{
				ConnectionClosed = 3,
				FrameReceived = 4,
				BandwidthExceeded = 6,
				OutOfMemory = 7
			};

			virtual ~InFrame() = default;

			virtual void destroy() = 0;
			virtual EventType get_event_type() = 0;
			virtual uint32_t _0x18() = 0;

			char pad_0008[56]; //0x0008
			uint32_t m_msg_id; //0x0040
			uint32_t m_connection_identifier; //0x0044
			InFrame* m_this; //0x0048
			uint32_t m_peer_id; //0x0050
			char pad_0050[36]; //0x0058
			uint32_t m_length; //0x0078
			char pad_007C[4]; //0x007C
			void* m_data; //0x0080
		};
		static_assert(sizeof(rage::netConnection::InFrame) == 0x88);
	}

	class CEventNetwork
	{
	public:
		virtual ~CEventNetwork() = default;
		virtual void unk_0x8() = 0;
		virtual void unk_0x10() = 0;
		virtual __int64 get_type() = 0;
		virtual void unk_0x20() = 0;
		virtual void unk_0x28() = 0;
		virtual bool get_extra_information(__int64* info_array, int check) = 0;
		virtual void unk_0x38() = 0;
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
	std::uint32_t m_amount; // 0x34
};
#pragma pack(pop)
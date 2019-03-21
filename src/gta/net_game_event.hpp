#pragma once
#include <cstdint>
#include "fwddec.hpp"

#pragma pack(push, 1)
namespace rage
{
	class netGameEvent
	{
	public:
		virtual ~netGameEvent() = default;

		virtual const char *get_name() const = 0;
		virtual bool is_applicable_to_player(netPlayer *player) = 0;
		virtual bool time_to_resend(std::uint32_t time) = 0;
		virtual bool needs_reply() = 0;

		virtual void serialize(datBitBuffer *buffer, netPlayer* source_player, netPlayer* target_player) = 0;
		virtual void deserialize(datBitBuffer *buffer, netPlayer* source_player, netPlayer* target_player) = 0;

		virtual bool handle(netPlayer* source_player, netPlayer* target_player) = 0;

		virtual void deserialize_reply(datBitBuffer *buffer, netPlayer* reply_player) = 0;
		virtual void serialize_reply(datBitBuffer *buffer, netPlayer* souce_player) = 0;

		virtual void deserialize_extra_data(datBitBuffer *buffer, bool is_reply, netPlayer *player, netPlayer *player2) = 0;
		virtual void serialize_extra_data(datBitBuffer *buffer, bool is_reply, netPlayer *player, netPlayer *player2) = 0;

		virtual void _0x60() = 0;
		virtual void _0x68() = 0;
		virtual void _0x70() = 0;
		virtual void _0x78() = 0;

		virtual bool operator==(netGameEvent const& other) = 0;
		virtual bool operator!=(netGameEvent const& other) = 0;

		virtual bool must_persist() = 0;
		virtual bool must_persist_when_out_of_scope() = 0;
		virtual bool has_timed_out() = 0;
	public:
		std::uint16_t m_id;          // 0x08
		bool m_requires_reply;       // 0x0A
	private:
		char m_padding1[0x05];       // 0x0B
	public:
		netPlayer* m_source_player;  // 0x10
		netPlayer* m_target_player;  // 0x18
		std::uint32_t m_resend_time; // 0x20
		std::uint16_t m_0x24;        // 0x24
		std::uint8_t m_0x26;         // 0x26
		std::uint8_t m_0x27;         // 0x27
		std::uint32_t m_0x28;        // 0x28
		char m_padding2[0x04];       // 0x2C
	};

	static_assert(sizeof(netGameEvent) == 0x30);
}
#pragma pack(pop)

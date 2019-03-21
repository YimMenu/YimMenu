#pragma once
#include <cstdint>
#include "fwddec.hpp"
#include "joaat.hpp"

#pragma pack(push, 1)
namespace rage
{
	class scriptIdBase
	{
	public:
		virtual ~scriptIdBase() = default;                            // 0 (0x00)

		// Assumes the script thread's identity.
		virtual void assume_thread_identity(scrThread*) {};           // 1 (0x08)

		// Returns whether the hash of the script id is valid.
		virtual bool is_valid() {};                                   // 2 (0x10)

		// Gets the hash of the script id.
		virtual joaat_t *get_hash(joaat_t *out) {};                   // 3 (0x18)

		// Gets an unknown value from the script id.
		virtual std::uint32_t *get_hash2(std::uint32_t *out) {};      // 4 (0x20)
		
		// Gets the name of the script id.
		virtual const char *get_name() {};                            // 5 (0x28)

		// Serializes the script id from the buffer.
		virtual void deserialize(datBitBuffer* buffer) {};            // 6 (0x30)

		// Serializes the script id to the buffer.
		virtual void serialize(datBitBuffer* buffer) {};              // 7 (0x38)
		
		// Calculates some information with the position hash & instance id.
		virtual std::uint32_t _0x40() {};                             // 8 (0x40)

		// Calls _0x40 and returns it's value added to another value.
		virtual std::uint32_t _0x48() {};                             // 9 (0x48)

		// Logs some information about the script id.
		virtual void log_information(netLoggingInterface* logger) {}; // 10 (0x50)
		
		// Copies the information of other to this object.
		virtual void copy_data(scriptIdBase *other) {}                // 11 (0x58)
		
		// Returns whether the other script id is equal.
		virtual bool operator==(scriptIdBase*) {};                    // 12 (0x60)

		virtual bool _0x68(void*) {};                                 // 13 (0x68)
	};

	class scriptId : public scriptIdBase
	{
	public:
		joaat_t m_hash;           // 0x08
		char m_name[0x20];        // 0x0C
	};
}

class CGameScriptId : public rage::scriptId
{
public:
	char m_padding[0x04];         // 0x2C
	std::int32_t m_timestamp;     // 0x30
	std::int32_t m_position_hash; // 0x34
	std::int32_t m_instance_id;   // 0x38
	std::int32_t m_unk;           // 0x3C
};

static_assert(sizeof(CGameScriptId) == 0x40);
#pragma pack(pop)

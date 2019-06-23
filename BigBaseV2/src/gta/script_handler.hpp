#pragma once
#include <cstdint>
#include "fwddec.hpp"
#include "node_list.hpp"
#include "script_id.hpp"

#pragma pack(push, 1)
namespace rage
{
	class scriptResource
	{
	public:
		virtual ~scriptResource() = default;
	};

	class scriptResourceEntry
	{
	public:
		scriptResource *m_data;      // 0x00
		std::uint32_t m_unk;         // 0x04
		char m_padding[0x0C];        // 0x0C
		scriptResourceEntry *m_next; // 0x18
	};

	class scriptHandlerNetComponent
	{
	public:
		virtual ~scriptHandlerNetComponent() = default;

	public:
		scriptHandler *m_script_handler; // 0x08
	};

	class scriptHandler
	{
	public:
		class atDScriptObjectNode : public atDNode<scriptHandlerObject*>
		{
		};
	public:
		virtual ~scriptHandler() = default;                                                                   //  0 (0x00)

		virtual bool _0x08() = 0;                                                                             //  1 (0x08)

		virtual void _0x10() = 0;                                                                             //  2 (0x10)

		virtual void cleanup_objects() = 0;                                                                   //  3 (0x18)

		virtual scriptId *_0x20() = 0;                                                                        //  4 (0x20)

		virtual scriptId *get_id() = 0;                                                                       //  5 (0x28)

		// Returns whether the script handler belongs to a networked script.
		virtual bool is_networked() = 0;                                                                      //  6 (0x30)

		// Initializes the network component for the script handler.
		virtual void init_net_component() = 0;                                                                //  7 (0x38)

		// Deletes the script handler's network component, if it exists.
		virtual void reset_net_component() = 0;                                                               //  8 (0x40)

		// Destroys the script handler.
		virtual bool destroy() = 0;                                                                           //  9 (0x48)

		// Adds the object to the script handler's list of objects.
		virtual void add_object(scriptHandlerObject*, bool is_network, bool is_network_and_scriptcheck) = 0; // 10 (0x50)

		// Something related to reservations.
		virtual void _0x58(void*) = 0;                                                                        // 11 (0x58)

		virtual void register_resource(scriptResource*, void*) = 0;                                           // 12 (0x60)

		virtual void _0x68() = 0;                                                                             // 13 (0x68)

		virtual void _0x70() = 0;                                                                             // 14 (0x70)

		virtual void _0x78() = 0;                                                                             // 15 (0x78)

		virtual void _0x80() = 0;                                                                             // 16 (0x80)

		virtual void _0x88() = 0;                                                                             // 17 (0x88)

		virtual void _0x90() = 0;                                                                             // 18 (0x90)

		virtual void _0x98() = 0;                                                                             // 19 (0x98)
	public:
		void *m_0x08;                                // 0x08
		void *m_0x10;                                // 0x10
		scrThread *m_script_thread;                  // 0x18
		atDList<atDScriptObjectNode> m_objects;      // 0x20
		scriptResource *m_resource_list_head;        // 0x30
		scriptResource *m_resource_list_tail;        // 0x38
		void *m_0x40;                                // 0x40
		scriptHandlerNetComponent *m_net_component;  // 0x48
		std::uint32_t m_0x50;                        // 0x50
		std::uint32_t m_0x54;                        // 0x54
		std::uint32_t m_0x58;                        // 0x58
		std::uint32_t m_0x60;                        // 0x5C
	};

	class scriptHandlerMgr
	{
	public:
		virtual ~scriptHandlerMgr() = default;

		// Initializes some scripting-related pools.
		virtual bool initialize() = 0;                                                          // 1 (0x08)

		// Called every tick.
		virtual void _0x10() = 0;                                                               // 2 (0x10)

		// Frees some scripting-related pools.
		virtual void shutdown() = 0;                                                            // 3 (0x18)

		virtual void _0x20() = 0;                                                               // 4 (0x20)
		virtual void _0x28() = 0;                                                               // 5 (0x28)
		virtual void _0x30() = 0;                                                               // 6 (0x30)

		// Generates a rage::scriptId from the thread and copies it over to a global structure.
		virtual void _0x38(scrThread*) = 0;                                                     // 7 (0x38)

		// Allocates and constructs a script handler.
		virtual scriptHandler *create_script_handler() = 0;                                     // 8 (0x40)

		// Finds the script handler for a given script id.
		virtual scriptHandler *get_script_handler(scriptId*) = 0;                               // 9 (0x48)

		// Attaches a script thread.
		virtual void attach_thread(scrThread*) = 0;                                             // 10 (0x50)

		// Detaches a script thread.
		virtual void detach_thread(scrThread*) = 0;                                             // 11 (0x58)

		// Called when a player joins.
		virtual void on_player_join(netPlayer*) = 0;                                            // 12 (0x60)

		// Called when a player leaves.
		virtual void on_player_left(netPlayer*) = 0;                                            // 13 (0x68)

		virtual std::int32_t _0x70() = 0;                                                       // 14 (0x70)
		virtual void *_0x78() = 0;                                                              // 15 (0x78)
	public:
		char m_padding1[0x28];                         // 0x08
		bool m_initialized;                            // 0x30
		bool m_initialized2;                           // 0x31
		char m_padding2[0x0E];                         // 0x32
		rage::netLoggingInterface *m_logger;           // 0x40
	};
}

class CGameScriptHandler : public rage::scriptHandler
{
public:
	CGameScriptId m_script_id; // 0x60
};

class CGameScriptHandlerNetwork : public CGameScriptHandler
{
public:
	std::uint8_t m_0xA0;        // 0xA0
	std::uint8_t m_0xA1;        // 0xA1
	std::uint8_t m_0xA2;        // 0xA2
	std::uint8_t m_0xA3;        // 0xA3
	std::uint8_t m_num_players; // 0xA4
	std::uint8_t m_0xA5;        // 0xA5
	std::uint8_t m_0xA6;        // 0xA6
	std::uint8_t m_0xA7;        // 0xA7
	std::uint8_t m_0xA8;        // 0xA8
	std::uint8_t m_0xA9;        // 0xA9
	std::uint8_t m_0xAA;        // 0xAA
	std::uint8_t m_0xAB;        // 0xAB
	std::uint8_t m_0xAC;        // 0xAC
	std::uint8_t m_0xAD;        // 0xAD
	std::uint8_t m_0xAE;        // 0xAE
	std::uint8_t m_0xAF;        // 0xAF
};

class CGameScriptHandlerMgr : public rage::scriptHandlerMgr
{
};

static_assert(sizeof(rage::scriptHandler) == 0x60);
static_assert(sizeof(CGameScriptHandler) == 0xA0);
static_assert(sizeof(CGameScriptHandlerNetwork) == 0xB0);
#pragma pack(pop)

#pragma once
#pragma pack(push, 4)

#include "common.hpp"
#include "fwddec.hpp"

namespace rage
{
	class CObject : public fwEntity
	{
	public:
	}; //Size: 0x018C

	class CPickup : public fwEntity
	{
	public:
	}; //Size: 0x018C

	//CUSTOM CLASS TO IMPROVE R* SHIT CLASS STRUCTURE
	class CEntityHandle {
	public:
		class fwEntity* m_entity_ptr; //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	}; //Size: 0x0010
	static_assert(sizeof(CEntityHandle) == 0x10, "CEntityHandle is not properly sized");

	class CEntityList
	{
	public:
		class CEntityHandle m_entities[256]; //0x0000
	}; //Size: 0x1000



	class CObjectInterface
	{
	public:
		char pad_0000[344]; //0x0000
		class CEntityList* m_object_list; //0x0158
		int32_t m_max_objects; //0x0160
		char pad_0164[4]; //0x0164
		int32_t m_cur_objects; //0x0168

		CObject* get_object(const int& index)
		{
			return (CObject*)m_object_list->m_entities[index].m_entity_ptr;
		}
	}; //Size: 0x016C

	class CPickupInterface
	{
	public:
		char pad_0000[256]; //0x0000
		class CEntityList* m_pickup_list; //0x0100
		int32_t m_max_pickups; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_cur_pickups; //0x0110

		CPickup* get_pickup(const int& index)
		{
			return (CPickup*)m_pickup_list->m_entities[index].m_entity_ptr;
		}
	}; //Size: 0x0114

	class CPedInterface
	{
	public:
		char pad_0000[256]; //0x0000
		class CEntityList* m_ped_list; //0x0100
		int32_t m_max_peds; //0x0108
		char pad_010C[4]; //0x010C
		int32_t m_cur_peds; //0x0110

		CPed* get_ped(const int& index)
		{
			return (CPed*)m_ped_list->m_entities[index].m_entity_ptr;
		}
	}; //Size: 0x0114

	class CVehicleInterface
	{
	public:
		char pad_0000[384]; //0x0000
		class CEntityList* m_vehicle_list; //0x0180
		int32_t m_max_vehicles; //0x0188
		char pad_018C[4]; //0x018C
		int32_t m_cur_vehicles; //0x0190

		CAutomobile* get_vehicle(const int& index)
		{
			return (CAutomobile*)m_vehicle_list->m_entities[index].m_entity_ptr;
		}
	}; //Size: 0x0194



	class CReplayInterface
	{
	public:
		char pad_0000[16]; //0x0000
		class CVehicleInterface* m_vehicle_interface; //0x0010
		class CPedInterface* m_ped_interface; //0x0018
		class CPickupInterface* m_pickup_interface; //0x0020
		class CObjectInterface* m_object_interface; //0x0028
	}; //Size: 0x0030
}
#pragma pack(pop)
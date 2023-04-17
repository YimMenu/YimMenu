#pragma once

#include "base/CObject.hpp"
#include "common.hpp"
#include "fwddec.hpp"

#pragma pack(push, 4)
namespace rage
{
	template<typename T = CDynamicEntity>
	class CEntityEntry
	{
	public:
		T* m_entity_ptr;  //0x0000
		int32_t m_handle; //0x0008
		char pad_000C[4]; //0x000C
	};                    //Size: 0x0010
	static_assert(sizeof(CEntityEntry<CDynamicEntity>) == 0x10, "CEntityHandle is not properly sized");

	class CObjectEntry : public CEntityEntry<CObject>
	{
	};

	class CPedEntry : public CEntityEntry<CPed>
	{
	};

	class CVehicleEntry : public CEntityEntry<CVehicle>
	{
	}; //Size: 0x8FC0

	class CObjectInterface
	{
	public:
		char pad_0000[344];                            //0x0000
		std::array<CObjectEntry, 2300>* m_object_list; //0x0158
		int32_t m_max_objects;                         //0x0160
		char pad_0164[4];                              //0x0164
		int32_t m_cur_objects;                         //0x0168

		CObject* get_object(const int& index)
		{
			if (index < m_max_objects)
				return (*m_object_list)[index].m_entity_ptr;
			return nullptr;
		}
	}; //Size: 0x016C

	class CPedInterface
	{
	public:
		char pad_0000[256];                     //0x0000
		std::array<CPedEntry, 256>* m_ped_list; //0x0100
		int32_t m_max_peds;                     //0x0108
		char pad_010C[4];                       //0x010C
		int32_t m_cur_peds;                     //0x0110

		CPed* get_ped(const int& index)
		{
			if (index < m_max_peds)
				return (*m_ped_list)[index].m_entity_ptr;
			return nullptr;
		}
	}; //Size: 0x0114

	class CVehicleInterface
	{
	public:
		char pad_0000[384];                             //0x0000
		std::array<CVehicleEntry, 300>* m_vehicle_list; //0x0180
		int32_t m_max_vehicles;                         //0x0188
		char pad_018C[4];                               //0x018C
		int32_t m_cur_vehicles;                         //0x0190

		CVehicle* get_vehicle(const int& index)
		{
			if (index < m_max_vehicles)
				return (*m_vehicle_list)[index].m_entity_ptr;
			return nullptr;
		}
	}; //Size: 0x0194


	class CReplayInterface
	{
	public:
		char pad_0000[16];                            //0x0000
		class CVehicleInterface* m_vehicle_interface; //0x0010
		class CPedInterface* m_ped_interface;         //0x0018
		char pad_0020[8];                             //0x0020
		class CObjectInterface* m_object_interface;   //0x0028
	};                                                //Size: 0x0030
}
#pragma pack(pop)
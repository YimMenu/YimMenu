#include "Pools.h"
#include "pointers.hpp"

namespace rage
{
	struct EntityPoolTask
	{
		inline bool TypeHasFlag(uint16_t flag)
		{
			assert(!(_type & ~31));
			assert(!(flag & ~31));
			return (_type & flag) != 0;
		}

		EntityPoolTask(uint16_t type) : _type(type) {}

		void Run(std::vector<uintptr_t>& _pointers)
		{
			if (TypeHasFlag(PoolTypePed))
			{
				for (int i = 0; i < big::g_pointers->m_ped_pool->size; i++)
				{
					if (uintptr_t address = big::g_pointers->m_ped_pool->getAddress(i))
					{
						_pointers.push_back(address);
					}
				}
			}

			if (TypeHasFlag(PoolTypeVehicle))
			{
				for (int i = 0; i < big::g_pointers->m_vehicle_pool->size; i++)
				{
					if (big::g_pointers->m_vehicle_pool->isValid(i))
					{
						if (uintptr_t address = big::g_pointers->m_vehicle_pool->getAddress(i))
						{
							_pointers.push_back(address);
						}
					}
				}
			}

			if (TypeHasFlag(PoolTypeObject))
			{
				for (int i = 0; i < big::g_pointers->m_prop_pool->size; i++)
				{
					if (uintptr_t address = big::g_pointers->m_prop_pool->getAddress(i))
					{
						_pointers.push_back(address);
					}
				}
			}

			if (TypeHasFlag(PoolTypePickup))
			{
				for (int i = 0; i < big::g_pointers->m_pickup_pool->size; i++)
				{
					if (uintptr_t address = big::g_pointers->m_pickup_pool->getAddress(i))
					{
						_pointers.push_back(address);
					}
				}
			}

			if (TypeHasFlag(PoolTypeCamera))
			{
				for (int i = 0; i < big::g_pointers->m_camera_pool->size; i++)
				{
					if (uintptr_t address = big::g_pointers->m_camera_pool->getAddress(i))
					{
						_pointers.push_back(address);
					}
				}
			}
		}
	private:
		uint16_t _type;
	};

	void GetEntityPointers(EntityPoolType type, std::vector<uintptr_t>& result)
	{
		EntityPoolTask(type).Run(result);
	}

	std::vector<Entity> GetAllWorld(EntityPoolType type, int max)
	{
		int count = 0;
		std::vector<Entity> entities;
		std::vector<uintptr_t> pointers;
		GetEntityPointers(type, pointers);

		for (const auto& cEntity : pointers)
		{
			if (count == max) break;
			auto entity = big::g_pointers->m_get_script_handle((int64_t)cEntity);
			if (entity)
			{
				entities.push_back((const Entity&)entity);
				count++;
			}
		}

		return entities;
	}

	int GetAllWorld(EntityPoolType type, int max, int* arr)
	{
		auto entities = GetAllWorld(type, max);

		for (int i = 0; i < entities.size(); ++i)
		{
			arr[i] = entities[i];
		}

		return (int)entities.size();
	}
}
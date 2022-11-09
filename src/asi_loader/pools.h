#pragma once

enum EntityPoolType : uint16_t
{
	PoolTypeVehicle = 1,
	PoolTypePed = 2,
	PoolTypeObject = 4,
	PoolTypePickup = 8,
	PoolTypeCamera = 16
};

namespace rage
{
	class GenericPool
	{
	public:
		uint64_t poolStartAddress;
		uint8_t* byteArray;
		int  size;
		int  itemSize;

		inline bool isValid(int i)
		{
			assert(i >= 0);
			return mask(i) != 0;
		}

		inline uint64_t getAddress(int i)
		{
			assert(i >= 0);
			return mask(i) & (poolStartAddress + i * itemSize);
		}
	private:
		inline long long mask(int i)
		{
			assert(i >= 0);
			long long num1 = byteArray[i] & 0x80; // check for high bit.
			return ~((num1 | -num1) >> 63);
		}
	};

	class VehiclePool
	{
	public:
		uint64_t* listAddress;
		int  size;
		char _padding2[36];
		uint32_t* bitArray;
		char _padding3[40];
		int  itemCount;

		inline bool isValid(int i)
		{
			assert(i >= 0);
			return (bitArray[i >> 5] >> (i & 0x1F)) & 1;
		}

		inline uint64_t getAddress(int i)
		{
			return listAddress[i];
		}
	};

	int GetAllWorld(EntityPoolType type, int max, int* arr);

	std::vector<Entity> GetAllWorld(EntityPoolType type, int max);
};
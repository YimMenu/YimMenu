#pragma once
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"

struct world_model_bypass
{
	inline static memory::byte_patch* m_world_model_spawn_bypass;
};

namespace big::world_model
{
	inline Object spawn(Hash hash, Vector3 location = Vector3(), bool is_networked = true)
	{
		if (entity::request_model(hash))
		{
			world_model_bypass::m_world_model_spawn_bypass->apply();

			const auto object = OBJECT::CREATE_OBJECT(hash, location.x, location.y, location.z, is_networked, false, false);

			world_model_bypass::m_world_model_spawn_bypass->restore();

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			return object;
		}

		LOG(WARNING) << "Failed to load model " << HEX_TO_UPPER(hash);
		return 0;
	}
}

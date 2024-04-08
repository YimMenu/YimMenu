#include "backend/player_command.hpp"
#include "backend/looped/looped.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include <chrono>
#include <future>
#include <vector>

// Keep spawned objects in a vector so we can keep track of them
//std::vector<Object> spawnedObjects;

namespace big
{
	//Object CREATE_OBJECT_WITH_ROTATION(DWORD model, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, bool dynamic, bool visible);
	Object CREATE_OBJECT_WITH_HEADING(DWORD model, float posX, float posY, float posZ, float heading, bool dynamic, bool visible);

	class cageObject
	{
	private:
		Object cage;
		std::chrono::seconds cageDuration;
		std::future<void> cageTimer;

		bool isExpired = false;
		bool isVisible = false;

		void startTimer(std::chrono::seconds cageDuration)
		{
			cageTimer = std::async(std::launch::async, [cageDuration, this]()
			{
				std::this_thread::sleep_for(cageDuration);
				isExpired = true;
			});
		}

		Object createTimedCage(DWORD model, float xLoc, float yLoc, float zLoc, float pedHeading, std::chrono::seconds cageDuration)
		{	
			startTimer(cageDuration);
			return CREATE_OBJECT_WITH_HEADING(model, xLoc, yLoc, zLoc, pedHeading, false, isVisible);
		}

	public:
		cageObject(DWORD model, float xLoc, float yLoc, float zLoc, float pedHeading, std::chrono::seconds cageDuration)
		{
			isExpired = false;
			this->cage = createTimedCage(model, xLoc, yLoc, zLoc, pedHeading, cageDuration);
		}

		inline bool cageExpired()
		{
			return this->isExpired;
		}

		void deleteCage()
		{
			ENTITY::DELETE_ENTITY(&(this->cage));
		}

		~cageObject()
		{
			// The async timer SHOULD be done since we're setting isExpired afterward, but just to be safe...
			if (cageTimer.valid())
			{
				cageTimer.wait();
			}
		}
	};

	std::vector<cageObject*> spawnedCages;

	class small_cage_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player->get_ped())
				return;

			Ped pedHandle = g_pointers->m_gta.m_ptr_to_handle(player->get_ped());

			float pedHeading = ENTITY::GET_ENTITY_HEADING(pedHandle);
			Vector3 spawnLocation;

			// Offset values are relative to the entity
			// x = left / right
			// y = forward / backward
			// z = up / down
			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, 0.0f, -21.5f);
			// Offset the heading by +90 degrees so the concave side of the stunt tube end faces the player
			spawnedCages.push_back(new cageObject(779277682, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading + 90.0, std::chrono::seconds(30))); // Stunt Tube End

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, 0.0f, -21.5f);
			// Offset the heading by +90 degrees so the concave side of the stunt tube end faces the player
			spawnedCages.push_back(new cageObject(779277682, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading - 90.0, std::chrono::seconds(30))); // Stunt Tube End

			/*
			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, 1.0f, -0.50f); // Front
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, -1.0f, 1.0f, -0.50f); // Front Left
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, -1.0f, 0.0f, -0.50f); // Left
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, -1.0f, -1.0f, -0.50f); // Back Left
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, -1.0f, -0.50f); // Back
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 1.f, -1.0f, -0.50f); // Back Right
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 1.0f, 0.0f, -0.50f); // Right
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 1.0f, 1.0f, -0.50f); // Front Right
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.0f, 0.0f, 1.25f); // Above
			CREATE_OBJECT_WITH_HEADING(3300099005, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading, false, false);
			*/
		}
	};

	small_cage_player g_small_cage_player("smallcage", "SMALL_CAGE_PLAYER", "SMALL_CAGE_PLAYER_DESC", 0);

	class big_cage_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player->get_ped())
				return;

			rage::fvector3 pedPosition = *player->get_ped()->get_position();

			Ped pedHandle        = g_pointers->m_gta.m_ptr_to_handle(player->get_ped());
			Vehicle pedVehHandle = g_pointers->m_gta.m_ptr_to_handle(player->get_current_vehicle());
			int pedVehClass      = VEHICLE::GET_VEHICLE_CLASS(pedVehHandle);

			float pedHeading = ENTITY::GET_ENTITY_HEADING(pedHandle);
			Vector3 spawnLocation;

			// Offset values are relative to the entity
			// x = left / right
			// y = forward / backward
			// z = up / down
			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, 3.0f, -11.0f);
			// Offset the heading by +90 degrees so the concave side of the stunt tube end faces the player
			spawnedCages.push_back(new cageObject(779277682, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading + 90.0f, std::chrono::seconds(30))); // Front Stunt Tube End (stt_prop_stunt_tube_end)

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 0.f, -3.0f, -11.0f);
			// Offset the heading by -90 degrees so the concave side of the stunt tube end faces the player
			spawnedCages.push_back(new cageObject(779277682, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading - 90.0f, std::chrono::seconds(30))); // Back Stunt Tube End (stt_prop_stunt_tube_end)
		}
	};

	big_cage_player g_big_cage_player("bigcage", "BIG_CAGE_PLAYER", "BIG_CAGE_PLAYER_DESC", 0);

	class barrier_player : player_command
	{
		using player_command::player_command;

		virtual CommandAccessLevel get_access_level() override
		{
			return CommandAccessLevel::AGGRESSIVE;
		}

		virtual void execute(player_ptr player, const command_arguments& _args, const std::shared_ptr<command_context> ctx) override
		{
			if (!player->get_ped())
				return;

			Ped pedHandle = g_pointers->m_gta.m_ptr_to_handle(player->get_ped());

			float pedHeading = ENTITY::GET_ENTITY_HEADING(pedHandle);
			Vector3 spawnLocation;

			// Offset values are relative to the entity
			// x = left / right
			// y = forward / backward
			// z = up / down
			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, -1.5f, 8.0f, -1.25f);
			spawnedCages.push_back(new cageObject(3620375846, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading + 45.0, std::chrono::seconds(2))); // prop_barier_conc_02c

			spawnLocation = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(pedHandle, 1.5f, 8.0f, -1.25f);
			spawnedCages.push_back(new cageObject(3620375846, spawnLocation.x, spawnLocation.y, spawnLocation.z, pedHeading - 45.0, std::chrono::seconds(2)));
		}
	};

	barrier_player g_barrier_player("barrier", "BARRIER_PLAYER", "BARRIER_PLAYER_DESC", 0);

	// Credits: https://www.unknowncheats.me/forum/grand-theft-auto-v/230325-trolling-features.html
	Object CREATE_OBJECT_WITH_ROTATION(DWORD model, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float rotW, bool dynamic, bool visible)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				script::get_current()->yield();

			Object retObject = OBJECT::CREATE_OBJECT(model, posX, posY, posZ, true, false, dynamic);

			ENTITY::SET_ENTITY_QUATERNION(retObject, rotX, rotY, rotZ, rotW);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(retObject, true, true);
			ENTITY::SET_ENTITY_DYNAMIC(retObject, false);
			if (!visible)
			{
				ENTITY::SET_ENTITY_VISIBLE(retObject, false, false);
			}
			ENTITY::SET_ENTITY_PROOFS(retObject, true, true, true, true, true, true, true, true);
			ENTITY::SET_ENTITY_INVINCIBLE(retObject, true);
			script::get_current()->yield();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			return retObject;
		}
		return 0;
	}

	Object CREATE_OBJECT_WITH_HEADING(DWORD model, float posX, float posY, float posZ, float heading, bool dynamic, bool visible)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				script::get_current()->yield();

			Object retObject = OBJECT::CREATE_OBJECT(model, posX, posY, posZ, true, false, dynamic);

			ENTITY::SET_ENTITY_HEADING(retObject, heading);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(retObject, true, true);
			ENTITY::SET_ENTITY_DYNAMIC(retObject, false);
			if (!visible)
			{
				ENTITY::SET_ENTITY_VISIBLE(retObject, false, false);
			}
			ENTITY::SET_ENTITY_PROOFS(retObject, true, true, true, true, true, true, true, true);
			ENTITY::SET_ENTITY_INVINCIBLE(retObject, true);
			script::get_current()->yield();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			return retObject;
		}
		return 0;
	}

	void looped::player_cage_maintenance()
	{
	spawnedCages.erase(std::remove_if(spawnedCages.begin(), spawnedCages.end(), [](cageObject* cage)
		{
			if (cage->cageExpired())
			{
				cage->deleteCage();
				delete cage;
				return true;
			}
			return false;
		}),
	spawnedCages.end());
	}
}

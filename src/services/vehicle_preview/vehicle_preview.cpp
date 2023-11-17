#include "vehicle_preview.hpp"

#include "core/settings/context_menu.hpp"
#include "core/settings/self.hpp"
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "pointers.hpp"
#include "services/vehicle/persist_car_service.hpp"
#include "util/delete_entity.hpp"
#include "util/math.hpp"
#include "util/vehicle.hpp"

constexpr static int camera_height  = 500.f;
constexpr static int preview_height = camera_height - 1.f;

namespace big
{
	inline static Vector3 get_spawn_location(Hash hash)
	{
		auto spawn_location = vehicle::get_spawn_location(hash);
		spawn_location.z += preview_height;
		return spawn_location;
	}

	void vehicle_preview::preview(std::function<void()> func, bool should_run_fun)
	{
		if (!is_camera_prepared && !busy)
		{
			busy               = true;
			is_camera_prepared = true;
			g_self.free_cam = g_self.noclip = g_context_menu.enabled = false;

			g_fiber_pool->queue_job([this] {
				camera = CAM::CREATE_CAM("DEFAULT_SCRIPTED_CAMERA", 0);

				Vector3 position = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(self::ped, 0, 0, camera_height);
				Vector3 rotation = CAM::GET_GAMEPLAY_CAM_ROT(2);

				CAM::SET_CAM_COORD(camera, position.x, position.y, position.z);
				CAM::SET_CAM_ROT(camera, rotation.x, rotation.y, rotation.z, 2);
				CAM::SET_CAM_ACTIVE(camera, true);
				CAM::RENDER_SCRIPT_CAMS(true, true, 500, true, true, 0);

				busy = false;
			});
		}
		else if (should_run_fun && !busy)
			func();
	}

	void vehicle_preview::preview_veh(Hash hash)
	{
		preview(
		    [this, hash] {
			    busy          = true;
			    last_veh_hash = hash;

			    g_fiber_pool->queue_job([this] {
				    script::get_current()->yield(500ms);

				    if (last_spawned)
					    entity::delete_entity(last_spawned);

				    last_spawned = vehicle::spawn(last_veh_hash, get_spawn_location(last_veh_hash), 0, false);
				    ENTITY::FREEZE_ENTITY_POSITION(last_spawned, true);

				    busy = false;
			    });
		    },
		    last_veh_hash != hash);
	}

	void vehicle_preview::preview_personal_veh(const std::unique_ptr<big::personal_vehicle>& personal_veh)
	{
		auto hash = personal_veh->get_hash();

		preview(
		    [this, hash, &personal_veh] {
			    busy                        = true;
			    last_veh_hash               = hash;
			    std::map<int, int32_t> mods = vehicle::get_owned_mods_from_vehicle_idx(personal_veh->get_vehicle_idx());

			    g_fiber_pool->queue_job([this, mods] {
				    script::get_current()->yield(500ms);

				    if (last_spawned)
					    entity::delete_entity(last_spawned);

				    last_spawned = vehicle::clone_from_owned_mods(mods, get_spawn_location(last_veh_hash), false);
				    ENTITY::FREEZE_ENTITY_POSITION(last_spawned, true);

				    busy = false;
			    });
		    },
		    last_veh_hash != hash);
	}

	void vehicle_preview::preview_persisted_veh(std::string file_name, std::string folder_name)
	{
		preview(
		    [this, file_name, folder_name] {
			    busy               = true;
			    last_veh_file_name = file_name;

			    g_fiber_pool->queue_job([this, file_name, folder_name] {
				    script::get_current()->yield(500ms);

				    if (last_spawned)
					    entity::delete_entity(last_spawned);

				    nlohmann::json vehicle_json = persist_car_service::load_vehicle_json(file_name, folder_name);
				    const Hash hash             = vehicle_json[persist_car_service::vehicle_model_hash_key];

				    last_spawned = persist_car_service::spawn_vehicle_full(vehicle_json, get_spawn_location(hash), false);
				    ENTITY::FREEZE_ENTITY_POSITION(last_spawned, true);

				    busy = false;
			    });
		    },
		    last_veh_file_name != file_name);
	}

	void vehicle_preview::reset()
	{
		camera             = -1;
		last_spawned       = 0;
		last_veh_hash      = 0;
		last_veh_file_name = "";

		busy = false;
	}

	void vehicle_preview::clear()
	{
		if (is_camera_prepared && !busy)
		{
			busy               = true;
			is_camera_prepared = false;

			g_fiber_pool->queue_job([this] {
				CAM::SET_CAM_ACTIVE(camera, false);
				CAM::RENDER_SCRIPT_CAMS(false, true, 500, true, true, 0);
				CAM::DESTROY_CAM(camera, false);
				STREAMING::CLEAR_FOCUS();

				if (last_spawned)
					entity::delete_entity(last_spawned);

				reset();
			});
		}
	}
}
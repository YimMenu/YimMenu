#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_CAM_RENDER_SCRIPT_CAMS(bool render, bool ease, int easeTime, bool p3, bool p4, Any p5)
	{
		CAM::RENDER_SCRIPT_CAMS(render, ease, easeTime, p3, p4, p5);
	}

	static void LUA_NATIVE_CAM_STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP(bool render, float p1, int p2, Any p3)
	{
		CAM::STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP(render, p1, p2, p3);
	}

	static Cam LUA_NATIVE_CAM_CREATE_CAM(sol::stack_object camName, bool p1)
	{
		auto retval = CAM::CREATE_CAM(camName.is<const char*>() ? camName.as<const char*>() : nullptr, p1);
		return retval;
	}

	static Cam LUA_NATIVE_CAM_CREATE_CAM_WITH_PARAMS(sol::stack_object camName, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, int p9)
	{
		auto retval = CAM::CREATE_CAM_WITH_PARAMS(camName.is<const char*>() ? camName.as<const char*>() : nullptr, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9);
		return retval;
	}

	static Cam LUA_NATIVE_CAM_CREATE_CAMERA(Hash camHash, bool p1)
	{
		auto retval = CAM::CREATE_CAMERA(camHash, p1);
		return retval;
	}

	static Cam LUA_NATIVE_CAM_CREATE_CAMERA_WITH_PARAMS(Hash camHash, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fov, bool p8, Any p9)
	{
		auto retval = CAM::CREATE_CAMERA_WITH_PARAMS(camHash, posX, posY, posZ, rotX, rotY, rotZ, fov, p8, p9);
		return retval;
	}

	static void LUA_NATIVE_CAM_DESTROY_CAM(Cam cam, bool bScriptHostCam)
	{
		CAM::DESTROY_CAM(cam, bScriptHostCam);
	}

	static void LUA_NATIVE_CAM_DESTROY_ALL_CAMS(bool bScriptHostCam)
	{
		CAM::DESTROY_ALL_CAMS(bScriptHostCam);
	}

	static bool LUA_NATIVE_CAM_DOES_CAM_EXIST(Cam cam)
	{
		auto retval = (bool)CAM::DOES_CAM_EXIST(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_ACTIVE(Cam cam, bool active)
	{
		CAM::SET_CAM_ACTIVE(cam, active);
	}

	static bool LUA_NATIVE_CAM_IS_CAM_ACTIVE(Cam cam)
	{
		auto retval = (bool)CAM::IS_CAM_ACTIVE(cam);
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_CAM_RENDERING(Cam cam)
	{
		auto retval = (bool)CAM::IS_CAM_RENDERING(cam);
		return retval;
	}

	static Cam LUA_NATIVE_CAM_GET_RENDERING_CAM()
	{
		auto retval = CAM::GET_RENDERING_CAM();
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_CAM_COORD(Cam cam)
	{
		auto retval = CAM::GET_CAM_COORD(cam);
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_CAM_ROT(Cam cam, int rotationOrder)
	{
		auto retval = CAM::GET_CAM_ROT(cam, rotationOrder);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_FOV(Cam cam)
	{
		auto retval = CAM::GET_CAM_FOV(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_NEAR_CLIP(Cam cam)
	{
		auto retval = CAM::GET_CAM_NEAR_CLIP(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_FAR_CLIP(Cam cam)
	{
		auto retval = CAM::GET_CAM_FAR_CLIP(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_NEAR_DOF(Cam cam)
	{
		auto retval = CAM::GET_CAM_NEAR_DOF(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_FAR_DOF(Cam cam)
	{
		auto retval = CAM::GET_CAM_FAR_DOF(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_DOF_STRENGTH(Cam cam)
	{
		auto retval = CAM::GET_CAM_DOF_STRENGTH(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_PARAMS(Cam cam, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float fieldOfView, Any p8, int p9, int p10, int p11)
	{
		CAM::SET_CAM_PARAMS(cam, posX, posY, posZ, rotX, rotY, rotZ, fieldOfView, p8, p9, p10, p11);
	}

	static void LUA_NATIVE_CAM_SET_CAM_COORD(Cam cam, float posX, float posY, float posZ)
	{
		CAM::SET_CAM_COORD(cam, posX, posY, posZ);
	}

	static void LUA_NATIVE_CAM_SET_CAM_ROT(Cam cam, float rotX, float rotY, float rotZ, int rotationOrder)
	{
		CAM::SET_CAM_ROT(cam, rotX, rotY, rotZ, rotationOrder);
	}

	static void LUA_NATIVE_CAM_SET_CAM_FOV(Cam cam, float fieldOfView)
	{
		CAM::SET_CAM_FOV(cam, fieldOfView);
	}

	static void LUA_NATIVE_CAM_SET_CAM_NEAR_CLIP(Cam cam, float nearClip)
	{
		CAM::SET_CAM_NEAR_CLIP(cam, nearClip);
	}

	static void LUA_NATIVE_CAM_SET_CAM_FAR_CLIP(Cam cam, float farClip)
	{
		CAM::SET_CAM_FAR_CLIP(cam, farClip);
	}

	static void LUA_NATIVE_CAM_FORCE_CAM_FAR_CLIP(Cam cam, float p1)
	{
		CAM::FORCE_CAM_FAR_CLIP(cam, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_MOTION_BLUR_STRENGTH(Cam cam, float strength)
	{
		CAM::SET_CAM_MOTION_BLUR_STRENGTH(cam, strength);
	}

	static void LUA_NATIVE_CAM_SET_CAM_NEAR_DOF(Cam cam, float nearDOF)
	{
		CAM::SET_CAM_NEAR_DOF(cam, nearDOF);
	}

	static void LUA_NATIVE_CAM_SET_CAM_FAR_DOF(Cam cam, float farDOF)
	{
		CAM::SET_CAM_FAR_DOF(cam, farDOF);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_STRENGTH(Cam cam, float dofStrength)
	{
		CAM::SET_CAM_DOF_STRENGTH(cam, dofStrength);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_PLANES(Cam cam, float p1, float p2, float p3, float p4)
	{
		CAM::SET_CAM_DOF_PLANES(cam, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_CAM_SET_CAM_USE_SHALLOW_DOF_MODE(Cam cam, bool toggle)
	{
		CAM::SET_CAM_USE_SHALLOW_DOF_MODE(cam, toggle);
	}

	static void LUA_NATIVE_CAM_SET_USE_HI_DOF()
	{
		CAM::SET_USE_HI_DOF();
	}

	static void LUA_NATIVE_CAM_SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE()
	{
		CAM::SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE(Cam camera, float p1)
	{
		CAM::SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE(camera, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL(Any p0, float p1)
	{
		CAM::SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_FNUMBER_OF_LENS(Cam camera, float p1)
	{
		CAM::SET_CAM_DOF_FNUMBER_OF_LENS(camera, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER(Cam camera, float multiplier)
	{
		CAM::SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER(camera, multiplier);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_FOCUS_DISTANCE_BIAS(Cam camera, float p1)
	{
		CAM::SET_CAM_DOF_FOCUS_DISTANCE_BIAS(camera, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(Cam camera, float p1)
	{
		CAM::SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE(camera, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(Cam camera, float p1)
	{
		CAM::SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL(camera, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS(Cam camera, bool state)
	{
		CAM::SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS(camera, state);
	}

	static void LUA_NATIVE_CAM_ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xOffset, float yOffset, float zOffset, bool isRelative)
	{
		CAM::ATTACH_CAM_TO_ENTITY(cam, entity, xOffset, yOffset, zOffset, isRelative);
	}

	static void LUA_NATIVE_CAM_ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool heading)
	{
		CAM::ATTACH_CAM_TO_PED_BONE(cam, ped, boneIndex, x, y, z, heading);
	}

	static void LUA_NATIVE_CAM_HARD_ATTACH_CAM_TO_PED_BONE(Cam cam, Ped ped, int boneIndex, float p3, float p4, float p5, float p6, float p7, float p8, bool p9)
	{
		CAM::HARD_ATTACH_CAM_TO_PED_BONE(cam, ped, boneIndex, p3, p4, p5, p6, p7, p8, p9);
	}

	static void LUA_NATIVE_CAM_HARD_ATTACH_CAM_TO_ENTITY(Cam cam, Entity entity, float xRot, float yRot, float zRot, float xOffset, float yOffset, float zOffset, bool isRelative)
	{
		CAM::HARD_ATTACH_CAM_TO_ENTITY(cam, entity, xRot, yRot, zRot, xOffset, yOffset, zOffset, isRelative);
	}

	static void LUA_NATIVE_CAM_ATTACH_CAM_TO_VEHICLE_BONE(Cam cam, Vehicle vehicle, int boneIndex, bool relativeRotation, float rotX, float rotY, float rotZ, float offsetX, float offsetY, float offsetZ, bool fixedDirection)
	{
		CAM::ATTACH_CAM_TO_VEHICLE_BONE(cam, vehicle, boneIndex, relativeRotation, rotX, rotY, rotZ, offsetX, offsetY, offsetZ, fixedDirection);
	}

	static void LUA_NATIVE_CAM_DETACH_CAM(Cam cam)
	{
		CAM::DETACH_CAM(cam);
	}

	static void LUA_NATIVE_CAM_SET_CAM_INHERIT_ROLL_VEHICLE(Cam cam, bool p1)
	{
		CAM::SET_CAM_INHERIT_ROLL_VEHICLE(cam, p1);
	}

	static void LUA_NATIVE_CAM_POINT_CAM_AT_COORD(Cam cam, float x, float y, float z)
	{
		CAM::POINT_CAM_AT_COORD(cam, x, y, z);
	}

	static void LUA_NATIVE_CAM_POINT_CAM_AT_ENTITY(Cam cam, Entity entity, float p2, float p3, float p4, bool p5)
	{
		CAM::POINT_CAM_AT_ENTITY(cam, entity, p2, p3, p4, p5);
	}

	static void LUA_NATIVE_CAM_POINT_CAM_AT_PED_BONE(Cam cam, Ped ped, int boneIndex, float x, float y, float z, bool p6)
	{
		CAM::POINT_CAM_AT_PED_BONE(cam, ped, boneIndex, x, y, z, p6);
	}

	static void LUA_NATIVE_CAM_STOP_CAM_POINTING(Cam cam)
	{
		CAM::STOP_CAM_POINTING(cam);
	}

	static void LUA_NATIVE_CAM_SET_CAM_AFFECTS_AIMING(Cam cam, bool toggle)
	{
		CAM::SET_CAM_AFFECTS_AIMING(cam, toggle);
	}

	static void LUA_NATIVE_CAM_SET_CAM_CONTROLS_MINI_MAP_HEADING(Cam cam, bool toggle)
	{
		CAM::SET_CAM_CONTROLS_MINI_MAP_HEADING(cam, toggle);
	}

	static void LUA_NATIVE_CAM_SET_CAM_IS_INSIDE_VEHICLE(Cam cam, bool toggle)
	{
		CAM::SET_CAM_IS_INSIDE_VEHICLE(cam, toggle);
	}

	static void LUA_NATIVE_CAM_ALLOW_MOTION_BLUR_DECAY(Any p0, bool p1)
	{
		CAM::ALLOW_MOTION_BLUR_DECAY(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_CAM_DEBUG_NAME(Cam camera, sol::stack_object name)
	{
		CAM::SET_CAM_DEBUG_NAME(camera, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static Cam LUA_NATIVE_CAM_GET_DEBUG_CAM()
	{
		auto retval = CAM::GET_DEBUG_CAM();
		return retval;
	}

	static void LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE(Cam camera, float x, float y, float z, float xRot, float yRot, float zRot, int length, int smoothingStyle, int rotationOrder)
	{
		CAM::ADD_CAM_SPLINE_NODE(camera, x, y, z, xRot, yRot, zRot, length, smoothingStyle, rotationOrder);
	}

	static void LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME(Cam cam, Cam cam2, int length, int p3)
	{
		CAM::ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME(cam, cam2, length, p3);
	}

	static void LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_CAMERA(Cam cam, Cam cam2, int length, int p3)
	{
		CAM::ADD_CAM_SPLINE_NODE_USING_CAMERA(cam, cam2, length, p3);
	}

	static void LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME(Cam cam, int length, int p2)
	{
		CAM::ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME(cam, length, p2);
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_PHASE(Cam cam, float p1)
	{
		CAM::SET_CAM_SPLINE_PHASE(cam, p1);
	}

	static float LUA_NATIVE_CAM_GET_CAM_SPLINE_PHASE(Cam cam)
	{
		auto retval = CAM::GET_CAM_SPLINE_PHASE(cam);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_CAM_SPLINE_NODE_PHASE(Cam cam)
	{
		auto retval = CAM::GET_CAM_SPLINE_NODE_PHASE(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_DURATION(Cam cam, int timeDuration)
	{
		CAM::SET_CAM_SPLINE_DURATION(cam, timeDuration);
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_SMOOTHING_STYLE(Cam cam, int smoothingStyle)
	{
		CAM::SET_CAM_SPLINE_SMOOTHING_STYLE(cam, smoothingStyle);
	}

	static int LUA_NATIVE_CAM_GET_CAM_SPLINE_NODE_INDEX(Cam cam)
	{
		auto retval = CAM::GET_CAM_SPLINE_NODE_INDEX(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_EASE(Cam cam, int easingFunction, int p2, float p3)
	{
		CAM::SET_CAM_SPLINE_NODE_EASE(cam, easingFunction, p2, p3);
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_VELOCITY_SCALE(Cam cam, int p1, float scale)
	{
		CAM::SET_CAM_SPLINE_NODE_VELOCITY_SCALE(cam, p1, scale);
	}

	static void LUA_NATIVE_CAM_OVERRIDE_CAM_SPLINE_VELOCITY(Cam cam, int p1, float p2, float p3)
	{
		CAM::OVERRIDE_CAM_SPLINE_VELOCITY(cam, p1, p2, p3);
	}

	static void LUA_NATIVE_CAM_OVERRIDE_CAM_SPLINE_MOTION_BLUR(Cam cam, int p1, float p2, float p3)
	{
		CAM::OVERRIDE_CAM_SPLINE_MOTION_BLUR(cam, p1, p2, p3);
	}

	static void LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_EXTRA_FLAGS(Cam cam, int p1, int flags)
	{
		CAM::SET_CAM_SPLINE_NODE_EXTRA_FLAGS(cam, p1, flags);
	}

	static bool LUA_NATIVE_CAM_IS_CAM_SPLINE_PAUSED(Cam cam)
	{
		auto retval = (bool)CAM::IS_CAM_SPLINE_PAUSED(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_ACTIVE_WITH_INTERP(Cam camTo, Cam camFrom, int duration, int easeLocation, int easeRotation)
	{
		CAM::SET_CAM_ACTIVE_WITH_INTERP(camTo, camFrom, duration, easeLocation, easeRotation);
	}

	static bool LUA_NATIVE_CAM_IS_CAM_INTERPOLATING(Cam cam)
	{
		auto retval = (bool)CAM::IS_CAM_INTERPOLATING(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SHAKE_CAM(Cam cam, sol::stack_object type, float amplitude)
	{
		CAM::SHAKE_CAM(cam, type.is<const char*>() ? type.as<const char*>() : nullptr, amplitude);
	}

	static void LUA_NATIVE_CAM_ANIMATED_SHAKE_CAM(Cam cam, sol::stack_object p1, sol::stack_object p2, sol::stack_object p3, float amplitude)
	{
		CAM::ANIMATED_SHAKE_CAM(cam, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3.is<const char*>() ? p3.as<const char*>() : nullptr, amplitude);
	}

	static bool LUA_NATIVE_CAM_IS_CAM_SHAKING(Cam cam)
	{
		auto retval = (bool)CAM::IS_CAM_SHAKING(cam);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_SHAKE_AMPLITUDE(Cam cam, float amplitude)
	{
		CAM::SET_CAM_SHAKE_AMPLITUDE(cam, amplitude);
	}

	static void LUA_NATIVE_CAM_STOP_CAM_SHAKING(Cam cam, bool p1)
	{
		CAM::STOP_CAM_SHAKING(cam, p1);
	}

	static void LUA_NATIVE_CAM_SHAKE_SCRIPT_GLOBAL(sol::stack_object p0, float p1)
	{
		CAM::SHAKE_SCRIPT_GLOBAL(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_CAM_ANIMATED_SHAKE_SCRIPT_GLOBAL(sol::stack_object p0, sol::stack_object p1, sol::stack_object p2, float p3)
	{
		CAM::ANIMATED_SHAKE_SCRIPT_GLOBAL(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3);
	}

	static bool LUA_NATIVE_CAM_IS_SCRIPT_GLOBAL_SHAKING()
	{
		auto retval = (bool)CAM::IS_SCRIPT_GLOBAL_SHAKING();
		return retval;
	}

	static void LUA_NATIVE_CAM_STOP_SCRIPT_GLOBAL_SHAKING(bool p0)
	{
		CAM::STOP_SCRIPT_GLOBAL_SHAKING(p0);
	}

	static void LUA_NATIVE_CAM_TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE(Vehicle vehicle, int p1, float p2)
	{
		CAM::TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE(vehicle, p1, p2);
	}

	static bool LUA_NATIVE_CAM_PLAY_CAM_ANIM(Cam cam, sol::stack_object animName, sol::stack_object animDictionary, float x, float y, float z, float xRot, float yRot, float zRot, bool p9, int p10)
	{
		auto retval = (bool)CAM::PLAY_CAM_ANIM(cam, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr, x, y, z, xRot, yRot, zRot, p9, p10);
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_CAM_PLAYING_ANIM(Cam cam, sol::stack_object animName, sol::stack_object animDictionary)
	{
		auto retval = (bool)CAM::IS_CAM_PLAYING_ANIM(cam, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_ANIM_CURRENT_PHASE(Cam cam, float phase)
	{
		CAM::SET_CAM_ANIM_CURRENT_PHASE(cam, phase);
	}

	static float LUA_NATIVE_CAM_GET_CAM_ANIM_CURRENT_PHASE(Cam cam)
	{
		auto retval = CAM::GET_CAM_ANIM_CURRENT_PHASE(cam);
		return retval;
	}

	static bool LUA_NATIVE_CAM_PLAY_SYNCHRONIZED_CAM_ANIM(Any p0, Any p1, sol::stack_object animName, sol::stack_object animDictionary)
	{
		auto retval = (bool)CAM::PLAY_SYNCHRONIZED_CAM_ANIM(p0, p1, animName.is<const char*>() ? animName.as<const char*>() : nullptr, animDictionary.is<const char*>() ? animDictionary.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FLY_CAM_HORIZONTAL_RESPONSE(Cam cam, float p1, float p2, float p3)
	{
		CAM::SET_FLY_CAM_HORIZONTAL_RESPONSE(cam, p1, p2, p3);
	}

	static void LUA_NATIVE_CAM_SET_FLY_CAM_VERTICAL_RESPONSE(Cam cam, float p1, float p2, float p3)
	{
		CAM::SET_FLY_CAM_VERTICAL_RESPONSE(cam, p1, p2, p3);
	}

	static void LUA_NATIVE_CAM_SET_FLY_CAM_MAX_HEIGHT(Cam cam, float height)
	{
		CAM::SET_FLY_CAM_MAX_HEIGHT(cam, height);
	}

	static void LUA_NATIVE_CAM_SET_FLY_CAM_COORD_AND_CONSTRAIN(Cam cam, float x, float y, float z)
	{
		CAM::SET_FLY_CAM_COORD_AND_CONSTRAIN(cam, x, y, z);
	}

	static void LUA_NATIVE_CAM_SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE(Cam cam)
	{
		CAM::SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE(cam);
	}

	static bool LUA_NATIVE_CAM_WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE(Cam cam)
	{
		auto retval = (bool)CAM::WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE(cam);
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_SCREEN_FADED_OUT()
	{
		auto retval = (bool)CAM::IS_SCREEN_FADED_OUT();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_SCREEN_FADED_IN()
	{
		auto retval = (bool)CAM::IS_SCREEN_FADED_IN();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_SCREEN_FADING_OUT()
	{
		auto retval = (bool)CAM::IS_SCREEN_FADING_OUT();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_SCREEN_FADING_IN()
	{
		auto retval = (bool)CAM::IS_SCREEN_FADING_IN();
		return retval;
	}

	static void LUA_NATIVE_CAM_DO_SCREEN_FADE_IN(int duration)
	{
		CAM::DO_SCREEN_FADE_IN(duration);
	}

	static void LUA_NATIVE_CAM_DO_SCREEN_FADE_OUT(int duration)
	{
		CAM::DO_SCREEN_FADE_OUT(duration);
	}

	static void LUA_NATIVE_CAM_SET_WIDESCREEN_BORDERS(bool p0, int p1)
	{
		CAM::SET_WIDESCREEN_BORDERS(p0, p1);
	}

	static bool LUA_NATIVE_CAM_ARE_WIDESCREEN_BORDERS_ACTIVE()
	{
		auto retval = (bool)CAM::ARE_WIDESCREEN_BORDERS_ACTIVE();
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_COORD()
	{
		auto retval = CAM::GET_GAMEPLAY_CAM_COORD();
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_ROT(int rotationOrder)
	{
		auto retval = CAM::GET_GAMEPLAY_CAM_ROT(rotationOrder);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_FOV()
	{
		auto retval = CAM::GET_GAMEPLAY_CAM_FOV();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(float p0)
	{
		CAM::SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE(float p0)
	{
		CAM::SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE(p0);
	}

	static float LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_RELATIVE_HEADING()
	{
		auto retval = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading)
	{
		CAM::SET_GAMEPLAY_CAM_RELATIVE_HEADING(heading);
	}

	static float LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_RELATIVE_PITCH()
	{
		auto retval = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_RELATIVE_PITCH(float angle, float scalingFactor)
	{
		CAM::SET_GAMEPLAY_CAM_RELATIVE_PITCH(angle, scalingFactor);
	}

	static void LUA_NATIVE_CAM_RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER()
	{
		CAM::RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER();
	}

	static void LUA_NATIVE_CAM_FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH(float roll, float pitch, float yaw)
	{
		CAM::FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH(roll, pitch, yaw);
	}

	static void LUA_NATIVE_CAM_FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH(float p0, float p1)
	{
		CAM::FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(float yaw)
	{
		CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING(yaw);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(float pitch)
	{
		CAM::SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH(pitch);
	}

	static void LUA_NATIVE_CAM_SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME(bool p0)
	{
		CAM::SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME(p0);
	}

	static void LUA_NATIVE_CAM_SHAKE_GAMEPLAY_CAM(sol::stack_object shakeName, float intensity)
	{
		CAM::SHAKE_GAMEPLAY_CAM(shakeName.is<const char*>() ? shakeName.as<const char*>() : nullptr, intensity);
	}

	static bool LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_SHAKING()
	{
		auto retval = (bool)CAM::IS_GAMEPLAY_CAM_SHAKING();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(float amplitude)
	{
		CAM::SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE(amplitude);
	}

	static void LUA_NATIVE_CAM_STOP_GAMEPLAY_CAM_SHAKING(bool p0)
	{
		CAM::STOP_GAMEPLAY_CAM_SHAKING(p0);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE(Ped ped)
	{
		CAM::SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE(ped);
	}

	static bool LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_RENDERING()
	{
		auto retval = (bool)CAM::IS_GAMEPLAY_CAM_RENDERING();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_INTERPOLATING_FROM_SCRIPT_CAMS()
	{
		auto retval = (bool)CAM::IS_INTERPOLATING_FROM_SCRIPT_CAMS();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_INTERPOLATING_TO_SCRIPT_CAMS()
	{
		auto retval = (bool)CAM::IS_INTERPOLATING_TO_SCRIPT_CAMS();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE(bool p0)
	{
		CAM::SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE(p0);
	}

	static void LUA_NATIVE_CAM_DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE()
	{
		CAM::DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE();
	}

	static bool LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_LOOKING_BEHIND()
	{
		auto retval = (bool)CAM::IS_GAMEPLAY_CAM_LOOKING_BEHIND();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE(Entity entity)
	{
		CAM::SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE(entity);
	}

	static void LUA_NATIVE_CAM_DISABLE_CAM_COLLISION_FOR_OBJECT(Entity entity)
	{
		CAM::DISABLE_CAM_COLLISION_FOR_OBJECT(entity);
	}

	static void LUA_NATIVE_CAM_BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE()
	{
		CAM::BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE(Entity entity)
	{
		CAM::SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE(entity);
	}

	static void LUA_NATIVE_CAM_DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE()
	{
		CAM::DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE()
	{
		CAM::SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE();
	}

	static bool LUA_NATIVE_CAM_IS_SPHERE_VISIBLE(float x, float y, float z, float radius)
	{
		auto retval = (bool)CAM::IS_SPHERE_VISIBLE(x, y, z, radius);
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_FOLLOW_PED_CAM_ACTIVE()
	{
		auto retval = (bool)CAM::IS_FOLLOW_PED_CAM_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_THIS_UPDATE(sol::stack_object camName, int p1)
	{
		auto retval = (bool)CAM::SET_FOLLOW_PED_CAM_THIS_UPDATE(camName.is<const char*>() ? camName.as<const char*>() : nullptr, p1);
		return retval;
	}

	static void LUA_NATIVE_CAM_USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME(bool p0, bool p1)
	{
		CAM::USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE()
	{
		CAM::SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float minimum, float maximum)
	{
		CAM::SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(minimum, maximum);
	}

	static void LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float minimum, float maximum)
	{
		CAM::SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(minimum, maximum);
	}

	static void LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(float p0, float distance)
	{
		CAM::SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE(p0, distance);
	}

	static float LUA_NATIVE_CAM_GET_THIRD_PERSON_CAM_MIN_ORBIT_DISTANCE_SPRING_()
	{
		auto retval = CAM::_GET_THIRD_PERSON_CAM_MIN_ORBIT_DISTANCE_SPRING();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_THIRD_PERSON_CAM_MAX_ORBIT_DISTANCE_SPRING_()
	{
		auto retval = CAM::_GET_THIRD_PERSON_CAM_MAX_ORBIT_DISTANCE_SPRING();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE(Vehicle p0, int p1)
	{
		CAM::SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE(p0, p1);
	}

	static void LUA_NATIVE_CAM_DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE()
	{
		CAM::DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE()
	{
		CAM::DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE()
	{
		CAM::BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE();
	}

	static int LUA_NATIVE_CAM_GET_FOLLOW_PED_CAM_ZOOM_LEVEL()
	{
		auto retval = CAM::GET_FOLLOW_PED_CAM_ZOOM_LEVEL();
		return retval;
	}

	static int LUA_NATIVE_CAM_GET_FOLLOW_PED_CAM_VIEW_MODE()
	{
		auto retval = CAM::GET_FOLLOW_PED_CAM_VIEW_MODE();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_VIEW_MODE(int viewMode)
	{
		CAM::SET_FOLLOW_PED_CAM_VIEW_MODE(viewMode);
	}

	static bool LUA_NATIVE_CAM_IS_FOLLOW_VEHICLE_CAM_ACTIVE()
	{
		auto retval = (bool)CAM::IS_FOLLOW_VEHICLE_CAM_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE(bool p0)
	{
		CAM::SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE(bool p0, bool p1)
	{
		CAM::SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE(p0, p1);
	}

	static bool LUA_NATIVE_CAM_SET_TABLE_GAMES_CAMERA_THIS_UPDATE(Hash hash)
	{
		auto retval = (bool)CAM::SET_TABLE_GAMES_CAMERA_THIS_UPDATE(hash);
		return retval;
	}

	static int LUA_NATIVE_CAM_GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL()
	{
		auto retval = CAM::GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(int zoomLevel)
	{
		CAM::SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL(zoomLevel);
	}

	static int LUA_NATIVE_CAM_GET_FOLLOW_VEHICLE_CAM_VIEW_MODE()
	{
		auto retval = CAM::GET_FOLLOW_VEHICLE_CAM_VIEW_MODE();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(int viewMode)
	{
		CAM::SET_FOLLOW_VEHICLE_CAM_VIEW_MODE(viewMode);
	}

	static int LUA_NATIVE_CAM_GET_CAM_VIEW_MODE_FOR_CONTEXT(int context)
	{
		auto retval = CAM::GET_CAM_VIEW_MODE_FOR_CONTEXT(context);
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CAM_VIEW_MODE_FOR_CONTEXT(int context, int viewMode)
	{
		CAM::SET_CAM_VIEW_MODE_FOR_CONTEXT(context, viewMode);
	}

	static int LUA_NATIVE_CAM_GET_CAM_ACTIVE_VIEW_MODE_CONTEXT()
	{
		auto retval = CAM::GET_CAM_ACTIVE_VIEW_MODE_CONTEXT();
		return retval;
	}

	static void LUA_NATIVE_CAM_USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE()
	{
		CAM::USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE(sol::stack_object camName)
	{
		CAM::USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE(camName.is<const char*>() ? camName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_CAM_FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE()
	{
		CAM::FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE(int seatIndex)
	{
		CAM::SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE(seatIndex);
	}

	static bool LUA_NATIVE_CAM_IS_AIM_CAM_ACTIVE()
	{
		auto retval = (bool)CAM::IS_AIM_CAM_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE()
	{
		auto retval = (bool)CAM::IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_FIRST_PERSON_AIM_CAM_ACTIVE()
	{
		auto retval = (bool)CAM::IS_FIRST_PERSON_AIM_CAM_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_CAM_DISABLE_AIM_CAM_THIS_UPDATE()
	{
		CAM::DISABLE_AIM_CAM_THIS_UPDATE();
	}

	static float LUA_NATIVE_CAM_GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR()
	{
		auto retval = CAM::GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR(float zoomFactor)
	{
		CAM::SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR(zoomFactor);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE(float p0, float p1)
	{
		CAM::SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(float p0, float p1)
	{
		CAM::SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(float p0, float p1)
	{
		CAM::SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE(p0, p1);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0)
	{
		CAM::SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(float p0)
	{
		CAM::SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE(bool p0)
	{
		CAM::SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE()
	{
		CAM::FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE();
	}

	static Vector3 LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_COORD()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_COORD();
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_ROT(int rotationOrder)
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_ROT(rotationOrder);
		return retval;
	}

	static Vector3 LUA_NATIVE_CAM_GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT(Player player, int rotationOrder)
	{
		auto retval = CAM::GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT(player, rotationOrder);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FOV()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_FOV();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV(Player player)
	{
		auto retval = CAM::GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV(player);
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_NEAR_CLIP()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_NEAR_CLIP();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FAR_CLIP()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_FAR_CLIP();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_NEAR_DOF()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_NEAR_DOF();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FAR_DOF()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_FAR_DOF();
		return retval;
	}

	static float LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH()
	{
		auto retval = CAM::GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_COORD_HINT(float x, float y, float z, int duration, int blendOutDuration, int blendInDuration, int p6)
	{
		CAM::SET_GAMEPLAY_COORD_HINT(x, y, z, duration, blendOutDuration, blendInDuration, p6);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_PED_HINT(Ped ped, float x1, float y1, float z1, bool p4, int duration, int blendOutDuration, int blendInDuration)
	{
		CAM::SET_GAMEPLAY_PED_HINT(ped, x1, y1, z1, p4, duration, blendOutDuration, blendInDuration);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_VEHICLE_HINT(Vehicle vehicle, float offsetX, float offsetY, float offsetZ, bool p4, int time, int easeInTime, int easeOutTime)
	{
		CAM::SET_GAMEPLAY_VEHICLE_HINT(vehicle, offsetX, offsetY, offsetZ, p4, time, easeInTime, easeOutTime);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_OBJECT_HINT(Object object, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime)
	{
		CAM::SET_GAMEPLAY_OBJECT_HINT(object, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_ENTITY_HINT(Entity entity, float xOffset, float yOffset, float zOffset, bool p4, int time, int easeInTime, int easeOutTime, int p8)
	{
		CAM::SET_GAMEPLAY_ENTITY_HINT(entity, xOffset, yOffset, zOffset, p4, time, easeInTime, easeOutTime, p8);
	}

	static bool LUA_NATIVE_CAM_IS_GAMEPLAY_HINT_ACTIVE()
	{
		auto retval = (bool)CAM::IS_GAMEPLAY_HINT_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_CAM_STOP_GAMEPLAY_HINT(bool p0)
	{
		CAM::STOP_GAMEPLAY_HINT(p0);
	}

	static void LUA_NATIVE_CAM_STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE(bool p0)
	{
		CAM::STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE(p0);
	}

	static void LUA_NATIVE_CAM_STOP_CODE_GAMEPLAY_HINT(bool p0)
	{
		CAM::STOP_CODE_GAMEPLAY_HINT(p0);
	}

	static bool LUA_NATIVE_CAM_IS_CODE_GAMEPLAY_HINT_ACTIVE()
	{
		auto retval = (bool)CAM::IS_CODE_GAMEPLAY_HINT_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_FOV(float FOV)
	{
		CAM::SET_GAMEPLAY_HINT_FOV(FOV);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR(float value)
	{
		CAM::SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR(value);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET(float value)
	{
		CAM::SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET(value);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET(float xOffset)
	{
		CAM::SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET(xOffset);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET(float yOffset)
	{
		CAM::SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET(yOffset);
	}

	static void LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE(bool toggle)
	{
		CAM::SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE(toggle);
	}

	static void LUA_NATIVE_CAM_SET_CINEMATIC_BUTTON_ACTIVE(bool p0)
	{
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(p0);
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_CAM_RENDERING()
	{
		auto retval = (bool)CAM::IS_CINEMATIC_CAM_RENDERING();
		return retval;
	}

	static void LUA_NATIVE_CAM_SHAKE_CINEMATIC_CAM(sol::stack_object shakeType, float amount)
	{
		CAM::SHAKE_CINEMATIC_CAM(shakeType.is<const char*>() ? shakeType.as<const char*>() : nullptr, amount);
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_CAM_SHAKING()
	{
		auto retval = (bool)CAM::IS_CINEMATIC_CAM_SHAKING();
		return retval;
	}

	static void LUA_NATIVE_CAM_SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(float p0)
	{
		CAM::SET_CINEMATIC_CAM_SHAKE_AMPLITUDE(p0);
	}

	static void LUA_NATIVE_CAM_STOP_CINEMATIC_CAM_SHAKING(bool p0)
	{
		CAM::STOP_CINEMATIC_CAM_SHAKING(p0);
	}

	static void LUA_NATIVE_CAM_DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE()
	{
		CAM::DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE()
	{
		CAM::DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE()
	{
		CAM::INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE();
	}

	static void LUA_NATIVE_CAM_INVALIDATE_IDLE_CAM()
	{
		CAM::INVALIDATE_IDLE_CAM();
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_IDLE_CAM_RENDERING()
	{
		auto retval = (bool)CAM::IS_CINEMATIC_IDLE_CAM_RENDERING();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING()
	{
		auto retval = (bool)CAM::IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING();
		return retval;
	}

	static void LUA_NATIVE_CAM_CREATE_CINEMATIC_SHOT(Hash p0, int time, bool p2, Entity entity)
	{
		CAM::CREATE_CINEMATIC_SHOT(p0, time, p2, entity);
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_SHOT_ACTIVE(Hash p0)
	{
		auto retval = (bool)CAM::IS_CINEMATIC_SHOT_ACTIVE(p0);
		return retval;
	}

	static void LUA_NATIVE_CAM_STOP_CINEMATIC_SHOT(Hash p0)
	{
		CAM::STOP_CINEMATIC_SHOT(p0);
	}

	static void LUA_NATIVE_CAM_FORCE_CINEMATIC_RENDERING_THIS_UPDATE(bool toggle)
	{
		CAM::FORCE_CINEMATIC_RENDERING_THIS_UPDATE(toggle);
	}

	static void LUA_NATIVE_CAM_SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE()
	{
		CAM::SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_CINEMATIC_MODE_ACTIVE(bool toggle)
	{
		CAM::SET_CINEMATIC_MODE_ACTIVE(toggle);
	}

	static bool LUA_NATIVE_CAM_IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING()
	{
		auto retval = (bool)CAM::IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING();
		return retval;
	}

	static bool LUA_NATIVE_CAM_DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE()
	{
		auto retval = (bool)CAM::DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_BONNET_CINEMATIC_CAM_RENDERING()
	{
		auto retval = (bool)CAM::IS_BONNET_CINEMATIC_CAM_RENDERING();
		return retval;
	}

	static bool LUA_NATIVE_CAM_IS_CINEMATIC_CAM_INPUT_ACTIVE()
	{
		auto retval = (bool)CAM::IS_CINEMATIC_CAM_INPUT_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_CAM_IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE()
	{
		CAM::IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE()
	{
		CAM::BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_STOP_CUTSCENE_CAM_SHAKING(Any p0)
	{
		CAM::STOP_CUTSCENE_CAM_SHAKING(p0);
	}

	static void LUA_NATIVE_CAM_SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE(float p0)
	{
		CAM::SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE(p0);
	}

	static Ped LUA_NATIVE_CAM_GET_FOCUS_PED_ON_SCREEN(float p0, int p1, float p2, float p3, float p4, float p5, float p6, int p7, int p8)
	{
		auto retval = CAM::GET_FOCUS_PED_ON_SCREEN(p0, p1, p2, p3, p4, p5, p6, p7, p8);
		return retval;
	}

	static void LUA_NATIVE_CAM_DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE()
	{
		CAM::DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE();
	}

	static void LUA_NATIVE_CAM_SET_CAM_DEATH_FAIL_EFFECT_STATE(int p0)
	{
		CAM::SET_CAM_DEATH_FAIL_EFFECT_STATE(p0);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_TYPE(Any p0)
	{
		CAM::SET_FIRST_PERSON_FLASH_EFFECT_TYPE(p0);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME(sol::stack_object vehicleName)
	{
		CAM::SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME(vehicleName.is<const char*>() ? vehicleName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH(Hash vehicleModel)
	{
		CAM::SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH(vehicleModel);
	}

	static bool LUA_NATIVE_CAM_IS_ALLOWED_INDEPENDENT_CAMERA_MODES()
	{
		auto retval = (bool)CAM::IS_ALLOWED_INDEPENDENT_CAMERA_MODES();
		return retval;
	}

	static void LUA_NATIVE_CAM_CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE()
	{
		CAM::CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE();
	}

	static float LUA_NATIVE_CAM_REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER()
	{
		auto retval = CAM::REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER();
		return retval;
	}

	void init_native_binding_CAM(sol::state& L)
	{
		auto CAM = L["CAM"].get_or_create<sol::table>();
		CAM.set_function("RENDER_SCRIPT_CAMS", LUA_NATIVE_CAM_RENDER_SCRIPT_CAMS);
		CAM.set_function("STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP", LUA_NATIVE_CAM_STOP_RENDERING_SCRIPT_CAMS_USING_CATCH_UP);
		CAM.set_function("CREATE_CAM", LUA_NATIVE_CAM_CREATE_CAM);
		CAM.set_function("CREATE_CAM_WITH_PARAMS", LUA_NATIVE_CAM_CREATE_CAM_WITH_PARAMS);
		CAM.set_function("CREATE_CAMERA", LUA_NATIVE_CAM_CREATE_CAMERA);
		CAM.set_function("CREATE_CAMERA_WITH_PARAMS", LUA_NATIVE_CAM_CREATE_CAMERA_WITH_PARAMS);
		CAM.set_function("DESTROY_CAM", LUA_NATIVE_CAM_DESTROY_CAM);
		CAM.set_function("DESTROY_ALL_CAMS", LUA_NATIVE_CAM_DESTROY_ALL_CAMS);
		CAM.set_function("DOES_CAM_EXIST", LUA_NATIVE_CAM_DOES_CAM_EXIST);
		CAM.set_function("SET_CAM_ACTIVE", LUA_NATIVE_CAM_SET_CAM_ACTIVE);
		CAM.set_function("IS_CAM_ACTIVE", LUA_NATIVE_CAM_IS_CAM_ACTIVE);
		CAM.set_function("IS_CAM_RENDERING", LUA_NATIVE_CAM_IS_CAM_RENDERING);
		CAM.set_function("GET_RENDERING_CAM", LUA_NATIVE_CAM_GET_RENDERING_CAM);
		CAM.set_function("GET_CAM_COORD", LUA_NATIVE_CAM_GET_CAM_COORD);
		CAM.set_function("GET_CAM_ROT", LUA_NATIVE_CAM_GET_CAM_ROT);
		CAM.set_function("GET_CAM_FOV", LUA_NATIVE_CAM_GET_CAM_FOV);
		CAM.set_function("GET_CAM_NEAR_CLIP", LUA_NATIVE_CAM_GET_CAM_NEAR_CLIP);
		CAM.set_function("GET_CAM_FAR_CLIP", LUA_NATIVE_CAM_GET_CAM_FAR_CLIP);
		CAM.set_function("GET_CAM_NEAR_DOF", LUA_NATIVE_CAM_GET_CAM_NEAR_DOF);
		CAM.set_function("GET_CAM_FAR_DOF", LUA_NATIVE_CAM_GET_CAM_FAR_DOF);
		CAM.set_function("GET_CAM_DOF_STRENGTH", LUA_NATIVE_CAM_GET_CAM_DOF_STRENGTH);
		CAM.set_function("SET_CAM_PARAMS", LUA_NATIVE_CAM_SET_CAM_PARAMS);
		CAM.set_function("SET_CAM_COORD", LUA_NATIVE_CAM_SET_CAM_COORD);
		CAM.set_function("SET_CAM_ROT", LUA_NATIVE_CAM_SET_CAM_ROT);
		CAM.set_function("SET_CAM_FOV", LUA_NATIVE_CAM_SET_CAM_FOV);
		CAM.set_function("SET_CAM_NEAR_CLIP", LUA_NATIVE_CAM_SET_CAM_NEAR_CLIP);
		CAM.set_function("SET_CAM_FAR_CLIP", LUA_NATIVE_CAM_SET_CAM_FAR_CLIP);
		CAM.set_function("FORCE_CAM_FAR_CLIP", LUA_NATIVE_CAM_FORCE_CAM_FAR_CLIP);
		CAM.set_function("SET_CAM_MOTION_BLUR_STRENGTH", LUA_NATIVE_CAM_SET_CAM_MOTION_BLUR_STRENGTH);
		CAM.set_function("SET_CAM_NEAR_DOF", LUA_NATIVE_CAM_SET_CAM_NEAR_DOF);
		CAM.set_function("SET_CAM_FAR_DOF", LUA_NATIVE_CAM_SET_CAM_FAR_DOF);
		CAM.set_function("SET_CAM_DOF_STRENGTH", LUA_NATIVE_CAM_SET_CAM_DOF_STRENGTH);
		CAM.set_function("SET_CAM_DOF_PLANES", LUA_NATIVE_CAM_SET_CAM_DOF_PLANES);
		CAM.set_function("SET_CAM_USE_SHALLOW_DOF_MODE", LUA_NATIVE_CAM_SET_CAM_USE_SHALLOW_DOF_MODE);
		CAM.set_function("SET_USE_HI_DOF", LUA_NATIVE_CAM_SET_USE_HI_DOF);
		CAM.set_function("SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE", LUA_NATIVE_CAM_SET_USE_HI_DOF_ON_SYNCED_SCENE_THIS_UPDATE);
		CAM.set_function("SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE", LUA_NATIVE_CAM_SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE);
		CAM.set_function("SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL", LUA_NATIVE_CAM_SET_CAM_DOF_OVERRIDDEN_FOCUS_DISTANCE_BLEND_LEVEL);
		CAM.set_function("SET_CAM_DOF_FNUMBER_OF_LENS", LUA_NATIVE_CAM_SET_CAM_DOF_FNUMBER_OF_LENS);
		CAM.set_function("SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER", LUA_NATIVE_CAM_SET_CAM_DOF_FOCAL_LENGTH_MULTIPLIER);
		CAM.set_function("SET_CAM_DOF_FOCUS_DISTANCE_BIAS", LUA_NATIVE_CAM_SET_CAM_DOF_FOCUS_DISTANCE_BIAS);
		CAM.set_function("SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE", LUA_NATIVE_CAM_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE);
		CAM.set_function("SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL", LUA_NATIVE_CAM_SET_CAM_DOF_MAX_NEAR_IN_FOCUS_DISTANCE_BLEND_LEVEL);
		CAM.set_function("SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS", LUA_NATIVE_CAM_SET_CAM_DOF_SHOULD_KEEP_LOOK_AT_TARGET_IN_FOCUS);
		CAM.set_function("ATTACH_CAM_TO_ENTITY", LUA_NATIVE_CAM_ATTACH_CAM_TO_ENTITY);
		CAM.set_function("ATTACH_CAM_TO_PED_BONE", LUA_NATIVE_CAM_ATTACH_CAM_TO_PED_BONE);
		CAM.set_function("HARD_ATTACH_CAM_TO_PED_BONE", LUA_NATIVE_CAM_HARD_ATTACH_CAM_TO_PED_BONE);
		CAM.set_function("HARD_ATTACH_CAM_TO_ENTITY", LUA_NATIVE_CAM_HARD_ATTACH_CAM_TO_ENTITY);
		CAM.set_function("ATTACH_CAM_TO_VEHICLE_BONE", LUA_NATIVE_CAM_ATTACH_CAM_TO_VEHICLE_BONE);
		CAM.set_function("DETACH_CAM", LUA_NATIVE_CAM_DETACH_CAM);
		CAM.set_function("SET_CAM_INHERIT_ROLL_VEHICLE", LUA_NATIVE_CAM_SET_CAM_INHERIT_ROLL_VEHICLE);
		CAM.set_function("POINT_CAM_AT_COORD", LUA_NATIVE_CAM_POINT_CAM_AT_COORD);
		CAM.set_function("POINT_CAM_AT_ENTITY", LUA_NATIVE_CAM_POINT_CAM_AT_ENTITY);
		CAM.set_function("POINT_CAM_AT_PED_BONE", LUA_NATIVE_CAM_POINT_CAM_AT_PED_BONE);
		CAM.set_function("STOP_CAM_POINTING", LUA_NATIVE_CAM_STOP_CAM_POINTING);
		CAM.set_function("SET_CAM_AFFECTS_AIMING", LUA_NATIVE_CAM_SET_CAM_AFFECTS_AIMING);
		CAM.set_function("SET_CAM_CONTROLS_MINI_MAP_HEADING", LUA_NATIVE_CAM_SET_CAM_CONTROLS_MINI_MAP_HEADING);
		CAM.set_function("SET_CAM_IS_INSIDE_VEHICLE", LUA_NATIVE_CAM_SET_CAM_IS_INSIDE_VEHICLE);
		CAM.set_function("ALLOW_MOTION_BLUR_DECAY", LUA_NATIVE_CAM_ALLOW_MOTION_BLUR_DECAY);
		CAM.set_function("SET_CAM_DEBUG_NAME", LUA_NATIVE_CAM_SET_CAM_DEBUG_NAME);
		CAM.set_function("GET_DEBUG_CAM", LUA_NATIVE_CAM_GET_DEBUG_CAM);
		CAM.set_function("ADD_CAM_SPLINE_NODE", LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE);
		CAM.set_function("ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME", LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_CAMERA_FRAME);
		CAM.set_function("ADD_CAM_SPLINE_NODE_USING_CAMERA", LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_CAMERA);
		CAM.set_function("ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME", LUA_NATIVE_CAM_ADD_CAM_SPLINE_NODE_USING_GAMEPLAY_FRAME);
		CAM.set_function("SET_CAM_SPLINE_PHASE", LUA_NATIVE_CAM_SET_CAM_SPLINE_PHASE);
		CAM.set_function("GET_CAM_SPLINE_PHASE", LUA_NATIVE_CAM_GET_CAM_SPLINE_PHASE);
		CAM.set_function("GET_CAM_SPLINE_NODE_PHASE", LUA_NATIVE_CAM_GET_CAM_SPLINE_NODE_PHASE);
		CAM.set_function("SET_CAM_SPLINE_DURATION", LUA_NATIVE_CAM_SET_CAM_SPLINE_DURATION);
		CAM.set_function("SET_CAM_SPLINE_SMOOTHING_STYLE", LUA_NATIVE_CAM_SET_CAM_SPLINE_SMOOTHING_STYLE);
		CAM.set_function("GET_CAM_SPLINE_NODE_INDEX", LUA_NATIVE_CAM_GET_CAM_SPLINE_NODE_INDEX);
		CAM.set_function("SET_CAM_SPLINE_NODE_EASE", LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_EASE);
		CAM.set_function("SET_CAM_SPLINE_NODE_VELOCITY_SCALE", LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_VELOCITY_SCALE);
		CAM.set_function("OVERRIDE_CAM_SPLINE_VELOCITY", LUA_NATIVE_CAM_OVERRIDE_CAM_SPLINE_VELOCITY);
		CAM.set_function("OVERRIDE_CAM_SPLINE_MOTION_BLUR", LUA_NATIVE_CAM_OVERRIDE_CAM_SPLINE_MOTION_BLUR);
		CAM.set_function("SET_CAM_SPLINE_NODE_EXTRA_FLAGS", LUA_NATIVE_CAM_SET_CAM_SPLINE_NODE_EXTRA_FLAGS);
		CAM.set_function("IS_CAM_SPLINE_PAUSED", LUA_NATIVE_CAM_IS_CAM_SPLINE_PAUSED);
		CAM.set_function("SET_CAM_ACTIVE_WITH_INTERP", LUA_NATIVE_CAM_SET_CAM_ACTIVE_WITH_INTERP);
		CAM.set_function("IS_CAM_INTERPOLATING", LUA_NATIVE_CAM_IS_CAM_INTERPOLATING);
		CAM.set_function("SHAKE_CAM", LUA_NATIVE_CAM_SHAKE_CAM);
		CAM.set_function("ANIMATED_SHAKE_CAM", LUA_NATIVE_CAM_ANIMATED_SHAKE_CAM);
		CAM.set_function("IS_CAM_SHAKING", LUA_NATIVE_CAM_IS_CAM_SHAKING);
		CAM.set_function("SET_CAM_SHAKE_AMPLITUDE", LUA_NATIVE_CAM_SET_CAM_SHAKE_AMPLITUDE);
		CAM.set_function("STOP_CAM_SHAKING", LUA_NATIVE_CAM_STOP_CAM_SHAKING);
		CAM.set_function("SHAKE_SCRIPT_GLOBAL", LUA_NATIVE_CAM_SHAKE_SCRIPT_GLOBAL);
		CAM.set_function("ANIMATED_SHAKE_SCRIPT_GLOBAL", LUA_NATIVE_CAM_ANIMATED_SHAKE_SCRIPT_GLOBAL);
		CAM.set_function("IS_SCRIPT_GLOBAL_SHAKING", LUA_NATIVE_CAM_IS_SCRIPT_GLOBAL_SHAKING);
		CAM.set_function("STOP_SCRIPT_GLOBAL_SHAKING", LUA_NATIVE_CAM_STOP_SCRIPT_GLOBAL_SHAKING);
		CAM.set_function("TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE", LUA_NATIVE_CAM_TRIGGER_VEHICLE_PART_BROKEN_CAMERA_SHAKE);
		CAM.set_function("PLAY_CAM_ANIM", LUA_NATIVE_CAM_PLAY_CAM_ANIM);
		CAM.set_function("IS_CAM_PLAYING_ANIM", LUA_NATIVE_CAM_IS_CAM_PLAYING_ANIM);
		CAM.set_function("SET_CAM_ANIM_CURRENT_PHASE", LUA_NATIVE_CAM_SET_CAM_ANIM_CURRENT_PHASE);
		CAM.set_function("GET_CAM_ANIM_CURRENT_PHASE", LUA_NATIVE_CAM_GET_CAM_ANIM_CURRENT_PHASE);
		CAM.set_function("PLAY_SYNCHRONIZED_CAM_ANIM", LUA_NATIVE_CAM_PLAY_SYNCHRONIZED_CAM_ANIM);
		CAM.set_function("SET_FLY_CAM_HORIZONTAL_RESPONSE", LUA_NATIVE_CAM_SET_FLY_CAM_HORIZONTAL_RESPONSE);
		CAM.set_function("SET_FLY_CAM_VERTICAL_RESPONSE", LUA_NATIVE_CAM_SET_FLY_CAM_VERTICAL_RESPONSE);
		CAM.set_function("SET_FLY_CAM_MAX_HEIGHT", LUA_NATIVE_CAM_SET_FLY_CAM_MAX_HEIGHT);
		CAM.set_function("SET_FLY_CAM_COORD_AND_CONSTRAIN", LUA_NATIVE_CAM_SET_FLY_CAM_COORD_AND_CONSTRAIN);
		CAM.set_function("SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE", LUA_NATIVE_CAM_SET_FLY_CAM_VERTICAL_CONTROLS_THIS_UPDATE);
		CAM.set_function("WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE", LUA_NATIVE_CAM_WAS_FLY_CAM_CONSTRAINED_ON_PREVIOUS_UDPATE);
		CAM.set_function("IS_SCREEN_FADED_OUT", LUA_NATIVE_CAM_IS_SCREEN_FADED_OUT);
		CAM.set_function("IS_SCREEN_FADED_IN", LUA_NATIVE_CAM_IS_SCREEN_FADED_IN);
		CAM.set_function("IS_SCREEN_FADING_OUT", LUA_NATIVE_CAM_IS_SCREEN_FADING_OUT);
		CAM.set_function("IS_SCREEN_FADING_IN", LUA_NATIVE_CAM_IS_SCREEN_FADING_IN);
		CAM.set_function("DO_SCREEN_FADE_IN", LUA_NATIVE_CAM_DO_SCREEN_FADE_IN);
		CAM.set_function("DO_SCREEN_FADE_OUT", LUA_NATIVE_CAM_DO_SCREEN_FADE_OUT);
		CAM.set_function("SET_WIDESCREEN_BORDERS", LUA_NATIVE_CAM_SET_WIDESCREEN_BORDERS);
		CAM.set_function("ARE_WIDESCREEN_BORDERS_ACTIVE", LUA_NATIVE_CAM_ARE_WIDESCREEN_BORDERS_ACTIVE);
		CAM.set_function("GET_GAMEPLAY_CAM_COORD", LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_COORD);
		CAM.set_function("GET_GAMEPLAY_CAM_ROT", LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_ROT);
		CAM.set_function("GET_GAMEPLAY_CAM_FOV", LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_FOV);
		CAM.set_function("SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_MOTION_BLUR_SCALING_THIS_UPDATE);
		CAM.set_function("SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_MAX_MOTION_BLUR_STRENGTH_THIS_UPDATE);
		CAM.set_function("GET_GAMEPLAY_CAM_RELATIVE_HEADING", LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_RELATIVE_HEADING);
		CAM.set_function("SET_GAMEPLAY_CAM_RELATIVE_HEADING", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_RELATIVE_HEADING);
		CAM.set_function("GET_GAMEPLAY_CAM_RELATIVE_PITCH", LUA_NATIVE_CAM_GET_GAMEPLAY_CAM_RELATIVE_PITCH);
		CAM.set_function("SET_GAMEPLAY_CAM_RELATIVE_PITCH", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_RELATIVE_PITCH);
		CAM.set_function("RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER", LUA_NATIVE_CAM_RESET_GAMEPLAY_CAM_FULL_ATTACH_PARENT_TRANSFORM_TIMER);
		CAM.set_function("FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH", LUA_NATIVE_CAM_FORCE_CAMERA_RELATIVE_HEADING_AND_PITCH);
		CAM.set_function("FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH", LUA_NATIVE_CAM_FORCE_BONNET_CAMERA_RELATIVE_HEADING_AND_PITCH);
		CAM.set_function("SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING", LUA_NATIVE_CAM_SET_FIRST_PERSON_SHOOTER_CAMERA_HEADING);
		CAM.set_function("SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH", LUA_NATIVE_CAM_SET_FIRST_PERSON_SHOOTER_CAMERA_PITCH);
		CAM.set_function("SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME", LUA_NATIVE_CAM_SET_SCRIPTED_CAMERA_IS_FIRST_PERSON_THIS_FRAME);
		CAM.set_function("SHAKE_GAMEPLAY_CAM", LUA_NATIVE_CAM_SHAKE_GAMEPLAY_CAM);
		CAM.set_function("IS_GAMEPLAY_CAM_SHAKING", LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_SHAKING);
		CAM.set_function("SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_SHAKE_AMPLITUDE);
		CAM.set_function("STOP_GAMEPLAY_CAM_SHAKING", LUA_NATIVE_CAM_STOP_GAMEPLAY_CAM_SHAKING);
		CAM.set_function("SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_FOLLOW_PED_THIS_UPDATE);
		CAM.set_function("IS_GAMEPLAY_CAM_RENDERING", LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_RENDERING);
		CAM.set_function("IS_INTERPOLATING_FROM_SCRIPT_CAMS", LUA_NATIVE_CAM_IS_INTERPOLATING_FROM_SCRIPT_CAMS);
		CAM.set_function("IS_INTERPOLATING_TO_SCRIPT_CAMS", LUA_NATIVE_CAM_IS_INTERPOLATING_TO_SCRIPT_CAMS);
		CAM.set_function("SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_STATE);
		CAM.set_function("DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_GAMEPLAY_CAM_ALTITUDE_FOV_SCALING_THIS_UPDATE);
		CAM.set_function("IS_GAMEPLAY_CAM_LOOKING_BEHIND", LUA_NATIVE_CAM_IS_GAMEPLAY_CAM_LOOKING_BEHIND);
		CAM.set_function("SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_IGNORE_ENTITY_COLLISION_THIS_UPDATE);
		CAM.set_function("DISABLE_CAM_COLLISION_FOR_OBJECT", LUA_NATIVE_CAM_DISABLE_CAM_COLLISION_FOR_OBJECT);
		CAM.set_function("BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE", LUA_NATIVE_CAM_BYPASS_CAMERA_COLLISION_BUOYANCY_TEST_THIS_UPDATE);
		CAM.set_function("SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE", LUA_NATIVE_CAM_SET_GAMEPLAY_CAM_ENTITY_TO_LIMIT_FOCUS_OVER_BOUNDING_SPHERE_THIS_UPDATE);
		CAM.set_function("DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_FIRST_PERSON_CAMERA_WATER_CLIPPING_TEST_THIS_UPDATE);
		CAM.set_function("SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_CAM_IGNORE_ATTACH_PARENT_MOVEMENT_THIS_UPDATE);
		CAM.set_function("IS_SPHERE_VISIBLE", LUA_NATIVE_CAM_IS_SPHERE_VISIBLE);
		CAM.set_function("IS_FOLLOW_PED_CAM_ACTIVE", LUA_NATIVE_CAM_IS_FOLLOW_PED_CAM_ACTIVE);
		CAM.set_function("SET_FOLLOW_PED_CAM_THIS_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_THIS_UPDATE);
		CAM.set_function("USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME", LUA_NATIVE_CAM_USE_SCRIPT_CAM_FOR_AMBIENT_POPULATION_ORIGIN_THIS_FRAME);
		CAM.set_function("SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_LADDER_ALIGN_THIS_UPDATE);
		CAM.set_function("SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE);
		CAM.set_function("SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE);
		CAM.set_function("SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_THIRD_PERSON_CAM_ORBIT_DISTANCE_LIMITS_THIS_UPDATE);
		CAM.set_function("GET_THIRD_PERSON_CAM_MIN_ORBIT_DISTANCE_SPRING_", LUA_NATIVE_CAM_GET_THIRD_PERSON_CAM_MIN_ORBIT_DISTANCE_SPRING_);
		CAM.set_function("GET_THIRD_PERSON_CAM_MAX_ORBIT_DISTANCE_SPRING_", LUA_NATIVE_CAM_GET_THIRD_PERSON_CAM_MAX_ORBIT_DISTANCE_SPRING_);
		CAM.set_function("SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE", LUA_NATIVE_CAM_SET_IN_VEHICLE_CAM_STATE_THIS_UPDATE);
		CAM.set_function("DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_ON_FOOT_FIRST_PERSON_VIEW_THIS_UPDATE);
		CAM.set_function("DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_FIRST_PERSON_FLASH_EFFECT_THIS_UPDATE);
		CAM.set_function("BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE", LUA_NATIVE_CAM_BLOCK_FIRST_PERSON_ORIENTATION_RESET_THIS_UPDATE);
		CAM.set_function("GET_FOLLOW_PED_CAM_ZOOM_LEVEL", LUA_NATIVE_CAM_GET_FOLLOW_PED_CAM_ZOOM_LEVEL);
		CAM.set_function("GET_FOLLOW_PED_CAM_VIEW_MODE", LUA_NATIVE_CAM_GET_FOLLOW_PED_CAM_VIEW_MODE);
		CAM.set_function("SET_FOLLOW_PED_CAM_VIEW_MODE", LUA_NATIVE_CAM_SET_FOLLOW_PED_CAM_VIEW_MODE);
		CAM.set_function("IS_FOLLOW_VEHICLE_CAM_ACTIVE", LUA_NATIVE_CAM_IS_FOLLOW_VEHICLE_CAM_ACTIVE);
		CAM.set_function("SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_THIS_UPDATE);
		CAM.set_function("SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_HIGH_ANGLE_MODE_EVERY_UPDATE);
		CAM.set_function("SET_TABLE_GAMES_CAMERA_THIS_UPDATE", LUA_NATIVE_CAM_SET_TABLE_GAMES_CAMERA_THIS_UPDATE);
		CAM.set_function("GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL", LUA_NATIVE_CAM_GET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL);
		CAM.set_function("SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL", LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_ZOOM_LEVEL);
		CAM.set_function("GET_FOLLOW_VEHICLE_CAM_VIEW_MODE", LUA_NATIVE_CAM_GET_FOLLOW_VEHICLE_CAM_VIEW_MODE);
		CAM.set_function("SET_FOLLOW_VEHICLE_CAM_VIEW_MODE", LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_VIEW_MODE);
		CAM.set_function("GET_CAM_VIEW_MODE_FOR_CONTEXT", LUA_NATIVE_CAM_GET_CAM_VIEW_MODE_FOR_CONTEXT);
		CAM.set_function("SET_CAM_VIEW_MODE_FOR_CONTEXT", LUA_NATIVE_CAM_SET_CAM_VIEW_MODE_FOR_CONTEXT);
		CAM.set_function("GET_CAM_ACTIVE_VIEW_MODE_CONTEXT", LUA_NATIVE_CAM_GET_CAM_ACTIVE_VIEW_MODE_CONTEXT);
		CAM.set_function("USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE", LUA_NATIVE_CAM_USE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE);
		CAM.set_function("USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE", LUA_NATIVE_CAM_USE_DEDICATED_STUNT_CAMERA_THIS_UPDATE);
		CAM.set_function("FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE", LUA_NATIVE_CAM_FORCE_VEHICLE_CAM_STUNT_SETTINGS_THIS_UPDATE);
		CAM.set_function("SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE", LUA_NATIVE_CAM_SET_FOLLOW_VEHICLE_CAM_SEAT_THIS_UPDATE);
		CAM.set_function("IS_AIM_CAM_ACTIVE", LUA_NATIVE_CAM_IS_AIM_CAM_ACTIVE);
		CAM.set_function("IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE", LUA_NATIVE_CAM_IS_AIM_CAM_ACTIVE_IN_ACCURATE_MODE);
		CAM.set_function("IS_FIRST_PERSON_AIM_CAM_ACTIVE", LUA_NATIVE_CAM_IS_FIRST_PERSON_AIM_CAM_ACTIVE);
		CAM.set_function("DISABLE_AIM_CAM_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_AIM_CAM_THIS_UPDATE);
		CAM.set_function("GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR", LUA_NATIVE_CAM_GET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR);
		CAM.set_function("SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR", LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR);
		CAM.set_function("SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_ZOOM_FACTOR_LIMITS_THIS_UPDATE);
		CAM.set_function("SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_RELATIVE_HEADING_LIMITS_THIS_UPDATE);
		CAM.set_function("SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE", LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_RELATIVE_PITCH_LIMITS_THIS_UPDATE);
		CAM.set_function("SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE", LUA_NATIVE_CAM_SET_FIRST_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE);
		CAM.set_function("SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE", LUA_NATIVE_CAM_SET_THIRD_PERSON_AIM_CAM_NEAR_CLIP_THIS_UPDATE);
		CAM.set_function("SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE", LUA_NATIVE_CAM_SET_ALLOW_CUSTOM_VEHICLE_DRIVE_BY_CAM_THIS_UPDATE);
		CAM.set_function("FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE", LUA_NATIVE_CAM_FORCE_TIGHTSPACE_CUSTOM_FRAMING_THIS_UPDATE);
		CAM.set_function("GET_FINAL_RENDERED_CAM_COORD", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_COORD);
		CAM.set_function("GET_FINAL_RENDERED_CAM_ROT", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_ROT);
		CAM.set_function("GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT", LUA_NATIVE_CAM_GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_ROT);
		CAM.set_function("GET_FINAL_RENDERED_CAM_FOV", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FOV);
		CAM.set_function("GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV", LUA_NATIVE_CAM_GET_FINAL_RENDERED_REMOTE_PLAYER_CAM_FOV);
		CAM.set_function("GET_FINAL_RENDERED_CAM_NEAR_CLIP", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_NEAR_CLIP);
		CAM.set_function("GET_FINAL_RENDERED_CAM_FAR_CLIP", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FAR_CLIP);
		CAM.set_function("GET_FINAL_RENDERED_CAM_NEAR_DOF", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_NEAR_DOF);
		CAM.set_function("GET_FINAL_RENDERED_CAM_FAR_DOF", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_FAR_DOF);
		CAM.set_function("GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH", LUA_NATIVE_CAM_GET_FINAL_RENDERED_CAM_MOTION_BLUR_STRENGTH);
		CAM.set_function("SET_GAMEPLAY_COORD_HINT", LUA_NATIVE_CAM_SET_GAMEPLAY_COORD_HINT);
		CAM.set_function("SET_GAMEPLAY_PED_HINT", LUA_NATIVE_CAM_SET_GAMEPLAY_PED_HINT);
		CAM.set_function("SET_GAMEPLAY_VEHICLE_HINT", LUA_NATIVE_CAM_SET_GAMEPLAY_VEHICLE_HINT);
		CAM.set_function("SET_GAMEPLAY_OBJECT_HINT", LUA_NATIVE_CAM_SET_GAMEPLAY_OBJECT_HINT);
		CAM.set_function("SET_GAMEPLAY_ENTITY_HINT", LUA_NATIVE_CAM_SET_GAMEPLAY_ENTITY_HINT);
		CAM.set_function("IS_GAMEPLAY_HINT_ACTIVE", LUA_NATIVE_CAM_IS_GAMEPLAY_HINT_ACTIVE);
		CAM.set_function("STOP_GAMEPLAY_HINT", LUA_NATIVE_CAM_STOP_GAMEPLAY_HINT);
		CAM.set_function("STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE", LUA_NATIVE_CAM_STOP_GAMEPLAY_HINT_BEING_CANCELLED_THIS_UPDATE);
		CAM.set_function("STOP_CODE_GAMEPLAY_HINT", LUA_NATIVE_CAM_STOP_CODE_GAMEPLAY_HINT);
		CAM.set_function("IS_CODE_GAMEPLAY_HINT_ACTIVE", LUA_NATIVE_CAM_IS_CODE_GAMEPLAY_HINT_ACTIVE);
		CAM.set_function("SET_GAMEPLAY_HINT_FOV", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_FOV);
		CAM.set_function("SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_FOLLOW_DISTANCE_SCALAR);
		CAM.set_function("SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_BASE_ORBIT_PITCH_OFFSET);
		CAM.set_function("SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_RELATIVE_SIDE_OFFSET);
		CAM.set_function("SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_RELATIVE_VERTICAL_OFFSET);
		CAM.set_function("SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE", LUA_NATIVE_CAM_SET_GAMEPLAY_HINT_CAMERA_BLEND_TO_FOLLOW_PED_MEDIUM_VIEW_MODE);
		CAM.set_function("SET_CINEMATIC_BUTTON_ACTIVE", LUA_NATIVE_CAM_SET_CINEMATIC_BUTTON_ACTIVE);
		CAM.set_function("IS_CINEMATIC_CAM_RENDERING", LUA_NATIVE_CAM_IS_CINEMATIC_CAM_RENDERING);
		CAM.set_function("SHAKE_CINEMATIC_CAM", LUA_NATIVE_CAM_SHAKE_CINEMATIC_CAM);
		CAM.set_function("IS_CINEMATIC_CAM_SHAKING", LUA_NATIVE_CAM_IS_CINEMATIC_CAM_SHAKING);
		CAM.set_function("SET_CINEMATIC_CAM_SHAKE_AMPLITUDE", LUA_NATIVE_CAM_SET_CINEMATIC_CAM_SHAKE_AMPLITUDE);
		CAM.set_function("STOP_CINEMATIC_CAM_SHAKING", LUA_NATIVE_CAM_STOP_CINEMATIC_CAM_SHAKING);
		CAM.set_function("DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_CINEMATIC_BONNET_CAMERA_THIS_UPDATE);
		CAM.set_function("DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_CINEMATIC_VEHICLE_IDLE_MODE_THIS_UPDATE);
		CAM.set_function("INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE", LUA_NATIVE_CAM_INVALIDATE_CINEMATIC_VEHICLE_IDLE_MODE);
		CAM.set_function("INVALIDATE_IDLE_CAM", LUA_NATIVE_CAM_INVALIDATE_IDLE_CAM);
		CAM.set_function("IS_CINEMATIC_IDLE_CAM_RENDERING", LUA_NATIVE_CAM_IS_CINEMATIC_IDLE_CAM_RENDERING);
		CAM.set_function("IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING", LUA_NATIVE_CAM_IS_CINEMATIC_FIRST_PERSON_VEHICLE_INTERIOR_CAM_RENDERING);
		CAM.set_function("CREATE_CINEMATIC_SHOT", LUA_NATIVE_CAM_CREATE_CINEMATIC_SHOT);
		CAM.set_function("IS_CINEMATIC_SHOT_ACTIVE", LUA_NATIVE_CAM_IS_CINEMATIC_SHOT_ACTIVE);
		CAM.set_function("STOP_CINEMATIC_SHOT", LUA_NATIVE_CAM_STOP_CINEMATIC_SHOT);
		CAM.set_function("FORCE_CINEMATIC_RENDERING_THIS_UPDATE", LUA_NATIVE_CAM_FORCE_CINEMATIC_RENDERING_THIS_UPDATE);
		CAM.set_function("SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE", LUA_NATIVE_CAM_SET_CINEMATIC_NEWS_CHANNEL_ACTIVE_THIS_UPDATE);
		CAM.set_function("SET_CINEMATIC_MODE_ACTIVE", LUA_NATIVE_CAM_SET_CINEMATIC_MODE_ACTIVE);
		CAM.set_function("IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING", LUA_NATIVE_CAM_IS_IN_VEHICLE_MOBILE_PHONE_CAMERA_RENDERING);
		CAM.set_function("DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_CINEMATIC_SLOW_MO_THIS_UPDATE);
		CAM.set_function("IS_BONNET_CINEMATIC_CAM_RENDERING", LUA_NATIVE_CAM_IS_BONNET_CINEMATIC_CAM_RENDERING);
		CAM.set_function("IS_CINEMATIC_CAM_INPUT_ACTIVE", LUA_NATIVE_CAM_IS_CINEMATIC_CAM_INPUT_ACTIVE);
		CAM.set_function("IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE", LUA_NATIVE_CAM_IGNORE_MENU_PREFERENCE_FOR_BONNET_CAMERA_THIS_UPDATE);
		CAM.set_function("BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE", LUA_NATIVE_CAM_BYPASS_CUTSCENE_CAM_RENDERING_THIS_UPDATE);
		CAM.set_function("STOP_CUTSCENE_CAM_SHAKING", LUA_NATIVE_CAM_STOP_CUTSCENE_CAM_SHAKING);
		CAM.set_function("SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE", LUA_NATIVE_CAM_SET_CUTSCENE_CAM_FAR_CLIP_THIS_UPDATE);
		CAM.set_function("GET_FOCUS_PED_ON_SCREEN", LUA_NATIVE_CAM_GET_FOCUS_PED_ON_SCREEN);
		CAM.set_function("DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE", LUA_NATIVE_CAM_DISABLE_NEAR_CLIP_SCAN_THIS_UPDATE);
		CAM.set_function("SET_CAM_DEATH_FAIL_EFFECT_STATE", LUA_NATIVE_CAM_SET_CAM_DEATH_FAIL_EFFECT_STATE);
		CAM.set_function("SET_FIRST_PERSON_FLASH_EFFECT_TYPE", LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_TYPE);
		CAM.set_function("SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME", LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_NAME);
		CAM.set_function("SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH", LUA_NATIVE_CAM_SET_FIRST_PERSON_FLASH_EFFECT_VEHICLE_MODEL_HASH);
		CAM.set_function("IS_ALLOWED_INDEPENDENT_CAMERA_MODES", LUA_NATIVE_CAM_IS_ALLOWED_INDEPENDENT_CAMERA_MODES);
		CAM.set_function("CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE", LUA_NATIVE_CAM_CAMERA_PREVENT_COLLISION_SETTINGS_FOR_TRIPLEHEAD_IN_INTERIORS_THIS_UPDATE);
		CAM.set_function("REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER", LUA_NATIVE_CAM_REPLAY_GET_MAX_DISTANCE_ALLOWED_FROM_PLAYER);
	}
}

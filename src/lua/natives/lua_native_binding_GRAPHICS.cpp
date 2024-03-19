#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_GRAPHICS_SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(bool enabled)
	{
		GRAPHICS::SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE(enabled);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_LINE(x1, y1, z1, x2, y2, z2, r, g, b, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_LINE_WITH_TWO_COLOURS(float x1, float y1, float z1, float x2, float y2, float z2, int r1, int g1, int b1, int r2, int g2, int b2, int alpha1, int alpha2)
	{
		GRAPHICS::DRAW_DEBUG_LINE_WITH_TWO_COLOURS(x1, y1, z1, x2, y2, z2, r1, g1, b1, r2, g2, b2, alpha1, alpha2);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_SPHERE(x, y, z, radius, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int r, int g, int b, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_BOX(x1, y1, z1, x2, y2, z2, r, g, b, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_CROSS(float x, float y, float z, float size, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_CROSS(x, y, z, size, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_TEXT(sol::stack_object text, float x, float y, float z, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_TEXT(text.is<const char*>() ? text.as<const char*>() : nullptr, x, y, z, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_DEBUG_TEXT_2D(sol::stack_object text, float x, float y, float z, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_DEBUG_TEXT_2D(text.is<const char*>() ? text.as<const char*>() : nullptr, x, y, z, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_LINE(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_LINE(x1, y1, z1, x2, y2, z2, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_POLY(x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_TEXTURED_POLY(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int red, int green, int blue, int alpha, sol::stack_object textureDict, sol::stack_object textureName, float u1, float v1, float w1, float u2, float v2, float w2, float u3, float v3, float w3)
	{
		GRAPHICS::DRAW_TEXTURED_POLY(x1, y1, z1, x2, y2, z2, x3, y3, z3, red, green, blue, alpha, textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, u1, v1, w1, u2, v2, w2, u3, v3, w3);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_BOX(float x1, float y1, float z1, float x2, float y2, float z2, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_BOX(x1, y1, z1, x2, y2, z2, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_BACKFACECULLING(bool toggle)
	{
		GRAPHICS::SET_BACKFACECULLING(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_DEPTHWRITING(bool toggle)
	{
		GRAPHICS::SET_DEPTHWRITING(toggle);
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_TAKE_MISSION_CREATOR_PHOTO()
	{
		auto retval = (bool)GRAPHICS::BEGIN_TAKE_MISSION_CREATOR_PHOTO();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO()
	{
		auto retval = GRAPHICS::GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO()
	{
		GRAPHICS::FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO();
	}

	static bool LUA_NATIVE_GRAPHICS_LOAD_MISSION_CREATOR_PHOTO(uintptr_t p0, Any p1, Any p2, Any p3)
	{
		auto retval = (bool)GRAPHICS::LOAD_MISSION_CREATOR_PHOTO((Any*)p0, p1, p2, p3);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO(uintptr_t p0)
	{
		auto retval = GRAPHICS::GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO((Any*)p0);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW()
	{
		auto retval = (bool)GRAPHICS::BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW()
	{
		auto retval = GRAPHICS::GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW()
	{
		GRAPHICS::FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW();
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_TAKE_HIGH_QUALITY_PHOTO()
	{
		auto retval = (bool)GRAPHICS::BEGIN_TAKE_HIGH_QUALITY_PHOTO();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO()
	{
		auto retval = GRAPHICS::GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO()
	{
		GRAPHICS::FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO();
	}

	static void LUA_NATIVE_GRAPHICS_SET_TAKEN_PHOTO_IS_MUGSHOT(bool toggle)
	{
		GRAPHICS::SET_TAKEN_PHOTO_IS_MUGSHOT(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO(Any p0, int p1)
	{
		GRAPHICS::SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO(p0, p1);
	}

	static void LUA_NATIVE_GRAPHICS_SET_ON_ISLAND_X_FOR_TAKEN_PHOTO(Any p0)
	{
		GRAPHICS::SET_ON_ISLAND_X_FOR_TAKEN_PHOTO(p0);
	}

	static bool LUA_NATIVE_GRAPHICS_SAVE_HIGH_QUALITY_PHOTO(int unused)
	{
		auto retval = (bool)GRAPHICS::SAVE_HIGH_QUALITY_PHOTO(unused);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO()
	{
		auto retval = GRAPHICS::GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO(Any p0)
	{
		auto retval = (bool)GRAPHICS::BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO(p0);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO(int p0)
	{
		auto retval = GRAPHICS::GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO(p0);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_LOW_QUALITY_PHOTO()
	{
		GRAPHICS::FREE_MEMORY_FOR_LOW_QUALITY_PHOTO();
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_LOW_QUALITY_PHOTO_TO_PHONE(bool p0, bool p1)
	{
		GRAPHICS::DRAW_LOW_QUALITY_PHOTO_TO_PHONE(p0, p1);
	}

	static int LUA_NATIVE_GRAPHICS_GET_MAXIMUM_NUMBER_OF_PHOTOS()
	{
		auto retval = GRAPHICS::GET_MAXIMUM_NUMBER_OF_PHOTOS();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS()
	{
		auto retval = GRAPHICS::GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS()
	{
		auto retval = GRAPHICS::GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS(Any p0)
	{
		auto retval = (bool)GRAPHICS::QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS(p0);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_STATUS_OF_SORTED_LIST_OPERATION(Any p0)
	{
		auto retval = GRAPHICS::GET_STATUS_OF_SORTED_LIST_OPERATION(p0);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_STATUS_OF_SORTED_LIST_OPERATION()
	{
		GRAPHICS::CLEAR_STATUS_OF_SORTED_LIST_OPERATION();
	}

	static bool LUA_NATIVE_GRAPHICS_DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO(Any p0)
	{
		auto retval = (bool)GRAPHICS::DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO(p0);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_LOAD_HIGH_QUALITY_PHOTO(Any p0)
	{
		auto retval = (bool)GRAPHICS::LOAD_HIGH_QUALITY_PHOTO(p0);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_LOAD_HIGH_QUALITY_PHOTO_STATUS(int p0)
	{
		auto retval = GRAPHICS::GET_LOAD_HIGH_QUALITY_PHOTO_STATUS(p0);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_LIGHT_WITH_RANGEEX(float x, float y, float z, int r, int g, int b, float range, float intensity, float shadow)
	{
		GRAPHICS::DRAW_LIGHT_WITH_RANGEEX(x, y, z, r, g, b, range, intensity, shadow);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_LIGHT_WITH_RANGE(float posX, float posY, float posZ, int colorR, int colorG, int colorB, float range, float intensity)
	{
		GRAPHICS::DRAW_LIGHT_WITH_RANGE(posX, posY, posZ, colorR, colorG, colorB, range, intensity);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float hardness, float radius, float falloff)
	{
		GRAPHICS::DRAW_SPOT_LIGHT(posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, hardness, radius, falloff);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SHADOWED_SPOT_LIGHT(float posX, float posY, float posZ, float dirX, float dirY, float dirZ, int colorR, int colorG, int colorB, float distance, float brightness, float roundness, float radius, float falloff, int shadowId)
	{
		GRAPHICS::DRAW_SHADOWED_SPOT_LIGHT(posX, posY, posZ, dirX, dirY, dirZ, colorR, colorG, colorB, distance, brightness, roundness, radius, falloff, shadowId);
	}

	static void LUA_NATIVE_GRAPHICS_FADE_UP_PED_LIGHT(float p0)
	{
		GRAPHICS::FADE_UP_PED_LIGHT(p0);
	}

	static void LUA_NATIVE_GRAPHICS_UPDATE_LIGHTS_ON_ENTITY(Entity entity)
	{
		GRAPHICS::UPDATE_LIGHTS_ON_ENTITY(entity);
	}

	static void LUA_NATIVE_GRAPHICS_SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE(Any p0)
	{
		GRAPHICS::SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE(p0);
	}

	static float LUA_NATIVE_GRAPHICS_GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE()
	{
		auto retval = GRAPHICS::GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_MARKER(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, int p19, bool rotate, sol::stack_object textureDict, sol::stack_object textureName, bool drawOnEnts)
	{
		GRAPHICS::DRAW_MARKER(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, drawOnEnts);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_MARKER_EX(int type, float posX, float posY, float posZ, float dirX, float dirY, float dirZ, float rotX, float rotY, float rotZ, float scaleX, float scaleY, float scaleZ, int red, int green, int blue, int alpha, bool bobUpAndDown, bool faceCamera, Any p19, bool rotate, sol::stack_object textureDict, sol::stack_object textureName, bool drawOnEnts, bool p24, bool p25)
	{
		GRAPHICS::DRAW_MARKER_EX(type, posX, posY, posZ, dirX, dirY, dirZ, rotX, rotY, rotZ, scaleX, scaleY, scaleZ, red, green, blue, alpha, bobUpAndDown, faceCamera, p19, rotate, textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, drawOnEnts, p24, p25);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_MARKER_SPHERE(float x, float y, float z, float radius, int red, int green, int blue, float alpha)
	{
		GRAPHICS::DRAW_MARKER_SPHERE(x, y, z, radius, red, green, blue, alpha);
	}

	static int LUA_NATIVE_GRAPHICS_CREATE_CHECKPOINT(int type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, float diameter, int red, int green, int blue, int alpha, int reserved)
	{
		auto retval = GRAPHICS::CREATE_CHECKPOINT(type, posX1, posY1, posZ1, posX2, posY2, posZ2, diameter, red, green, blue, alpha, reserved);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE(int checkpoint, float scale)
	{
		GRAPHICS::SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE(checkpoint, scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_INSIDE_CYLINDER_SCALE(int checkpoint, float scale)
	{
		GRAPHICS::SET_CHECKPOINT_INSIDE_CYLINDER_SCALE(checkpoint, scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_CYLINDER_HEIGHT(int checkpoint, float nearHeight, float farHeight, float radius)
	{
		GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(checkpoint, nearHeight, farHeight, radius);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_RGBA(int checkpoint, int red, int green, int blue, int alpha)
	{
		GRAPHICS::SET_CHECKPOINT_RGBA(checkpoint, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_RGBA2(int checkpoint, int red, int green, int blue, int alpha)
	{
		GRAPHICS::SET_CHECKPOINT_RGBA2(checkpoint, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM(int checkpoint, float posX, float posY, float posZ, float unkX, float unkY, float unkZ)
	{
		GRAPHICS::SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM(checkpoint, posX, posY, posZ, unkX, unkY, unkZ);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING(int checkpoint)
	{
		GRAPHICS::SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING(checkpoint);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT(int checkpoint)
	{
		GRAPHICS::SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT(checkpoint);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_FORCE_DIRECTION(int checkpoint)
	{
		GRAPHICS::SET_CHECKPOINT_FORCE_DIRECTION(checkpoint);
	}

	static void LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_DIRECTION(int checkpoint, float posX, float posY, float posZ)
	{
		GRAPHICS::SET_CHECKPOINT_DIRECTION(checkpoint, posX, posY, posZ);
	}

	static void LUA_NATIVE_GRAPHICS_DELETE_CHECKPOINT(int checkpoint)
	{
		GRAPHICS::DELETE_CHECKPOINT(checkpoint);
	}

	static void LUA_NATIVE_GRAPHICS_DONT_RENDER_IN_GAME_UI(bool p0)
	{
		GRAPHICS::DONT_RENDER_IN_GAME_UI(p0);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_RENDER_IN_GAME_UI(bool toggle)
	{
		GRAPHICS::FORCE_RENDER_IN_GAME_UI(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_REQUEST_STREAMED_TEXTURE_DICT(sol::stack_object textureDict, bool p1)
	{
		GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, p1);
	}

	static bool LUA_NATIVE_GRAPHICS_HAS_STREAMED_TEXTURE_DICT_LOADED(sol::stack_object textureDict)
	{
		auto retval = (bool)GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(sol::stack_object textureDict)
	{
		GRAPHICS::SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_RECT(float x, float y, float width, float height, int r, int g, int b, int a, bool p8)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, r, g, b, a, p8);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(bool toggle)
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_DRAW_ORDER(int drawOrder)
	{
		GRAPHICS::SET_SCRIPT_GFX_DRAW_ORDER(drawOrder);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_ALIGN(int horizontalAlign, int verticalAlign)
	{
		GRAPHICS::SET_SCRIPT_GFX_ALIGN(horizontalAlign, verticalAlign);
	}

	static void LUA_NATIVE_GRAPHICS_RESET_SCRIPT_GFX_ALIGN()
	{
		GRAPHICS::RESET_SCRIPT_GFX_ALIGN();
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_ALIGN_PARAMS(float x, float y, float w, float h)
	{
		GRAPHICS::SET_SCRIPT_GFX_ALIGN_PARAMS(x, y, w, h);
	}

	static std::tuple<float, float> LUA_NATIVE_GRAPHICS_GET_SCRIPT_GFX_ALIGN_POSITION(float x, float y, float calculatedX, float calculatedY)
	{
		std::tuple<float, float> return_values;
		GRAPHICS::GET_SCRIPT_GFX_ALIGN_POSITION(x, y, &calculatedX, &calculatedY);
		std::get<0>(return_values) = calculatedX;
		std::get<1>(return_values) = calculatedY;

		return return_values;
	}

	static float LUA_NATIVE_GRAPHICS_GET_SAFE_ZONE_SIZE()
	{
		auto retval = GRAPHICS::GET_SAFE_ZONE_SIZE();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SPRITE(sol::stack_object textureDict, sol::stack_object textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, bool p11, Any p12)
	{
		GRAPHICS::DRAW_SPRITE(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, screenX, screenY, width, height, heading, red, green, blue, alpha, p11, p12);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SPRITE_ARX(sol::stack_object textureDict, sol::stack_object textureName, float x, float y, float width, float height, float p6, int red, int green, int blue, int alpha, Any p11, Any p12)
	{
		GRAPHICS::DRAW_SPRITE_ARX(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, x, y, width, height, p6, red, green, blue, alpha, p11, p12);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SPRITE_NAMED_RENDERTARGET(sol::stack_object textureDict, sol::stack_object textureName, float screenX, float screenY, float width, float height, float heading, int red, int green, int blue, int alpha, Any p11)
	{
		GRAPHICS::DRAW_SPRITE_NAMED_RENDERTARGET(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, screenX, screenY, width, height, heading, red, green, blue, alpha, p11);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SPRITE_ARX_WITH_UV(sol::stack_object textureDict, sol::stack_object textureName, float x, float y, float width, float height, float u1, float v1, float u2, float v2, float heading, int red, int green, int blue, int alpha, Any p15)
	{
		GRAPHICS::DRAW_SPRITE_ARX_WITH_UV(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr, x, y, width, height, u1, v1, u2, v2, heading, red, green, blue, alpha, p15);
	}

	static int LUA_NATIVE_GRAPHICS_ADD_ENTITY_ICON(Entity entity, sol::stack_object icon)
	{
		auto retval = GRAPHICS::ADD_ENTITY_ICON(entity, icon.is<const char*>() ? icon.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_ENTITY_ICON_VISIBILITY(Entity entity, bool toggle)
	{
		GRAPHICS::SET_ENTITY_ICON_VISIBILITY(entity, toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_ENTITY_ICON_COLOR(Entity entity, int red, int green, int blue, int alpha)
	{
		GRAPHICS::SET_ENTITY_ICON_COLOR(entity, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_DRAW_ORIGIN(float x, float y, float z, bool p3)
	{
		GRAPHICS::SET_DRAW_ORIGIN(x, y, z, p3);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_DRAW_ORIGIN()
	{
		GRAPHICS::CLEAR_DRAW_ORIGIN();
	}

	static int LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE(sol::stack_object name)
	{
		auto retval = GRAPHICS::SET_BINK_MOVIE(name.is<const char*>() ? name.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_PLAY_BINK_MOVIE(int binkMovie)
	{
		GRAPHICS::PLAY_BINK_MOVIE(binkMovie);
	}

	static void LUA_NATIVE_GRAPHICS_STOP_BINK_MOVIE(int binkMovie)
	{
		GRAPHICS::STOP_BINK_MOVIE(binkMovie);
	}

	static void LUA_NATIVE_GRAPHICS_RELEASE_BINK_MOVIE(int binkMovie)
	{
		GRAPHICS::RELEASE_BINK_MOVIE(binkMovie);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_BINK_MOVIE(int binkMovie, float p1, float p2, float p3, float p4, float p5, int r, int g, int b, int a)
	{
		GRAPHICS::DRAW_BINK_MOVIE(binkMovie, p1, p2, p3, p4, p5, r, g, b, a);
	}

	static void LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_TIME(int binkMovie, float progress)
	{
		GRAPHICS::SET_BINK_MOVIE_TIME(binkMovie, progress);
	}

	static float LUA_NATIVE_GRAPHICS_GET_BINK_MOVIE_TIME(int binkMovie)
	{
		auto retval = GRAPHICS::GET_BINK_MOVIE_TIME(binkMovie);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_VOLUME(int binkMovie, float value)
	{
		GRAPHICS::SET_BINK_MOVIE_VOLUME(binkMovie, value);
	}

	static void LUA_NATIVE_GRAPHICS_ATTACH_TV_AUDIO_TO_ENTITY(Entity entity)
	{
		GRAPHICS::ATTACH_TV_AUDIO_TO_ENTITY(entity);
	}

	static void LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_AUDIO_FRONTEND(int binkMovie, bool p1)
	{
		GRAPHICS::SET_BINK_MOVIE_AUDIO_FRONTEND(binkMovie, p1);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_AUDIO_FRONTEND(bool toggle)
	{
		GRAPHICS::SET_TV_AUDIO_FRONTEND(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_BINK_SHOULD_SKIP(int binkMovie, bool bShouldSkip)
	{
		GRAPHICS::SET_BINK_SHOULD_SKIP(binkMovie, bShouldSkip);
	}

	static int LUA_NATIVE_GRAPHICS_LOAD_MOVIE_MESH_SET(sol::stack_object movieMeshSetName)
	{
		auto retval = GRAPHICS::LOAD_MOVIE_MESH_SET(movieMeshSetName.is<const char*>() ? movieMeshSetName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_RELEASE_MOVIE_MESH_SET(int movieMeshSet)
	{
		GRAPHICS::RELEASE_MOVIE_MESH_SET(movieMeshSet);
	}

	static int LUA_NATIVE_GRAPHICS_QUERY_MOVIE_MESH_SET_STATE(Any p0)
	{
		auto retval = GRAPHICS::QUERY_MOVIE_MESH_SET_STATE(p0);
		return retval;
	}

	static std::tuple<int, int> LUA_NATIVE_GRAPHICS_GET_SCREEN_RESOLUTION(int x, int y)
	{
		std::tuple<int, int> return_values;
		GRAPHICS::GET_SCREEN_RESOLUTION(&x, &y);
		std::get<0>(return_values) = x;
		std::get<1>(return_values) = y;

		return return_values;
	}

	static std::tuple<int, int> LUA_NATIVE_GRAPHICS_GET_ACTUAL_SCREEN_RESOLUTION(int x, int y)
	{
		std::tuple<int, int> return_values;
		GRAPHICS::GET_ACTUAL_SCREEN_RESOLUTION(&x, &y);
		std::get<0>(return_values) = x;
		std::get<1>(return_values) = y;

		return return_values;
	}

	static float LUA_NATIVE_GRAPHICS_GET_ASPECT_RATIO(bool b)
	{
		auto retval = GRAPHICS::GET_ASPECT_RATIO(b);
		return retval;
	}

	static float LUA_NATIVE_GRAPHICS_GET_SCREEN_ASPECT_RATIO()
	{
		auto retval = GRAPHICS::GET_SCREEN_ASPECT_RATIO();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_GET_IS_WIDESCREEN()
	{
		auto retval = (bool)GRAPHICS::GET_IS_WIDESCREEN();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_GET_IS_HIDEF()
	{
		auto retval = (bool)GRAPHICS::GET_IS_HIDEF();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9()
	{
		GRAPHICS::ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9();
	}

	static void LUA_NATIVE_GRAPHICS_SET_NIGHTVISION(bool toggle)
	{
		GRAPHICS::SET_NIGHTVISION(toggle);
	}

	static bool LUA_NATIVE_GRAPHICS_GET_REQUESTINGNIGHTVISION()
	{
		auto retval = (bool)GRAPHICS::GET_REQUESTINGNIGHTVISION();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_GET_USINGNIGHTVISION()
	{
		auto retval = (bool)GRAPHICS::GET_USINGNIGHTVISION();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_EXPOSURETWEAK(bool toggle)
	{
		GRAPHICS::SET_EXPOSURETWEAK(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_EXPOSURE_READBACK(bool toggle)
	{
		GRAPHICS::FORCE_EXPOSURE_READBACK(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_OVERRIDE_NIGHTVISION_LIGHT_RANGE(float p0)
	{
		GRAPHICS::OVERRIDE_NIGHTVISION_LIGHT_RANGE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_NOISEOVERIDE(bool toggle)
	{
		GRAPHICS::SET_NOISEOVERIDE(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_NOISINESSOVERIDE(float value)
	{
		GRAPHICS::SET_NOISINESSOVERIDE(value);
	}

	static std::tuple<bool, float, float> LUA_NATIVE_GRAPHICS_GET_SCREEN_COORD_FROM_WORLD_COORD(float worldX, float worldY, float worldZ, float screenX, float screenY)
	{
		std::tuple<bool, float, float> return_values;
		std::get<0>(return_values) = (bool)GRAPHICS::GET_SCREEN_COORD_FROM_WORLD_COORD(worldX, worldY, worldZ, &screenX, &screenY);
		std::get<1>(return_values) = screenX;
		std::get<2>(return_values) = screenY;

		return return_values;
	}

	static Vector3 LUA_NATIVE_GRAPHICS_GET_TEXTURE_RESOLUTION(sol::stack_object textureDict, sol::stack_object textureName)
	{
		auto retval = GRAPHICS::GET_TEXTURE_RESOLUTION(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_OVERRIDE_PED_CREW_LOGO_TEXTURE(Ped ped, sol::stack_object txd, sol::stack_object txn)
	{
		auto retval = (bool)GRAPHICS::OVERRIDE_PED_CREW_LOGO_TEXTURE(ped, txd.is<const char*>() ? txd.as<const char*>() : nullptr, txn.is<const char*>() ? txn.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_DISTANCE_BLUR_STRENGTH_OVERRIDE(float p0)
	{
		GRAPHICS::SET_DISTANCE_BLUR_STRENGTH_OVERRIDE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_FLASH(float p0, float p1, float fadeIn, float duration, float fadeOut)
	{
		GRAPHICS::SET_FLASH(p0, p1, fadeIn, duration, fadeOut);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_OCCLUSION_THIS_FRAME()
	{
		GRAPHICS::DISABLE_OCCLUSION_THIS_FRAME();
	}

	static void LUA_NATIVE_GRAPHICS_SET_ARTIFICIAL_LIGHTS_STATE(bool state)
	{
		GRAPHICS::SET_ARTIFICIAL_LIGHTS_STATE(state);
	}

	static void LUA_NATIVE_GRAPHICS_SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(bool toggle)
	{
		GRAPHICS::SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_HDTEX_THIS_FRAME()
	{
		GRAPHICS::DISABLE_HDTEX_THIS_FRAME();
	}

	static int LUA_NATIVE_GRAPHICS_CREATE_TRACKED_POINT()
	{
		auto retval = GRAPHICS::CREATE_TRACKED_POINT();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_TRACKED_POINT_INFO(int point, float x, float y, float z, float radius)
	{
		GRAPHICS::SET_TRACKED_POINT_INFO(point, x, y, z, radius);
	}

	static bool LUA_NATIVE_GRAPHICS_IS_TRACKED_POINT_VISIBLE(int point)
	{
		auto retval = (bool)GRAPHICS::IS_TRACKED_POINT_VISIBLE(point);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DESTROY_TRACKED_POINT(int point)
	{
		GRAPHICS::DESTROY_TRACKED_POINT(point);
	}

	static int LUA_NATIVE_GRAPHICS_SET_GRASS_CULL_SPHERE(float p0, float p1, float p2, float p3)
	{
		auto retval = GRAPHICS::SET_GRASS_CULL_SPHERE(p0, p1, p2, p3);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_GRASS_CULL_SPHERE(int handle)
	{
		GRAPHICS::REMOVE_GRASS_CULL_SPHERE(handle);
	}

	static void LUA_NATIVE_GRAPHICS_PROCGRASS_ENABLE_CULLSPHERE(int handle, float x, float y, float z, float scale)
	{
		GRAPHICS::PROCGRASS_ENABLE_CULLSPHERE(handle, x, y, z, scale);
	}

	static void LUA_NATIVE_GRAPHICS_PROCGRASS_DISABLE_CULLSPHERE(int handle)
	{
		GRAPHICS::PROCGRASS_DISABLE_CULLSPHERE(handle);
	}

	static bool LUA_NATIVE_GRAPHICS_PROCGRASS_IS_CULLSPHERE_ENABLED(int handle)
	{
		auto retval = (bool)GRAPHICS::PROCGRASS_IS_CULLSPHERE_ENABLED(handle);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_PROCGRASS_ENABLE_AMBSCALESCAN()
	{
		GRAPHICS::PROCGRASS_ENABLE_AMBSCALESCAN();
	}

	static void LUA_NATIVE_GRAPHICS_PROCGRASS_DISABLE_AMBSCALESCAN()
	{
		GRAPHICS::PROCGRASS_DISABLE_AMBSCALESCAN();
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_PROCOBJ_CREATION()
	{
		GRAPHICS::DISABLE_PROCOBJ_CREATION();
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_PROCOBJ_CREATION()
	{
		GRAPHICS::ENABLE_PROCOBJ_CREATION();
	}

	static void LUA_NATIVE_GRAPHICS_GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE(float x, float y, float z, Any p3, float p4, float p5, float p6, float scale)
	{
		GRAPHICS::GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE(x, y, z, p3, p4, p5, p6, scale);
	}

	static void LUA_NATIVE_GRAPHICS_GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE(float x, float y, float z, float radius, float p4, float p5, float p6)
	{
		GRAPHICS::GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE(x, y, z, radius, p4, p5, p6);
	}

	static void LUA_NATIVE_GRAPHICS_GRASSBATCH_DISABLE_FLATTENING()
	{
		GRAPHICS::GRASSBATCH_DISABLE_FLATTENING();
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_INIT_SESSION()
	{
		GRAPHICS::CASCADE_SHADOWS_INIT_SESSION();
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_CASCADE_BOUNDS(Any p0, bool p1, float p2, float p3, float p4, float p5, bool p6, float p7)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_CASCADE_BOUNDS(p0, p1, p2, p3, p4, p5, p6, p7);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE(float p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE(float p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT(float p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_BOUND_POSITION(Any p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_BOUND_POSITION(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER(bool toggle)
	{
		GRAPHICS::CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED(bool p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE(sol::stack_object type)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE(type.is<const char*>() ? type.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE()
	{
		GRAPHICS::CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE();
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_AIRCRAFT_MODE(bool p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_AIRCRAFT_MODE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE(bool p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE(float p0)
	{
		GRAPHICS::CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_ENABLE_FREEZER(bool p0)
	{
		GRAPHICS::CASCADE_SHADOWS_ENABLE_FREEZER(p0);
	}

	static void LUA_NATIVE_GRAPHICS_WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY(Any p0)
	{
		GRAPHICS::WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY(p0);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_ENABLED(bool toggle)
	{
		GRAPHICS::GOLF_TRAIL_SET_ENABLED(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_PATH(float p0, float p1, float p2, float p3, float p4, float p5, float p6, float p7, bool p8)
	{
		GRAPHICS::GOLF_TRAIL_SET_PATH(p0, p1, p2, p3, p4, p5, p6, p7, p8);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_RADIUS(float p0, float p1, float p2)
	{
		GRAPHICS::GOLF_TRAIL_SET_RADIUS(p0, p1, p2);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_COLOUR(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8, int p9, int p10, int p11)
	{
		GRAPHICS::GOLF_TRAIL_SET_COLOUR(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_TESSELLATION(int p0, int p1)
	{
		GRAPHICS::GOLF_TRAIL_SET_TESSELLATION(p0, p1);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE(bool p0)
	{
		GRAPHICS::GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FIXED_CONTROL_POINT(int type, float xPos, float yPos, float zPos, float p4, int red, int green, int blue, int alpha)
	{
		GRAPHICS::GOLF_TRAIL_SET_FIXED_CONTROL_POINT(type, xPos, yPos, zPos, p4, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_SHADER_PARAMS(float p0, float p1, float p2, float p3, float p4)
	{
		GRAPHICS::GOLF_TRAIL_SET_SHADER_PARAMS(p0, p1, p2, p3, p4);
	}

	static void LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FACING(bool p0)
	{
		GRAPHICS::GOLF_TRAIL_SET_FACING(p0);
	}

	static float LUA_NATIVE_GRAPHICS_GOLF_TRAIL_GET_MAX_HEIGHT()
	{
		auto retval = GRAPHICS::GOLF_TRAIL_GET_MAX_HEIGHT();
		return retval;
	}

	static Vector3 LUA_NATIVE_GRAPHICS_GOLF_TRAIL_GET_VISUAL_CONTROL_POINT(int p0)
	{
		auto retval = GRAPHICS::GOLF_TRAIL_GET_VISUAL_CONTROL_POINT(p0);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_SEETHROUGH(bool toggle)
	{
		GRAPHICS::SET_SEETHROUGH(toggle);
	}

	static bool LUA_NATIVE_GRAPHICS_GET_USINGSEETHROUGH()
	{
		auto retval = (bool)GRAPHICS::GET_USINGSEETHROUGH();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_RESET()
	{
		GRAPHICS::SEETHROUGH_RESET();
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_FADE_STARTDISTANCE(float distance)
	{
		GRAPHICS::SEETHROUGH_SET_FADE_STARTDISTANCE(distance);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_FADE_ENDDISTANCE(float distance)
	{
		GRAPHICS::SEETHROUGH_SET_FADE_ENDDISTANCE(distance);
	}

	static float LUA_NATIVE_GRAPHICS_SEETHROUGH_GET_MAX_THICKNESS()
	{
		auto retval = GRAPHICS::SEETHROUGH_GET_MAX_THICKNESS();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_MAX_THICKNESS(float thickness)
	{
		GRAPHICS::SEETHROUGH_SET_MAX_THICKNESS(thickness);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_NOISE_MIN(float amount)
	{
		GRAPHICS::SEETHROUGH_SET_NOISE_MIN(amount);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_NOISE_MAX(float amount)
	{
		GRAPHICS::SEETHROUGH_SET_NOISE_MAX(amount);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HILIGHT_INTENSITY(float intensity)
	{
		GRAPHICS::SEETHROUGH_SET_HILIGHT_INTENSITY(intensity);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HIGHLIGHT_NOISE(float noise)
	{
		GRAPHICS::SEETHROUGH_SET_HIGHLIGHT_NOISE(noise);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HEATSCALE(int index, float heatScale)
	{
		GRAPHICS::SEETHROUGH_SET_HEATSCALE(index, heatScale);
	}

	static void LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_COLOR_NEAR(int red, int green, int blue)
	{
		GRAPHICS::SEETHROUGH_SET_COLOR_NEAR(red, green, blue);
	}

	static void LUA_NATIVE_GRAPHICS_SET_MOTIONBLUR_MAX_VEL_SCALER(float p0)
	{
		GRAPHICS::SET_MOTIONBLUR_MAX_VEL_SCALER(p0);
	}

	static float LUA_NATIVE_GRAPHICS_GET_MOTIONBLUR_MAX_VEL_SCALER()
	{
		auto retval = GRAPHICS::GET_MOTIONBLUR_MAX_VEL_SCALER();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_FORCE_MOTIONBLUR(bool toggle)
	{
		GRAPHICS::SET_FORCE_MOTIONBLUR(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_TOGGLE_PLAYER_DAMAGE_OVERLAY(bool toggle)
	{
		GRAPHICS::TOGGLE_PLAYER_DAMAGE_OVERLAY(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_RESET_ADAPTATION(int p0)
	{
		GRAPHICS::RESET_ADAPTATION(p0);
	}

	static bool LUA_NATIVE_GRAPHICS_TRIGGER_SCREENBLUR_FADE_IN(float transitionTime)
	{
		auto retval = (bool)GRAPHICS::TRIGGER_SCREENBLUR_FADE_IN(transitionTime);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_TRIGGER_SCREENBLUR_FADE_OUT(float transitionTime)
	{
		auto retval = (bool)GRAPHICS::TRIGGER_SCREENBLUR_FADE_OUT(transitionTime);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_SCREENBLUR_FADE()
	{
		GRAPHICS::DISABLE_SCREENBLUR_FADE();
	}

	static float LUA_NATIVE_GRAPHICS_GET_SCREENBLUR_FADE_CURRENT_TIME()
	{
		auto retval = GRAPHICS::GET_SCREENBLUR_FADE_CURRENT_TIME();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_IS_SCREENBLUR_FADE_RUNNING()
	{
		auto retval = (bool)GRAPHICS::IS_SCREENBLUR_FADE_RUNNING();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_TOGGLE_PAUSED_RENDERPHASES(bool toggle)
	{
		GRAPHICS::TOGGLE_PAUSED_RENDERPHASES(toggle);
	}

	static bool LUA_NATIVE_GRAPHICS_GET_TOGGLE_PAUSED_RENDERPHASES_STATUS()
	{
		auto retval = (bool)GRAPHICS::GET_TOGGLE_PAUSED_RENDERPHASES_STATUS();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_RESET_PAUSED_RENDERPHASES()
	{
		GRAPHICS::RESET_PAUSED_RENDERPHASES();
	}

	static void LUA_NATIVE_GRAPHICS_GRAB_PAUSEMENU_OWNERSHIP()
	{
		GRAPHICS::GRAB_PAUSEMENU_OWNERSHIP();
	}

	static void LUA_NATIVE_GRAPHICS_SET_HIDOF_OVERRIDE(bool p0, bool p1, float nearplaneOut, float nearplaneIn, float farplaneOut, float farplaneIn)
	{
		GRAPHICS::SET_HIDOF_OVERRIDE(p0, p1, nearplaneOut, nearplaneIn, farplaneOut, farplaneIn);
	}

	static void LUA_NATIVE_GRAPHICS_SET_LOCK_ADAPTIVE_DOF_DISTANCE(bool p0)
	{
		GRAPHICS::SET_LOCK_ADAPTIVE_DOF_DISTANCE(p0);
	}

	static bool LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_TOGGLE(bool p0)
	{
		auto retval = (bool)GRAPHICS::PHONEPHOTOEDITOR_TOGGLE(p0);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_IS_ACTIVE()
	{
		auto retval = (bool)GRAPHICS::PHONEPHOTOEDITOR_IS_ACTIVE();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_SET_FRAME_TXD(sol::stack_object textureDict, bool p1)
	{
		auto retval = (bool)GRAPHICS::PHONEPHOTOEDITOR_SET_FRAME_TXD(textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, p1);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_AT_COORD(sol::stack_object effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis)
	{
		auto retval = (bool)GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(sol::stack_object effectName, float xPos, float yPos, float zPos, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)
	{
		auto retval = (bool)GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, xPos, yPos, zPos, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(sol::stack_object effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)
	{
		auto retval = (bool)GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(sol::stack_object effectName, Ped ped, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)
	{
		auto retval = (bool)GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, ped, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(sol::stack_object effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ)
	{
		auto retval = (bool)GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(sol::stack_object effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, float scale, bool axisX, bool axisY, bool axisZ)
	{
		auto retval = (bool)GRAPHICS::START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, scale, axisX, axisY, axisZ);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(sol::stack_object effectName, Entity entity, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, int boneIndex, float scale, bool axisX, bool axisY, bool axisZ)
	{
		auto retval = (bool)GRAPHICS::START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, boneIndex, scale, axisX, axisY, axisZ);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_COLOUR(float r, float g, float b)
	{
		GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_COLOUR(r, g, b);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_ALPHA(float alpha)
	{
		GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_ALPHA(alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_SCALE(float scale)
	{
		GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_SCALE(scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE(float p0, float p1, float scale)
	{
		GRAPHICS::SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE(p0, p1, scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR(bool toggle)
	{
		GRAPHICS::SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR(toggle);
	}

	static int LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_AT_COORD(sol::stack_object effectName, float x, float y, float z, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, bool p11)
	{
		auto retval = GRAPHICS::START_PARTICLE_FX_LOOPED_AT_COORD(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, x, y, z, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, p11);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_PED_BONE(sol::stack_object effectName, Ped ped, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)
	{
		auto retval = GRAPHICS::START_PARTICLE_FX_LOOPED_ON_PED_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, ped, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_ENTITY(sol::stack_object effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis)
	{
		auto retval = GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(sol::stack_object effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis)
	{
		auto retval = GRAPHICS::START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(sol::stack_object effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a)
	{
		auto retval = GRAPHICS::START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, scale, xAxis, yAxis, zAxis, r, g, b, a);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(sol::stack_object effectName, Entity entity, float xOffset, float yOffset, float zOffset, float xRot, float yRot, float zRot, int boneIndex, float scale, bool xAxis, bool yAxis, bool zAxis, float r, float g, float b, float a)
	{
		auto retval = GRAPHICS::START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, entity, xOffset, yOffset, zOffset, xRot, yRot, zRot, boneIndex, scale, xAxis, yAxis, zAxis, r, g, b, a);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_STOP_PARTICLE_FX_LOOPED(int ptfxHandle, bool p1)
	{
		GRAPHICS::STOP_PARTICLE_FX_LOOPED(ptfxHandle, p1);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX(int ptfxHandle, bool p1)
	{
		GRAPHICS::REMOVE_PARTICLE_FX(ptfxHandle, p1);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX_FROM_ENTITY(Entity entity)
	{
		GRAPHICS::REMOVE_PARTICLE_FX_FROM_ENTITY(entity);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX_IN_RANGE(float X, float Y, float Z, float radius)
	{
		GRAPHICS::REMOVE_PARTICLE_FX_IN_RANGE(X, Y, Z, radius);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR(Any p0, Any p1)
	{
		GRAPHICS::FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR(p0, p1);
	}

	static bool LUA_NATIVE_GRAPHICS_DOES_PARTICLE_FX_LOOPED_EXIST(int ptfxHandle)
	{
		auto retval = (bool)GRAPHICS::DOES_PARTICLE_FX_LOOPED_EXIST(ptfxHandle);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_OFFSETS(int ptfxHandle, float x, float y, float z, float rotX, float rotY, float rotZ)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_OFFSETS(ptfxHandle, x, y, z, rotX, rotY, rotZ);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_EVOLUTION(int ptfxHandle, sol::stack_object propertyName, float amount, bool noNetwork)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_EVOLUTION(ptfxHandle, propertyName.is<const char*>() ? propertyName.as<const char*>() : nullptr, amount, noNetwork);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_COLOUR(int ptfxHandle, float r, float g, float b, bool p4)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_COLOUR(ptfxHandle, r, g, b, p4);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_ALPHA(int ptfxHandle, float alpha)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_ALPHA(ptfxHandle, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_SCALE(int ptfxHandle, float scale)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_SCALE(ptfxHandle, scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST(int ptfxHandle, float range)
	{
		GRAPHICS::SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST(ptfxHandle, range);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_CAMERA_BIAS_(int ptfxHandle, float p1)
	{
		GRAPHICS::_SET_PARTICLE_FX_LOOPED_CAMERA_BIAS(ptfxHandle, p1);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(bool p0)
	{
		GRAPHICS::SET_PARTICLE_FX_CAM_INSIDE_VEHICLE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(Vehicle vehicle, bool p1)
	{
		GRAPHICS::SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE(vehicle, p1);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_SHOOTOUT_BOAT(Any p0)
	{
		GRAPHICS::SET_PARTICLE_FX_SHOOTOUT_BOAT(p0);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_PARTICLE_FX_SHOOTOUT_BOAT()
	{
		GRAPHICS::CLEAR_PARTICLE_FX_SHOOTOUT_BOAT();
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BLOOD_SCALE(Any p0)
	{
		GRAPHICS::SET_PARTICLE_FX_BLOOD_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_IN_WATER_PTFX(bool toggle)
	{
		GRAPHICS::DISABLE_IN_WATER_PTFX(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_DOWNWASH_PTFX(bool toggle)
	{
		GRAPHICS::DISABLE_DOWNWASH_PTFX(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE(float scale)
	{
		GRAPHICS::SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE(scale);
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_CLOWN_BLOOD_VFX(bool toggle)
	{
		GRAPHICS::ENABLE_CLOWN_BLOOD_VFX(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_ALIEN_BLOOD_VFX(bool toggle)
	{
		GRAPHICS::ENABLE_ALIEN_BLOOD_VFX(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_IMPACT_SCALE(float scale)
	{
		GRAPHICS::SET_PARTICLE_FX_BULLET_IMPACT_SCALE(scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE(float p0)
	{
		GRAPHICS::SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT(bool p0)
	{
		GRAPHICS::SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE(float p0)
	{
		GRAPHICS::SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FOOT_LODRANGE_SCALE(float p0)
	{
		GRAPHICS::SET_PARTICLE_FX_FOOT_LODRANGE_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FOOT_OVERRIDE_NAME(sol::stack_object p0)
	{
		GRAPHICS::SET_PARTICLE_FX_FOOT_OVERRIDE_NAME(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SKIDMARK_RANGE_SCALE(float scale)
	{
		GRAPHICS::SET_SKIDMARK_RANGE_SCALE(scale);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG(Any p0)
	{
		GRAPHICS::SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG(p0);
	}

	static void LUA_NATIVE_GRAPHICS_REGISTER_POSTFX_BULLET_IMPACT(float weaponWorldPosX, float weaponWorldPosY, float weaponWorldPosZ, float intensity)
	{
		GRAPHICS::REGISTER_POSTFX_BULLET_IMPACT(weaponWorldPosX, weaponWorldPosY, weaponWorldPosZ, intensity);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD(bool p0)
	{
		GRAPHICS::FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD(p0);
	}

	static void LUA_NATIVE_GRAPHICS_USE_PARTICLE_FX_ASSET(sol::stack_object name)
	{
		GRAPHICS::USE_PARTICLE_FX_ASSET(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_OVERRIDE(sol::stack_object oldAsset, sol::stack_object newAsset)
	{
		GRAPHICS::SET_PARTICLE_FX_OVERRIDE(oldAsset.is<const char*>() ? oldAsset.as<const char*>() : nullptr, newAsset.is<const char*>() ? newAsset.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_RESET_PARTICLE_FX_OVERRIDE(sol::stack_object name)
	{
		GRAPHICS::RESET_PARTICLE_FX_OVERRIDE(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_GRAPHICS_START_VEHICLE_PARTICLE_FX_LOOPED_(Vehicle vehicle, sol::stack_object effectName, bool frontBack, bool leftRight, bool localOnly)
	{
		auto retval = GRAPHICS::_START_VEHICLE_PARTICLE_FX_LOOPED(vehicle, effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, frontBack, leftRight, localOnly);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS(bool p0)
	{
		GRAPHICS::SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS(p0);
	}

	static void LUA_NATIVE_GRAPHICS_SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL(float p0)
	{
		GRAPHICS::SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL(p0);
	}

	static void LUA_NATIVE_GRAPHICS_WASH_DECALS_IN_RANGE(float x, float y, float z, float range, float p4)
	{
		GRAPHICS::WASH_DECALS_IN_RANGE(x, y, z, range, p4);
	}

	static void LUA_NATIVE_GRAPHICS_WASH_DECALS_FROM_VEHICLE(Vehicle vehicle, float p1)
	{
		GRAPHICS::WASH_DECALS_FROM_VEHICLE(vehicle, p1);
	}

	static void LUA_NATIVE_GRAPHICS_FADE_DECALS_IN_RANGE(float x, float y, float z, float p3, float p4)
	{
		GRAPHICS::FADE_DECALS_IN_RANGE(x, y, z, p3, p4);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_DECALS_IN_RANGE(float x, float y, float z, float range)
	{
		GRAPHICS::REMOVE_DECALS_IN_RANGE(x, y, z, range);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_OBJECT(Object obj)
	{
		GRAPHICS::REMOVE_DECALS_FROM_OBJECT(obj);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_OBJECT_FACING(Object obj, float x, float y, float z)
	{
		GRAPHICS::REMOVE_DECALS_FROM_OBJECT_FACING(obj, x, y, z);
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_VEHICLE(Vehicle vehicle)
	{
		GRAPHICS::REMOVE_DECALS_FROM_VEHICLE(vehicle);
	}

	static int LUA_NATIVE_GRAPHICS_ADD_DECAL(int decalType, float posX, float posY, float posZ, float p4, float p5, float p6, float p7, float p8, float p9, float width, float height, float rCoef, float gCoef, float bCoef, float opacity, float timeout, bool p17, bool p18, bool p19)
	{
		auto retval = GRAPHICS::ADD_DECAL(decalType, posX, posY, posZ, p4, p5, p6, p7, p8, p9, width, height, rCoef, gCoef, bCoef, opacity, timeout, p17, p18, p19);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_ADD_PETROL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency)
	{
		auto retval = GRAPHICS::ADD_PETROL_DECAL(x, y, z, groundLvl, width, transparency);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_ADD_OIL_DECAL(float x, float y, float z, float groundLvl, float width, float transparency)
	{
		auto retval = GRAPHICS::ADD_OIL_DECAL(x, y, z, groundLvl, width, transparency);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_START_PETROL_TRAIL_DECALS(float p0)
	{
		GRAPHICS::START_PETROL_TRAIL_DECALS(p0);
	}

	static void LUA_NATIVE_GRAPHICS_ADD_PETROL_TRAIL_DECAL_INFO(float x, float y, float z, float p3)
	{
		GRAPHICS::ADD_PETROL_TRAIL_DECAL_INFO(x, y, z, p3);
	}

	static void LUA_NATIVE_GRAPHICS_END_PETROL_TRAIL_DECALS()
	{
		GRAPHICS::END_PETROL_TRAIL_DECALS();
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_DECAL(int decal)
	{
		GRAPHICS::REMOVE_DECAL(decal);
	}

	static bool LUA_NATIVE_GRAPHICS_IS_DECAL_ALIVE(int decal)
	{
		auto retval = (bool)GRAPHICS::IS_DECAL_ALIVE(decal);
		return retval;
	}

	static float LUA_NATIVE_GRAPHICS_GET_DECAL_WASH_LEVEL(int decal)
	{
		auto retval = GRAPHICS::GET_DECAL_WASH_LEVEL(decal);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME()
	{
		GRAPHICS::SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME();
	}

	static void LUA_NATIVE_GRAPHICS_SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME()
	{
		GRAPHICS::SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME();
	}

	static void LUA_NATIVE_GRAPHICS_SET_DISABLE_DECAL_RENDERING_THIS_FRAME()
	{
		GRAPHICS::SET_DISABLE_DECAL_RENDERING_THIS_FRAME();
	}

	static bool LUA_NATIVE_GRAPHICS_GET_IS_PETROL_DECAL_IN_RANGE(float xCoord, float yCoord, float zCoord, float radius)
	{
		auto retval = (bool)GRAPHICS::GET_IS_PETROL_DECAL_IN_RANGE(xCoord, yCoord, zCoord, radius);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_PATCH_DECAL_DIFFUSE_MAP(int decalType, sol::stack_object textureDict, sol::stack_object textureName)
	{
		GRAPHICS::PATCH_DECAL_DIFFUSE_MAP(decalType, textureDict.is<const char*>() ? textureDict.as<const char*>() : nullptr, textureName.is<const char*>() ? textureName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_UNPATCH_DECAL_DIFFUSE_MAP(int decalType)
	{
		GRAPHICS::UNPATCH_DECAL_DIFFUSE_MAP(decalType);
	}

	static void LUA_NATIVE_GRAPHICS_MOVE_VEHICLE_DECALS(Any p0, Any p1)
	{
		GRAPHICS::MOVE_VEHICLE_DECALS(p0, p1);
	}

	static bool LUA_NATIVE_GRAPHICS_ADD_VEHICLE_CREW_EMBLEM(Vehicle vehicle, Ped ped, int boneIndex, float x1, float x2, float x3, float y1, float y2, float y3, float z1, float z2, float z3, float scale, Any p13, int alpha)
	{
		auto retval = (bool)GRAPHICS::ADD_VEHICLE_CREW_EMBLEM(vehicle, ped, boneIndex, x1, x2, x3, y1, y2, y3, z1, z2, z3, scale, p13, alpha);
		return retval;
	}

	static std::tuple<bool, int> LUA_NATIVE_GRAPHICS_ABORT_VEHICLE_CREW_EMBLEM_REQUEST(int p0)
	{
		std::tuple<bool, int> return_values;
		std::get<0>(return_values) = (bool)GRAPHICS::ABORT_VEHICLE_CREW_EMBLEM_REQUEST(&p0);
		std::get<1>(return_values) = p0;

		return return_values;
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_VEHICLE_CREW_EMBLEM(Vehicle vehicle, int p1)
	{
		GRAPHICS::REMOVE_VEHICLE_CREW_EMBLEM(vehicle, p1);
	}

	static int LUA_NATIVE_GRAPHICS_GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE(Vehicle vehicle, int p1)
	{
		auto retval = GRAPHICS::GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE(vehicle, p1);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_DOES_VEHICLE_HAVE_CREW_EMBLEM(Vehicle vehicle, int p1)
	{
		auto retval = (bool)GRAPHICS::DOES_VEHICLE_HAVE_CREW_EMBLEM(vehicle, p1);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_COMPOSITE_SHOTGUN_DECALS(bool toggle)
	{
		GRAPHICS::DISABLE_COMPOSITE_SHOTGUN_DECALS(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_SCUFF_DECALS(bool toggle)
	{
		GRAPHICS::DISABLE_SCUFF_DECALS(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_DECAL_BULLET_IMPACT_RANGE_SCALE(float p0)
	{
		GRAPHICS::SET_DECAL_BULLET_IMPACT_RANGE_SCALE(p0);
	}

	static void LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_NAME(sol::stack_object name)
	{
		GRAPHICS::OVERRIDE_INTERIOR_SMOKE_NAME(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_LEVEL(float level)
	{
		GRAPHICS::OVERRIDE_INTERIOR_SMOKE_LEVEL(level);
	}

	static void LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_END()
	{
		GRAPHICS::OVERRIDE_INTERIOR_SMOKE_END();
	}

	static void LUA_NATIVE_GRAPHICS_REGISTER_NOIR_LENS_EFFECT()
	{
		GRAPHICS::REGISTER_NOIR_LENS_EFFECT();
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_VEHICLE_DISTANTLIGHTS(bool toggle)
	{
		GRAPHICS::DISABLE_VEHICLE_DISTANTLIGHTS(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS(bool p0)
	{
		GRAPHICS::RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS(p0);
	}

	static void LUA_NATIVE_GRAPHICS_REQUEST_EARLY_LIGHT_CHECK()
	{
		GRAPHICS::REQUEST_EARLY_LIGHT_CHECK();
	}

	static void LUA_NATIVE_GRAPHICS_USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(bool toggle)
	{
		GRAPHICS::USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_ALLOW_SNOW_FOOT_VFX_ON_ICE_(bool toggle)
	{
		GRAPHICS::_FORCE_ALLOW_SNOW_FOOT_VFX_ON_ICE(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(bool toggle)
	{
		GRAPHICS::USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_REGION_VFX(Any p0)
	{
		GRAPHICS::DISABLE_REGION_VFX(p0);
	}

	static void LUA_NATIVE_GRAPHICS_FORCE_GROUND_SNOW_PASS_(bool toggle)
	{
		GRAPHICS::_FORCE_GROUND_SNOW_PASS(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_PRESET_INTERIOR_AMBIENT_CACHE(sol::stack_object timecycleModifierName)
	{
		GRAPHICS::PRESET_INTERIOR_AMBIENT_CACHE(timecycleModifierName.is<const char*>() ? timecycleModifierName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TIMECYCLE_MODIFIER(sol::stack_object modifierName)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER(modifierName.is<const char*>() ? modifierName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TIMECYCLE_MODIFIER_STRENGTH(float strength)
	{
		GRAPHICS::SET_TIMECYCLE_MODIFIER_STRENGTH(strength);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TRANSITION_TIMECYCLE_MODIFIER(sol::stack_object modifierName, float transition)
	{
		GRAPHICS::SET_TRANSITION_TIMECYCLE_MODIFIER(modifierName.is<const char*>() ? modifierName.as<const char*>() : nullptr, transition);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER(float strength)
	{
		GRAPHICS::SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER(strength);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_TIMECYCLE_MODIFIER()
	{
		GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
	}

	static int LUA_NATIVE_GRAPHICS_GET_TIMECYCLE_MODIFIER_INDEX()
	{
		auto retval = GRAPHICS::GET_TIMECYCLE_MODIFIER_INDEX();
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX()
	{
		auto retval = GRAPHICS::GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_GET_IS_TIMECYCLE_TRANSITIONING_OUT()
	{
		auto retval = (bool)GRAPHICS::GET_IS_TIMECYCLE_TRANSITIONING_OUT();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_PUSH_TIMECYCLE_MODIFIER()
	{
		GRAPHICS::PUSH_TIMECYCLE_MODIFIER();
	}

	static void LUA_NATIVE_GRAPHICS_POP_TIMECYCLE_MODIFIER()
	{
		GRAPHICS::POP_TIMECYCLE_MODIFIER();
	}

	static void LUA_NATIVE_GRAPHICS_SET_CURRENT_PLAYER_TCMODIFIER(sol::stack_object modifierName)
	{
		GRAPHICS::SET_CURRENT_PLAYER_TCMODIFIER(modifierName.is<const char*>() ? modifierName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_PLAYER_TCMODIFIER_TRANSITION(float value)
	{
		GRAPHICS::SET_PLAYER_TCMODIFIER_TRANSITION(value);
	}

	static void LUA_NATIVE_GRAPHICS_SET_NEXT_PLAYER_TCMODIFIER(sol::stack_object modifierName)
	{
		GRAPHICS::SET_NEXT_PLAYER_TCMODIFIER(modifierName.is<const char*>() ? modifierName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_ADD_TCMODIFIER_OVERRIDE(sol::stack_object modifierName1, sol::stack_object modifierName2)
	{
		GRAPHICS::ADD_TCMODIFIER_OVERRIDE(modifierName1.is<const char*>() ? modifierName1.as<const char*>() : nullptr, modifierName2.is<const char*>() ? modifierName2.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_ALL_TCMODIFIER_OVERRIDES(sol::stack_object p0)
	{
		GRAPHICS::CLEAR_ALL_TCMODIFIER_OVERRIDES(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SET_EXTRA_TCMODIFIER(sol::stack_object modifierName)
	{
		GRAPHICS::SET_EXTRA_TCMODIFIER(modifierName.is<const char*>() ? modifierName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_EXTRA_TCMODIFIER()
	{
		GRAPHICS::CLEAR_EXTRA_TCMODIFIER();
	}

	static int LUA_NATIVE_GRAPHICS_GET_EXTRA_TCMODIFIER()
	{
		auto retval = GRAPHICS::GET_EXTRA_TCMODIFIER();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_MOON_CYCLE_OVERRIDE(float strength)
	{
		GRAPHICS::ENABLE_MOON_CYCLE_OVERRIDE(strength);
	}

	static void LUA_NATIVE_GRAPHICS_DISABLE_MOON_CYCLE_OVERRIDE()
	{
		GRAPHICS::DISABLE_MOON_CYCLE_OVERRIDE();
	}

	static int LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE(sol::stack_object scaleformName)
	{
		auto retval = GRAPHICS::REQUEST_SCALEFORM_MOVIE(scaleformName.is<const char*>() ? scaleformName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN(sol::stack_object scaleformName)
	{
		auto retval = GRAPHICS::REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN(scaleformName.is<const char*>() ? scaleformName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_INSTANCE(sol::stack_object scaleformName)
	{
		auto retval = GRAPHICS::REQUEST_SCALEFORM_MOVIE_INSTANCE(scaleformName.is<const char*>() ? scaleformName.as<const char*>() : nullptr);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED(sol::stack_object scaleformName)
	{
		auto retval = GRAPHICS::REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED(scaleformName.is<const char*>() ? scaleformName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_MOVIE_LOADED(int scaleformHandle)
	{
		auto retval = (bool)GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(scaleformHandle);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_IS_ACTIVE_SCALEFORM_MOVIE_DELETING(int val)
	{
		auto retval = (bool)GRAPHICS::IS_ACTIVE_SCALEFORM_MOVIE_DELETING(val);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_IS_SCALEFORM_MOVIE_DELETING(int val)
	{
		auto retval = (bool)GRAPHICS::IS_SCALEFORM_MOVIE_DELETING(val);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_MOVIE_FILENAME_LOADED(sol::stack_object scaleformName)
	{
		auto retval = (bool)GRAPHICS::HAS_SCALEFORM_MOVIE_FILENAME_LOADED(scaleformName.is<const char*>() ? scaleformName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(int scaleformHandle)
	{
		auto retval = (bool)GRAPHICS::HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT(scaleformHandle);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(int scaleformHandle)
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED(&scaleformHandle);
		return scaleformHandle;
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(int scaleform, bool toggle)
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME(scaleform, toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT(int scaleformHandle, bool toggle)
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT(scaleformHandle, toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT(int scaleformHandle, bool toggle)
	{
		GRAPHICS::SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT(scaleformHandle, toggle);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE(int scaleformHandle, float x, float y, float width, float height, int red, int green, int blue, int alpha, int p9)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE(scaleformHandle, x, y, width, height, red, green, blue, alpha, p9);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_FULLSCREEN(int scaleform, int red, int green, int blue, int alpha, int p5)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN(scaleform, red, green, blue, alpha, p5);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(int scaleform1, int scaleform2, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED(scaleform1, scaleform2, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_3D(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_3D(scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder);
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_3D_SOLID(int scaleform, float posX, float posY, float posZ, float rotX, float rotY, float rotZ, float p7, float p8, float p9, float scaleX, float scaleY, float scaleZ, int rotationOrder)
	{
		GRAPHICS::DRAW_SCALEFORM_MOVIE_3D_SOLID(scaleform, posX, posY, posZ, rotX, rotY, rotZ, p7, p8, p9, scaleX, scaleY, scaleZ, rotationOrder);
	}

	static void LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD(int scaleform, sol::stack_object method)
	{
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD(scaleform, method.is<const char*>() ? method.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER(int scaleform, sol::stack_object methodName, float param1, float param2, float param3, float param4, float param5)
	{
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER(scaleform, methodName.is<const char*>() ? methodName.as<const char*>() : nullptr, param1, param2, param3, param4, param5);
	}

	static void LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING(int scaleform, sol::stack_object methodName, sol::stack_object param1, sol::stack_object param2, sol::stack_object param3, sol::stack_object param4, sol::stack_object param5)
	{
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING(scaleform, methodName.is<const char*>() ? methodName.as<const char*>() : nullptr, param1.is<const char*>() ? param1.as<const char*>() : nullptr, param2.is<const char*>() ? param2.as<const char*>() : nullptr, param3.is<const char*>() ? param3.as<const char*>() : nullptr, param4.is<const char*>() ? param4.as<const char*>() : nullptr, param5.is<const char*>() ? param5.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING(int scaleform, sol::stack_object methodName, float floatParam1, float floatParam2, float floatParam3, float floatParam4, float floatParam5, sol::stack_object stringParam1, sol::stack_object stringParam2, sol::stack_object stringParam3, sol::stack_object stringParam4, sol::stack_object stringParam5)
	{
		GRAPHICS::CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING(scaleform, methodName.is<const char*>() ? methodName.as<const char*>() : nullptr, floatParam1, floatParam2, floatParam3, floatParam4, floatParam5, stringParam1.is<const char*>() ? stringParam1.as<const char*>() : nullptr, stringParam2.is<const char*>() ? stringParam2.as<const char*>() : nullptr, stringParam3.is<const char*>() ? stringParam3.as<const char*>() : nullptr, stringParam4.is<const char*>() ? stringParam4.as<const char*>() : nullptr, stringParam5.is<const char*>() ? stringParam5.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD(int hudComponent, sol::stack_object methodName)
	{
		auto retval = (bool)GRAPHICS::BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD(hudComponent, methodName.is<const char*>() ? methodName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD(int scaleform, sol::stack_object methodName)
	{
		auto retval = (bool)GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD(scaleform, methodName.is<const char*>() ? methodName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(sol::stack_object methodName)
	{
		auto retval = (bool)GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND(methodName.is<const char*>() ? methodName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(sol::stack_object methodName)
	{
		auto retval = (bool)GRAPHICS::BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER(methodName.is<const char*>() ? methodName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_END_SCALEFORM_MOVIE_METHOD()
	{
		GRAPHICS::END_SCALEFORM_MOVIE_METHOD();
	}

	static int LUA_NATIVE_GRAPHICS_END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE()
	{
		auto retval = GRAPHICS::END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(int methodReturn)
	{
		auto retval = (bool)GRAPHICS::IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY(methodReturn);
		return retval;
	}

	static int LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(int methodReturn)
	{
		auto retval = GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT(methodReturn);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(int methodReturn)
	{
		auto retval = (bool)GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL(methodReturn);
		return retval;
	}

	static const char* LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(int methodReturn)
	{
		auto retval = GRAPHICS::GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING(methodReturn);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(int value)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT(value);
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(float value)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT(value);
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(bool value)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL(value);
	}

	static void LUA_NATIVE_GRAPHICS_BEGIN_TEXT_COMMAND_SCALEFORM_STRING(sol::stack_object componentType)
	{
		GRAPHICS::BEGIN_TEXT_COMMAND_SCALEFORM_STRING(componentType.is<const char*>() ? componentType.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_END_TEXT_COMMAND_SCALEFORM_STRING()
	{
		GRAPHICS::END_TEXT_COMMAND_SCALEFORM_STRING();
	}

	static void LUA_NATIVE_GRAPHICS_END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING()
	{
		GRAPHICS::END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING();
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(sol::stack_object string)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(sol::stack_object string)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(sol::stack_object string)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING(string.is<const char*>() ? string.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_GRAPHICS_DOES_LATEST_BRIEF_STRING_EXIST(int p0)
	{
		auto retval = (bool)GRAPHICS::DOES_LATEST_BRIEF_STRING_EXIST(p0);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING(int value)
	{
		GRAPHICS::SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING(value);
	}

	static void LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent)
	{
		GRAPHICS::REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE(hudComponent);
	}

	static bool LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(int hudComponent)
	{
		auto retval = (bool)GRAPHICS::HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED(hudComponent);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE(int hudComponent)
	{
		GRAPHICS::REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE(hudComponent);
	}

	static bool LUA_NATIVE_GRAPHICS_PASS_KEYBOARD_INPUT_TO_SCALEFORM(int scaleformHandle)
	{
		auto retval = (bool)GRAPHICS::PASS_KEYBOARD_INPUT_TO_SCALEFORM(scaleformHandle);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL(int channel)
	{
		GRAPHICS::SET_TV_CHANNEL(channel);
	}

	static int LUA_NATIVE_GRAPHICS_GET_TV_CHANNEL()
	{
		auto retval = GRAPHICS::GET_TV_CHANNEL();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_VOLUME(float volume)
	{
		GRAPHICS::SET_TV_VOLUME(volume);
	}

	static float LUA_NATIVE_GRAPHICS_GET_TV_VOLUME()
	{
		auto retval = GRAPHICS::GET_TV_VOLUME();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_DRAW_TV_CHANNEL(float xPos, float yPos, float xScale, float yScale, float rotation, int red, int green, int blue, int alpha)
	{
		GRAPHICS::DRAW_TV_CHANNEL(xPos, yPos, xScale, yScale, rotation, red, green, blue, alpha);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST(int tvChannel, sol::stack_object playlistName, bool restart)
	{
		GRAPHICS::SET_TV_CHANNEL_PLAYLIST(tvChannel, playlistName.is<const char*>() ? playlistName.as<const char*>() : nullptr, restart);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST_AT_HOUR(int tvChannel, sol::stack_object playlistName, int hour)
	{
		GRAPHICS::SET_TV_CHANNEL_PLAYLIST_AT_HOUR(tvChannel, playlistName.is<const char*>() ? playlistName.as<const char*>() : nullptr, hour);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST_DIRTY_(int tvChannel, bool p1)
	{
		GRAPHICS::_SET_TV_CHANNEL_PLAYLIST_DIRTY(tvChannel, p1);
	}

	static void LUA_NATIVE_GRAPHICS_CLEAR_TV_CHANNEL_PLAYLIST(int tvChannel)
	{
		GRAPHICS::CLEAR_TV_CHANNEL_PLAYLIST(tvChannel);
	}

	static bool LUA_NATIVE_GRAPHICS_IS_PLAYLIST_ON_CHANNEL(int tvChannel, Any p1)
	{
		auto retval = (bool)GRAPHICS::IS_PLAYLIST_ON_CHANNEL(tvChannel, p1);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_IS_TVSHOW_CURRENTLY_PLAYING(Hash videoCliphash)
	{
		auto retval = (bool)GRAPHICS::IS_TVSHOW_CURRENTLY_PLAYING(videoCliphash);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_MOVIE_KEYFRAME_WAIT(bool toggle)
	{
		GRAPHICS::ENABLE_MOVIE_KEYFRAME_WAIT(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_SET_TV_PLAYER_WATCHING_THIS_FRAME(Any p0)
	{
		GRAPHICS::SET_TV_PLAYER_WATCHING_THIS_FRAME(p0);
	}

	static Hash LUA_NATIVE_GRAPHICS_GET_CURRENT_TV_CLIP_NAMEHASH()
	{
		auto retval = GRAPHICS::GET_CURRENT_TV_CLIP_NAMEHASH();
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_ENABLE_MOVIE_SUBTITLES(bool toggle)
	{
		GRAPHICS::ENABLE_MOVIE_SUBTITLES(toggle);
	}

	static bool LUA_NATIVE_GRAPHICS_UI3DSCENE_IS_AVAILABLE()
	{
		auto retval = (bool)GRAPHICS::UI3DSCENE_IS_AVAILABLE();
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_UI3DSCENE_PUSH_PRESET(sol::stack_object presetName)
	{
		auto retval = (bool)GRAPHICS::UI3DSCENE_PUSH_PRESET(presetName.is<const char*>() ? presetName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_UI3DSCENE_ASSIGN_PED_TO_SLOT(sol::stack_object presetName, Ped ped, int slot, float posX, float posY, float posZ)
	{
		auto retval = (bool)GRAPHICS::UI3DSCENE_ASSIGN_PED_TO_SLOT(presetName.is<const char*>() ? presetName.as<const char*>() : nullptr, ped, slot, posX, posY, posZ);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_UI3DSCENE_CLEAR_PATCHED_DATA()
	{
		GRAPHICS::UI3DSCENE_CLEAR_PATCHED_DATA();
	}

	static void LUA_NATIVE_GRAPHICS_UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT(bool toggle)
	{
		GRAPHICS::UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_TERRAINGRID_ACTIVATE(bool toggle)
	{
		GRAPHICS::TERRAINGRID_ACTIVATE(toggle);
	}

	static void LUA_NATIVE_GRAPHICS_TERRAINGRID_SET_PARAMS(float x, float y, float z, float forwardX, float forwardY, float forwardZ, float sizeX, float sizeY, float sizeZ, float gridScale, float glowIntensity, float normalHeight, float heightDiff)
	{
		GRAPHICS::TERRAINGRID_SET_PARAMS(x, y, z, forwardX, forwardY, forwardZ, sizeX, sizeY, sizeZ, gridScale, glowIntensity, normalHeight, heightDiff);
	}

	static void LUA_NATIVE_GRAPHICS_TERRAINGRID_SET_COLOURS(int lowR, int lowG, int lowB, int lowAlpha, int r, int g, int b, int alpha, int highR, int highG, int highB, int highAlpha)
	{
		GRAPHICS::TERRAINGRID_SET_COLOURS(lowR, lowG, lowB, lowAlpha, r, g, b, alpha, highR, highG, highB, highAlpha);
	}

	static void LUA_NATIVE_GRAPHICS_ANIMPOSTFX_PLAY(sol::stack_object effectName, int duration, bool looped)
	{
		GRAPHICS::ANIMPOSTFX_PLAY(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr, duration, looped);
	}

	static void LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP(sol::stack_object effectName)
	{
		GRAPHICS::ANIMPOSTFX_STOP(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr);
	}

	static float LUA_NATIVE_GRAPHICS_ANIMPOSTFX_GET_CURRENT_TIME(sol::stack_object effectName)
	{
		auto retval = GRAPHICS::ANIMPOSTFX_GET_CURRENT_TIME(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_GRAPHICS_ANIMPOSTFX_IS_RUNNING(sol::stack_object effectName)
	{
		auto retval = (bool)GRAPHICS::ANIMPOSTFX_IS_RUNNING(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP_ALL()
	{
		GRAPHICS::ANIMPOSTFX_STOP_ALL();
	}

	static void LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS(sol::stack_object effectName)
	{
		GRAPHICS::ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS(effectName.is<const char*>() ? effectName.as<const char*>() : nullptr);
	}

	void init_native_binding_GRAPHICS(sol::state& L)
	{
		auto GRAPHICS = L["GRAPHICS"].get_or_create<sol::table>();
		GRAPHICS.set_function("SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE", LUA_NATIVE_GRAPHICS_SET_DEBUG_LINES_AND_SPHERES_DRAWING_ACTIVE);
		GRAPHICS.set_function("DRAW_DEBUG_LINE", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_LINE);
		GRAPHICS.set_function("DRAW_DEBUG_LINE_WITH_TWO_COLOURS", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_LINE_WITH_TWO_COLOURS);
		GRAPHICS.set_function("DRAW_DEBUG_SPHERE", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_SPHERE);
		GRAPHICS.set_function("DRAW_DEBUG_BOX", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_BOX);
		GRAPHICS.set_function("DRAW_DEBUG_CROSS", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_CROSS);
		GRAPHICS.set_function("DRAW_DEBUG_TEXT", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_TEXT);
		GRAPHICS.set_function("DRAW_DEBUG_TEXT_2D", LUA_NATIVE_GRAPHICS_DRAW_DEBUG_TEXT_2D);
		GRAPHICS.set_function("DRAW_LINE", LUA_NATIVE_GRAPHICS_DRAW_LINE);
		GRAPHICS.set_function("DRAW_POLY", LUA_NATIVE_GRAPHICS_DRAW_POLY);
		GRAPHICS.set_function("DRAW_TEXTURED_POLY", LUA_NATIVE_GRAPHICS_DRAW_TEXTURED_POLY);
		GRAPHICS.set_function("DRAW_BOX", LUA_NATIVE_GRAPHICS_DRAW_BOX);
		GRAPHICS.set_function("SET_BACKFACECULLING", LUA_NATIVE_GRAPHICS_SET_BACKFACECULLING);
		GRAPHICS.set_function("SET_DEPTHWRITING", LUA_NATIVE_GRAPHICS_SET_DEPTHWRITING);
		GRAPHICS.set_function("BEGIN_TAKE_MISSION_CREATOR_PHOTO", LUA_NATIVE_GRAPHICS_BEGIN_TAKE_MISSION_CREATOR_PHOTO);
		GRAPHICS.set_function("GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_TAKE_MISSION_CREATOR_PHOTO);
		GRAPHICS.set_function("FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO", LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO);
		GRAPHICS.set_function("LOAD_MISSION_CREATOR_PHOTO", LUA_NATIVE_GRAPHICS_LOAD_MISSION_CREATOR_PHOTO);
		GRAPHICS.set_function("GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_LOAD_MISSION_CREATOR_PHOTO);
		GRAPHICS.set_function("BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW", LUA_NATIVE_GRAPHICS_BEGIN_CREATE_MISSION_CREATOR_PHOTO_PREVIEW);
		GRAPHICS.set_function("GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_CREATE_MISSION_CREATOR_PHOTO_PREVIEW);
		GRAPHICS.set_function("FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW", LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_MISSION_CREATOR_PHOTO_PREVIEW);
		GRAPHICS.set_function("BEGIN_TAKE_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_BEGIN_TAKE_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_TAKE_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("SET_TAKEN_PHOTO_IS_MUGSHOT", LUA_NATIVE_GRAPHICS_SET_TAKEN_PHOTO_IS_MUGSHOT);
		GRAPHICS.set_function("SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO", LUA_NATIVE_GRAPHICS_SET_ARENA_THEME_AND_VARIATION_FOR_TAKEN_PHOTO);
		GRAPHICS.set_function("SET_ON_ISLAND_X_FOR_TAKEN_PHOTO", LUA_NATIVE_GRAPHICS_SET_ON_ISLAND_X_FOR_TAKEN_PHOTO);
		GRAPHICS.set_function("SAVE_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_SAVE_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_SAVE_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO", LUA_NATIVE_GRAPHICS_BEGIN_CREATE_LOW_QUALITY_COPY_OF_PHOTO);
		GRAPHICS.set_function("GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_CREATE_LOW_QUALITY_COPY_OF_PHOTO);
		GRAPHICS.set_function("FREE_MEMORY_FOR_LOW_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_FREE_MEMORY_FOR_LOW_QUALITY_PHOTO);
		GRAPHICS.set_function("DRAW_LOW_QUALITY_PHOTO_TO_PHONE", LUA_NATIVE_GRAPHICS_DRAW_LOW_QUALITY_PHOTO_TO_PHONE);
		GRAPHICS.set_function("GET_MAXIMUM_NUMBER_OF_PHOTOS", LUA_NATIVE_GRAPHICS_GET_MAXIMUM_NUMBER_OF_PHOTOS);
		GRAPHICS.set_function("GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS", LUA_NATIVE_GRAPHICS_GET_MAXIMUM_NUMBER_OF_CLOUD_PHOTOS);
		GRAPHICS.set_function("GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS", LUA_NATIVE_GRAPHICS_GET_CURRENT_NUMBER_OF_CLOUD_PHOTOS);
		GRAPHICS.set_function("QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS", LUA_NATIVE_GRAPHICS_QUEUE_OPERATION_TO_CREATE_SORTED_LIST_OF_PHOTOS);
		GRAPHICS.set_function("GET_STATUS_OF_SORTED_LIST_OPERATION", LUA_NATIVE_GRAPHICS_GET_STATUS_OF_SORTED_LIST_OPERATION);
		GRAPHICS.set_function("CLEAR_STATUS_OF_SORTED_LIST_OPERATION", LUA_NATIVE_GRAPHICS_CLEAR_STATUS_OF_SORTED_LIST_OPERATION);
		GRAPHICS.set_function("DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO", LUA_NATIVE_GRAPHICS_DOES_THIS_PHOTO_SLOT_CONTAIN_A_VALID_PHOTO);
		GRAPHICS.set_function("LOAD_HIGH_QUALITY_PHOTO", LUA_NATIVE_GRAPHICS_LOAD_HIGH_QUALITY_PHOTO);
		GRAPHICS.set_function("GET_LOAD_HIGH_QUALITY_PHOTO_STATUS", LUA_NATIVE_GRAPHICS_GET_LOAD_HIGH_QUALITY_PHOTO_STATUS);
		GRAPHICS.set_function("DRAW_LIGHT_WITH_RANGEEX", LUA_NATIVE_GRAPHICS_DRAW_LIGHT_WITH_RANGEEX);
		GRAPHICS.set_function("DRAW_LIGHT_WITH_RANGE", LUA_NATIVE_GRAPHICS_DRAW_LIGHT_WITH_RANGE);
		GRAPHICS.set_function("DRAW_SPOT_LIGHT", LUA_NATIVE_GRAPHICS_DRAW_SPOT_LIGHT);
		GRAPHICS.set_function("DRAW_SHADOWED_SPOT_LIGHT", LUA_NATIVE_GRAPHICS_DRAW_SHADOWED_SPOT_LIGHT);
		GRAPHICS.set_function("FADE_UP_PED_LIGHT", LUA_NATIVE_GRAPHICS_FADE_UP_PED_LIGHT);
		GRAPHICS.set_function("UPDATE_LIGHTS_ON_ENTITY", LUA_NATIVE_GRAPHICS_UPDATE_LIGHTS_ON_ENTITY);
		GRAPHICS.set_function("SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE", LUA_NATIVE_GRAPHICS_SET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE);
		GRAPHICS.set_function("GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE", LUA_NATIVE_GRAPHICS_GET_LIGHT_OVERRIDE_MAX_INTENSITY_SCALE);
		GRAPHICS.set_function("DRAW_MARKER", LUA_NATIVE_GRAPHICS_DRAW_MARKER);
		GRAPHICS.set_function("DRAW_MARKER_EX", LUA_NATIVE_GRAPHICS_DRAW_MARKER_EX);
		GRAPHICS.set_function("DRAW_MARKER_SPHERE", LUA_NATIVE_GRAPHICS_DRAW_MARKER_SPHERE);
		GRAPHICS.set_function("CREATE_CHECKPOINT", LUA_NATIVE_GRAPHICS_CREATE_CHECKPOINT);
		GRAPHICS.set_function("SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_INSIDE_CYLINDER_HEIGHT_SCALE);
		GRAPHICS.set_function("SET_CHECKPOINT_INSIDE_CYLINDER_SCALE", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_INSIDE_CYLINDER_SCALE);
		GRAPHICS.set_function("SET_CHECKPOINT_CYLINDER_HEIGHT", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_CYLINDER_HEIGHT);
		GRAPHICS.set_function("SET_CHECKPOINT_RGBA", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_RGBA);
		GRAPHICS.set_function("SET_CHECKPOINT_RGBA2", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_RGBA2);
		GRAPHICS.set_function("SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_CLIPPLANE_WITH_POS_NORM);
		GRAPHICS.set_function("SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_FORCE_OLD_ARROW_POINTING);
		GRAPHICS.set_function("SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_DECAL_ROT_ALIGNED_TO_CAMERA_ROT);
		GRAPHICS.set_function("SET_CHECKPOINT_FORCE_DIRECTION", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_FORCE_DIRECTION);
		GRAPHICS.set_function("SET_CHECKPOINT_DIRECTION", LUA_NATIVE_GRAPHICS_SET_CHECKPOINT_DIRECTION);
		GRAPHICS.set_function("DELETE_CHECKPOINT", LUA_NATIVE_GRAPHICS_DELETE_CHECKPOINT);
		GRAPHICS.set_function("DONT_RENDER_IN_GAME_UI", LUA_NATIVE_GRAPHICS_DONT_RENDER_IN_GAME_UI);
		GRAPHICS.set_function("FORCE_RENDER_IN_GAME_UI", LUA_NATIVE_GRAPHICS_FORCE_RENDER_IN_GAME_UI);
		GRAPHICS.set_function("REQUEST_STREAMED_TEXTURE_DICT", LUA_NATIVE_GRAPHICS_REQUEST_STREAMED_TEXTURE_DICT);
		GRAPHICS.set_function("HAS_STREAMED_TEXTURE_DICT_LOADED", LUA_NATIVE_GRAPHICS_HAS_STREAMED_TEXTURE_DICT_LOADED);
		GRAPHICS.set_function("SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED", LUA_NATIVE_GRAPHICS_SET_STREAMED_TEXTURE_DICT_AS_NO_LONGER_NEEDED);
		GRAPHICS.set_function("DRAW_RECT", LUA_NATIVE_GRAPHICS_DRAW_RECT);
		GRAPHICS.set_function("SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU", LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_DRAW_BEHIND_PAUSEMENU);
		GRAPHICS.set_function("SET_SCRIPT_GFX_DRAW_ORDER", LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_DRAW_ORDER);
		GRAPHICS.set_function("SET_SCRIPT_GFX_ALIGN", LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_ALIGN);
		GRAPHICS.set_function("RESET_SCRIPT_GFX_ALIGN", LUA_NATIVE_GRAPHICS_RESET_SCRIPT_GFX_ALIGN);
		GRAPHICS.set_function("SET_SCRIPT_GFX_ALIGN_PARAMS", LUA_NATIVE_GRAPHICS_SET_SCRIPT_GFX_ALIGN_PARAMS);
		GRAPHICS.set_function("GET_SCRIPT_GFX_ALIGN_POSITION", LUA_NATIVE_GRAPHICS_GET_SCRIPT_GFX_ALIGN_POSITION);
		GRAPHICS.set_function("GET_SAFE_ZONE_SIZE", LUA_NATIVE_GRAPHICS_GET_SAFE_ZONE_SIZE);
		GRAPHICS.set_function("DRAW_SPRITE", LUA_NATIVE_GRAPHICS_DRAW_SPRITE);
		GRAPHICS.set_function("DRAW_SPRITE_ARX", LUA_NATIVE_GRAPHICS_DRAW_SPRITE_ARX);
		GRAPHICS.set_function("DRAW_SPRITE_NAMED_RENDERTARGET", LUA_NATIVE_GRAPHICS_DRAW_SPRITE_NAMED_RENDERTARGET);
		GRAPHICS.set_function("DRAW_SPRITE_ARX_WITH_UV", LUA_NATIVE_GRAPHICS_DRAW_SPRITE_ARX_WITH_UV);
		GRAPHICS.set_function("ADD_ENTITY_ICON", LUA_NATIVE_GRAPHICS_ADD_ENTITY_ICON);
		GRAPHICS.set_function("SET_ENTITY_ICON_VISIBILITY", LUA_NATIVE_GRAPHICS_SET_ENTITY_ICON_VISIBILITY);
		GRAPHICS.set_function("SET_ENTITY_ICON_COLOR", LUA_NATIVE_GRAPHICS_SET_ENTITY_ICON_COLOR);
		GRAPHICS.set_function("SET_DRAW_ORIGIN", LUA_NATIVE_GRAPHICS_SET_DRAW_ORIGIN);
		GRAPHICS.set_function("CLEAR_DRAW_ORIGIN", LUA_NATIVE_GRAPHICS_CLEAR_DRAW_ORIGIN);
		GRAPHICS.set_function("SET_BINK_MOVIE", LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE);
		GRAPHICS.set_function("PLAY_BINK_MOVIE", LUA_NATIVE_GRAPHICS_PLAY_BINK_MOVIE);
		GRAPHICS.set_function("STOP_BINK_MOVIE", LUA_NATIVE_GRAPHICS_STOP_BINK_MOVIE);
		GRAPHICS.set_function("RELEASE_BINK_MOVIE", LUA_NATIVE_GRAPHICS_RELEASE_BINK_MOVIE);
		GRAPHICS.set_function("DRAW_BINK_MOVIE", LUA_NATIVE_GRAPHICS_DRAW_BINK_MOVIE);
		GRAPHICS.set_function("SET_BINK_MOVIE_TIME", LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_TIME);
		GRAPHICS.set_function("GET_BINK_MOVIE_TIME", LUA_NATIVE_GRAPHICS_GET_BINK_MOVIE_TIME);
		GRAPHICS.set_function("SET_BINK_MOVIE_VOLUME", LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_VOLUME);
		GRAPHICS.set_function("ATTACH_TV_AUDIO_TO_ENTITY", LUA_NATIVE_GRAPHICS_ATTACH_TV_AUDIO_TO_ENTITY);
		GRAPHICS.set_function("SET_BINK_MOVIE_AUDIO_FRONTEND", LUA_NATIVE_GRAPHICS_SET_BINK_MOVIE_AUDIO_FRONTEND);
		GRAPHICS.set_function("SET_TV_AUDIO_FRONTEND", LUA_NATIVE_GRAPHICS_SET_TV_AUDIO_FRONTEND);
		GRAPHICS.set_function("SET_BINK_SHOULD_SKIP", LUA_NATIVE_GRAPHICS_SET_BINK_SHOULD_SKIP);
		GRAPHICS.set_function("LOAD_MOVIE_MESH_SET", LUA_NATIVE_GRAPHICS_LOAD_MOVIE_MESH_SET);
		GRAPHICS.set_function("RELEASE_MOVIE_MESH_SET", LUA_NATIVE_GRAPHICS_RELEASE_MOVIE_MESH_SET);
		GRAPHICS.set_function("QUERY_MOVIE_MESH_SET_STATE", LUA_NATIVE_GRAPHICS_QUERY_MOVIE_MESH_SET_STATE);
		GRAPHICS.set_function("GET_SCREEN_RESOLUTION", LUA_NATIVE_GRAPHICS_GET_SCREEN_RESOLUTION);
		GRAPHICS.set_function("GET_ACTUAL_SCREEN_RESOLUTION", LUA_NATIVE_GRAPHICS_GET_ACTUAL_SCREEN_RESOLUTION);
		GRAPHICS.set_function("GET_ASPECT_RATIO", LUA_NATIVE_GRAPHICS_GET_ASPECT_RATIO);
		GRAPHICS.set_function("GET_SCREEN_ASPECT_RATIO", LUA_NATIVE_GRAPHICS_GET_SCREEN_ASPECT_RATIO);
		GRAPHICS.set_function("GET_IS_WIDESCREEN", LUA_NATIVE_GRAPHICS_GET_IS_WIDESCREEN);
		GRAPHICS.set_function("GET_IS_HIDEF", LUA_NATIVE_GRAPHICS_GET_IS_HIDEF);
		GRAPHICS.set_function("ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9", LUA_NATIVE_GRAPHICS_ADJUST_NEXT_POS_SIZE_AS_NORMALIZED_16_9);
		GRAPHICS.set_function("SET_NIGHTVISION", LUA_NATIVE_GRAPHICS_SET_NIGHTVISION);
		GRAPHICS.set_function("GET_REQUESTINGNIGHTVISION", LUA_NATIVE_GRAPHICS_GET_REQUESTINGNIGHTVISION);
		GRAPHICS.set_function("GET_USINGNIGHTVISION", LUA_NATIVE_GRAPHICS_GET_USINGNIGHTVISION);
		GRAPHICS.set_function("SET_EXPOSURETWEAK", LUA_NATIVE_GRAPHICS_SET_EXPOSURETWEAK);
		GRAPHICS.set_function("FORCE_EXPOSURE_READBACK", LUA_NATIVE_GRAPHICS_FORCE_EXPOSURE_READBACK);
		GRAPHICS.set_function("OVERRIDE_NIGHTVISION_LIGHT_RANGE", LUA_NATIVE_GRAPHICS_OVERRIDE_NIGHTVISION_LIGHT_RANGE);
		GRAPHICS.set_function("SET_NOISEOVERIDE", LUA_NATIVE_GRAPHICS_SET_NOISEOVERIDE);
		GRAPHICS.set_function("SET_NOISINESSOVERIDE", LUA_NATIVE_GRAPHICS_SET_NOISINESSOVERIDE);
		GRAPHICS.set_function("GET_SCREEN_COORD_FROM_WORLD_COORD", LUA_NATIVE_GRAPHICS_GET_SCREEN_COORD_FROM_WORLD_COORD);
		GRAPHICS.set_function("GET_TEXTURE_RESOLUTION", LUA_NATIVE_GRAPHICS_GET_TEXTURE_RESOLUTION);
		GRAPHICS.set_function("OVERRIDE_PED_CREW_LOGO_TEXTURE", LUA_NATIVE_GRAPHICS_OVERRIDE_PED_CREW_LOGO_TEXTURE);
		GRAPHICS.set_function("SET_DISTANCE_BLUR_STRENGTH_OVERRIDE", LUA_NATIVE_GRAPHICS_SET_DISTANCE_BLUR_STRENGTH_OVERRIDE);
		GRAPHICS.set_function("SET_FLASH", LUA_NATIVE_GRAPHICS_SET_FLASH);
		GRAPHICS.set_function("DISABLE_OCCLUSION_THIS_FRAME", LUA_NATIVE_GRAPHICS_DISABLE_OCCLUSION_THIS_FRAME);
		GRAPHICS.set_function("SET_ARTIFICIAL_LIGHTS_STATE", LUA_NATIVE_GRAPHICS_SET_ARTIFICIAL_LIGHTS_STATE);
		GRAPHICS.set_function("SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE", LUA_NATIVE_GRAPHICS_SET_ARTIFICIAL_VEHICLE_LIGHTS_STATE);
		GRAPHICS.set_function("DISABLE_HDTEX_THIS_FRAME", LUA_NATIVE_GRAPHICS_DISABLE_HDTEX_THIS_FRAME);
		GRAPHICS.set_function("CREATE_TRACKED_POINT", LUA_NATIVE_GRAPHICS_CREATE_TRACKED_POINT);
		GRAPHICS.set_function("SET_TRACKED_POINT_INFO", LUA_NATIVE_GRAPHICS_SET_TRACKED_POINT_INFO);
		GRAPHICS.set_function("IS_TRACKED_POINT_VISIBLE", LUA_NATIVE_GRAPHICS_IS_TRACKED_POINT_VISIBLE);
		GRAPHICS.set_function("DESTROY_TRACKED_POINT", LUA_NATIVE_GRAPHICS_DESTROY_TRACKED_POINT);
		GRAPHICS.set_function("SET_GRASS_CULL_SPHERE", LUA_NATIVE_GRAPHICS_SET_GRASS_CULL_SPHERE);
		GRAPHICS.set_function("REMOVE_GRASS_CULL_SPHERE", LUA_NATIVE_GRAPHICS_REMOVE_GRASS_CULL_SPHERE);
		GRAPHICS.set_function("PROCGRASS_ENABLE_CULLSPHERE", LUA_NATIVE_GRAPHICS_PROCGRASS_ENABLE_CULLSPHERE);
		GRAPHICS.set_function("PROCGRASS_DISABLE_CULLSPHERE", LUA_NATIVE_GRAPHICS_PROCGRASS_DISABLE_CULLSPHERE);
		GRAPHICS.set_function("PROCGRASS_IS_CULLSPHERE_ENABLED", LUA_NATIVE_GRAPHICS_PROCGRASS_IS_CULLSPHERE_ENABLED);
		GRAPHICS.set_function("PROCGRASS_ENABLE_AMBSCALESCAN", LUA_NATIVE_GRAPHICS_PROCGRASS_ENABLE_AMBSCALESCAN);
		GRAPHICS.set_function("PROCGRASS_DISABLE_AMBSCALESCAN", LUA_NATIVE_GRAPHICS_PROCGRASS_DISABLE_AMBSCALESCAN);
		GRAPHICS.set_function("DISABLE_PROCOBJ_CREATION", LUA_NATIVE_GRAPHICS_DISABLE_PROCOBJ_CREATION);
		GRAPHICS.set_function("ENABLE_PROCOBJ_CREATION", LUA_NATIVE_GRAPHICS_ENABLE_PROCOBJ_CREATION);
		GRAPHICS.set_function("GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE", LUA_NATIVE_GRAPHICS_GRASSBATCH_ENABLE_FLATTENING_EXT_IN_SPHERE);
		GRAPHICS.set_function("GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE", LUA_NATIVE_GRAPHICS_GRASSBATCH_ENABLE_FLATTENING_IN_SPHERE);
		GRAPHICS.set_function("GRASSBATCH_DISABLE_FLATTENING", LUA_NATIVE_GRAPHICS_GRASSBATCH_DISABLE_FLATTENING);
		GRAPHICS.set_function("CASCADE_SHADOWS_INIT_SESSION", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_INIT_SESSION);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_CASCADE_BOUNDS", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_CASCADE_BOUNDS);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_CASCADE_BOUNDS_SCALE);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_ENTITY_TRACKER_SCALE);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SPLIT_Z_EXP_WEIGHT);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_BOUND_POSITION", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_BOUND_POSITION);
		GRAPHICS.set_function("CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_ENABLE_ENTITY_TRACKER);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SCREEN_SIZE_CHECK_ENABLED);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_SHADOW_SAMPLE_TYPE);
		GRAPHICS.set_function("CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_CLEAR_SHADOW_SAMPLE_TYPE);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_AIRCRAFT_MODE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_AIRCRAFT_MODE);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_MODE);
		GRAPHICS.set_function("CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_SET_DYNAMIC_DEPTH_VALUE);
		GRAPHICS.set_function("CASCADE_SHADOWS_ENABLE_FREEZER", LUA_NATIVE_GRAPHICS_CASCADE_SHADOWS_ENABLE_FREEZER);
		GRAPHICS.set_function("WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY", LUA_NATIVE_GRAPHICS_WATER_REFLECTION_SET_SCRIPT_OBJECT_VISIBILITY);
		GRAPHICS.set_function("GOLF_TRAIL_SET_ENABLED", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_ENABLED);
		GRAPHICS.set_function("GOLF_TRAIL_SET_PATH", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_PATH);
		GRAPHICS.set_function("GOLF_TRAIL_SET_RADIUS", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_RADIUS);
		GRAPHICS.set_function("GOLF_TRAIL_SET_COLOUR", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_COLOUR);
		GRAPHICS.set_function("GOLF_TRAIL_SET_TESSELLATION", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_TESSELLATION);
		GRAPHICS.set_function("GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FIXED_CONTROL_POINT_ENABLE);
		GRAPHICS.set_function("GOLF_TRAIL_SET_FIXED_CONTROL_POINT", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FIXED_CONTROL_POINT);
		GRAPHICS.set_function("GOLF_TRAIL_SET_SHADER_PARAMS", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_SHADER_PARAMS);
		GRAPHICS.set_function("GOLF_TRAIL_SET_FACING", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_SET_FACING);
		GRAPHICS.set_function("GOLF_TRAIL_GET_MAX_HEIGHT", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_GET_MAX_HEIGHT);
		GRAPHICS.set_function("GOLF_TRAIL_GET_VISUAL_CONTROL_POINT", LUA_NATIVE_GRAPHICS_GOLF_TRAIL_GET_VISUAL_CONTROL_POINT);
		GRAPHICS.set_function("SET_SEETHROUGH", LUA_NATIVE_GRAPHICS_SET_SEETHROUGH);
		GRAPHICS.set_function("GET_USINGSEETHROUGH", LUA_NATIVE_GRAPHICS_GET_USINGSEETHROUGH);
		GRAPHICS.set_function("SEETHROUGH_RESET", LUA_NATIVE_GRAPHICS_SEETHROUGH_RESET);
		GRAPHICS.set_function("SEETHROUGH_SET_FADE_STARTDISTANCE", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_FADE_STARTDISTANCE);
		GRAPHICS.set_function("SEETHROUGH_SET_FADE_ENDDISTANCE", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_FADE_ENDDISTANCE);
		GRAPHICS.set_function("SEETHROUGH_GET_MAX_THICKNESS", LUA_NATIVE_GRAPHICS_SEETHROUGH_GET_MAX_THICKNESS);
		GRAPHICS.set_function("SEETHROUGH_SET_MAX_THICKNESS", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_MAX_THICKNESS);
		GRAPHICS.set_function("SEETHROUGH_SET_NOISE_MIN", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_NOISE_MIN);
		GRAPHICS.set_function("SEETHROUGH_SET_NOISE_MAX", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_NOISE_MAX);
		GRAPHICS.set_function("SEETHROUGH_SET_HILIGHT_INTENSITY", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HILIGHT_INTENSITY);
		GRAPHICS.set_function("SEETHROUGH_SET_HIGHLIGHT_NOISE", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HIGHLIGHT_NOISE);
		GRAPHICS.set_function("SEETHROUGH_SET_HEATSCALE", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_HEATSCALE);
		GRAPHICS.set_function("SEETHROUGH_SET_COLOR_NEAR", LUA_NATIVE_GRAPHICS_SEETHROUGH_SET_COLOR_NEAR);
		GRAPHICS.set_function("SET_MOTIONBLUR_MAX_VEL_SCALER", LUA_NATIVE_GRAPHICS_SET_MOTIONBLUR_MAX_VEL_SCALER);
		GRAPHICS.set_function("GET_MOTIONBLUR_MAX_VEL_SCALER", LUA_NATIVE_GRAPHICS_GET_MOTIONBLUR_MAX_VEL_SCALER);
		GRAPHICS.set_function("SET_FORCE_MOTIONBLUR", LUA_NATIVE_GRAPHICS_SET_FORCE_MOTIONBLUR);
		GRAPHICS.set_function("TOGGLE_PLAYER_DAMAGE_OVERLAY", LUA_NATIVE_GRAPHICS_TOGGLE_PLAYER_DAMAGE_OVERLAY);
		GRAPHICS.set_function("RESET_ADAPTATION", LUA_NATIVE_GRAPHICS_RESET_ADAPTATION);
		GRAPHICS.set_function("TRIGGER_SCREENBLUR_FADE_IN", LUA_NATIVE_GRAPHICS_TRIGGER_SCREENBLUR_FADE_IN);
		GRAPHICS.set_function("TRIGGER_SCREENBLUR_FADE_OUT", LUA_NATIVE_GRAPHICS_TRIGGER_SCREENBLUR_FADE_OUT);
		GRAPHICS.set_function("DISABLE_SCREENBLUR_FADE", LUA_NATIVE_GRAPHICS_DISABLE_SCREENBLUR_FADE);
		GRAPHICS.set_function("GET_SCREENBLUR_FADE_CURRENT_TIME", LUA_NATIVE_GRAPHICS_GET_SCREENBLUR_FADE_CURRENT_TIME);
		GRAPHICS.set_function("IS_SCREENBLUR_FADE_RUNNING", LUA_NATIVE_GRAPHICS_IS_SCREENBLUR_FADE_RUNNING);
		GRAPHICS.set_function("TOGGLE_PAUSED_RENDERPHASES", LUA_NATIVE_GRAPHICS_TOGGLE_PAUSED_RENDERPHASES);
		GRAPHICS.set_function("GET_TOGGLE_PAUSED_RENDERPHASES_STATUS", LUA_NATIVE_GRAPHICS_GET_TOGGLE_PAUSED_RENDERPHASES_STATUS);
		GRAPHICS.set_function("RESET_PAUSED_RENDERPHASES", LUA_NATIVE_GRAPHICS_RESET_PAUSED_RENDERPHASES);
		GRAPHICS.set_function("GRAB_PAUSEMENU_OWNERSHIP", LUA_NATIVE_GRAPHICS_GRAB_PAUSEMENU_OWNERSHIP);
		GRAPHICS.set_function("SET_HIDOF_OVERRIDE", LUA_NATIVE_GRAPHICS_SET_HIDOF_OVERRIDE);
		GRAPHICS.set_function("SET_LOCK_ADAPTIVE_DOF_DISTANCE", LUA_NATIVE_GRAPHICS_SET_LOCK_ADAPTIVE_DOF_DISTANCE);
		GRAPHICS.set_function("PHONEPHOTOEDITOR_TOGGLE", LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_TOGGLE);
		GRAPHICS.set_function("PHONEPHOTOEDITOR_IS_ACTIVE", LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_IS_ACTIVE);
		GRAPHICS.set_function("PHONEPHOTOEDITOR_SET_FRAME_TXD", LUA_NATIVE_GRAPHICS_PHONEPHOTOEDITOR_SET_FRAME_TXD);
		GRAPHICS.set_function("START_PARTICLE_FX_NON_LOOPED_AT_COORD", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_AT_COORD);
		GRAPHICS.set_function("START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD", LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_AT_COORD);
		GRAPHICS.set_function("START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_PED_BONE);
		GRAPHICS.set_function("START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE", LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_PED_BONE);
		GRAPHICS.set_function("START_PARTICLE_FX_NON_LOOPED_ON_ENTITY", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY);
		GRAPHICS.set_function("START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY", LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_NON_LOOPED_ON_ENTITY);
		GRAPHICS.set_function("START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_NON_LOOPED_ON_ENTITY_BONE);
		GRAPHICS.set_function("SET_PARTICLE_FX_NON_LOOPED_COLOUR", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_COLOUR);
		GRAPHICS.set_function("SET_PARTICLE_FX_NON_LOOPED_ALPHA", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_ALPHA);
		GRAPHICS.set_function("SET_PARTICLE_FX_NON_LOOPED_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_NON_LOOPED_EMITTER_SIZE);
		GRAPHICS.set_function("SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FORCE_VEHICLE_INTERIOR);
		GRAPHICS.set_function("START_PARTICLE_FX_LOOPED_AT_COORD", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_AT_COORD);
		GRAPHICS.set_function("START_PARTICLE_FX_LOOPED_ON_PED_BONE", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_PED_BONE);
		GRAPHICS.set_function("START_PARTICLE_FX_LOOPED_ON_ENTITY", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_ENTITY);
		GRAPHICS.set_function("START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE", LUA_NATIVE_GRAPHICS_START_PARTICLE_FX_LOOPED_ON_ENTITY_BONE);
		GRAPHICS.set_function("START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY", LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY);
		GRAPHICS.set_function("START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE", LUA_NATIVE_GRAPHICS_START_NETWORKED_PARTICLE_FX_LOOPED_ON_ENTITY_BONE);
		GRAPHICS.set_function("STOP_PARTICLE_FX_LOOPED", LUA_NATIVE_GRAPHICS_STOP_PARTICLE_FX_LOOPED);
		GRAPHICS.set_function("REMOVE_PARTICLE_FX", LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX);
		GRAPHICS.set_function("REMOVE_PARTICLE_FX_FROM_ENTITY", LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX_FROM_ENTITY);
		GRAPHICS.set_function("REMOVE_PARTICLE_FX_IN_RANGE", LUA_NATIVE_GRAPHICS_REMOVE_PARTICLE_FX_IN_RANGE);
		GRAPHICS.set_function("FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR", LUA_NATIVE_GRAPHICS_FORCE_PARTICLE_FX_IN_VEHICLE_INTERIOR);
		GRAPHICS.set_function("DOES_PARTICLE_FX_LOOPED_EXIST", LUA_NATIVE_GRAPHICS_DOES_PARTICLE_FX_LOOPED_EXIST);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_OFFSETS", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_OFFSETS);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_EVOLUTION", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_EVOLUTION);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_COLOUR", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_COLOUR);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_ALPHA", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_ALPHA);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_FAR_CLIP_DIST);
		GRAPHICS.set_function("SET_PARTICLE_FX_LOOPED_CAMERA_BIAS_", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_LOOPED_CAMERA_BIAS_);
		GRAPHICS.set_function("SET_PARTICLE_FX_CAM_INSIDE_VEHICLE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_CAM_INSIDE_VEHICLE);
		GRAPHICS.set_function("SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_CAM_INSIDE_NONPLAYER_VEHICLE);
		GRAPHICS.set_function("SET_PARTICLE_FX_SHOOTOUT_BOAT", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_SHOOTOUT_BOAT);
		GRAPHICS.set_function("CLEAR_PARTICLE_FX_SHOOTOUT_BOAT", LUA_NATIVE_GRAPHICS_CLEAR_PARTICLE_FX_SHOOTOUT_BOAT);
		GRAPHICS.set_function("SET_PARTICLE_FX_BLOOD_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BLOOD_SCALE);
		GRAPHICS.set_function("DISABLE_IN_WATER_PTFX", LUA_NATIVE_GRAPHICS_DISABLE_IN_WATER_PTFX);
		GRAPHICS.set_function("DISABLE_DOWNWASH_PTFX", LUA_NATIVE_GRAPHICS_DISABLE_DOWNWASH_PTFX);
		GRAPHICS.set_function("SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_SLIPSTREAM_LODRANGE_SCALE);
		GRAPHICS.set_function("ENABLE_CLOWN_BLOOD_VFX", LUA_NATIVE_GRAPHICS_ENABLE_CLOWN_BLOOD_VFX);
		GRAPHICS.set_function("ENABLE_ALIEN_BLOOD_VFX", LUA_NATIVE_GRAPHICS_ENABLE_ALIEN_BLOOD_VFX);
		GRAPHICS.set_function("SET_PARTICLE_FX_BULLET_IMPACT_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_IMPACT_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_IMPACT_LODRANGE_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BULLET_TRACE_NO_ANGLE_REJECT);
		GRAPHICS.set_function("SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_BANG_SCRAPE_LODRANGE_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_FOOT_LODRANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FOOT_LODRANGE_SCALE);
		GRAPHICS.set_function("SET_PARTICLE_FX_FOOT_OVERRIDE_NAME", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_FOOT_OVERRIDE_NAME);
		GRAPHICS.set_function("SET_SKIDMARK_RANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_SKIDMARK_RANGE_SCALE);
		GRAPHICS.set_function("SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG", LUA_NATIVE_GRAPHICS_SET_PTFX_FORCE_VEHICLE_INTERIOR_FLAG);
		GRAPHICS.set_function("REGISTER_POSTFX_BULLET_IMPACT", LUA_NATIVE_GRAPHICS_REGISTER_POSTFX_BULLET_IMPACT);
		GRAPHICS.set_function("FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD", LUA_NATIVE_GRAPHICS_FORCE_POSTFX_BULLET_IMPACTS_AFTER_HUD);
		GRAPHICS.set_function("USE_PARTICLE_FX_ASSET", LUA_NATIVE_GRAPHICS_USE_PARTICLE_FX_ASSET);
		GRAPHICS.set_function("SET_PARTICLE_FX_OVERRIDE", LUA_NATIVE_GRAPHICS_SET_PARTICLE_FX_OVERRIDE);
		GRAPHICS.set_function("RESET_PARTICLE_FX_OVERRIDE", LUA_NATIVE_GRAPHICS_RESET_PARTICLE_FX_OVERRIDE);
		GRAPHICS.set_function("START_VEHICLE_PARTICLE_FX_LOOPED_", LUA_NATIVE_GRAPHICS_START_VEHICLE_PARTICLE_FX_LOOPED_);
		GRAPHICS.set_function("SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS", LUA_NATIVE_GRAPHICS_SET_WEATHER_PTFX_USE_OVERRIDE_SETTINGS);
		GRAPHICS.set_function("SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL", LUA_NATIVE_GRAPHICS_SET_WEATHER_PTFX_OVERRIDE_CURR_LEVEL);
		GRAPHICS.set_function("WASH_DECALS_IN_RANGE", LUA_NATIVE_GRAPHICS_WASH_DECALS_IN_RANGE);
		GRAPHICS.set_function("WASH_DECALS_FROM_VEHICLE", LUA_NATIVE_GRAPHICS_WASH_DECALS_FROM_VEHICLE);
		GRAPHICS.set_function("FADE_DECALS_IN_RANGE", LUA_NATIVE_GRAPHICS_FADE_DECALS_IN_RANGE);
		GRAPHICS.set_function("REMOVE_DECALS_IN_RANGE", LUA_NATIVE_GRAPHICS_REMOVE_DECALS_IN_RANGE);
		GRAPHICS.set_function("REMOVE_DECALS_FROM_OBJECT", LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_OBJECT);
		GRAPHICS.set_function("REMOVE_DECALS_FROM_OBJECT_FACING", LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_OBJECT_FACING);
		GRAPHICS.set_function("REMOVE_DECALS_FROM_VEHICLE", LUA_NATIVE_GRAPHICS_REMOVE_DECALS_FROM_VEHICLE);
		GRAPHICS.set_function("ADD_DECAL", LUA_NATIVE_GRAPHICS_ADD_DECAL);
		GRAPHICS.set_function("ADD_PETROL_DECAL", LUA_NATIVE_GRAPHICS_ADD_PETROL_DECAL);
		GRAPHICS.set_function("ADD_OIL_DECAL", LUA_NATIVE_GRAPHICS_ADD_OIL_DECAL);
		GRAPHICS.set_function("START_PETROL_TRAIL_DECALS", LUA_NATIVE_GRAPHICS_START_PETROL_TRAIL_DECALS);
		GRAPHICS.set_function("ADD_PETROL_TRAIL_DECAL_INFO", LUA_NATIVE_GRAPHICS_ADD_PETROL_TRAIL_DECAL_INFO);
		GRAPHICS.set_function("END_PETROL_TRAIL_DECALS", LUA_NATIVE_GRAPHICS_END_PETROL_TRAIL_DECALS);
		GRAPHICS.set_function("REMOVE_DECAL", LUA_NATIVE_GRAPHICS_REMOVE_DECAL);
		GRAPHICS.set_function("IS_DECAL_ALIVE", LUA_NATIVE_GRAPHICS_IS_DECAL_ALIVE);
		GRAPHICS.set_function("GET_DECAL_WASH_LEVEL", LUA_NATIVE_GRAPHICS_GET_DECAL_WASH_LEVEL);
		GRAPHICS.set_function("SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME", LUA_NATIVE_GRAPHICS_SET_DISABLE_PETROL_DECALS_IGNITING_THIS_FRAME);
		GRAPHICS.set_function("SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME", LUA_NATIVE_GRAPHICS_SET_DISABLE_PETROL_DECALS_RECYCLING_THIS_FRAME);
		GRAPHICS.set_function("SET_DISABLE_DECAL_RENDERING_THIS_FRAME", LUA_NATIVE_GRAPHICS_SET_DISABLE_DECAL_RENDERING_THIS_FRAME);
		GRAPHICS.set_function("GET_IS_PETROL_DECAL_IN_RANGE", LUA_NATIVE_GRAPHICS_GET_IS_PETROL_DECAL_IN_RANGE);
		GRAPHICS.set_function("PATCH_DECAL_DIFFUSE_MAP", LUA_NATIVE_GRAPHICS_PATCH_DECAL_DIFFUSE_MAP);
		GRAPHICS.set_function("UNPATCH_DECAL_DIFFUSE_MAP", LUA_NATIVE_GRAPHICS_UNPATCH_DECAL_DIFFUSE_MAP);
		GRAPHICS.set_function("MOVE_VEHICLE_DECALS", LUA_NATIVE_GRAPHICS_MOVE_VEHICLE_DECALS);
		GRAPHICS.set_function("ADD_VEHICLE_CREW_EMBLEM", LUA_NATIVE_GRAPHICS_ADD_VEHICLE_CREW_EMBLEM);
		GRAPHICS.set_function("ABORT_VEHICLE_CREW_EMBLEM_REQUEST", LUA_NATIVE_GRAPHICS_ABORT_VEHICLE_CREW_EMBLEM_REQUEST);
		GRAPHICS.set_function("REMOVE_VEHICLE_CREW_EMBLEM", LUA_NATIVE_GRAPHICS_REMOVE_VEHICLE_CREW_EMBLEM);
		GRAPHICS.set_function("GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE", LUA_NATIVE_GRAPHICS_GET_VEHICLE_CREW_EMBLEM_REQUEST_STATE);
		GRAPHICS.set_function("DOES_VEHICLE_HAVE_CREW_EMBLEM", LUA_NATIVE_GRAPHICS_DOES_VEHICLE_HAVE_CREW_EMBLEM);
		GRAPHICS.set_function("DISABLE_COMPOSITE_SHOTGUN_DECALS", LUA_NATIVE_GRAPHICS_DISABLE_COMPOSITE_SHOTGUN_DECALS);
		GRAPHICS.set_function("DISABLE_SCUFF_DECALS", LUA_NATIVE_GRAPHICS_DISABLE_SCUFF_DECALS);
		GRAPHICS.set_function("SET_DECAL_BULLET_IMPACT_RANGE_SCALE", LUA_NATIVE_GRAPHICS_SET_DECAL_BULLET_IMPACT_RANGE_SCALE);
		GRAPHICS.set_function("OVERRIDE_INTERIOR_SMOKE_NAME", LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_NAME);
		GRAPHICS.set_function("OVERRIDE_INTERIOR_SMOKE_LEVEL", LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_LEVEL);
		GRAPHICS.set_function("OVERRIDE_INTERIOR_SMOKE_END", LUA_NATIVE_GRAPHICS_OVERRIDE_INTERIOR_SMOKE_END);
		GRAPHICS.set_function("REGISTER_NOIR_LENS_EFFECT", LUA_NATIVE_GRAPHICS_REGISTER_NOIR_LENS_EFFECT);
		GRAPHICS.set_function("DISABLE_VEHICLE_DISTANTLIGHTS", LUA_NATIVE_GRAPHICS_DISABLE_VEHICLE_DISTANTLIGHTS);
		GRAPHICS.set_function("RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS", LUA_NATIVE_GRAPHICS_RENDER_SHADOWED_LIGHTS_WITH_NO_SHADOWS);
		GRAPHICS.set_function("REQUEST_EARLY_LIGHT_CHECK", LUA_NATIVE_GRAPHICS_REQUEST_EARLY_LIGHT_CHECK);
		GRAPHICS.set_function("USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED", LUA_NATIVE_GRAPHICS_USE_SNOW_FOOT_VFX_WHEN_UNSHELTERED);
		GRAPHICS.set_function("FORCE_ALLOW_SNOW_FOOT_VFX_ON_ICE_", LUA_NATIVE_GRAPHICS_FORCE_ALLOW_SNOW_FOOT_VFX_ON_ICE_);
		GRAPHICS.set_function("USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED", LUA_NATIVE_GRAPHICS_USE_SNOW_WHEEL_VFX_WHEN_UNSHELTERED);
		GRAPHICS.set_function("DISABLE_REGION_VFX", LUA_NATIVE_GRAPHICS_DISABLE_REGION_VFX);
		GRAPHICS.set_function("FORCE_GROUND_SNOW_PASS_", LUA_NATIVE_GRAPHICS_FORCE_GROUND_SNOW_PASS_);
		GRAPHICS.set_function("PRESET_INTERIOR_AMBIENT_CACHE", LUA_NATIVE_GRAPHICS_PRESET_INTERIOR_AMBIENT_CACHE);
		GRAPHICS.set_function("SET_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_SET_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("SET_TIMECYCLE_MODIFIER_STRENGTH", LUA_NATIVE_GRAPHICS_SET_TIMECYCLE_MODIFIER_STRENGTH);
		GRAPHICS.set_function("SET_TRANSITION_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_SET_TRANSITION_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_SET_TRANSITION_OUT_OF_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("CLEAR_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_CLEAR_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("GET_TIMECYCLE_MODIFIER_INDEX", LUA_NATIVE_GRAPHICS_GET_TIMECYCLE_MODIFIER_INDEX);
		GRAPHICS.set_function("GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX", LUA_NATIVE_GRAPHICS_GET_TIMECYCLE_TRANSITION_MODIFIER_INDEX);
		GRAPHICS.set_function("GET_IS_TIMECYCLE_TRANSITIONING_OUT", LUA_NATIVE_GRAPHICS_GET_IS_TIMECYCLE_TRANSITIONING_OUT);
		GRAPHICS.set_function("PUSH_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_PUSH_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("POP_TIMECYCLE_MODIFIER", LUA_NATIVE_GRAPHICS_POP_TIMECYCLE_MODIFIER);
		GRAPHICS.set_function("SET_CURRENT_PLAYER_TCMODIFIER", LUA_NATIVE_GRAPHICS_SET_CURRENT_PLAYER_TCMODIFIER);
		GRAPHICS.set_function("SET_PLAYER_TCMODIFIER_TRANSITION", LUA_NATIVE_GRAPHICS_SET_PLAYER_TCMODIFIER_TRANSITION);
		GRAPHICS.set_function("SET_NEXT_PLAYER_TCMODIFIER", LUA_NATIVE_GRAPHICS_SET_NEXT_PLAYER_TCMODIFIER);
		GRAPHICS.set_function("ADD_TCMODIFIER_OVERRIDE", LUA_NATIVE_GRAPHICS_ADD_TCMODIFIER_OVERRIDE);
		GRAPHICS.set_function("CLEAR_ALL_TCMODIFIER_OVERRIDES", LUA_NATIVE_GRAPHICS_CLEAR_ALL_TCMODIFIER_OVERRIDES);
		GRAPHICS.set_function("SET_EXTRA_TCMODIFIER", LUA_NATIVE_GRAPHICS_SET_EXTRA_TCMODIFIER);
		GRAPHICS.set_function("CLEAR_EXTRA_TCMODIFIER", LUA_NATIVE_GRAPHICS_CLEAR_EXTRA_TCMODIFIER);
		GRAPHICS.set_function("GET_EXTRA_TCMODIFIER", LUA_NATIVE_GRAPHICS_GET_EXTRA_TCMODIFIER);
		GRAPHICS.set_function("ENABLE_MOON_CYCLE_OVERRIDE", LUA_NATIVE_GRAPHICS_ENABLE_MOON_CYCLE_OVERRIDE);
		GRAPHICS.set_function("DISABLE_MOON_CYCLE_OVERRIDE", LUA_NATIVE_GRAPHICS_DISABLE_MOON_CYCLE_OVERRIDE);
		GRAPHICS.set_function("REQUEST_SCALEFORM_MOVIE", LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE);
		GRAPHICS.set_function("REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN", LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_WITH_IGNORE_SUPER_WIDESCREEN);
		GRAPHICS.set_function("REQUEST_SCALEFORM_MOVIE_INSTANCE", LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_INSTANCE);
		GRAPHICS.set_function("REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED", LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_MOVIE_SKIP_RENDER_WHILE_PAUSED);
		GRAPHICS.set_function("HAS_SCALEFORM_MOVIE_LOADED", LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_MOVIE_LOADED);
		GRAPHICS.set_function("IS_ACTIVE_SCALEFORM_MOVIE_DELETING", LUA_NATIVE_GRAPHICS_IS_ACTIVE_SCALEFORM_MOVIE_DELETING);
		GRAPHICS.set_function("IS_SCALEFORM_MOVIE_DELETING", LUA_NATIVE_GRAPHICS_IS_SCALEFORM_MOVIE_DELETING);
		GRAPHICS.set_function("HAS_SCALEFORM_MOVIE_FILENAME_LOADED", LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_MOVIE_FILENAME_LOADED);
		GRAPHICS.set_function("HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT", LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_CONTAINER_MOVIE_LOADED_INTO_PARENT);
		GRAPHICS.set_function("SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED", LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_AS_NO_LONGER_NEEDED);
		GRAPHICS.set_function("SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME", LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_SYSTEM_TIME);
		GRAPHICS.set_function("SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT", LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_LARGE_RT);
		GRAPHICS.set_function("SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT", LUA_NATIVE_GRAPHICS_SET_SCALEFORM_MOVIE_TO_USE_SUPER_LARGE_RT);
		GRAPHICS.set_function("DRAW_SCALEFORM_MOVIE", LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE);
		GRAPHICS.set_function("DRAW_SCALEFORM_MOVIE_FULLSCREEN", LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_FULLSCREEN);
		GRAPHICS.set_function("DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED", LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_FULLSCREEN_MASKED);
		GRAPHICS.set_function("DRAW_SCALEFORM_MOVIE_3D", LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_3D);
		GRAPHICS.set_function("DRAW_SCALEFORM_MOVIE_3D_SOLID", LUA_NATIVE_GRAPHICS_DRAW_SCALEFORM_MOVIE_3D_SOLID);
		GRAPHICS.set_function("CALL_SCALEFORM_MOVIE_METHOD", LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD);
		GRAPHICS.set_function("CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER", LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER);
		GRAPHICS.set_function("CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING", LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_STRING);
		GRAPHICS.set_function("CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING", LUA_NATIVE_GRAPHICS_CALL_SCALEFORM_MOVIE_METHOD_WITH_NUMBER_AND_STRING);
		GRAPHICS.set_function("BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD", LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_SCRIPT_HUD_MOVIE_METHOD);
		GRAPHICS.set_function("BEGIN_SCALEFORM_MOVIE_METHOD", LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD);
		GRAPHICS.set_function("BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND", LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND);
		GRAPHICS.set_function("BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER", LUA_NATIVE_GRAPHICS_BEGIN_SCALEFORM_MOVIE_METHOD_ON_FRONTEND_HEADER);
		GRAPHICS.set_function("END_SCALEFORM_MOVIE_METHOD", LUA_NATIVE_GRAPHICS_END_SCALEFORM_MOVIE_METHOD);
		GRAPHICS.set_function("END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE", LUA_NATIVE_GRAPHICS_END_SCALEFORM_MOVIE_METHOD_RETURN_VALUE);
		GRAPHICS.set_function("IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY", LUA_NATIVE_GRAPHICS_IS_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_READY);
		GRAPHICS.set_function("GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT", LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_INT);
		GRAPHICS.set_function("GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL", LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_BOOL);
		GRAPHICS.set_function("GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING", LUA_NATIVE_GRAPHICS_GET_SCALEFORM_MOVIE_METHOD_RETURN_VALUE_STRING);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_INT);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_FLOAT);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_BOOL);
		GRAPHICS.set_function("BEGIN_TEXT_COMMAND_SCALEFORM_STRING", LUA_NATIVE_GRAPHICS_BEGIN_TEXT_COMMAND_SCALEFORM_STRING);
		GRAPHICS.set_function("END_TEXT_COMMAND_SCALEFORM_STRING", LUA_NATIVE_GRAPHICS_END_TEXT_COMMAND_SCALEFORM_STRING);
		GRAPHICS.set_function("END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING", LUA_NATIVE_GRAPHICS_END_TEXT_COMMAND_UNPARSED_SCALEFORM_STRING);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_LITERAL_STRING);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_TEXTURE_NAME_STRING);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_PLAYER_NAME_STRING);
		GRAPHICS.set_function("DOES_LATEST_BRIEF_STRING_EXIST", LUA_NATIVE_GRAPHICS_DOES_LATEST_BRIEF_STRING_EXIST);
		GRAPHICS.set_function("SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING", LUA_NATIVE_GRAPHICS_SCALEFORM_MOVIE_METHOD_ADD_PARAM_LATEST_BRIEF_STRING);
		GRAPHICS.set_function("REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE", LUA_NATIVE_GRAPHICS_REQUEST_SCALEFORM_SCRIPT_HUD_MOVIE);
		GRAPHICS.set_function("HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED", LUA_NATIVE_GRAPHICS_HAS_SCALEFORM_SCRIPT_HUD_MOVIE_LOADED);
		GRAPHICS.set_function("REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE", LUA_NATIVE_GRAPHICS_REMOVE_SCALEFORM_SCRIPT_HUD_MOVIE);
		GRAPHICS.set_function("PASS_KEYBOARD_INPUT_TO_SCALEFORM", LUA_NATIVE_GRAPHICS_PASS_KEYBOARD_INPUT_TO_SCALEFORM);
		GRAPHICS.set_function("SET_TV_CHANNEL", LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL);
		GRAPHICS.set_function("GET_TV_CHANNEL", LUA_NATIVE_GRAPHICS_GET_TV_CHANNEL);
		GRAPHICS.set_function("SET_TV_VOLUME", LUA_NATIVE_GRAPHICS_SET_TV_VOLUME);
		GRAPHICS.set_function("GET_TV_VOLUME", LUA_NATIVE_GRAPHICS_GET_TV_VOLUME);
		GRAPHICS.set_function("DRAW_TV_CHANNEL", LUA_NATIVE_GRAPHICS_DRAW_TV_CHANNEL);
		GRAPHICS.set_function("SET_TV_CHANNEL_PLAYLIST", LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST);
		GRAPHICS.set_function("SET_TV_CHANNEL_PLAYLIST_AT_HOUR", LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST_AT_HOUR);
		GRAPHICS.set_function("SET_TV_CHANNEL_PLAYLIST_DIRTY_", LUA_NATIVE_GRAPHICS_SET_TV_CHANNEL_PLAYLIST_DIRTY_);
		GRAPHICS.set_function("CLEAR_TV_CHANNEL_PLAYLIST", LUA_NATIVE_GRAPHICS_CLEAR_TV_CHANNEL_PLAYLIST);
		GRAPHICS.set_function("IS_PLAYLIST_ON_CHANNEL", LUA_NATIVE_GRAPHICS_IS_PLAYLIST_ON_CHANNEL);
		GRAPHICS.set_function("IS_TVSHOW_CURRENTLY_PLAYING", LUA_NATIVE_GRAPHICS_IS_TVSHOW_CURRENTLY_PLAYING);
		GRAPHICS.set_function("ENABLE_MOVIE_KEYFRAME_WAIT", LUA_NATIVE_GRAPHICS_ENABLE_MOVIE_KEYFRAME_WAIT);
		GRAPHICS.set_function("SET_TV_PLAYER_WATCHING_THIS_FRAME", LUA_NATIVE_GRAPHICS_SET_TV_PLAYER_WATCHING_THIS_FRAME);
		GRAPHICS.set_function("GET_CURRENT_TV_CLIP_NAMEHASH", LUA_NATIVE_GRAPHICS_GET_CURRENT_TV_CLIP_NAMEHASH);
		GRAPHICS.set_function("ENABLE_MOVIE_SUBTITLES", LUA_NATIVE_GRAPHICS_ENABLE_MOVIE_SUBTITLES);
		GRAPHICS.set_function("UI3DSCENE_IS_AVAILABLE", LUA_NATIVE_GRAPHICS_UI3DSCENE_IS_AVAILABLE);
		GRAPHICS.set_function("UI3DSCENE_PUSH_PRESET", LUA_NATIVE_GRAPHICS_UI3DSCENE_PUSH_PRESET);
		GRAPHICS.set_function("UI3DSCENE_ASSIGN_PED_TO_SLOT", LUA_NATIVE_GRAPHICS_UI3DSCENE_ASSIGN_PED_TO_SLOT);
		GRAPHICS.set_function("UI3DSCENE_CLEAR_PATCHED_DATA", LUA_NATIVE_GRAPHICS_UI3DSCENE_CLEAR_PATCHED_DATA);
		GRAPHICS.set_function("UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT", LUA_NATIVE_GRAPHICS_UI3DSCENE_MAKE_PUSHED_PRESET_PERSISTENT);
		GRAPHICS.set_function("TERRAINGRID_ACTIVATE", LUA_NATIVE_GRAPHICS_TERRAINGRID_ACTIVATE);
		GRAPHICS.set_function("TERRAINGRID_SET_PARAMS", LUA_NATIVE_GRAPHICS_TERRAINGRID_SET_PARAMS);
		GRAPHICS.set_function("TERRAINGRID_SET_COLOURS", LUA_NATIVE_GRAPHICS_TERRAINGRID_SET_COLOURS);
		GRAPHICS.set_function("ANIMPOSTFX_PLAY", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_PLAY);
		GRAPHICS.set_function("ANIMPOSTFX_STOP", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP);
		GRAPHICS.set_function("ANIMPOSTFX_GET_CURRENT_TIME", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_GET_CURRENT_TIME);
		GRAPHICS.set_function("ANIMPOSTFX_IS_RUNNING", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_IS_RUNNING);
		GRAPHICS.set_function("ANIMPOSTFX_STOP_ALL", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP_ALL);
		GRAPHICS.set_function("ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS", LUA_NATIVE_GRAPHICS_ANIMPOSTFX_STOP_AND_FLUSH_REQUESTS);
	}
}

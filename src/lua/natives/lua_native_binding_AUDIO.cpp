#include "lua_native_binding.hpp"
#include "natives.hpp"

namespace lua::native
{
	static void LUA_NATIVE_AUDIO_PLAY_PED_RINGTONE(sol::stack_object ringtoneName, Ped ped, bool p2)
	{
		AUDIO::PLAY_PED_RINGTONE(ringtoneName.is<const char*>() ? ringtoneName.as<const char*>() : nullptr, ped, p2);
	}

	static bool LUA_NATIVE_AUDIO_IS_PED_RINGTONE_PLAYING(Ped ped)
	{
		auto retval = (bool)AUDIO::IS_PED_RINGTONE_PLAYING(ped);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_STOP_PED_RINGTONE(Ped ped)
	{
		AUDIO::STOP_PED_RINGTONE(ped);
	}

	static bool LUA_NATIVE_AUDIO_IS_MOBILE_PHONE_CALL_ONGOING()
	{
		auto retval = (bool)AUDIO::IS_MOBILE_PHONE_CALL_ONGOING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_MOBILE_INTERFERENCE_ACTIVE()
	{
		auto retval = (bool)AUDIO::IS_MOBILE_INTERFERENCE_ACTIVE();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_CURRENT_TV_SHOW_PLAY_TIME()
	{
		auto retval = AUDIO::GET_CURRENT_TV_SHOW_PLAY_TIME();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_CREATE_NEW_SCRIPTED_CONVERSATION()
	{
		AUDIO::CREATE_NEW_SCRIPTED_CONVERSATION();
	}

	static void LUA_NATIVE_AUDIO_ADD_LINE_TO_CONVERSATION(int index, sol::stack_object p1, sol::stack_object p2, int p3, int p4, bool p5, bool p6, bool p7, bool p8, int p9, bool p10, bool p11, bool p12)
	{
		AUDIO::ADD_LINE_TO_CONVERSATION(index, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
	}

	static void LUA_NATIVE_AUDIO_ADD_PED_TO_CONVERSATION(int index, Ped ped, sol::stack_object p2)
	{
		AUDIO::ADD_PED_TO_CONVERSATION(index, ped, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_POSITION_FOR_NULL_CONV_PED(Any p0, float p1, float p2, float p3)
	{
		AUDIO::SET_POSITION_FOR_NULL_CONV_PED(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_AUDIO_SET_ENTITY_FOR_NULL_CONV_PED(int p0, Entity entity)
	{
		AUDIO::SET_ENTITY_FOR_NULL_CONV_PED(p0, entity);
	}

	static void LUA_NATIVE_AUDIO_SET_MICROPHONE_POSITION(bool toggle, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
	{
		AUDIO::SET_MICROPHONE_POSITION(toggle, x1, y1, z1, x2, y2, z2, x3, y3, z3);
	}

	static void LUA_NATIVE_AUDIO_SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM(bool p0)
	{
		AUDIO::SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM(p0);
	}

	static void LUA_NATIVE_AUDIO_SET_CONVERSATION_AUDIO_PLACEHOLDER(bool p0)
	{
		AUDIO::SET_CONVERSATION_AUDIO_PLACEHOLDER(p0);
	}

	static void LUA_NATIVE_AUDIO_START_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)
	{
		AUDIO::START_SCRIPT_PHONE_CONVERSATION(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_PRELOAD_SCRIPT_PHONE_CONVERSATION(bool p0, bool p1)
	{
		AUDIO::PRELOAD_SCRIPT_PHONE_CONVERSATION(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_START_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)
	{
		AUDIO::START_SCRIPT_CONVERSATION(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_AUDIO_PRELOAD_SCRIPT_CONVERSATION(bool p0, bool p1, bool p2, bool p3)
	{
		AUDIO::PRELOAD_SCRIPT_CONVERSATION(p0, p1, p2, p3);
	}

	static void LUA_NATIVE_AUDIO_START_PRELOADED_CONVERSATION()
	{
		AUDIO::START_PRELOADED_CONVERSATION();
	}

	static bool LUA_NATIVE_AUDIO_GET_IS_PRELOADED_CONVERSATION_READY()
	{
		auto retval = (bool)AUDIO::GET_IS_PRELOADED_CONVERSATION_READY();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_SCRIPTED_CONVERSATION_ONGOING()
	{
		auto retval = (bool)AUDIO::IS_SCRIPTED_CONVERSATION_ONGOING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_SCRIPTED_CONVERSATION_LOADED()
	{
		auto retval = (bool)AUDIO::IS_SCRIPTED_CONVERSATION_LOADED();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_CURRENT_SCRIPTED_CONVERSATION_LINE()
	{
		auto retval = AUDIO::GET_CURRENT_SCRIPTED_CONVERSATION_LINE();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_PAUSE_SCRIPTED_CONVERSATION(bool p0)
	{
		AUDIO::PAUSE_SCRIPTED_CONVERSATION(p0);
	}

	static void LUA_NATIVE_AUDIO_RESTART_SCRIPTED_CONVERSATION()
	{
		AUDIO::RESTART_SCRIPTED_CONVERSATION();
	}

	static int LUA_NATIVE_AUDIO_STOP_SCRIPTED_CONVERSATION(bool p0)
	{
		auto retval = AUDIO::STOP_SCRIPTED_CONVERSATION(p0);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE()
	{
		AUDIO::SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE();
	}

	static void LUA_NATIVE_AUDIO_INTERRUPT_CONVERSATION(Ped ped, sol::stack_object voiceline, sol::stack_object speaker)
	{
		AUDIO::INTERRUPT_CONVERSATION(ped, voiceline.is<const char*>() ? voiceline.as<const char*>() : nullptr, speaker.is<const char*>() ? speaker.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_INTERRUPT_CONVERSATION_AND_PAUSE(Ped ped, sol::stack_object p1, sol::stack_object speaker)
	{
		AUDIO::INTERRUPT_CONVERSATION_AND_PAUSE(ped, p1.is<const char*>() ? p1.as<const char*>() : nullptr, speaker.is<const char*>() ? speaker.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_AUDIO_GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE(uintptr_t p0)
	{
		auto retval = AUDIO::GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE((Any*)p0);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_NO_DUCKING_FOR_CONVERSATION(bool p0)
	{
		AUDIO::SET_NO_DUCKING_FOR_CONVERSATION(p0);
	}

	static void LUA_NATIVE_AUDIO_REGISTER_SCRIPT_WITH_AUDIO(int p0)
	{
		AUDIO::REGISTER_SCRIPT_WITH_AUDIO(p0);
	}

	static void LUA_NATIVE_AUDIO_UNREGISTER_SCRIPT_WITH_AUDIO()
	{
		AUDIO::UNREGISTER_SCRIPT_WITH_AUDIO();
	}

	static bool LUA_NATIVE_AUDIO_REQUEST_MISSION_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::REQUEST_MISSION_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_REQUEST_AMBIENT_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::REQUEST_AMBIENT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_REQUEST_SCRIPT_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::REQUEST_SCRIPT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_HINT_MISSION_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::HINT_MISSION_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_HINT_AMBIENT_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::HINT_AMBIENT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_HINT_SCRIPT_AUDIO_BANK(sol::stack_object audioBank, bool p1, Any p2)
	{
		auto retval = (bool)AUDIO::HINT_SCRIPT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr, p1, p2);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_RELEASE_MISSION_AUDIO_BANK()
	{
		AUDIO::RELEASE_MISSION_AUDIO_BANK();
	}

	static void LUA_NATIVE_AUDIO_RELEASE_AMBIENT_AUDIO_BANK()
	{
		AUDIO::RELEASE_AMBIENT_AUDIO_BANK();
	}

	static void LUA_NATIVE_AUDIO_RELEASE_NAMED_SCRIPT_AUDIO_BANK(sol::stack_object audioBank)
	{
		AUDIO::RELEASE_NAMED_SCRIPT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_RELEASE_SCRIPT_AUDIO_BANK()
	{
		AUDIO::RELEASE_SCRIPT_AUDIO_BANK();
	}

	static void LUA_NATIVE_AUDIO_UNHINT_AMBIENT_AUDIO_BANK()
	{
		AUDIO::UNHINT_AMBIENT_AUDIO_BANK();
	}

	static void LUA_NATIVE_AUDIO_UNHINT_SCRIPT_AUDIO_BANK()
	{
		AUDIO::UNHINT_SCRIPT_AUDIO_BANK();
	}

	static void LUA_NATIVE_AUDIO_UNHINT_NAMED_SCRIPT_AUDIO_BANK(sol::stack_object audioBank)
	{
		AUDIO::UNHINT_NAMED_SCRIPT_AUDIO_BANK(audioBank.is<const char*>() ? audioBank.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_AUDIO_GET_SOUND_ID()
	{
		auto retval = AUDIO::GET_SOUND_ID();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_RELEASE_SOUND_ID(int soundId)
	{
		AUDIO::RELEASE_SOUND_ID(soundId);
	}

	static void LUA_NATIVE_AUDIO_PLAY_SOUND(int soundId, sol::stack_object audioName, sol::stack_object audioRef, bool p3, Any p4, bool p5)
	{
		AUDIO::PLAY_SOUND(soundId, audioName.is<const char*>() ? audioName.as<const char*>() : nullptr, audioRef.is<const char*>() ? audioRef.as<const char*>() : nullptr, p3, p4, p5);
	}

	static void LUA_NATIVE_AUDIO_PLAY_SOUND_FRONTEND(int soundId, sol::stack_object audioName, sol::stack_object audioRef, bool p3)
	{
		AUDIO::PLAY_SOUND_FRONTEND(soundId, audioName.is<const char*>() ? audioName.as<const char*>() : nullptr, audioRef.is<const char*>() ? audioRef.as<const char*>() : nullptr, p3);
	}

	static void LUA_NATIVE_AUDIO_PLAY_DEFERRED_SOUND_FRONTEND(sol::stack_object soundName, sol::stack_object soundsetName)
	{
		AUDIO::PLAY_DEFERRED_SOUND_FRONTEND(soundName.is<const char*>() ? soundName.as<const char*>() : nullptr, soundsetName.is<const char*>() ? soundsetName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_ENTITY(int soundId, sol::stack_object audioName, Entity entity, sol::stack_object audioRef, bool isNetwork, Any p5)
	{
		AUDIO::PLAY_SOUND_FROM_ENTITY(soundId, audioName.is<const char*>() ? audioName.as<const char*>() : nullptr, entity, audioRef.is<const char*>() ? audioRef.as<const char*>() : nullptr, isNetwork, p5);
	}

	static void LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_ENTITY_HASH(int soundId, Hash model, Entity entity, Hash soundSetHash, Any p4, Any p5)
	{
		AUDIO::PLAY_SOUND_FROM_ENTITY_HASH(soundId, model, entity, soundSetHash, p4, p5);
	}

	static void LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_COORD(int soundId, sol::stack_object audioName, float x, float y, float z, sol::stack_object audioRef, bool isNetwork, int range, bool p8)
	{
		AUDIO::PLAY_SOUND_FROM_COORD(soundId, audioName.is<const char*>() ? audioName.as<const char*>() : nullptr, x, y, z, audioRef.is<const char*>() ? audioRef.as<const char*>() : nullptr, isNetwork, range, p8);
	}

	static void LUA_NATIVE_AUDIO_UPDATE_SOUND_COORD(int soundId, float x, float y, float z)
	{
		AUDIO::UPDATE_SOUND_COORD(soundId, x, y, z);
	}

	static void LUA_NATIVE_AUDIO_STOP_SOUND(int soundId)
	{
		AUDIO::STOP_SOUND(soundId);
	}

	static int LUA_NATIVE_AUDIO_GET_NETWORK_ID_FROM_SOUND_ID(int soundId)
	{
		auto retval = AUDIO::GET_NETWORK_ID_FROM_SOUND_ID(soundId);
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_SOUND_ID_FROM_NETWORK_ID(int netId)
	{
		auto retval = AUDIO::GET_SOUND_ID_FROM_NETWORK_ID(netId);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VARIABLE_ON_SOUND(int soundId, sol::stack_object variable, float p2)
	{
		AUDIO::SET_VARIABLE_ON_SOUND(soundId, variable.is<const char*>() ? variable.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_SET_VARIABLE_ON_STREAM(sol::stack_object variable, float p1)
	{
		AUDIO::SET_VARIABLE_ON_STREAM(variable.is<const char*>() ? variable.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_AUDIO_OVERRIDE_UNDERWATER_STREAM(sol::stack_object p0, bool p1)
	{
		AUDIO::OVERRIDE_UNDERWATER_STREAM(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_VARIABLE_ON_UNDER_WATER_STREAM(sol::stack_object variableName, float value)
	{
		AUDIO::SET_VARIABLE_ON_UNDER_WATER_STREAM(variableName.is<const char*>() ? variableName.as<const char*>() : nullptr, value);
	}

	static bool LUA_NATIVE_AUDIO_HAS_SOUND_FINISHED(int soundId)
	{
		auto retval = (bool)AUDIO::HAS_SOUND_FINISHED(soundId);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_NATIVE(Ped ped, sol::stack_object speechName, sol::stack_object speechParam, Any p3)
	{
		AUDIO::PLAY_PED_AMBIENT_SPEECH_NATIVE(ped, speechName.is<const char*>() ? speechName.as<const char*>() : nullptr, speechParam.is<const char*>() ? speechParam.as<const char*>() : nullptr, p3);
	}

	static void LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE(Ped ped, sol::stack_object speechName, sol::stack_object speechParam, Any p3)
	{
		AUDIO::PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE(ped, speechName.is<const char*>() ? speechName.as<const char*>() : nullptr, speechParam.is<const char*>() ? speechParam.as<const char*>() : nullptr, p3);
	}

	static void LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(Ped ped, sol::stack_object speechName, sol::stack_object voiceName, sol::stack_object speechParam, bool p4)
	{
		AUDIO::PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(ped, speechName.is<const char*>() ? speechName.as<const char*>() : nullptr, voiceName.is<const char*>() ? voiceName.as<const char*>() : nullptr, speechParam.is<const char*>() ? speechParam.as<const char*>() : nullptr, p4);
	}

	static void LUA_NATIVE_AUDIO_PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE(sol::stack_object speechName, sol::stack_object voiceName, float x, float y, float z, sol::stack_object speechParam)
	{
		AUDIO::PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE(speechName.is<const char*>() ? speechName.as<const char*>() : nullptr, voiceName.is<const char*>() ? voiceName.as<const char*>() : nullptr, x, y, z, speechParam.is<const char*>() ? speechParam.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_OVERRIDE_TREVOR_RAGE(sol::stack_object voiceEffect)
	{
		AUDIO::OVERRIDE_TREVOR_RAGE(voiceEffect.is<const char*>() ? voiceEffect.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_RESET_TREVOR_RAGE()
	{
		AUDIO::RESET_TREVOR_RAGE();
	}

	static void LUA_NATIVE_AUDIO_SET_PLAYER_ANGRY(Ped ped, bool toggle)
	{
		AUDIO::SET_PLAYER_ANGRY(ped, toggle);
	}

	static void LUA_NATIVE_AUDIO_PLAY_PAIN(Ped ped, int painID, int p1, Any p3)
	{
		AUDIO::PLAY_PAIN(ped, painID, p1, p3);
	}

	static void LUA_NATIVE_AUDIO_RELEASE_WEAPON_AUDIO()
	{
		AUDIO::RELEASE_WEAPON_AUDIO();
	}

	static void LUA_NATIVE_AUDIO_ACTIVATE_AUDIO_SLOWMO_MODE(sol::stack_object mode)
	{
		AUDIO::ACTIVATE_AUDIO_SLOWMO_MODE(mode.is<const char*>() ? mode.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_DEACTIVATE_AUDIO_SLOWMO_MODE(sol::stack_object mode)
	{
		AUDIO::DEACTIVATE_AUDIO_SLOWMO_MODE(mode.is<const char*>() ? mode.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_VOICE_NAME(Ped ped, sol::stack_object name)
	{
		AUDIO::SET_AMBIENT_VOICE_NAME(ped, name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_VOICE_NAME_HASH(Ped ped, Hash hash)
	{
		AUDIO::SET_AMBIENT_VOICE_NAME_HASH(ped, hash);
	}

	static Hash LUA_NATIVE_AUDIO_GET_AMBIENT_VOICE_NAME_HASH(Ped ped)
	{
		auto retval = AUDIO::GET_AMBIENT_VOICE_NAME_HASH(ped);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_PED_VOICE_FULL(Ped ped)
	{
		AUDIO::SET_PED_VOICE_FULL(ped);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_RACE_AND_VOICE_GROUP(Ped ped, int p1, Hash voiceGroup)
	{
		AUDIO::SET_PED_RACE_AND_VOICE_GROUP(ped, p1, voiceGroup);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_VOICE_GROUP(Ped ped, Hash voiceGroupHash)
	{
		AUDIO::SET_PED_VOICE_GROUP(ped, voiceGroupHash);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG(Ped ped, Hash voiceGroupHash)
	{
		AUDIO::SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG(ped, voiceGroupHash);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_GENDER(Ped ped, bool p1)
	{
		AUDIO::SET_PED_GENDER(ped, p1);
	}

	static void LUA_NATIVE_AUDIO_STOP_CURRENT_PLAYING_SPEECH(Ped ped)
	{
		AUDIO::STOP_CURRENT_PLAYING_SPEECH(ped);
	}

	static void LUA_NATIVE_AUDIO_STOP_CURRENT_PLAYING_AMBIENT_SPEECH(Ped ped)
	{
		AUDIO::STOP_CURRENT_PLAYING_AMBIENT_SPEECH(ped);
	}

	static bool LUA_NATIVE_AUDIO_IS_AMBIENT_SPEECH_PLAYING(Ped ped)
	{
		auto retval = (bool)AUDIO::IS_AMBIENT_SPEECH_PLAYING(ped);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_SCRIPTED_SPEECH_PLAYING(Ped p0)
	{
		auto retval = (bool)AUDIO::IS_SCRIPTED_SPEECH_PLAYING(p0);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_ANY_SPEECH_PLAYING(Ped ped)
	{
		auto retval = (bool)AUDIO::IS_ANY_SPEECH_PLAYING(ped);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_ANY_POSITIONAL_SPEECH_PLAYING()
	{
		auto retval = (bool)AUDIO::IS_ANY_POSITIONAL_SPEECH_PLAYING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_DOES_CONTEXT_EXIST_FOR_THIS_PED(Ped ped, sol::stack_object speechName, bool p2)
	{
		auto retval = (bool)AUDIO::DOES_CONTEXT_EXIST_FOR_THIS_PED(ped, speechName.is<const char*>() ? speechName.as<const char*>() : nullptr, p2);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_PED_IN_CURRENT_CONVERSATION(Ped ped)
	{
		auto retval = (bool)AUDIO::IS_PED_IN_CURRENT_CONVERSATION(ped);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_PED_IS_DRUNK(Ped ped, bool toggle)
	{
		AUDIO::SET_PED_IS_DRUNK(ped, toggle);
	}

	static void LUA_NATIVE_AUDIO_PLAY_ANIMAL_VOCALIZATION(Ped pedHandle, int p1, sol::stack_object speechName)
	{
		AUDIO::PLAY_ANIMAL_VOCALIZATION(pedHandle, p1, speechName.is<const char*>() ? speechName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_AUDIO_IS_ANIMAL_VOCALIZATION_PLAYING(Ped pedHandle)
	{
		auto retval = (bool)AUDIO::IS_ANIMAL_VOCALIZATION_PLAYING(pedHandle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_ANIMAL_MOOD(Ped animal, int mood)
	{
		AUDIO::SET_ANIMAL_MOOD(animal, mood);
	}

	static bool LUA_NATIVE_AUDIO_IS_MOBILE_PHONE_RADIO_ACTIVE()
	{
		auto retval = (bool)AUDIO::IS_MOBILE_PHONE_RADIO_ACTIVE();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_MOBILE_PHONE_RADIO_STATE(bool state)
	{
		AUDIO::SET_MOBILE_PHONE_RADIO_STATE(state);
	}

	static int LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_INDEX()
	{
		auto retval = AUDIO::GET_PLAYER_RADIO_STATION_INDEX();
		return retval;
	}

	static const char* LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_NAME()
	{
		auto retval = AUDIO::GET_PLAYER_RADIO_STATION_NAME();
		return retval;
	}

	static const char* LUA_NATIVE_AUDIO_GET_RADIO_STATION_NAME(int radioStation)
	{
		auto retval = AUDIO::GET_RADIO_STATION_NAME(radioStation);
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_GENRE()
	{
		auto retval = AUDIO::GET_PLAYER_RADIO_STATION_GENRE();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_RADIO_RETUNING()
	{
		auto retval = (bool)AUDIO::IS_RADIO_RETUNING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_RADIO_FADED_OUT()
	{
		auto retval = (bool)AUDIO::IS_RADIO_FADED_OUT();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_RETUNE_UP()
	{
		AUDIO::SET_RADIO_RETUNE_UP();
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_RETUNE_DOWN()
	{
		AUDIO::SET_RADIO_RETUNE_DOWN();
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_TO_STATION_NAME(sol::stack_object stationName)
	{
		AUDIO::SET_RADIO_TO_STATION_NAME(stationName.is<const char*>() ? stationName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_VEH_RADIO_STATION(Vehicle vehicle, sol::stack_object radioStation)
	{
		AUDIO::SET_VEH_RADIO_STATION(vehicle, radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_VEH_HAS_NORMAL_RADIO(Vehicle vehicle)
	{
		AUDIO::SET_VEH_HAS_NORMAL_RADIO(vehicle);
	}

	static bool LUA_NATIVE_AUDIO_IS_VEHICLE_RADIO_ON(Vehicle vehicle)
	{
		auto retval = (bool)AUDIO::IS_VEHICLE_RADIO_ON(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VEH_FORCED_RADIO_THIS_FRAME(Vehicle vehicle)
	{
		AUDIO::SET_VEH_FORCED_RADIO_THIS_FRAME(vehicle);
	}

	static void LUA_NATIVE_AUDIO_SET_EMITTER_RADIO_STATION(sol::stack_object emitterName, sol::stack_object radioStation, Any p2)
	{
		AUDIO::SET_EMITTER_RADIO_STATION(emitterName.is<const char*>() ? emitterName.as<const char*>() : nullptr, radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_SET_STATIC_EMITTER_ENABLED(sol::stack_object emitterName, bool toggle)
	{
		AUDIO::SET_STATIC_EMITTER_ENABLED(emitterName.is<const char*>() ? emitterName.as<const char*>() : nullptr, toggle);
	}

	static void LUA_NATIVE_AUDIO_LINK_STATIC_EMITTER_TO_ENTITY(sol::stack_object emitterName, Entity entity)
	{
		AUDIO::LINK_STATIC_EMITTER_TO_ENTITY(emitterName.is<const char*>() ? emitterName.as<const char*>() : nullptr, entity);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_TO_STATION_INDEX(int radioStation)
	{
		AUDIO::SET_RADIO_TO_STATION_INDEX(radioStation);
	}

	static void LUA_NATIVE_AUDIO_SET_FRONTEND_RADIO_ACTIVE(bool active)
	{
		AUDIO::SET_FRONTEND_RADIO_ACTIVE(active);
	}

	static void LUA_NATIVE_AUDIO_UNLOCK_MISSION_NEWS_STORY(int newsStory)
	{
		AUDIO::UNLOCK_MISSION_NEWS_STORY(newsStory);
	}

	static bool LUA_NATIVE_AUDIO_IS_MISSION_NEWS_STORY_UNLOCKED(int newsStory)
	{
		auto retval = (bool)AUDIO::IS_MISSION_NEWS_STORY_UNLOCKED(newsStory);
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_AUDIBLE_MUSIC_TRACK_TEXT_ID()
	{
		auto retval = AUDIO::GET_AUDIBLE_MUSIC_TRACK_TEXT_ID();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_PLAY_END_CREDITS_MUSIC(bool play)
	{
		AUDIO::PLAY_END_CREDITS_MUSIC(play);
	}

	static void LUA_NATIVE_AUDIO_SKIP_RADIO_FORWARD()
	{
		AUDIO::SKIP_RADIO_FORWARD();
	}

	static void LUA_NATIVE_AUDIO_FREEZE_RADIO_STATION(sol::stack_object radioStation)
	{
		AUDIO::FREEZE_RADIO_STATION(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_UNFREEZE_RADIO_STATION(sol::stack_object radioStation)
	{
		AUDIO::UNFREEZE_RADIO_STATION(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_AUTO_UNFREEZE(bool toggle)
	{
		AUDIO::SET_RADIO_AUTO_UNFREEZE(toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_INITIAL_PLAYER_STATION(sol::stack_object radioStation)
	{
		AUDIO::SET_INITIAL_PLAYER_STATION(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_USER_RADIO_CONTROL_ENABLED(bool toggle)
	{
		AUDIO::SET_USER_RADIO_CONTROL_ENABLED(toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_TRACK(sol::stack_object radioStation, sol::stack_object radioTrack)
	{
		AUDIO::SET_RADIO_TRACK(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, radioTrack.is<const char*>() ? radioTrack.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_TRACK_WITH_START_OFFSET(sol::stack_object radioStationName, sol::stack_object mixName, int p2)
	{
		AUDIO::SET_RADIO_TRACK_WITH_START_OFFSET(radioStationName.is<const char*>() ? radioStationName.as<const char*>() : nullptr, mixName.is<const char*>() ? mixName.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_SET_NEXT_RADIO_TRACK(sol::stack_object radioName, sol::stack_object radioTrack, sol::stack_object p2, sol::stack_object p3)
	{
		AUDIO::SET_NEXT_RADIO_TRACK(radioName.is<const char*>() ? radioName.as<const char*>() : nullptr, radioTrack.is<const char*>() ? radioTrack.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr, p3.is<const char*>() ? p3.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_RADIO_LOUD(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_VEHICLE_RADIO_LOUD(vehicle, toggle);
	}

	static bool LUA_NATIVE_AUDIO_CAN_VEHICLE_RECEIVE_CB_RADIO(Vehicle vehicle)
	{
		auto retval = (bool)AUDIO::CAN_VEHICLE_RECEIVE_CB_RADIO(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(bool toggle)
	{
		AUDIO::SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(toggle);
	}

	static bool LUA_NATIVE_AUDIO_DOES_PLAYER_VEH_HAVE_RADIO()
	{
		auto retval = (bool)AUDIO::DOES_PLAYER_VEH_HAVE_RADIO();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_PLAYER_VEH_RADIO_ENABLE()
	{
		auto retval = (bool)AUDIO::IS_PLAYER_VEH_RADIO_ENABLE();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_RADIO_ENABLED(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_VEHICLE_RADIO_ENABLED(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED(Any p0)
	{
		AUDIO::SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED(p0);
	}

	static void LUA_NATIVE_AUDIO_SET_CUSTOM_RADIO_TRACK_LIST(sol::stack_object radioStation, sol::stack_object trackListName, bool p2)
	{
		AUDIO::SET_CUSTOM_RADIO_TRACK_LIST(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, trackListName.is<const char*>() ? trackListName.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_CLEAR_CUSTOM_RADIO_TRACK_LIST(sol::stack_object radioStation)
	{
		AUDIO::CLEAR_CUSTOM_RADIO_TRACK_LIST(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
	}

	static int LUA_NATIVE_AUDIO_GET_NUM_UNLOCKED_RADIO_STATIONS()
	{
		auto retval = AUDIO::GET_NUM_UNLOCKED_RADIO_STATIONS();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_FIND_RADIO_STATION_INDEX(Hash stationNameHash)
	{
		auto retval = AUDIO::FIND_RADIO_STATION_INDEX(stationNameHash);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_STATION_MUSIC_ONLY(sol::stack_object radioStation, bool toggle)
	{
		AUDIO::SET_RADIO_STATION_MUSIC_ONLY(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_FRONTEND_FADE_TIME(float fadeTime)
	{
		AUDIO::SET_RADIO_FRONTEND_FADE_TIME(fadeTime);
	}

	static void LUA_NATIVE_AUDIO_UNLOCK_RADIO_STATION_TRACK_LIST(sol::stack_object radioStation, sol::stack_object trackListName)
	{
		AUDIO::UNLOCK_RADIO_STATION_TRACK_LIST(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, trackListName.is<const char*>() ? trackListName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_LOCK_RADIO_STATION_TRACK_LIST(sol::stack_object radioStation, sol::stack_object trackListName)
	{
		AUDIO::LOCK_RADIO_STATION_TRACK_LIST(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, trackListName.is<const char*>() ? trackListName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS(bool enableMixes)
	{
		AUDIO::UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS(enableMixes);
	}

	static void LUA_NATIVE_AUDIO_LOCK_RADIO_STATION(sol::stack_object radioStationName, bool toggle)
	{
		AUDIO::LOCK_RADIO_STATION(radioStationName.is<const char*>() ? radioStationName.as<const char*>() : nullptr, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_STATION_AS_FAVOURITE(sol::stack_object radioStation, bool toggle)
	{
		AUDIO::SET_RADIO_STATION_AS_FAVOURITE(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, toggle);
	}

	static bool LUA_NATIVE_AUDIO_IS_RADIO_STATION_FAVOURITED(sol::stack_object radioStation)
	{
		auto retval = (bool)AUDIO::IS_RADIO_STATION_FAVOURITED(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr);
		return retval;
	}

	static std::tuple<bool, float, float, int> LUA_NATIVE_AUDIO_GET_NEXT_AUDIBLE_BEAT(float out1, float out2, int out3)
	{
		std::tuple<bool, float, float, int> return_values;
		std::get<0>(return_values) = (bool)AUDIO::GET_NEXT_AUDIBLE_BEAT(&out1, &out2, &out3);
		std::get<1>(return_values) = out1;
		std::get<2>(return_values) = out2;
		std::get<3>(return_values) = out3;

		return return_values;
	}

	static void LUA_NATIVE_AUDIO_FORCE_MUSIC_TRACK_LIST(sol::stack_object radioStation, sol::stack_object trackListName, int milliseconds)
	{
		AUDIO::FORCE_MUSIC_TRACK_LIST(radioStation.is<const char*>() ? radioStation.as<const char*>() : nullptr, trackListName.is<const char*>() ? trackListName.as<const char*>() : nullptr, milliseconds);
	}

	static int LUA_NATIVE_AUDIO_GET_CURRENT_TRACK_PLAY_TIME(sol::stack_object radioStationName)
	{
		auto retval = AUDIO::GET_CURRENT_TRACK_PLAY_TIME(radioStationName.is<const char*>() ? radioStationName.as<const char*>() : nullptr);
		return retval;
	}

	static Hash LUA_NATIVE_AUDIO_GET_CURRENT_TRACK_SOUND_NAME(sol::stack_object radioStationName)
	{
		auto retval = AUDIO::GET_CURRENT_TRACK_SOUND_NAME(radioStationName.is<const char*>() ? radioStationName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_MISSILE_WARNING_ENABLED(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_VEHICLE_MISSILE_WARNING_ENABLED(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_STATE(sol::stack_object zoneName, bool p1, bool p2)
	{
		AUDIO::SET_AMBIENT_ZONE_STATE(zoneName.is<const char*>() ? zoneName.as<const char*>() : nullptr, p1, p2);
	}

	static void LUA_NATIVE_AUDIO_CLEAR_AMBIENT_ZONE_STATE(sol::stack_object zoneName, bool p1)
	{
		AUDIO::CLEAR_AMBIENT_ZONE_STATE(zoneName.is<const char*>() ? zoneName.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_LIST_STATE(sol::stack_object ambientZone, bool p1, bool p2)
	{
		AUDIO::SET_AMBIENT_ZONE_LIST_STATE(ambientZone.is<const char*>() ? ambientZone.as<const char*>() : nullptr, p1, p2);
	}

	static void LUA_NATIVE_AUDIO_CLEAR_AMBIENT_ZONE_LIST_STATE(sol::stack_object ambientZone, bool p1)
	{
		AUDIO::CLEAR_AMBIENT_ZONE_LIST_STATE(ambientZone.is<const char*>() ? ambientZone.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_STATE_PERSISTENT(sol::stack_object ambientZone, bool p1, bool p2)
	{
		AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT(ambientZone.is<const char*>() ? ambientZone.as<const char*>() : nullptr, p1, p2);
	}

	static void LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(sol::stack_object ambientZone, bool p1, bool p2)
	{
		AUDIO::SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT(ambientZone.is<const char*>() ? ambientZone.as<const char*>() : nullptr, p1, p2);
	}

	static bool LUA_NATIVE_AUDIO_IS_AMBIENT_ZONE_ENABLED(sol::stack_object ambientZone)
	{
		auto retval = (bool)AUDIO::IS_AMBIENT_ZONE_ENABLED(ambientZone.is<const char*>() ? ambientZone.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_REFRESH_CLOSEST_OCEAN_SHORELINE()
	{
		AUDIO::REFRESH_CLOSEST_OCEAN_SHORELINE();
	}

	static void LUA_NATIVE_AUDIO_SET_CUTSCENE_AUDIO_OVERRIDE(sol::stack_object name)
	{
		AUDIO::SET_CUTSCENE_AUDIO_OVERRIDE(name.is<const char*>() ? name.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_VARIABLE_ON_SYNCH_SCENE_AUDIO(sol::stack_object variableName, float value)
	{
		AUDIO::SET_VARIABLE_ON_SYNCH_SCENE_AUDIO(variableName.is<const char*>() ? variableName.as<const char*>() : nullptr, value);
	}

	static int LUA_NATIVE_AUDIO_PLAY_POLICE_REPORT(sol::stack_object name, float p1)
	{
		auto retval = AUDIO::PLAY_POLICE_REPORT(name.is<const char*>() ? name.as<const char*>() : nullptr, p1);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_CANCEL_ALL_POLICE_REPORTS()
	{
		AUDIO::CANCEL_ALL_POLICE_REPORTS();
	}

	static void LUA_NATIVE_AUDIO_BLIP_SIREN(Vehicle vehicle)
	{
		AUDIO::BLIP_SIREN(vehicle);
	}

	static void LUA_NATIVE_AUDIO_OVERRIDE_VEH_HORN(Vehicle vehicle, bool override, int hornHash)
	{
		AUDIO::OVERRIDE_VEH_HORN(vehicle, override, hornHash);
	}

	static bool LUA_NATIVE_AUDIO_IS_HORN_ACTIVE(Vehicle vehicle)
	{
		auto retval = (bool)AUDIO::IS_HORN_ACTIVE(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_AGGRESSIVE_HORNS(bool toggle)
	{
		AUDIO::SET_AGGRESSIVE_HORNS(toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_RADIO_POSITION_AUDIO_MUTE(bool p0)
	{
		AUDIO::SET_RADIO_POSITION_AUDIO_MUTE(p0);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_CONVERSATIONS_PERSIST(bool p0, bool p1)
	{
		AUDIO::SET_VEHICLE_CONVERSATIONS_PERSIST(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_CONVERSATIONS_PERSIST_NEW(bool p0, bool p1, bool p2)
	{
		AUDIO::SET_VEHICLE_CONVERSATIONS_PERSIST_NEW(p0, p1, p2);
	}

	static bool LUA_NATIVE_AUDIO_IS_STREAM_PLAYING()
	{
		auto retval = (bool)AUDIO::IS_STREAM_PLAYING();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_STREAM_PLAY_TIME()
	{
		auto retval = AUDIO::GET_STREAM_PLAY_TIME();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_LOAD_STREAM(sol::stack_object streamName, sol::stack_object soundSet)
	{
		auto retval = (bool)AUDIO::LOAD_STREAM(streamName.is<const char*>() ? streamName.as<const char*>() : nullptr, soundSet.is<const char*>() ? soundSet.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_LOAD_STREAM_WITH_START_OFFSET(sol::stack_object streamName, int startOffset, sol::stack_object soundSet)
	{
		auto retval = (bool)AUDIO::LOAD_STREAM_WITH_START_OFFSET(streamName.is<const char*>() ? streamName.as<const char*>() : nullptr, startOffset, soundSet.is<const char*>() ? soundSet.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_PED(Ped ped)
	{
		AUDIO::PLAY_STREAM_FROM_PED(ped);
	}

	static void LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_VEHICLE(Vehicle vehicle)
	{
		AUDIO::PLAY_STREAM_FROM_VEHICLE(vehicle);
	}

	static void LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_OBJECT(Object object)
	{
		AUDIO::PLAY_STREAM_FROM_OBJECT(object);
	}

	static void LUA_NATIVE_AUDIO_PLAY_STREAM_FRONTEND()
	{
		AUDIO::PLAY_STREAM_FRONTEND();
	}

	static void LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_POSITION(float x, float y, float z)
	{
		AUDIO::PLAY_STREAM_FROM_POSITION(x, y, z);
	}

	static void LUA_NATIVE_AUDIO_STOP_STREAM()
	{
		AUDIO::STOP_STREAM();
	}

	static void LUA_NATIVE_AUDIO_STOP_PED_SPEAKING(Ped ped, bool shaking)
	{
		AUDIO::STOP_PED_SPEAKING(ped, shaking);
	}

	static void LUA_NATIVE_AUDIO_BLOCK_ALL_SPEECH_FROM_PED(Ped ped, bool p1, bool p2)
	{
		AUDIO::BLOCK_ALL_SPEECH_FROM_PED(ped, p1, p2);
	}

	static void LUA_NATIVE_AUDIO_STOP_PED_SPEAKING_SYNCED(Ped ped, bool p1)
	{
		AUDIO::STOP_PED_SPEAKING_SYNCED(ped, p1);
	}

	static void LUA_NATIVE_AUDIO_DISABLE_PED_PAIN_AUDIO(Ped ped, bool toggle)
	{
		AUDIO::DISABLE_PED_PAIN_AUDIO(ped, toggle);
	}

	static bool LUA_NATIVE_AUDIO_IS_AMBIENT_SPEECH_DISABLED(Ped ped)
	{
		auto retval = (bool)AUDIO::IS_AMBIENT_SPEECH_DISABLED(ped);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_BLOCK_SPEECH_CONTEXT_GROUP(sol::stack_object p0, int p1)
	{
		AUDIO::BLOCK_SPEECH_CONTEXT_GROUP(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1);
	}

	static void LUA_NATIVE_AUDIO_UNBLOCK_SPEECH_CONTEXT_GROUP(sol::stack_object p0)
	{
		AUDIO::UNBLOCK_SPEECH_CONTEXT_GROUP(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_SET_SIREN_WITH_NO_DRIVER(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_SIREN_WITH_NO_DRIVER(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_SIREN_BYPASS_MP_DRIVER_CHECK(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_SIREN_BYPASS_MP_DRIVER_CHECK(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_TRIGGER_SIREN_AUDIO(Vehicle vehicle)
	{
		AUDIO::TRIGGER_SIREN_AUDIO(vehicle);
	}

	static void LUA_NATIVE_AUDIO_SET_HORN_PERMANENTLY_ON(Vehicle vehicle)
	{
		AUDIO::SET_HORN_PERMANENTLY_ON(vehicle);
	}

	static void LUA_NATIVE_AUDIO_SET_HORN_ENABLED(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_HORN_ENABLED(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_AUDIO_VEHICLE_PRIORITY(Vehicle vehicle, Any p1)
	{
		AUDIO::SET_AUDIO_VEHICLE_PRIORITY(vehicle, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_HORN_PERMANENTLY_ON_TIME(Vehicle vehicle, float time)
	{
		AUDIO::SET_HORN_PERMANENTLY_ON_TIME(vehicle, time);
	}

	static void LUA_NATIVE_AUDIO_USE_SIREN_AS_HORN(Vehicle vehicle, bool toggle)
	{
		AUDIO::USE_SIREN_AS_HORN(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_FORCE_USE_AUDIO_GAME_OBJECT(Vehicle vehicle, sol::stack_object audioName)
	{
		AUDIO::FORCE_USE_AUDIO_GAME_OBJECT(vehicle, audioName.is<const char*>() ? audioName.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_PRELOAD_VEHICLE_AUDIO_BANK(Hash vehicleModel)
	{
		AUDIO::PRELOAD_VEHICLE_AUDIO_BANK(vehicleModel);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle, sol::stack_object p1, sol::stack_object p2)
	{
		AUDIO::SET_VEHICLE_STARTUP_REV_SOUND(vehicle, p1.is<const char*>() ? p1.as<const char*>() : nullptr, p2.is<const char*>() ? p2.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_RESET_VEHICLE_STARTUP_REV_SOUND(Vehicle vehicle)
	{
		AUDIO::RESET_VEHICLE_STARTUP_REV_SOUND(vehicle);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_FORCE_REVERSE_WARNING(Any p0, Any p1)
	{
		AUDIO::SET_VEHICLE_FORCE_REVERSE_WARNING(p0, p1);
	}

	static bool LUA_NATIVE_AUDIO_IS_VEHICLE_AUDIBLY_DAMAGED(Vehicle vehicle)
	{
		auto retval = (bool)AUDIO::IS_VEHICLE_AUDIBLY_DAMAGED(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR(Vehicle vehicle, float damageFactor)
	{
		AUDIO::SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR(vehicle, damageFactor);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR(Vehicle vehicle, float intensity)
	{
		AUDIO::SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR(vehicle, intensity);
	}

	static void LUA_NATIVE_AUDIO_ENABLE_VEHICLE_FANBELT_DAMAGE(Vehicle vehicle, bool toggle)
	{
		AUDIO::ENABLE_VEHICLE_FANBELT_DAMAGE(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_ENABLE_VEHICLE_EXHAUST_POPS(Vehicle vehicle, bool toggle)
	{
		AUDIO::ENABLE_VEHICLE_EXHAUST_POPS(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_BOOST_ACTIVE(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_VEHICLE_BOOST_ACTIVE(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE(Vehicle vehicle, bool toggle)
	{
		AUDIO::SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_SCRIPT_UPDATE_DOOR_AUDIO(Hash doorHash, bool toggle)
	{
		AUDIO::SET_SCRIPT_UPDATE_DOOR_AUDIO(doorHash, toggle);
	}

	static void LUA_NATIVE_AUDIO_PLAY_VEHICLE_DOOR_OPEN_SOUND(Vehicle vehicle, int doorId)
	{
		AUDIO::PLAY_VEHICLE_DOOR_OPEN_SOUND(vehicle, doorId);
	}

	static void LUA_NATIVE_AUDIO_PLAY_VEHICLE_DOOR_CLOSE_SOUND(Vehicle vehicle, int doorId)
	{
		AUDIO::PLAY_VEHICLE_DOOR_CLOSE_SOUND(vehicle, doorId);
	}

	static void LUA_NATIVE_AUDIO_ENABLE_STALL_WARNING_SOUNDS(Vehicle vehicle, bool toggle)
	{
		AUDIO::ENABLE_STALL_WARNING_SOUNDS(vehicle, toggle);
	}

	static void LUA_NATIVE_AUDIO_ENABLE_DRAG_RACE_STATIONARY_WARNING_SOUNDS_(Vehicle vehicle, bool enable)
	{
		AUDIO::_ENABLE_DRAG_RACE_STATIONARY_WARNING_SOUNDS(vehicle, enable);
	}

	static bool LUA_NATIVE_AUDIO_IS_GAME_IN_CONTROL_OF_MUSIC()
	{
		auto retval = (bool)AUDIO::IS_GAME_IN_CONTROL_OF_MUSIC();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_GPS_ACTIVE(bool active)
	{
		AUDIO::SET_GPS_ACTIVE(active);
	}

	static void LUA_NATIVE_AUDIO_PLAY_MISSION_COMPLETE_AUDIO(sol::stack_object audioName)
	{
		AUDIO::PLAY_MISSION_COMPLETE_AUDIO(audioName.is<const char*>() ? audioName.as<const char*>() : nullptr);
	}

	static bool LUA_NATIVE_AUDIO_IS_MISSION_COMPLETE_PLAYING()
	{
		auto retval = (bool)AUDIO::IS_MISSION_COMPLETE_PLAYING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_MISSION_COMPLETE_READY_FOR_UI()
	{
		auto retval = (bool)AUDIO::IS_MISSION_COMPLETE_READY_FOR_UI();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_BLOCK_DEATH_JINGLE(bool toggle)
	{
		AUDIO::BLOCK_DEATH_JINGLE(toggle);
	}

	static bool LUA_NATIVE_AUDIO_START_AUDIO_SCENE(sol::stack_object scene)
	{
		auto retval = (bool)AUDIO::START_AUDIO_SCENE(scene.is<const char*>() ? scene.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_STOP_AUDIO_SCENE(sol::stack_object scene)
	{
		AUDIO::STOP_AUDIO_SCENE(scene.is<const char*>() ? scene.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_STOP_AUDIO_SCENES()
	{
		AUDIO::STOP_AUDIO_SCENES();
	}

	static bool LUA_NATIVE_AUDIO_IS_AUDIO_SCENE_ACTIVE(sol::stack_object scene)
	{
		auto retval = (bool)AUDIO::IS_AUDIO_SCENE_ACTIVE(scene.is<const char*>() ? scene.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_AUDIO_SCENE_VARIABLE(sol::stack_object scene, sol::stack_object variable, float value)
	{
		AUDIO::SET_AUDIO_SCENE_VARIABLE(scene.is<const char*>() ? scene.as<const char*>() : nullptr, variable.is<const char*>() ? variable.as<const char*>() : nullptr, value);
	}

	static void LUA_NATIVE_AUDIO_SET_AUDIO_SCRIPT_CLEANUP_TIME(int time)
	{
		AUDIO::SET_AUDIO_SCRIPT_CLEANUP_TIME(time);
	}

	static void LUA_NATIVE_AUDIO_ADD_ENTITY_TO_AUDIO_MIX_GROUP(Entity entity, sol::stack_object groupName, float p2)
	{
		AUDIO::ADD_ENTITY_TO_AUDIO_MIX_GROUP(entity, groupName.is<const char*>() ? groupName.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP(Entity entity, float p1)
	{
		AUDIO::REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP(entity, p1);
	}

	static bool LUA_NATIVE_AUDIO_AUDIO_IS_MUSIC_PLAYING()
	{
		auto retval = (bool)AUDIO::AUDIO_IS_MUSIC_PLAYING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_AUDIO_IS_SCRIPTED_MUSIC_PLAYING()
	{
		auto retval = (bool)AUDIO::AUDIO_IS_SCRIPTED_MUSIC_PLAYING();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_PREPARE_MUSIC_EVENT(sol::stack_object eventName)
	{
		auto retval = (bool)AUDIO::PREPARE_MUSIC_EVENT(eventName.is<const char*>() ? eventName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_CANCEL_MUSIC_EVENT(sol::stack_object eventName)
	{
		auto retval = (bool)AUDIO::CANCEL_MUSIC_EVENT(eventName.is<const char*>() ? eventName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_TRIGGER_MUSIC_EVENT(sol::stack_object eventName)
	{
		auto retval = (bool)AUDIO::TRIGGER_MUSIC_EVENT(eventName.is<const char*>() ? eventName.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_IS_MUSIC_ONESHOT_PLAYING()
	{
		auto retval = (bool)AUDIO::IS_MUSIC_ONESHOT_PLAYING();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_MUSIC_PLAYTIME()
	{
		auto retval = AUDIO::GET_MUSIC_PLAYTIME();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_GLOBAL_RADIO_SIGNAL_LEVEL(Any p0)
	{
		AUDIO::SET_GLOBAL_RADIO_SIGNAL_LEVEL(p0);
	}

	static void LUA_NATIVE_AUDIO_RECORD_BROKEN_GLASS(float x, float y, float z, float radius)
	{
		AUDIO::RECORD_BROKEN_GLASS(x, y, z, radius);
	}

	static void LUA_NATIVE_AUDIO_CLEAR_ALL_BROKEN_GLASS()
	{
		AUDIO::CLEAR_ALL_BROKEN_GLASS();
	}

	static void LUA_NATIVE_AUDIO_SCRIPT_OVERRIDES_WIND_ELEVATION(bool p0, Any p1)
	{
		AUDIO::SCRIPT_OVERRIDES_WIND_ELEVATION(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_WALLA_DENSITY(float p0, float p1)
	{
		AUDIO::SET_PED_WALLA_DENSITY(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_INTERIOR_WALLA_DENSITY(float p0, float p1)
	{
		AUDIO::SET_PED_INTERIOR_WALLA_DENSITY(p0, p1);
	}

	static void LUA_NATIVE_AUDIO_FORCE_PED_PANIC_WALLA()
	{
		AUDIO::FORCE_PED_PANIC_WALLA();
	}

	static bool LUA_NATIVE_AUDIO_PREPARE_ALARM(sol::stack_object alarmName)
	{
		auto retval = (bool)AUDIO::PREPARE_ALARM(alarmName.is<const char*>() ? alarmName.as<const char*>() : nullptr);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_START_ALARM(sol::stack_object alarmName, bool p2)
	{
		AUDIO::START_ALARM(alarmName.is<const char*>() ? alarmName.as<const char*>() : nullptr, p2);
	}

	static void LUA_NATIVE_AUDIO_STOP_ALARM(sol::stack_object alarmName, bool toggle)
	{
		AUDIO::STOP_ALARM(alarmName.is<const char*>() ? alarmName.as<const char*>() : nullptr, toggle);
	}

	static void LUA_NATIVE_AUDIO_STOP_ALL_ALARMS(bool stop)
	{
		AUDIO::STOP_ALL_ALARMS(stop);
	}

	static bool LUA_NATIVE_AUDIO_IS_ALARM_PLAYING(sol::stack_object alarmName)
	{
		auto retval = (bool)AUDIO::IS_ALARM_PLAYING(alarmName.is<const char*>() ? alarmName.as<const char*>() : nullptr);
		return retval;
	}

	static Hash LUA_NATIVE_AUDIO_GET_VEHICLE_DEFAULT_HORN(Vehicle vehicle)
	{
		auto retval = AUDIO::GET_VEHICLE_DEFAULT_HORN(vehicle);
		return retval;
	}

	static Hash LUA_NATIVE_AUDIO_GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS(Vehicle vehicle)
	{
		auto retval = AUDIO::GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_RESET_PED_AUDIO_FLAGS(Ped ped)
	{
		AUDIO::RESET_PED_AUDIO_FLAGS(ped);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_FOOTSTEPS_EVENTS_ENABLED(Ped ped, bool toggle)
	{
		AUDIO::SET_PED_FOOTSTEPS_EVENTS_ENABLED(ped, toggle);
	}

	static void LUA_NATIVE_AUDIO_SET_PED_CLOTH_EVENTS_ENABLED(Ped ped, bool toggle)
	{
		AUDIO::SET_PED_CLOTH_EVENTS_ENABLED(ped, toggle);
	}

	static void LUA_NATIVE_AUDIO_OVERRIDE_PLAYER_GROUND_MATERIAL(Hash hash, bool toggle)
	{
		AUDIO::OVERRIDE_PLAYER_GROUND_MATERIAL(hash, toggle);
	}

	static void LUA_NATIVE_AUDIO_USE_FOOTSTEP_SCRIPT_SWEETENERS(Ped ped, bool p1, Hash hash)
	{
		AUDIO::USE_FOOTSTEP_SCRIPT_SWEETENERS(ped, p1, hash);
	}

	static void LUA_NATIVE_AUDIO_OVERRIDE_MICROPHONE_SETTINGS(Hash hash, bool toggle)
	{
		AUDIO::OVERRIDE_MICROPHONE_SETTINGS(hash, toggle);
	}

	static void LUA_NATIVE_AUDIO_FREEZE_MICROPHONE()
	{
		AUDIO::FREEZE_MICROPHONE();
	}

	static void LUA_NATIVE_AUDIO_DISTANT_COP_CAR_SIRENS(bool value)
	{
		AUDIO::DISTANT_COP_CAR_SIRENS(value);
	}

	static void LUA_NATIVE_AUDIO_SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO(Vehicle vehicle, bool p1)
	{
		AUDIO::SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO(vehicle, p1);
	}

	static void LUA_NATIVE_AUDIO_ENABLE_STUNT_JUMP_AUDIO()
	{
		AUDIO::ENABLE_STUNT_JUMP_AUDIO();
	}

	static void LUA_NATIVE_AUDIO_SET_AUDIO_FLAG(sol::stack_object flagName, bool toggle)
	{
		AUDIO::SET_AUDIO_FLAG(flagName.is<const char*>() ? flagName.as<const char*>() : nullptr, toggle);
	}

	static bool LUA_NATIVE_AUDIO_PREPARE_SYNCHRONIZED_AUDIO_EVENT(sol::stack_object audioEvent, Any p1)
	{
		auto retval = (bool)AUDIO::PREPARE_SYNCHRONIZED_AUDIO_EVENT(audioEvent.is<const char*>() ? audioEvent.as<const char*>() : nullptr, p1);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(int sceneID, sol::stack_object audioEvent)
	{
		auto retval = (bool)AUDIO::PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE(sceneID, audioEvent.is<const char*>() ? audioEvent.as<const char*>() : nullptr);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_PLAY_SYNCHRONIZED_AUDIO_EVENT(int sceneID)
	{
		auto retval = (bool)AUDIO::PLAY_SYNCHRONIZED_AUDIO_EVENT(sceneID);
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_STOP_SYNCHRONIZED_AUDIO_EVENT(int sceneID)
	{
		auto retval = (bool)AUDIO::STOP_SYNCHRONIZED_AUDIO_EVENT(sceneID);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_INIT_SYNCH_SCENE_AUDIO_WITH_POSITION(sol::stack_object audioEvent, float x, float y, float z)
	{
		AUDIO::INIT_SYNCH_SCENE_AUDIO_WITH_POSITION(audioEvent.is<const char*>() ? audioEvent.as<const char*>() : nullptr, x, y, z);
	}

	static void LUA_NATIVE_AUDIO_INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY(sol::stack_object audioEvent, Entity entity)
	{
		AUDIO::INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY(audioEvent.is<const char*>() ? audioEvent.as<const char*>() : nullptr, entity);
	}

	static void LUA_NATIVE_AUDIO_SET_AUDIO_SPECIAL_EFFECT_MODE(int mode)
	{
		AUDIO::SET_AUDIO_SPECIAL_EFFECT_MODE(mode);
	}

	static void LUA_NATIVE_AUDIO_SET_PORTAL_SETTINGS_OVERRIDE(sol::stack_object p0, sol::stack_object p1)
	{
		AUDIO::SET_PORTAL_SETTINGS_OVERRIDE(p0.is<const char*>() ? p0.as<const char*>() : nullptr, p1.is<const char*>() ? p1.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_REMOVE_PORTAL_SETTINGS_OVERRIDE(sol::stack_object p0)
	{
		AUDIO::REMOVE_PORTAL_SETTINGS_OVERRIDE(p0.is<const char*>() ? p0.as<const char*>() : nullptr);
	}

	static void LUA_NATIVE_AUDIO_STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS()
	{
		AUDIO::STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS();
	}

	static int LUA_NATIVE_AUDIO_GET_MUSIC_VOL_SLIDER()
	{
		auto retval = AUDIO::GET_MUSIC_VOL_SLIDER();
		return retval;
	}

	static void LUA_NATIVE_AUDIO_REQUEST_TENNIS_BANKS(Ped ped)
	{
		AUDIO::REQUEST_TENNIS_BANKS(ped);
	}

	static void LUA_NATIVE_AUDIO_UNREQUEST_TENNIS_BANKS()
	{
		AUDIO::UNREQUEST_TENNIS_BANKS();
	}

	static void LUA_NATIVE_AUDIO_SET_SKIP_MINIGUN_SPIN_UP_AUDIO(bool p0)
	{
		AUDIO::SET_SKIP_MINIGUN_SPIN_UP_AUDIO(p0);
	}

	static void LUA_NATIVE_AUDIO_STOP_CUTSCENE_AUDIO()
	{
		AUDIO::STOP_CUTSCENE_AUDIO();
	}

	static bool LUA_NATIVE_AUDIO_HAS_LOADED_MP_DATA_SET()
	{
		auto retval = (bool)AUDIO::HAS_LOADED_MP_DATA_SET();
		return retval;
	}

	static bool LUA_NATIVE_AUDIO_HAS_LOADED_SP_DATA_SET()
	{
		auto retval = (bool)AUDIO::HAS_LOADED_SP_DATA_SET();
		return retval;
	}

	static int LUA_NATIVE_AUDIO_GET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle)
	{
		auto retval = AUDIO::GET_VEHICLE_HORN_SOUND_INDEX(vehicle);
		return retval;
	}

	static void LUA_NATIVE_AUDIO_SET_VEHICLE_HORN_SOUND_INDEX(Vehicle vehicle, int value)
	{
		AUDIO::SET_VEHICLE_HORN_SOUND_INDEX(vehicle, value);
	}

	void init_native_binding_AUDIO(sol::state& L)
	{
		auto AUDIO = L["AUDIO"].get_or_create<sol::table>();
		AUDIO.set_function("PLAY_PED_RINGTONE", LUA_NATIVE_AUDIO_PLAY_PED_RINGTONE);
		AUDIO.set_function("IS_PED_RINGTONE_PLAYING", LUA_NATIVE_AUDIO_IS_PED_RINGTONE_PLAYING);
		AUDIO.set_function("STOP_PED_RINGTONE", LUA_NATIVE_AUDIO_STOP_PED_RINGTONE);
		AUDIO.set_function("IS_MOBILE_PHONE_CALL_ONGOING", LUA_NATIVE_AUDIO_IS_MOBILE_PHONE_CALL_ONGOING);
		AUDIO.set_function("IS_MOBILE_INTERFERENCE_ACTIVE", LUA_NATIVE_AUDIO_IS_MOBILE_INTERFERENCE_ACTIVE);
		AUDIO.set_function("GET_CURRENT_TV_SHOW_PLAY_TIME", LUA_NATIVE_AUDIO_GET_CURRENT_TV_SHOW_PLAY_TIME);
		AUDIO.set_function("CREATE_NEW_SCRIPTED_CONVERSATION", LUA_NATIVE_AUDIO_CREATE_NEW_SCRIPTED_CONVERSATION);
		AUDIO.set_function("ADD_LINE_TO_CONVERSATION", LUA_NATIVE_AUDIO_ADD_LINE_TO_CONVERSATION);
		AUDIO.set_function("ADD_PED_TO_CONVERSATION", LUA_NATIVE_AUDIO_ADD_PED_TO_CONVERSATION);
		AUDIO.set_function("SET_POSITION_FOR_NULL_CONV_PED", LUA_NATIVE_AUDIO_SET_POSITION_FOR_NULL_CONV_PED);
		AUDIO.set_function("SET_ENTITY_FOR_NULL_CONV_PED", LUA_NATIVE_AUDIO_SET_ENTITY_FOR_NULL_CONV_PED);
		AUDIO.set_function("SET_MICROPHONE_POSITION", LUA_NATIVE_AUDIO_SET_MICROPHONE_POSITION);
		AUDIO.set_function("SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM", LUA_NATIVE_AUDIO_SET_CONVERSATION_AUDIO_CONTROLLED_BY_ANIM);
		AUDIO.set_function("SET_CONVERSATION_AUDIO_PLACEHOLDER", LUA_NATIVE_AUDIO_SET_CONVERSATION_AUDIO_PLACEHOLDER);
		AUDIO.set_function("START_SCRIPT_PHONE_CONVERSATION", LUA_NATIVE_AUDIO_START_SCRIPT_PHONE_CONVERSATION);
		AUDIO.set_function("PRELOAD_SCRIPT_PHONE_CONVERSATION", LUA_NATIVE_AUDIO_PRELOAD_SCRIPT_PHONE_CONVERSATION);
		AUDIO.set_function("START_SCRIPT_CONVERSATION", LUA_NATIVE_AUDIO_START_SCRIPT_CONVERSATION);
		AUDIO.set_function("PRELOAD_SCRIPT_CONVERSATION", LUA_NATIVE_AUDIO_PRELOAD_SCRIPT_CONVERSATION);
		AUDIO.set_function("START_PRELOADED_CONVERSATION", LUA_NATIVE_AUDIO_START_PRELOADED_CONVERSATION);
		AUDIO.set_function("GET_IS_PRELOADED_CONVERSATION_READY", LUA_NATIVE_AUDIO_GET_IS_PRELOADED_CONVERSATION_READY);
		AUDIO.set_function("IS_SCRIPTED_CONVERSATION_ONGOING", LUA_NATIVE_AUDIO_IS_SCRIPTED_CONVERSATION_ONGOING);
		AUDIO.set_function("IS_SCRIPTED_CONVERSATION_LOADED", LUA_NATIVE_AUDIO_IS_SCRIPTED_CONVERSATION_LOADED);
		AUDIO.set_function("GET_CURRENT_SCRIPTED_CONVERSATION_LINE", LUA_NATIVE_AUDIO_GET_CURRENT_SCRIPTED_CONVERSATION_LINE);
		AUDIO.set_function("PAUSE_SCRIPTED_CONVERSATION", LUA_NATIVE_AUDIO_PAUSE_SCRIPTED_CONVERSATION);
		AUDIO.set_function("RESTART_SCRIPTED_CONVERSATION", LUA_NATIVE_AUDIO_RESTART_SCRIPTED_CONVERSATION);
		AUDIO.set_function("STOP_SCRIPTED_CONVERSATION", LUA_NATIVE_AUDIO_STOP_SCRIPTED_CONVERSATION);
		AUDIO.set_function("SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE", LUA_NATIVE_AUDIO_SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE);
		AUDIO.set_function("INTERRUPT_CONVERSATION", LUA_NATIVE_AUDIO_INTERRUPT_CONVERSATION);
		AUDIO.set_function("INTERRUPT_CONVERSATION_AND_PAUSE", LUA_NATIVE_AUDIO_INTERRUPT_CONVERSATION_AND_PAUSE);
		AUDIO.set_function("GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE", LUA_NATIVE_AUDIO_GET_VARIATION_CHOSEN_FOR_SCRIPTED_LINE);
		AUDIO.set_function("SET_NO_DUCKING_FOR_CONVERSATION", LUA_NATIVE_AUDIO_SET_NO_DUCKING_FOR_CONVERSATION);
		AUDIO.set_function("REGISTER_SCRIPT_WITH_AUDIO", LUA_NATIVE_AUDIO_REGISTER_SCRIPT_WITH_AUDIO);
		AUDIO.set_function("UNREGISTER_SCRIPT_WITH_AUDIO", LUA_NATIVE_AUDIO_UNREGISTER_SCRIPT_WITH_AUDIO);
		AUDIO.set_function("REQUEST_MISSION_AUDIO_BANK", LUA_NATIVE_AUDIO_REQUEST_MISSION_AUDIO_BANK);
		AUDIO.set_function("REQUEST_AMBIENT_AUDIO_BANK", LUA_NATIVE_AUDIO_REQUEST_AMBIENT_AUDIO_BANK);
		AUDIO.set_function("REQUEST_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_REQUEST_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("HINT_MISSION_AUDIO_BANK", LUA_NATIVE_AUDIO_HINT_MISSION_AUDIO_BANK);
		AUDIO.set_function("HINT_AMBIENT_AUDIO_BANK", LUA_NATIVE_AUDIO_HINT_AMBIENT_AUDIO_BANK);
		AUDIO.set_function("HINT_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_HINT_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("RELEASE_MISSION_AUDIO_BANK", LUA_NATIVE_AUDIO_RELEASE_MISSION_AUDIO_BANK);
		AUDIO.set_function("RELEASE_AMBIENT_AUDIO_BANK", LUA_NATIVE_AUDIO_RELEASE_AMBIENT_AUDIO_BANK);
		AUDIO.set_function("RELEASE_NAMED_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_RELEASE_NAMED_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("RELEASE_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_RELEASE_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("UNHINT_AMBIENT_AUDIO_BANK", LUA_NATIVE_AUDIO_UNHINT_AMBIENT_AUDIO_BANK);
		AUDIO.set_function("UNHINT_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_UNHINT_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("UNHINT_NAMED_SCRIPT_AUDIO_BANK", LUA_NATIVE_AUDIO_UNHINT_NAMED_SCRIPT_AUDIO_BANK);
		AUDIO.set_function("GET_SOUND_ID", LUA_NATIVE_AUDIO_GET_SOUND_ID);
		AUDIO.set_function("RELEASE_SOUND_ID", LUA_NATIVE_AUDIO_RELEASE_SOUND_ID);
		AUDIO.set_function("PLAY_SOUND", LUA_NATIVE_AUDIO_PLAY_SOUND);
		AUDIO.set_function("PLAY_SOUND_FRONTEND", LUA_NATIVE_AUDIO_PLAY_SOUND_FRONTEND);
		AUDIO.set_function("PLAY_DEFERRED_SOUND_FRONTEND", LUA_NATIVE_AUDIO_PLAY_DEFERRED_SOUND_FRONTEND);
		AUDIO.set_function("PLAY_SOUND_FROM_ENTITY", LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_ENTITY);
		AUDIO.set_function("PLAY_SOUND_FROM_ENTITY_HASH", LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_ENTITY_HASH);
		AUDIO.set_function("PLAY_SOUND_FROM_COORD", LUA_NATIVE_AUDIO_PLAY_SOUND_FROM_COORD);
		AUDIO.set_function("UPDATE_SOUND_COORD", LUA_NATIVE_AUDIO_UPDATE_SOUND_COORD);
		AUDIO.set_function("STOP_SOUND", LUA_NATIVE_AUDIO_STOP_SOUND);
		AUDIO.set_function("GET_NETWORK_ID_FROM_SOUND_ID", LUA_NATIVE_AUDIO_GET_NETWORK_ID_FROM_SOUND_ID);
		AUDIO.set_function("GET_SOUND_ID_FROM_NETWORK_ID", LUA_NATIVE_AUDIO_GET_SOUND_ID_FROM_NETWORK_ID);
		AUDIO.set_function("SET_VARIABLE_ON_SOUND", LUA_NATIVE_AUDIO_SET_VARIABLE_ON_SOUND);
		AUDIO.set_function("SET_VARIABLE_ON_STREAM", LUA_NATIVE_AUDIO_SET_VARIABLE_ON_STREAM);
		AUDIO.set_function("OVERRIDE_UNDERWATER_STREAM", LUA_NATIVE_AUDIO_OVERRIDE_UNDERWATER_STREAM);
		AUDIO.set_function("SET_VARIABLE_ON_UNDER_WATER_STREAM", LUA_NATIVE_AUDIO_SET_VARIABLE_ON_UNDER_WATER_STREAM);
		AUDIO.set_function("HAS_SOUND_FINISHED", LUA_NATIVE_AUDIO_HAS_SOUND_FINISHED);
		AUDIO.set_function("PLAY_PED_AMBIENT_SPEECH_NATIVE", LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_NATIVE);
		AUDIO.set_function("PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE", LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_AND_CLONE_NATIVE);
		AUDIO.set_function("PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE", LUA_NATIVE_AUDIO_PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE);
		AUDIO.set_function("PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE", LUA_NATIVE_AUDIO_PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE);
		AUDIO.set_function("OVERRIDE_TREVOR_RAGE", LUA_NATIVE_AUDIO_OVERRIDE_TREVOR_RAGE);
		AUDIO.set_function("RESET_TREVOR_RAGE", LUA_NATIVE_AUDIO_RESET_TREVOR_RAGE);
		AUDIO.set_function("SET_PLAYER_ANGRY", LUA_NATIVE_AUDIO_SET_PLAYER_ANGRY);
		AUDIO.set_function("PLAY_PAIN", LUA_NATIVE_AUDIO_PLAY_PAIN);
		AUDIO.set_function("RELEASE_WEAPON_AUDIO", LUA_NATIVE_AUDIO_RELEASE_WEAPON_AUDIO);
		AUDIO.set_function("ACTIVATE_AUDIO_SLOWMO_MODE", LUA_NATIVE_AUDIO_ACTIVATE_AUDIO_SLOWMO_MODE);
		AUDIO.set_function("DEACTIVATE_AUDIO_SLOWMO_MODE", LUA_NATIVE_AUDIO_DEACTIVATE_AUDIO_SLOWMO_MODE);
		AUDIO.set_function("SET_AMBIENT_VOICE_NAME", LUA_NATIVE_AUDIO_SET_AMBIENT_VOICE_NAME);
		AUDIO.set_function("SET_AMBIENT_VOICE_NAME_HASH", LUA_NATIVE_AUDIO_SET_AMBIENT_VOICE_NAME_HASH);
		AUDIO.set_function("GET_AMBIENT_VOICE_NAME_HASH", LUA_NATIVE_AUDIO_GET_AMBIENT_VOICE_NAME_HASH);
		AUDIO.set_function("SET_PED_VOICE_FULL", LUA_NATIVE_AUDIO_SET_PED_VOICE_FULL);
		AUDIO.set_function("SET_PED_RACE_AND_VOICE_GROUP", LUA_NATIVE_AUDIO_SET_PED_RACE_AND_VOICE_GROUP);
		AUDIO.set_function("SET_PED_VOICE_GROUP", LUA_NATIVE_AUDIO_SET_PED_VOICE_GROUP);
		AUDIO.set_function("SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG", LUA_NATIVE_AUDIO_SET_PED_VOICE_GROUP_FROM_RACE_TO_PVG);
		AUDIO.set_function("SET_PED_GENDER", LUA_NATIVE_AUDIO_SET_PED_GENDER);
		AUDIO.set_function("STOP_CURRENT_PLAYING_SPEECH", LUA_NATIVE_AUDIO_STOP_CURRENT_PLAYING_SPEECH);
		AUDIO.set_function("STOP_CURRENT_PLAYING_AMBIENT_SPEECH", LUA_NATIVE_AUDIO_STOP_CURRENT_PLAYING_AMBIENT_SPEECH);
		AUDIO.set_function("IS_AMBIENT_SPEECH_PLAYING", LUA_NATIVE_AUDIO_IS_AMBIENT_SPEECH_PLAYING);
		AUDIO.set_function("IS_SCRIPTED_SPEECH_PLAYING", LUA_NATIVE_AUDIO_IS_SCRIPTED_SPEECH_PLAYING);
		AUDIO.set_function("IS_ANY_SPEECH_PLAYING", LUA_NATIVE_AUDIO_IS_ANY_SPEECH_PLAYING);
		AUDIO.set_function("IS_ANY_POSITIONAL_SPEECH_PLAYING", LUA_NATIVE_AUDIO_IS_ANY_POSITIONAL_SPEECH_PLAYING);
		AUDIO.set_function("DOES_CONTEXT_EXIST_FOR_THIS_PED", LUA_NATIVE_AUDIO_DOES_CONTEXT_EXIST_FOR_THIS_PED);
		AUDIO.set_function("IS_PED_IN_CURRENT_CONVERSATION", LUA_NATIVE_AUDIO_IS_PED_IN_CURRENT_CONVERSATION);
		AUDIO.set_function("SET_PED_IS_DRUNK", LUA_NATIVE_AUDIO_SET_PED_IS_DRUNK);
		AUDIO.set_function("PLAY_ANIMAL_VOCALIZATION", LUA_NATIVE_AUDIO_PLAY_ANIMAL_VOCALIZATION);
		AUDIO.set_function("IS_ANIMAL_VOCALIZATION_PLAYING", LUA_NATIVE_AUDIO_IS_ANIMAL_VOCALIZATION_PLAYING);
		AUDIO.set_function("SET_ANIMAL_MOOD", LUA_NATIVE_AUDIO_SET_ANIMAL_MOOD);
		AUDIO.set_function("IS_MOBILE_PHONE_RADIO_ACTIVE", LUA_NATIVE_AUDIO_IS_MOBILE_PHONE_RADIO_ACTIVE);
		AUDIO.set_function("SET_MOBILE_PHONE_RADIO_STATE", LUA_NATIVE_AUDIO_SET_MOBILE_PHONE_RADIO_STATE);
		AUDIO.set_function("GET_PLAYER_RADIO_STATION_INDEX", LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_INDEX);
		AUDIO.set_function("GET_PLAYER_RADIO_STATION_NAME", LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_NAME);
		AUDIO.set_function("GET_RADIO_STATION_NAME", LUA_NATIVE_AUDIO_GET_RADIO_STATION_NAME);
		AUDIO.set_function("GET_PLAYER_RADIO_STATION_GENRE", LUA_NATIVE_AUDIO_GET_PLAYER_RADIO_STATION_GENRE);
		AUDIO.set_function("IS_RADIO_RETUNING", LUA_NATIVE_AUDIO_IS_RADIO_RETUNING);
		AUDIO.set_function("IS_RADIO_FADED_OUT", LUA_NATIVE_AUDIO_IS_RADIO_FADED_OUT);
		AUDIO.set_function("SET_RADIO_RETUNE_UP", LUA_NATIVE_AUDIO_SET_RADIO_RETUNE_UP);
		AUDIO.set_function("SET_RADIO_RETUNE_DOWN", LUA_NATIVE_AUDIO_SET_RADIO_RETUNE_DOWN);
		AUDIO.set_function("SET_RADIO_TO_STATION_NAME", LUA_NATIVE_AUDIO_SET_RADIO_TO_STATION_NAME);
		AUDIO.set_function("SET_VEH_RADIO_STATION", LUA_NATIVE_AUDIO_SET_VEH_RADIO_STATION);
		AUDIO.set_function("SET_VEH_HAS_NORMAL_RADIO", LUA_NATIVE_AUDIO_SET_VEH_HAS_NORMAL_RADIO);
		AUDIO.set_function("IS_VEHICLE_RADIO_ON", LUA_NATIVE_AUDIO_IS_VEHICLE_RADIO_ON);
		AUDIO.set_function("SET_VEH_FORCED_RADIO_THIS_FRAME", LUA_NATIVE_AUDIO_SET_VEH_FORCED_RADIO_THIS_FRAME);
		AUDIO.set_function("SET_EMITTER_RADIO_STATION", LUA_NATIVE_AUDIO_SET_EMITTER_RADIO_STATION);
		AUDIO.set_function("SET_STATIC_EMITTER_ENABLED", LUA_NATIVE_AUDIO_SET_STATIC_EMITTER_ENABLED);
		AUDIO.set_function("LINK_STATIC_EMITTER_TO_ENTITY", LUA_NATIVE_AUDIO_LINK_STATIC_EMITTER_TO_ENTITY);
		AUDIO.set_function("SET_RADIO_TO_STATION_INDEX", LUA_NATIVE_AUDIO_SET_RADIO_TO_STATION_INDEX);
		AUDIO.set_function("SET_FRONTEND_RADIO_ACTIVE", LUA_NATIVE_AUDIO_SET_FRONTEND_RADIO_ACTIVE);
		AUDIO.set_function("UNLOCK_MISSION_NEWS_STORY", LUA_NATIVE_AUDIO_UNLOCK_MISSION_NEWS_STORY);
		AUDIO.set_function("IS_MISSION_NEWS_STORY_UNLOCKED", LUA_NATIVE_AUDIO_IS_MISSION_NEWS_STORY_UNLOCKED);
		AUDIO.set_function("GET_AUDIBLE_MUSIC_TRACK_TEXT_ID", LUA_NATIVE_AUDIO_GET_AUDIBLE_MUSIC_TRACK_TEXT_ID);
		AUDIO.set_function("PLAY_END_CREDITS_MUSIC", LUA_NATIVE_AUDIO_PLAY_END_CREDITS_MUSIC);
		AUDIO.set_function("SKIP_RADIO_FORWARD", LUA_NATIVE_AUDIO_SKIP_RADIO_FORWARD);
		AUDIO.set_function("FREEZE_RADIO_STATION", LUA_NATIVE_AUDIO_FREEZE_RADIO_STATION);
		AUDIO.set_function("UNFREEZE_RADIO_STATION", LUA_NATIVE_AUDIO_UNFREEZE_RADIO_STATION);
		AUDIO.set_function("SET_RADIO_AUTO_UNFREEZE", LUA_NATIVE_AUDIO_SET_RADIO_AUTO_UNFREEZE);
		AUDIO.set_function("SET_INITIAL_PLAYER_STATION", LUA_NATIVE_AUDIO_SET_INITIAL_PLAYER_STATION);
		AUDIO.set_function("SET_USER_RADIO_CONTROL_ENABLED", LUA_NATIVE_AUDIO_SET_USER_RADIO_CONTROL_ENABLED);
		AUDIO.set_function("SET_RADIO_TRACK", LUA_NATIVE_AUDIO_SET_RADIO_TRACK);
		AUDIO.set_function("SET_RADIO_TRACK_WITH_START_OFFSET", LUA_NATIVE_AUDIO_SET_RADIO_TRACK_WITH_START_OFFSET);
		AUDIO.set_function("SET_NEXT_RADIO_TRACK", LUA_NATIVE_AUDIO_SET_NEXT_RADIO_TRACK);
		AUDIO.set_function("SET_VEHICLE_RADIO_LOUD", LUA_NATIVE_AUDIO_SET_VEHICLE_RADIO_LOUD);
		AUDIO.set_function("CAN_VEHICLE_RECEIVE_CB_RADIO", LUA_NATIVE_AUDIO_CAN_VEHICLE_RECEIVE_CB_RADIO);
		AUDIO.set_function("SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY", LUA_NATIVE_AUDIO_SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY);
		AUDIO.set_function("DOES_PLAYER_VEH_HAVE_RADIO", LUA_NATIVE_AUDIO_DOES_PLAYER_VEH_HAVE_RADIO);
		AUDIO.set_function("IS_PLAYER_VEH_RADIO_ENABLE", LUA_NATIVE_AUDIO_IS_PLAYER_VEH_RADIO_ENABLE);
		AUDIO.set_function("SET_VEHICLE_RADIO_ENABLED", LUA_NATIVE_AUDIO_SET_VEHICLE_RADIO_ENABLED);
		AUDIO.set_function("SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED", LUA_NATIVE_AUDIO_SET_POSITIONED_PLAYER_VEHICLE_RADIO_EMITTER_ENABLED);
		AUDIO.set_function("SET_CUSTOM_RADIO_TRACK_LIST", LUA_NATIVE_AUDIO_SET_CUSTOM_RADIO_TRACK_LIST);
		AUDIO.set_function("CLEAR_CUSTOM_RADIO_TRACK_LIST", LUA_NATIVE_AUDIO_CLEAR_CUSTOM_RADIO_TRACK_LIST);
		AUDIO.set_function("GET_NUM_UNLOCKED_RADIO_STATIONS", LUA_NATIVE_AUDIO_GET_NUM_UNLOCKED_RADIO_STATIONS);
		AUDIO.set_function("FIND_RADIO_STATION_INDEX", LUA_NATIVE_AUDIO_FIND_RADIO_STATION_INDEX);
		AUDIO.set_function("SET_RADIO_STATION_MUSIC_ONLY", LUA_NATIVE_AUDIO_SET_RADIO_STATION_MUSIC_ONLY);
		AUDIO.set_function("SET_RADIO_FRONTEND_FADE_TIME", LUA_NATIVE_AUDIO_SET_RADIO_FRONTEND_FADE_TIME);
		AUDIO.set_function("UNLOCK_RADIO_STATION_TRACK_LIST", LUA_NATIVE_AUDIO_UNLOCK_RADIO_STATION_TRACK_LIST);
		AUDIO.set_function("LOCK_RADIO_STATION_TRACK_LIST", LUA_NATIVE_AUDIO_LOCK_RADIO_STATION_TRACK_LIST);
		AUDIO.set_function("UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS", LUA_NATIVE_AUDIO_UPDATE_UNLOCKABLE_DJ_RADIO_TRACKS);
		AUDIO.set_function("LOCK_RADIO_STATION", LUA_NATIVE_AUDIO_LOCK_RADIO_STATION);
		AUDIO.set_function("SET_RADIO_STATION_AS_FAVOURITE", LUA_NATIVE_AUDIO_SET_RADIO_STATION_AS_FAVOURITE);
		AUDIO.set_function("IS_RADIO_STATION_FAVOURITED", LUA_NATIVE_AUDIO_IS_RADIO_STATION_FAVOURITED);
		AUDIO.set_function("GET_NEXT_AUDIBLE_BEAT", LUA_NATIVE_AUDIO_GET_NEXT_AUDIBLE_BEAT);
		AUDIO.set_function("FORCE_MUSIC_TRACK_LIST", LUA_NATIVE_AUDIO_FORCE_MUSIC_TRACK_LIST);
		AUDIO.set_function("GET_CURRENT_TRACK_PLAY_TIME", LUA_NATIVE_AUDIO_GET_CURRENT_TRACK_PLAY_TIME);
		AUDIO.set_function("GET_CURRENT_TRACK_SOUND_NAME", LUA_NATIVE_AUDIO_GET_CURRENT_TRACK_SOUND_NAME);
		AUDIO.set_function("SET_VEHICLE_MISSILE_WARNING_ENABLED", LUA_NATIVE_AUDIO_SET_VEHICLE_MISSILE_WARNING_ENABLED);
		AUDIO.set_function("SET_AMBIENT_ZONE_STATE", LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_STATE);
		AUDIO.set_function("CLEAR_AMBIENT_ZONE_STATE", LUA_NATIVE_AUDIO_CLEAR_AMBIENT_ZONE_STATE);
		AUDIO.set_function("SET_AMBIENT_ZONE_LIST_STATE", LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_LIST_STATE);
		AUDIO.set_function("CLEAR_AMBIENT_ZONE_LIST_STATE", LUA_NATIVE_AUDIO_CLEAR_AMBIENT_ZONE_LIST_STATE);
		AUDIO.set_function("SET_AMBIENT_ZONE_STATE_PERSISTENT", LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_STATE_PERSISTENT);
		AUDIO.set_function("SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT", LUA_NATIVE_AUDIO_SET_AMBIENT_ZONE_LIST_STATE_PERSISTENT);
		AUDIO.set_function("IS_AMBIENT_ZONE_ENABLED", LUA_NATIVE_AUDIO_IS_AMBIENT_ZONE_ENABLED);
		AUDIO.set_function("REFRESH_CLOSEST_OCEAN_SHORELINE", LUA_NATIVE_AUDIO_REFRESH_CLOSEST_OCEAN_SHORELINE);
		AUDIO.set_function("SET_CUTSCENE_AUDIO_OVERRIDE", LUA_NATIVE_AUDIO_SET_CUTSCENE_AUDIO_OVERRIDE);
		AUDIO.set_function("SET_VARIABLE_ON_SYNCH_SCENE_AUDIO", LUA_NATIVE_AUDIO_SET_VARIABLE_ON_SYNCH_SCENE_AUDIO);
		AUDIO.set_function("PLAY_POLICE_REPORT", LUA_NATIVE_AUDIO_PLAY_POLICE_REPORT);
		AUDIO.set_function("CANCEL_ALL_POLICE_REPORTS", LUA_NATIVE_AUDIO_CANCEL_ALL_POLICE_REPORTS);
		AUDIO.set_function("BLIP_SIREN", LUA_NATIVE_AUDIO_BLIP_SIREN);
		AUDIO.set_function("OVERRIDE_VEH_HORN", LUA_NATIVE_AUDIO_OVERRIDE_VEH_HORN);
		AUDIO.set_function("IS_HORN_ACTIVE", LUA_NATIVE_AUDIO_IS_HORN_ACTIVE);
		AUDIO.set_function("SET_AGGRESSIVE_HORNS", LUA_NATIVE_AUDIO_SET_AGGRESSIVE_HORNS);
		AUDIO.set_function("SET_RADIO_POSITION_AUDIO_MUTE", LUA_NATIVE_AUDIO_SET_RADIO_POSITION_AUDIO_MUTE);
		AUDIO.set_function("SET_VEHICLE_CONVERSATIONS_PERSIST", LUA_NATIVE_AUDIO_SET_VEHICLE_CONVERSATIONS_PERSIST);
		AUDIO.set_function("SET_VEHICLE_CONVERSATIONS_PERSIST_NEW", LUA_NATIVE_AUDIO_SET_VEHICLE_CONVERSATIONS_PERSIST_NEW);
		AUDIO.set_function("IS_STREAM_PLAYING", LUA_NATIVE_AUDIO_IS_STREAM_PLAYING);
		AUDIO.set_function("GET_STREAM_PLAY_TIME", LUA_NATIVE_AUDIO_GET_STREAM_PLAY_TIME);
		AUDIO.set_function("LOAD_STREAM", LUA_NATIVE_AUDIO_LOAD_STREAM);
		AUDIO.set_function("LOAD_STREAM_WITH_START_OFFSET", LUA_NATIVE_AUDIO_LOAD_STREAM_WITH_START_OFFSET);
		AUDIO.set_function("PLAY_STREAM_FROM_PED", LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_PED);
		AUDIO.set_function("PLAY_STREAM_FROM_VEHICLE", LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_VEHICLE);
		AUDIO.set_function("PLAY_STREAM_FROM_OBJECT", LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_OBJECT);
		AUDIO.set_function("PLAY_STREAM_FRONTEND", LUA_NATIVE_AUDIO_PLAY_STREAM_FRONTEND);
		AUDIO.set_function("PLAY_STREAM_FROM_POSITION", LUA_NATIVE_AUDIO_PLAY_STREAM_FROM_POSITION);
		AUDIO.set_function("STOP_STREAM", LUA_NATIVE_AUDIO_STOP_STREAM);
		AUDIO.set_function("STOP_PED_SPEAKING", LUA_NATIVE_AUDIO_STOP_PED_SPEAKING);
		AUDIO.set_function("BLOCK_ALL_SPEECH_FROM_PED", LUA_NATIVE_AUDIO_BLOCK_ALL_SPEECH_FROM_PED);
		AUDIO.set_function("STOP_PED_SPEAKING_SYNCED", LUA_NATIVE_AUDIO_STOP_PED_SPEAKING_SYNCED);
		AUDIO.set_function("DISABLE_PED_PAIN_AUDIO", LUA_NATIVE_AUDIO_DISABLE_PED_PAIN_AUDIO);
		AUDIO.set_function("IS_AMBIENT_SPEECH_DISABLED", LUA_NATIVE_AUDIO_IS_AMBIENT_SPEECH_DISABLED);
		AUDIO.set_function("BLOCK_SPEECH_CONTEXT_GROUP", LUA_NATIVE_AUDIO_BLOCK_SPEECH_CONTEXT_GROUP);
		AUDIO.set_function("UNBLOCK_SPEECH_CONTEXT_GROUP", LUA_NATIVE_AUDIO_UNBLOCK_SPEECH_CONTEXT_GROUP);
		AUDIO.set_function("SET_SIREN_WITH_NO_DRIVER", LUA_NATIVE_AUDIO_SET_SIREN_WITH_NO_DRIVER);
		AUDIO.set_function("SET_SIREN_BYPASS_MP_DRIVER_CHECK", LUA_NATIVE_AUDIO_SET_SIREN_BYPASS_MP_DRIVER_CHECK);
		AUDIO.set_function("TRIGGER_SIREN_AUDIO", LUA_NATIVE_AUDIO_TRIGGER_SIREN_AUDIO);
		AUDIO.set_function("SET_HORN_PERMANENTLY_ON", LUA_NATIVE_AUDIO_SET_HORN_PERMANENTLY_ON);
		AUDIO.set_function("SET_HORN_ENABLED", LUA_NATIVE_AUDIO_SET_HORN_ENABLED);
		AUDIO.set_function("SET_AUDIO_VEHICLE_PRIORITY", LUA_NATIVE_AUDIO_SET_AUDIO_VEHICLE_PRIORITY);
		AUDIO.set_function("SET_HORN_PERMANENTLY_ON_TIME", LUA_NATIVE_AUDIO_SET_HORN_PERMANENTLY_ON_TIME);
		AUDIO.set_function("USE_SIREN_AS_HORN", LUA_NATIVE_AUDIO_USE_SIREN_AS_HORN);
		AUDIO.set_function("FORCE_USE_AUDIO_GAME_OBJECT", LUA_NATIVE_AUDIO_FORCE_USE_AUDIO_GAME_OBJECT);
		AUDIO.set_function("PRELOAD_VEHICLE_AUDIO_BANK", LUA_NATIVE_AUDIO_PRELOAD_VEHICLE_AUDIO_BANK);
		AUDIO.set_function("SET_VEHICLE_STARTUP_REV_SOUND", LUA_NATIVE_AUDIO_SET_VEHICLE_STARTUP_REV_SOUND);
		AUDIO.set_function("RESET_VEHICLE_STARTUP_REV_SOUND", LUA_NATIVE_AUDIO_RESET_VEHICLE_STARTUP_REV_SOUND);
		AUDIO.set_function("SET_VEHICLE_FORCE_REVERSE_WARNING", LUA_NATIVE_AUDIO_SET_VEHICLE_FORCE_REVERSE_WARNING);
		AUDIO.set_function("IS_VEHICLE_AUDIBLY_DAMAGED", LUA_NATIVE_AUDIO_IS_VEHICLE_AUDIBLY_DAMAGED);
		AUDIO.set_function("SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR", LUA_NATIVE_AUDIO_SET_VEHICLE_AUDIO_ENGINE_DAMAGE_FACTOR);
		AUDIO.set_function("SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR", LUA_NATIVE_AUDIO_SET_VEHICLE_AUDIO_BODY_DAMAGE_FACTOR);
		AUDIO.set_function("ENABLE_VEHICLE_FANBELT_DAMAGE", LUA_NATIVE_AUDIO_ENABLE_VEHICLE_FANBELT_DAMAGE);
		AUDIO.set_function("ENABLE_VEHICLE_EXHAUST_POPS", LUA_NATIVE_AUDIO_ENABLE_VEHICLE_EXHAUST_POPS);
		AUDIO.set_function("SET_VEHICLE_BOOST_ACTIVE", LUA_NATIVE_AUDIO_SET_VEHICLE_BOOST_ACTIVE);
		AUDIO.set_function("SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE", LUA_NATIVE_AUDIO_SET_PLAYER_VEHICLE_ALARM_AUDIO_ACTIVE);
		AUDIO.set_function("SET_SCRIPT_UPDATE_DOOR_AUDIO", LUA_NATIVE_AUDIO_SET_SCRIPT_UPDATE_DOOR_AUDIO);
		AUDIO.set_function("PLAY_VEHICLE_DOOR_OPEN_SOUND", LUA_NATIVE_AUDIO_PLAY_VEHICLE_DOOR_OPEN_SOUND);
		AUDIO.set_function("PLAY_VEHICLE_DOOR_CLOSE_SOUND", LUA_NATIVE_AUDIO_PLAY_VEHICLE_DOOR_CLOSE_SOUND);
		AUDIO.set_function("ENABLE_STALL_WARNING_SOUNDS", LUA_NATIVE_AUDIO_ENABLE_STALL_WARNING_SOUNDS);
		AUDIO.set_function("ENABLE_DRAG_RACE_STATIONARY_WARNING_SOUNDS_", LUA_NATIVE_AUDIO_ENABLE_DRAG_RACE_STATIONARY_WARNING_SOUNDS_);
		AUDIO.set_function("IS_GAME_IN_CONTROL_OF_MUSIC", LUA_NATIVE_AUDIO_IS_GAME_IN_CONTROL_OF_MUSIC);
		AUDIO.set_function("SET_GPS_ACTIVE", LUA_NATIVE_AUDIO_SET_GPS_ACTIVE);
		AUDIO.set_function("PLAY_MISSION_COMPLETE_AUDIO", LUA_NATIVE_AUDIO_PLAY_MISSION_COMPLETE_AUDIO);
		AUDIO.set_function("IS_MISSION_COMPLETE_PLAYING", LUA_NATIVE_AUDIO_IS_MISSION_COMPLETE_PLAYING);
		AUDIO.set_function("IS_MISSION_COMPLETE_READY_FOR_UI", LUA_NATIVE_AUDIO_IS_MISSION_COMPLETE_READY_FOR_UI);
		AUDIO.set_function("BLOCK_DEATH_JINGLE", LUA_NATIVE_AUDIO_BLOCK_DEATH_JINGLE);
		AUDIO.set_function("START_AUDIO_SCENE", LUA_NATIVE_AUDIO_START_AUDIO_SCENE);
		AUDIO.set_function("STOP_AUDIO_SCENE", LUA_NATIVE_AUDIO_STOP_AUDIO_SCENE);
		AUDIO.set_function("STOP_AUDIO_SCENES", LUA_NATIVE_AUDIO_STOP_AUDIO_SCENES);
		AUDIO.set_function("IS_AUDIO_SCENE_ACTIVE", LUA_NATIVE_AUDIO_IS_AUDIO_SCENE_ACTIVE);
		AUDIO.set_function("SET_AUDIO_SCENE_VARIABLE", LUA_NATIVE_AUDIO_SET_AUDIO_SCENE_VARIABLE);
		AUDIO.set_function("SET_AUDIO_SCRIPT_CLEANUP_TIME", LUA_NATIVE_AUDIO_SET_AUDIO_SCRIPT_CLEANUP_TIME);
		AUDIO.set_function("ADD_ENTITY_TO_AUDIO_MIX_GROUP", LUA_NATIVE_AUDIO_ADD_ENTITY_TO_AUDIO_MIX_GROUP);
		AUDIO.set_function("REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP", LUA_NATIVE_AUDIO_REMOVE_ENTITY_FROM_AUDIO_MIX_GROUP);
		AUDIO.set_function("AUDIO_IS_MUSIC_PLAYING", LUA_NATIVE_AUDIO_AUDIO_IS_MUSIC_PLAYING);
		AUDIO.set_function("AUDIO_IS_SCRIPTED_MUSIC_PLAYING", LUA_NATIVE_AUDIO_AUDIO_IS_SCRIPTED_MUSIC_PLAYING);
		AUDIO.set_function("PREPARE_MUSIC_EVENT", LUA_NATIVE_AUDIO_PREPARE_MUSIC_EVENT);
		AUDIO.set_function("CANCEL_MUSIC_EVENT", LUA_NATIVE_AUDIO_CANCEL_MUSIC_EVENT);
		AUDIO.set_function("TRIGGER_MUSIC_EVENT", LUA_NATIVE_AUDIO_TRIGGER_MUSIC_EVENT);
		AUDIO.set_function("IS_MUSIC_ONESHOT_PLAYING", LUA_NATIVE_AUDIO_IS_MUSIC_ONESHOT_PLAYING);
		AUDIO.set_function("GET_MUSIC_PLAYTIME", LUA_NATIVE_AUDIO_GET_MUSIC_PLAYTIME);
		AUDIO.set_function("SET_GLOBAL_RADIO_SIGNAL_LEVEL", LUA_NATIVE_AUDIO_SET_GLOBAL_RADIO_SIGNAL_LEVEL);
		AUDIO.set_function("RECORD_BROKEN_GLASS", LUA_NATIVE_AUDIO_RECORD_BROKEN_GLASS);
		AUDIO.set_function("CLEAR_ALL_BROKEN_GLASS", LUA_NATIVE_AUDIO_CLEAR_ALL_BROKEN_GLASS);
		AUDIO.set_function("SCRIPT_OVERRIDES_WIND_ELEVATION", LUA_NATIVE_AUDIO_SCRIPT_OVERRIDES_WIND_ELEVATION);
		AUDIO.set_function("SET_PED_WALLA_DENSITY", LUA_NATIVE_AUDIO_SET_PED_WALLA_DENSITY);
		AUDIO.set_function("SET_PED_INTERIOR_WALLA_DENSITY", LUA_NATIVE_AUDIO_SET_PED_INTERIOR_WALLA_DENSITY);
		AUDIO.set_function("FORCE_PED_PANIC_WALLA", LUA_NATIVE_AUDIO_FORCE_PED_PANIC_WALLA);
		AUDIO.set_function("PREPARE_ALARM", LUA_NATIVE_AUDIO_PREPARE_ALARM);
		AUDIO.set_function("START_ALARM", LUA_NATIVE_AUDIO_START_ALARM);
		AUDIO.set_function("STOP_ALARM", LUA_NATIVE_AUDIO_STOP_ALARM);
		AUDIO.set_function("STOP_ALL_ALARMS", LUA_NATIVE_AUDIO_STOP_ALL_ALARMS);
		AUDIO.set_function("IS_ALARM_PLAYING", LUA_NATIVE_AUDIO_IS_ALARM_PLAYING);
		AUDIO.set_function("GET_VEHICLE_DEFAULT_HORN", LUA_NATIVE_AUDIO_GET_VEHICLE_DEFAULT_HORN);
		AUDIO.set_function("GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS", LUA_NATIVE_AUDIO_GET_VEHICLE_DEFAULT_HORN_IGNORE_MODS);
		AUDIO.set_function("RESET_PED_AUDIO_FLAGS", LUA_NATIVE_AUDIO_RESET_PED_AUDIO_FLAGS);
		AUDIO.set_function("SET_PED_FOOTSTEPS_EVENTS_ENABLED", LUA_NATIVE_AUDIO_SET_PED_FOOTSTEPS_EVENTS_ENABLED);
		AUDIO.set_function("SET_PED_CLOTH_EVENTS_ENABLED", LUA_NATIVE_AUDIO_SET_PED_CLOTH_EVENTS_ENABLED);
		AUDIO.set_function("OVERRIDE_PLAYER_GROUND_MATERIAL", LUA_NATIVE_AUDIO_OVERRIDE_PLAYER_GROUND_MATERIAL);
		AUDIO.set_function("USE_FOOTSTEP_SCRIPT_SWEETENERS", LUA_NATIVE_AUDIO_USE_FOOTSTEP_SCRIPT_SWEETENERS);
		AUDIO.set_function("OVERRIDE_MICROPHONE_SETTINGS", LUA_NATIVE_AUDIO_OVERRIDE_MICROPHONE_SETTINGS);
		AUDIO.set_function("FREEZE_MICROPHONE", LUA_NATIVE_AUDIO_FREEZE_MICROPHONE);
		AUDIO.set_function("DISTANT_COP_CAR_SIRENS", LUA_NATIVE_AUDIO_DISTANT_COP_CAR_SIRENS);
		AUDIO.set_function("SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO", LUA_NATIVE_AUDIO_SET_SIREN_CAN_BE_CONTROLLED_BY_AUDIO);
		AUDIO.set_function("ENABLE_STUNT_JUMP_AUDIO", LUA_NATIVE_AUDIO_ENABLE_STUNT_JUMP_AUDIO);
		AUDIO.set_function("SET_AUDIO_FLAG", LUA_NATIVE_AUDIO_SET_AUDIO_FLAG);
		AUDIO.set_function("PREPARE_SYNCHRONIZED_AUDIO_EVENT", LUA_NATIVE_AUDIO_PREPARE_SYNCHRONIZED_AUDIO_EVENT);
		AUDIO.set_function("PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE", LUA_NATIVE_AUDIO_PREPARE_SYNCHRONIZED_AUDIO_EVENT_FOR_SCENE);
		AUDIO.set_function("PLAY_SYNCHRONIZED_AUDIO_EVENT", LUA_NATIVE_AUDIO_PLAY_SYNCHRONIZED_AUDIO_EVENT);
		AUDIO.set_function("STOP_SYNCHRONIZED_AUDIO_EVENT", LUA_NATIVE_AUDIO_STOP_SYNCHRONIZED_AUDIO_EVENT);
		AUDIO.set_function("INIT_SYNCH_SCENE_AUDIO_WITH_POSITION", LUA_NATIVE_AUDIO_INIT_SYNCH_SCENE_AUDIO_WITH_POSITION);
		AUDIO.set_function("INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY", LUA_NATIVE_AUDIO_INIT_SYNCH_SCENE_AUDIO_WITH_ENTITY);
		AUDIO.set_function("SET_AUDIO_SPECIAL_EFFECT_MODE", LUA_NATIVE_AUDIO_SET_AUDIO_SPECIAL_EFFECT_MODE);
		AUDIO.set_function("SET_PORTAL_SETTINGS_OVERRIDE", LUA_NATIVE_AUDIO_SET_PORTAL_SETTINGS_OVERRIDE);
		AUDIO.set_function("REMOVE_PORTAL_SETTINGS_OVERRIDE", LUA_NATIVE_AUDIO_REMOVE_PORTAL_SETTINGS_OVERRIDE);
		AUDIO.set_function("STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS", LUA_NATIVE_AUDIO_STOP_SMOKE_GRENADE_EXPLOSION_SOUNDS);
		AUDIO.set_function("GET_MUSIC_VOL_SLIDER", LUA_NATIVE_AUDIO_GET_MUSIC_VOL_SLIDER);
		AUDIO.set_function("REQUEST_TENNIS_BANKS", LUA_NATIVE_AUDIO_REQUEST_TENNIS_BANKS);
		AUDIO.set_function("UNREQUEST_TENNIS_BANKS", LUA_NATIVE_AUDIO_UNREQUEST_TENNIS_BANKS);
		AUDIO.set_function("SET_SKIP_MINIGUN_SPIN_UP_AUDIO", LUA_NATIVE_AUDIO_SET_SKIP_MINIGUN_SPIN_UP_AUDIO);
		AUDIO.set_function("STOP_CUTSCENE_AUDIO", LUA_NATIVE_AUDIO_STOP_CUTSCENE_AUDIO);
		AUDIO.set_function("HAS_LOADED_MP_DATA_SET", LUA_NATIVE_AUDIO_HAS_LOADED_MP_DATA_SET);
		AUDIO.set_function("HAS_LOADED_SP_DATA_SET", LUA_NATIVE_AUDIO_HAS_LOADED_SP_DATA_SET);
		AUDIO.set_function("GET_VEHICLE_HORN_SOUND_INDEX", LUA_NATIVE_AUDIO_GET_VEHICLE_HORN_SOUND_INDEX);
		AUDIO.set_function("SET_VEHICLE_HORN_SOUND_INDEX", LUA_NATIVE_AUDIO_SET_VEHICLE_HORN_SOUND_INDEX);
	}
}

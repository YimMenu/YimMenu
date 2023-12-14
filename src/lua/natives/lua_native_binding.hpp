#pragma once

namespace lua::native
{
	void init_native_binding(sol::state& L);

	void init_native_binding_SYSTEM(sol::state& L);
	void init_native_binding_APP(sol::state& L);
	void init_native_binding_AUDIO(sol::state& L);
	void init_native_binding_BRAIN(sol::state& L);
	void init_native_binding_CAM(sol::state& L);
	void init_native_binding_CLOCK(sol::state& L);
	void init_native_binding_CUTSCENE(sol::state& L);
	void init_native_binding_DATAFILE(sol::state& L);
	void init_native_binding_DECORATOR(sol::state& L);
	void init_native_binding_DLC(sol::state& L);
	void init_native_binding_ENTITY(sol::state& L);
	void init_native_binding_EVENT(sol::state& L);
	void init_native_binding_FILES(sol::state& L);
	void init_native_binding_FIRE(sol::state& L);
	void init_native_binding_GRAPHICS(sol::state& L);
	void init_native_binding_HUD(sol::state& L);
	void init_native_binding_INTERIOR(sol::state& L);
	void init_native_binding_ITEMSET(sol::state& L);
	void init_native_binding_LOADINGSCREEN(sol::state& L);
	void init_native_binding_LOCALIZATION(sol::state& L);
	void init_native_binding_MISC(sol::state& L);
	void init_native_binding_MOBILE(sol::state& L);
	void init_native_binding_MONEY(sol::state& L);
	void init_native_binding_NETSHOPPING(sol::state& L);
	void init_native_binding_NETWORK(sol::state& L);
	void init_native_binding_OBJECT(sol::state& L);
	void init_native_binding_PAD(sol::state& L);
	void init_native_binding_PATHFIND(sol::state& L);
	void init_native_binding_PED(sol::state& L);
	void init_native_binding_PHYSICS(sol::state& L);
	void init_native_binding_PLAYER(sol::state& L);
	void init_native_binding_RECORDING(sol::state& L);
	void init_native_binding_REPLAY(sol::state& L);
	void init_native_binding_SAVEMIGRATION(sol::state& L);
	void init_native_binding_SCRIPT(sol::state& L);
	void init_native_binding_SECURITY(sol::state& L);
	void init_native_binding_SHAPETEST(sol::state& L);
	void init_native_binding_SOCIALCLUB(sol::state& L);
	void init_native_binding_STATS(sol::state& L);
	void init_native_binding_STREAMING(sol::state& L);
	void init_native_binding_TASK(sol::state& L);
	void init_native_binding_VEHICLE(sol::state& L);
	void init_native_binding_WATER(sol::state& L);
	void init_native_binding_WEAPON(sol::state& L);
	void init_native_binding_ZONE(sol::state& L);
}

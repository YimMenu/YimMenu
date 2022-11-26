#include "script.hpp"
#include "invoker.hpp"
#include "pointers.hpp"
#include "shv_runner.h"
#include "script_manager.h"
#include <set>
#include "pools.h"
#include "renderer.hpp"

#define DLL_EXPORT __declspec( dllexport )

void DLL_EXPORT scriptWait(unsigned long waitTime)
{
	typedef std::chrono::duration<unsigned long long> my_duran_duran_duration;
	big::script::get_current()->yield(std::chrono::duration_cast<my_duran_duran_duration>(std::chrono::milliseconds(waitTime)));
}

void DLL_EXPORT scriptRegister(HMODULE module, void(*function)())
{
	big::shv_runner::scripts.emplace(module, function);
}

void DLL_EXPORT scriptUnregister(void(*function)())
{
	for(auto iter : big::shv_runner::scripts)
		if(function == iter.second)
			big::shv_runner::scripts.erase(iter.first);
}

void DLL_EXPORT scriptUnregister(HMODULE module)
{
	big::shv_runner::scripts.erase(module);
}

eGameVersion DLL_EXPORT getGameVersion()
{
	return VER_1_0_2699_16;
}

void DLL_EXPORT scriptRegisterAdditionalThread(HMODULE module, void(*function)())
{
	big::shv_runner::scripts.emplace(module, function);
}

static uint64_t g_hash;

void DLL_EXPORT nativeInit(uint64_t hash)
{
	big::g_native_invoker.begin_call();
	if (hash == 0x43A66C31C68491C0)
		hash = 0x50FAC3A3E030A6E1;
	if (hash == 0x239528EACDC3E7DE)
		hash = 0x3882114BDE571AD4;
	g_hash = hash;
}

void DLL_EXPORT nativePush64(uint64_t value)
{
	big::g_native_invoker.push_arg(std::forward<uint64_t>(value));
}

PUINT64 DLL_EXPORT nativeCall()
{
	big::g_native_invoker.end_call(g_hash);
	return reinterpret_cast<uint64_t*>(big::g_native_invoker.get_return_address());
}

typedef void(*TKeyboardFn)(DWORD key, WORD repeats, BYTE scanCode, BOOL isExtended, BOOL isWithAlt, BOOL wasDownBefore, BOOL isUpNow);

static std::set<TKeyboardFn> g_keyboardFunctions;

void DLL_EXPORT keyboardHandlerRegister(TKeyboardFn function) {

	g_keyboardFunctions.insert(function);
}

void DLL_EXPORT keyboardHandlerUnregister(TKeyboardFn function)
{
	g_keyboardFunctions.erase(function);
}

void ScriptManager::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (uMsg == WM_KEYDOWN || uMsg == WM_KEYUP || uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP) {

		auto functions = g_keyboardFunctions;

		for (auto& function : functions) {
			function((DWORD)wParam, lParam & 0xFFFF, (lParam >> 16) & 0xFF, (lParam >> 24) & 1, (uMsg == WM_SYSKEYDOWN || uMsg == WM_SYSKEYUP), (lParam >> 30) & 1, (uMsg == WM_SYSKEYUP || uMsg == WM_KEYUP));
		}
	}
}

PUINT64 DLL_EXPORT getGlobalPtr(int globalId)
{
	return reinterpret_cast<PUINT64>(&big::g_pointers->m_script_globals[globalId >> 18 & 0x3F][globalId & 0x3FFFF]);
}

int DLL_EXPORT worldGetAllPeds(int* arr, int arrSize)
{
	return rage::GetAllWorld(PoolTypePed, arrSize, arr);
}

int DLL_EXPORT worldGetAllVehicles(int* arr, int arrSize)
{
	return rage::GetAllWorld(PoolTypeVehicle, arrSize, arr);
}

int DLL_EXPORT worldGetAllObjects(int* arr, int arrSize)
{
	return rage::GetAllWorld(PoolTypeObject, arrSize, arr);
}

int DLL_EXPORT worldGetAllPickups(int* arr, int arrSize)
{
	return rage::GetAllWorld(PoolTypePickup, arrSize, arr);
}

DLL_EXPORT BYTE* getScriptHandleBaseAddress(int handle)
{
	return (BYTE*)big::g_pointers->m_handle_to_ptr(handle);
}

int DLL_EXPORT registerRawStreamingFile(const std::string& fileName, const std::string& registerAs)
{
	int textureID = -1;
	if (big::g_pointers->m_register_file(&textureID, fileName.c_str(), true, fileName.c_str(), false))
	{
		LOG(G3LOG_DEBUG) << "Registered File " << fileName.c_str() << " with ID:" << textureID;
		return textureID;
	}

	LOG(FATAL) << "Failed to register " << fileName.c_str();
	return 0;
}

/* D3d SwapChain */
DLL_EXPORT void presentCallbackRegister(PresentCallback cb)
{
	big::g_renderer->add_callback(cb);
}

DLL_EXPORT void presentCallbackUnregister(PresentCallback cb)
{
	big::g_renderer->remove_callback(cb);
}

/* textures */
DLL_EXPORT int createTexture(const char* texFileName)
{
	return -1; // Implement later if we can get the DirectXTK working.
}

DLL_EXPORT void drawTexture(int id, int index, int level, int time, float sizeX, float sizeY, float centerX, float centerY, float posX, float posY, float rotation, float screenHeightScaleFactor, float r, float g, float b, float a)
{
	// Implement later if we can get the DirectXTK working.
}
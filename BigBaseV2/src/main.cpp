#include "common.hpp"
#include "features.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "logger.hpp"
#include "hooking.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);

		g_hmodule = hmod;
		g_main_thread = CreateThread(nullptr, 0, [](PVOID) -> DWORD
		{
			auto logger_instance = std::make_unique<logger>();
			try
			{
				
				LOG_RAW(log_color::green | log_color::intensify,
u8R"kek(                     ...
                   ;::::;
                 ;::::; :;
               ;:::::'   :;
              ;:::::;     ;.
             ,:::::'       ;           OOO\
             ::::::;       ;          OOOOO\
             ;:::::;       ;         OOOOOOOO
            ,;::::::;     ;'         / OOOOOOO
          ;:::::::::`. ,,,;.        /  / DOOOOOO
        .';:::::::::::::::::;,     /  /     DOOOO
       ,::::::;::::::;;;;::::;,   /  /        DOOO
      ;`::::::`'::::::;;;::::: ,#/  /          DOOO
      :`:::::::`;::::::;;::: ;::#  /            DOOO
      ::`:::::::`;:::::::: ;::::# /              DOO
      `:`:::::::`;:::::: ;::::::#/               DOO
       :::`:::::::`;; ;:::::::::##                OO
       ::::`:::::::`;::::::::;:::#                OO
       `:::::`::::::::::::;'`:;::#                O
        `:::::`::::::::;' /  / `:#
         ::::::`:::::;'  /  /   `#

)kek");
				
				auto pointers_instance = std::make_unique<pointers>();
				LOG_INFO("Pointers initialized.");

				if (*g_pointers->m_game_state != eGameState::Playing)
				{
					LOG_INFO("Waiting for the game to load.");
					do
					{
						std::this_thread::sleep_for(100ms);
					} while (*g_pointers->m_game_state != eGameState::Playing);

					LOG_INFO("The game has loaded.");
				}
				else
				{
					LOG_INFO("The game is already loaded.");
				}

				auto renderer_instance = std::make_unique<renderer>();
				LOG_INFO("Renderer initialized.");

				auto fiber_pool_instance = std::make_unique<fiber_pool>(10);
				LOG_INFO("Fiber pool initialized.");

				auto hooking_instance = std::make_unique<hooking>();
				LOG_INFO("Hooking initialized.");

				g_script_mgr.add_script(std::make_unique<script>(&features::script_func));
				g_script_mgr.add_script(std::make_unique<script>(&gui::script_func));
				LOG_INFO("Scripts registered.");

				g_hooking->enable();
				LOG_INFO("Hooking enabled.");

				while (g_running)
				{
					if (GetAsyncKeyState(VK_END) & 0x8000)
						g_running = false;

					g_hooking->ensure_dynamic_hooks();
					std::this_thread::sleep_for(10ms);
				}

				g_hooking->disable();
				LOG_INFO("Hooking disabled.");

				std::this_thread::sleep_for(1000ms);

				g_script_mgr.remove_all_scripts();
				LOG_INFO("Scripts unregistered.");

				hooking_instance.reset();
				LOG_INFO("Hooking uninitialized.");

				fiber_pool_instance.reset();
				LOG_INFO("Fiber pool uninitialized.");

				renderer_instance.reset();
				LOG_INFO("Renderer uninitialized.");

				pointers_instance.reset();
				LOG_INFO("Pointers uninitialized.");
			}
			catch (std::exception const &ex)
			{
				LOG_ERROR("{}", ex.what());
				MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION);
			}

			LOG_INFO("Farewell!");
			logger_instance.reset();

			CloseHandle(g_main_thread);
			FreeLibraryAndExitThread(g_hmodule, 0);
		}, nullptr, 0, &g_main_thread_id);
	}

	return true;
}

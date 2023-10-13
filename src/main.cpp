#include "backend/backend.hpp"
#include "byte_patch_manager.hpp"
#include "fiber_pool.hpp"
#include "gui.hpp"
#include "hooking.hpp"
#include "logger/exception_handler.hpp"
#include "native_hooks/native_hooks.hpp"
#include "pointers.hpp"
#include "renderer.hpp"
#include "script_mgr.hpp"
#include "services/api/api_service.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "services/custom_text/custom_text_service.hpp"
#include "services/gta_data/gta_data_service.hpp"
#include "services/gui/gui_service.hpp"
#include "services/matchmaking/matchmaking_service.hpp"
#include "services/mobile/mobile_service.hpp"
#include "services/notifications/notification_service.hpp"
#include "services/pickups/pickup_service.hpp"
#include "services/players/player_service.hpp"
#include "services/script_patcher/script_patcher_service.hpp"
#include "services/tunables/tunables_service.hpp"
#include "thread_pool.hpp"
#include "util/migrate.hpp"
#include "version.hpp"
#include "core/settings.hpp"

BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, PVOID)
{
	using namespace big;
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);
		g_hmodule     = hmod;
		g_main_thread = CreateThread(
		    nullptr,
		    0,
		    [](PVOID) -> DWORD {
			    auto handler = exception_handler();

			    while (!FindWindow("grcWindow", nullptr))
				    std::this_thread::sleep_for(100ms);

			    std::filesystem::path base_dir = std::getenv("appdata");
			    base_dir /= "YimMenu";
			    do_migration(base_dir);
			    g_file_manager.init(base_dir);

			    auto logger_instance = std::make_unique<logger>("YimMenu", g_file_manager.get_project_file("./cout.log"));

			    EnableMenuItem(GetSystemMenu(GetConsoleWindow(), 0), SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);

			    std::srand(std::chrono::system_clock::now().time_since_epoch().count());

			    LOG(INFO) << "Yim's Menu Initializing";
			    LOGF(INFO, "Git Info\n\tBranch:\t{}\n\tHash:\t{}\n\tDate:\t{}", version::GIT_BRANCH, version::GIT_SHA1, version::GIT_DATE);

			    auto thread_pool_instance = std::make_unique<thread_pool>();
			    LOG(INFO) << "Thread pool initialized.";

			    g_menu_settings.init(g_file_manager.get_project_file("./settings.json"));
			    LOG(INFO) << "Settings Loaded.";

			    auto pointers_instance = std::make_unique<pointers>();
			    LOG(INFO) << "Pointers initialized.";

			    auto byte_patch_manager_instance = std::make_unique<byte_patch_manager>();
			    LOG(INFO) << "Byte Patch Manager initialized.";

			    auto renderer_instance = std::make_unique<renderer>();
			    LOG(INFO) << "Renderer initialized.";
			    auto gui_instance = std::make_unique<gui>();

			    auto fiber_pool_instance = std::make_unique<fiber_pool>(11);
			    LOG(INFO) << "Fiber pool initialized.";

			    auto hooking_instance = std::make_unique<hooking>();
			    LOG(INFO) << "Hooking initialized.";

			    auto context_menu_service_instance      = std::make_unique<context_menu_service>();
			    auto custom_text_service_instance       = std::make_unique<custom_text_service>();
			    auto mobile_service_instance            = std::make_unique<mobile_service>();
			    auto notification_service_instance      = std::make_unique<notification_service>();
			    auto pickup_service_instance            = std::make_unique<pickup_service>();
			    auto player_service_instance            = std::make_unique<player_service>();
			    auto gta_data_service_instance          = std::make_unique<gta_data_service>();
			    auto gui_service_instance               = std::make_unique<gui_service>();
			    auto script_patcher_service_instance    = std::make_unique<script_patcher_service>();
			    auto matchmaking_service_instance       = std::make_unique<matchmaking_service>();
			    auto api_service_instance               = std::make_unique<api_service>();
			    auto tunables_service_instance          = std::make_unique<tunables_service>();
			    LOG(INFO) << "Registered service instances...";

			    g_script_mgr.add_script(std::make_unique<script>(&gui::script_func, "GUI", false));

			    g_script_mgr.add_script(std::make_unique<script>(&backend::loop, "Backend Loop", false));
			    g_script_mgr.add_script(std::make_unique<script>(&backend::vehicles_loop, "Vehicle"));
			    g_script_mgr.add_script(std::make_unique<script>(&backend::misc_loop, "Miscellaneous"));
			    g_script_mgr.add_script(std::make_unique<script>(&backend::remote_loop, "Remote"));
			    g_script_mgr.add_script(std::make_unique<script>(&backend::disable_control_action_loop, "Disable Controls"));
				g_script_mgr.add_script(std::make_unique<script>(&backend::world_loop, "World"));
			    g_script_mgr.add_script(std::make_unique<script>(&context_menu_service::context_menu, "Context Menu"));
			    g_script_mgr.add_script(std::make_unique<script>(&backend::tunables_script, "Tunables"));

			    LOG(INFO) << "Scripts registered.";

			    g_hooking->enable();
			    LOG(INFO) << "Hooking enabled.";

			    auto native_hooks_instance = std::make_unique<native_hooks>();
			    LOG(INFO) << "Dynamic native hooker initialized.";

			    g_running = true;

			    while (g_running)
				    std::this_thread::sleep_for(500ms);

			    g_script_mgr.remove_all_scripts();
			    LOG(INFO) << "Scripts unregistered.";

			    g_hooking->disable();
			    LOG(INFO) << "Hooking disabled.";

			    native_hooks_instance.reset();
			    LOG(INFO) << "Dynamic native hooker uninitialized.";

			    // Make sure that all threads created don't have any blocking loops
			    // otherwise make sure that they have stopped executing
			    thread_pool_instance->destroy();
			    LOG(INFO) << "Destroyed thread pool.";

			    tunables_service_instance.reset();
			    LOG(INFO) << "Tunables Service reset.";
			    matchmaking_service_instance.reset();
			    LOG(INFO) << "Matchmaking Service reset.";
			    api_service_instance.reset();
			    LOG(INFO) << "API Service reset.";
			    script_patcher_service_instance.reset();
			    LOG(INFO) << "Script Patcher Service reset.";
			    gui_service_instance.reset();
			    LOG(INFO) << "Gui Service reset.";
			    gta_data_service_instance.reset();
			    LOG(INFO) << "GTA Data Service reset.";
			    mobile_service_instance.reset();
			    LOG(INFO) << "Mobile Service reset.";
			    player_service_instance.reset();
			    LOG(INFO) << "Player Service reset.";
			    pickup_service_instance.reset();
			    LOG(INFO) << "Pickup Service reset.";
			    custom_text_service_instance.reset();
			    LOG(INFO) << "Custom Text Service reset.";
			    context_menu_service_instance.reset();
			    LOG(INFO) << "Context Service reset.";

			    LOG(INFO) << "Services uninitialized.";

			    hooking_instance.reset();
			    LOG(INFO) << "Hooking uninitialized.";

			    fiber_pool_instance.reset();
			    LOG(INFO) << "Fiber pool uninitialized.";

			    renderer_instance.reset();
			    LOG(INFO) << "Renderer uninitialized.";

			    byte_patch_manager_instance.reset();
			    LOG(INFO) << "Byte Patch Manager uninitialized.";

			    pointers_instance.reset();
			    LOG(INFO) << "Pointers uninitialized.";

			    thread_pool_instance.reset();
			    LOG(INFO) << "Thread pool uninitialized.";

			    LOG(INFO) << "Farewell!";
			    logger_instance->destroy();
			    logger_instance.reset();

			    CloseHandle(g_main_thread);
			    FreeLibraryAndExitThread(g_hmodule, 0);
		    },
		    nullptr,
		    0,
		    &g_main_thread_id);
	}

	return true;
}
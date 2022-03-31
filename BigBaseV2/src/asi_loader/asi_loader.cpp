#include "asi_loader.hpp"
#include "file_manager.hpp"
#include "logger.hpp"
#include "util/pe_image.hpp"

using namespace big;

void asi_loader::initialize() {

    LOG(INFO) << "Loading *.asi plugins.";

    const auto asi_folder = g_file_manager->get_project_folder("./OpenHookV");

    for (const auto& item : std::filesystem::directory_iterator(asi_folder.get_path()))
    {
        if (item.is_directory())
            continue;

        const auto path = item.path();
        if (path.extension() != ".asi")
            continue;

        utility::pe_image plugin_image;
        if (!plugin_image.Load(path.string()))
        {
            LOG(WARNING) << "Failed to load image: " << path.filename();

            continue;
        }

        if (!plugin_image.IsOpenVHookCompatible())
        {
            LOG(INFO) << "ASI is not compatible, patching imports...";

            if (!plugin_image.PatchCompatibility())
            {
                LOG(WARNING) << "Failed to patch image: " << path.filename();

                continue;
            }
        }
        const auto hmod = LoadLibraryA(path.string().c_str());
        if (!hmod)
        {
            LOG(WARNING) << "Failed to load image: " << path.filename();

            continue;
        }
        LOG(INFO) << "Loaded image: " << path.filename() << " -> " << HEX_TO_UPPER(hmod);
    }

    LOG(INFO) << "Finished loading *.asi plugins.";
}
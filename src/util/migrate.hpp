#pragma once
#include <filesystem>

namespace big
{
    void do_migration(const std::filesystem::path& current_dir)
    {
        std::filesystem::path old_dir = std::getenv("appdata");
        old_dir /= "BigBaseV2";

        if (exists(old_dir) && !exists(current_dir))
        {
            LOG(INFO) << "YimMenu folder does not exist, migrating to new folder.";
            std::filesystem::copy(old_dir, current_dir, std::filesystem::copy_options::recursive);
        }
    }
}
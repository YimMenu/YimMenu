#include "file_manager.hpp"

namespace big
{
    bool file_manager::init(const std::filesystem::path& base_dir)
    {
        m_base_dir = base_dir;
        file_manager::ensure_folder_exists(m_base_dir);

        return true;
    }

    const std::filesystem::path& file_manager::get_base_dir()
    {
        return m_base_dir;
    }
    
	file file_manager::get_project_file(std::filesystem::path file_path)
    {
        if (file_path.is_absolute())
            throw std::exception("Project files are relative to the BaseDir, don't use absolute paths!");

        return file_manager::ensure_file_can_be_created(m_base_dir / file_path);
    }

	folder file_manager::get_project_folder(std::filesystem::path folder_path)
    {
        if (folder_path.is_absolute())
            throw std::exception("Project folders are relative to the BaseDir, don't use absolute paths!");

        return file_manager::ensure_folder_exists(m_base_dir / folder_path);
    }

	std::filesystem::path file_manager::ensure_file_can_be_created(const std::filesystem::path file_path)
    {
        file_manager::ensure_folder_exists(file_path.parent_path());

        return file_path;
    }
    
	std::filesystem::path file_manager::ensure_folder_exists(const std::filesystem::path folder_path)
    {
        bool create_path = !std::filesystem::exists(folder_path);

        if (!create_path && !std::filesystem::is_directory(folder_path))
        {
            std::filesystem::remove(folder_path);
            create_path = true;
        }
        if (create_path)
            std::filesystem::create_directory(folder_path);

        return folder_path;
    }
}

#include "folder.hpp"

#include "file_manager.hpp"

namespace big
{
	folder::folder(file_manager* file_manager, std::filesystem::path file_path) :
	    folder(file_manager->get_base_dir() / file_path)
	{
		m_file_manager    = file_manager;
		m_is_project_file = true;
	}

	folder::folder(std::filesystem::path folder_path) :
	    m_folder_path(file_manager::ensure_folder_exists(folder_path))
	{
	}

	file folder::get_file(std::filesystem::path file_path) const
	{
		if (file_path.is_absolute())
			throw std::exception("folder#get_file requires a relative path.");

		return file(m_folder_path / file_path);
	}

	const std::filesystem::path folder::get_path() const
	{
		return m_folder_path;
	}
}
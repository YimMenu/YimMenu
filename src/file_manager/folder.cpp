#include "folder.hpp"

#include "file_manager.hpp"

namespace big
{
	folder::folder(const std::filesystem::path& folder_path) :
	    m_folder_path(folder_path)
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
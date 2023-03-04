#pragma once

namespace big
{
	class file_manager;

	class file
	{
	public:
		file(std::filesystem::path file_path);

		file copy(std::filesystem::path new_path);
		bool exists() const;
		const std::filesystem::path get_path() const;
		file move(std::filesystem::path new_path);

	protected:
		file(file_manager* file_manager, std::filesystem::path file_path);

	private:
		friend class file_manager;

		bool m_is_project_file;
		std::filesystem::path m_file_path;
	};
}
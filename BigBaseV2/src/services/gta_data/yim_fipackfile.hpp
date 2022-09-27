#pragma once
#include <pugixml.hpp>

namespace big
{
	class yim_fipackfile
	{
		static constexpr auto default_mount_name = "yimM:/";

		rage::fiPackfile* rpf;
		std::string mount_name;

	public:
		explicit yim_fipackfile(rage::fiPackfile* rpf, const std::string& mount_name);

		static void for_each_fipackfile(std::function<size_t(yim_fipackfile& rpf_wrapper)> cb);
		std::vector<std::string> get_file_paths();

		template <typename T>
		void read_file(const std::string& path, std::function<void(const T& file_content)> cb)
		{
			auto handle = rpf->Open(path.c_str(), true);
			if (handle != -1)
			{
				auto data_length = rpf->GetFileLength(handle);

				T file_content{};
				file_content.resize(data_length);

				int read = rpf->ReadFull(handle, file_content.data(), data_length);

				cb(file_content);

				rpf->Close(handle);
			}
		}

		void read_xml_file(const std::string& path, std::function<void(pugi::xml_document& doc)> cb);

	private:

	};
}

#include "yim_fipackfile.hpp"

#include "gta/fidevice.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	yim_fipackfile::yim_fipackfile(rage::fiPackfile* rpf, const std::string& mount_name)
	{
		this->rpf        = rpf;
		this->mount_name = mount_name;
	}

	void yim_fipackfile::add_wrapper_call_back(std::function<void(yim_fipackfile& rpf_wrapper, std::filesystem::path path)> cb)
	{
		m_wrapper_call_back.push_back(cb);
	}

	void yim_fipackfile::traverse_rpf_file(const std::u8string& path, int depth)
	{
		std::string mount_path = std::format("temp{}:/", depth);

		rage::fiPackfile packfile;
		packfile.OpenPackfile(reinterpret_cast<const char*>(path.c_str()), true, 0, 0);
		packfile.Mount(mount_path.c_str());

		yim_fipackfile rpf_wrapper = yim_fipackfile(&packfile, mount_path);

		const auto files = rpf_wrapper.get_file_paths();
		for (const auto& file : files)
		{
			if (file.extension() == ".rpf")
			{
				if (auto handle = ((rage::fiDevice*)&packfile)->Open(reinterpret_cast<const char*>(file.u8string().c_str()), true))
				{
					uint32_t encryption_type{};
					((rage::fiDevice*)&packfile)->Seek(handle, 12, 0);
					((rage::fiDevice*)&packfile)->Read(handle, &encryption_type, 4);
					((rage::fiDevice*)&packfile)->Close(handle);

					if (encryption_type == 0xFFFFFF9)
						continue; // skip AES encrypted RPFs

					traverse_rpf_file(file.u8string(), depth + 1);
				}
			}
			else
			{
				std::for_each(yim_fipackfile::m_wrapper_call_back.begin(), yim_fipackfile::m_wrapper_call_back.end(), [&rpf_wrapper, file](std::function<void(yim_fipackfile & rpf_wrapper, std::filesystem::path path)> cb) {
					cb(rpf_wrapper, file);
				});
			}
		}

		packfile.Unmount(mount_path.c_str());
		packfile.ClosePackfile();
	}

	static std::string UTF16ToCP(uint32_t code_page, std::wstring_view input)
	{
		if (input.empty())
			return {};

		const auto size = WideCharToMultiByte(code_page, 0, input.data(), static_cast<int>(input.size()), nullptr, 0, nullptr, nullptr);

		std::string output(size, '\0');

		if (size
		    != WideCharToMultiByte(code_page,
		        0,
		        input.data(),
		        static_cast<int>(input.size()),
		        output.data(),
		        static_cast<int>(output.size()),
		        nullptr,
		        nullptr))
		{
			const auto error_code = GetLastError();
			LOG(WARNING) << "WideCharToMultiByte Error in String " << error_code;
			return {};
		}

		return output;
	}

	void yim_fipackfile::for_each_fipackfile()
	{
		for (auto& entry : std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
		{
			if (!entry.is_regular_file())
			{
				continue;
			}

			const auto rel_path = std::filesystem::relative(entry.path());

			const auto utf8_path = UTF16ToCP(CP_UTF8, entry.path().native());

			if (utf8_path.empty())
				continue;

			if (utf8_path.contains("mods"))
				continue;

			if (rel_path.extension() == ".rpf")
				traverse_rpf_file(rel_path.u8string());
		}
	}

	std::vector<std::filesystem::path> yim_fipackfile::get_file_paths(std::string parent)
	{
		std::vector<std::filesystem::path> file_paths;
		if (parent.empty())
			parent = mount_name;

		std::vector<std::string> directories;

		rage::fiFindData findData = {0};
		auto handlef              = rpf->FindFirst(parent.c_str(), &findData);
		if (handlef != -1)
		{
			do
			{
				std::string fn;

				if (parent == mount_name)
					fn = std::string(parent.c_str()) + std::string(findData.fileName);
				else
					fn = std::string(parent.c_str()) + std::string("/") + std::string(findData.fileName);

				if (findData.fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					directories.push_back(fn);
				}
				else
				{
					file_paths.push_back(fn);
				}
			} while (rpf->FindNext(handlef, &findData));

			rpf->FindClose(handlef);
		}

		for (auto& directory : directories)
		{
			auto files = get_file_paths(directory);

			file_paths.insert(file_paths.end(), files.begin(), files.end());
		}

		return file_paths;
	}

	const char* yim_fipackfile::get_name()
	{
		return rpf->GetName();
	}

	void yim_fipackfile::read_file(const std::filesystem::path& path, file_contents_callback&& cb)
	{
		if (const auto handle = rpf->Open(path.string().c_str(), true); handle != -1)
		{
			const auto data_length  = rpf->GetFileLength(handle);
			const auto file_content = std::make_unique<std::uint8_t[]>(data_length);

			rpf->ReadFull(handle, file_content.get(), data_length);

			cb(file_content, data_length);

			rpf->Close(handle);
		}
	}

	void yim_fipackfile::read_xml_file(const std::filesystem::path& path, std::function<void(pugi::xml_document& doc)> cb)
	{
		read_file(path, [&cb](const std::unique_ptr<std::uint8_t[]>& file_content, const int data_size) {
			if (pugi::xml_document doc; doc.load_buffer(file_content.get(), data_size).status == pugi::xml_parse_status::status_ok)
			{
				cb(doc);
			}
		});
	}
}
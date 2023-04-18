#include "yim_fipackfile.hpp"

#include "gta/fidevice.hpp"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	yim_fipackfile::yim_fipackfile(rage::fiPackfile* rpf)
	{
		this->rpf = rpf;
	}

	void yim_fipackfile::add_wrapper_call_back(std::function<size_t(yim_fipackfile& rpf_wrapper)> cb)
	{
		m_wrapper_call_back.push_back(cb);
	}

	void yim_fipackfile::for_each_fipackfile()
	{
		for (int i = 0; i < 3672; i++)
		{
			auto* rpf = g_pointers->m_gta.m_fipackfile_instances[i];

			if (rpf)
			{
				yim_fipackfile rpf_wrapper = yim_fipackfile(rpf);

				std::for_each(yim_fipackfile::m_wrapper_call_back.begin(), yim_fipackfile::m_wrapper_call_back.end(), [&rpf_wrapper](std::function<size_t(yim_fipackfile & rpf_wrapper)> cb) {
					cb(rpf_wrapper);
				});
			}
		}
	}

	std::vector<std::filesystem::path> yim_fipackfile::get_file_paths(std::string parent)
	{
		std::vector<std::filesystem::path> file_paths;
		if (parent.empty())
			parent = "/";

		std::vector<std::string> directories;

		rage::fiFindData findData = {0};
		auto handlef              = rpf->FindFirst(parent.c_str(), &findData);
		if (handlef != -1)
		{
			do
			{
				std::string fn;

				if (parent == "/")
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

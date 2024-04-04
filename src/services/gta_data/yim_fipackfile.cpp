#include "yim_fipackfile.hpp"

#include "gta/fidevice.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "util/string_conversions.hpp"

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

	static bool safe_open_pack_file(rage::fiPackfile& packfile, const std::string& path)
	{
		return packfile.OpenPackfile(path.c_str(), true, 0, 0);
	}

	void yim_fipackfile::traverse_rpf_file(const std::string& path, int depth)
	{
		std::string mount_path = std::format("temp{}:/", depth);

		rage::fiPackfile packfile;
		if (!safe_open_pack_file(packfile, path))
		{
			LOG(INFO) << "Failed opening " << path;
			return;
		}

		packfile.Mount(mount_path.c_str());

		yim_fipackfile rpf_wrapper = yim_fipackfile(&packfile, mount_path);

		const auto files = rpf_wrapper.get_file_paths();
		for (const auto& file : files)
		{
			if (std::filesystem::path(file).extension() == ".rpf")
			{
				if (auto handle = ((rage::fiDevice*)&packfile)->Open(file.c_str(), true))
				{
					uint32_t encryption_type{};
					rage::fiDevice* device = &packfile;
					device->Seek(handle, 12, 0);
					device->Read(handle, &encryption_type, 4);
					device->Close(handle);

					if (encryption_type == 0xFFFFFF9)
						continue; // skip AES encrypted RPFs

					// OPEN / CFXP
					if (encryption_type == 0x4E45504F || encryption_type == 0x50584643)
					{
						LOG(INFO) << "Modded RPF, skipping " << file;

						continue;
					}

					traverse_rpf_file(file, depth + 1);
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

	static std::filesystem::path get_game_folder_path()
	{
		std::wstring game_module_path(MAX_PATH, '\0');

		if (GetModuleFileNameW(nullptr, game_module_path.data(), game_module_path.size()))
		{
			const auto game_folder = std::filesystem::path(game_module_path).parent_path();

			if (std::filesystem::is_directory(game_folder))
			{
				return game_folder;
			}
			else
			{
				LOG(WARNING) << "game_folder variable is not directory "
				             << reinterpret_cast<const char*>(game_folder.u8string().c_str());
			}
		}
		else
		{
			LOG(WARNING) << "Failed getting gta module path. Error code: " << GetLastError();
		}

		return {};
	}

	void yim_fipackfile::for_each_fipackfile()
	{
		const auto gta_folder = get_game_folder_path();
		if (gta_folder.empty())
		{
			LOG(WARNING) << "get_game_folder_path() failed, aborting.";
		}

		try
		{
			LOG(VERBOSE) << "GTA install directory: " << reinterpret_cast<const char*>(gta_folder.u8string().c_str());
		}
		catch (const std::exception& e)
		{
			LOG(WARNING) << "Failed printing GTA install directory: " << e.what();
		}

		// Ensure current_path is gta folder.
		std::filesystem::current_path(gta_folder);

		for (const auto& entry : std::filesystem::recursive_directory_iterator(std::filesystem::current_path(), std::filesystem::directory_options::skip_permission_denied))
		{
			if (!entry.is_regular_file())
			{
				continue;
			}

			const auto utf8_path = string_conversions::utf_16_to_code_page(CP_UTF8, entry.path().wstring());

			LOG(VERBOSE) << "Game file path: " << utf8_path;

			if (entry.path().empty())
				continue;

			const auto rel_path = std::filesystem::relative(utf8_path);

			const auto utf8_rel_path = string_conversions::utf_16_to_code_page(CP_UTF8, rel_path.wstring());
			LOG(VERBOSE) << "Game file path relative: " << utf8_rel_path;

			if (rel_path.empty())
				continue;

			if (utf8_rel_path.contains("mods"))
				continue;

			if (rel_path.extension() == ".rpf")
				traverse_rpf_file(utf8_rel_path);
		}
	}

	std::vector<std::string> yim_fipackfile::get_file_paths(std::string parent)
	{
		std::vector<std::string> file_paths;
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
			const auto file_content = std::make_unique<uint8_t[]>(data_length);

			rpf->ReadFull(handle, file_content.get(), data_length);

			cb(file_content, data_length);

			rpf->Close(handle);
		}
	}

	void yim_fipackfile::read_xml_file(const std::filesystem::path& path, std::function<void(pugi::xml_document& doc)> cb)
	{
		read_file(path, [&cb](const std::unique_ptr<uint8_t[]>& file_content, const int data_size) {
			if (pugi::xml_document doc; doc.load_buffer(file_content.get(), data_size).status == pugi::xml_parse_status::status_ok)
			{
				cb(doc);
			}
		});
	}
}
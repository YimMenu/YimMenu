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

	static std::vector<std::string> get_non_dlc_mounted_devices_names()
	{
		std::vector<std::string> non_dlc_mounted_devices_names;

		uint16_t mounted_devices_len = *g_pointers->m_fidevices_len;
		if (mounted_devices_len)
		{
			auto devices_arr                        = *(uint64_t*)g_pointers->m_fidevices;
			uint8_t** current_device_mount_name_ptr = *(unsigned __int8***)g_pointers->m_fidevices;
			auto device_i                           = 0;

			while (true)
			{
				non_dlc_mounted_devices_names.push_back(*(const char**)current_device_mount_name_ptr);

				++device_i;
				current_device_mount_name_ptr += 4;
				if (device_i >= mounted_devices_len)
					break;
			}
		}

		return non_dlc_mounted_devices_names;
	}

	void yim_fipackfile::for_each_fipackfile(std::function<size_t(yim_fipackfile& rpf_wrapper)> cb)
	{
		// the idea is to reuse existing mount points as much as possible because
		// even when mounting / unmounting properly you'll get file errors
		// and crashes if the rpf file was already mounted

		// iterate the fidevice array which contains devices that are currently mounted
		// the dlc devices are in another array
		const auto non_dlc_mounted_devices_names = get_non_dlc_mounted_devices_names();

		// for not hanging the game too much
		constexpr auto yield_increment = 80;

		auto i = 1;
		while (g_pointers->m_fipackfile_instances[i])
		{
			auto* rpf = g_pointers->m_fipackfile_instances[i];

			// its hard coded in the binary?
			if (++i >= 3672)
			{
				break;
			}

			yim_fipackfile rpf_wrapper = yim_fipackfile(rpf, default_mount_name);

			auto already_mounted = false;
			for (const auto& non_dlc_mounted_device_name : non_dlc_mounted_devices_names)
			{
				auto* non_dlc_mounted_device = rage::fiDevice::GetDevice(non_dlc_mounted_device_name.c_str(), true);

				if (rpf == non_dlc_mounted_device)
				{
					rpf_wrapper.mount_name = non_dlc_mounted_device_name;
					already_mounted        = true;
				}
			}

			if (!already_mounted)
			{
				size_t acc = 0;

				rpf_wrapper.mount_name = "memory:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "memory:";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc:";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlc:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "dlcpacks:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "common:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "commoncrc:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "update:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "update2:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "platform:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "platformcrc:/";
				acc += cb(rpf_wrapper);

				rpf_wrapper.mount_name = "gamecache:/";
				acc += cb(rpf_wrapper);

				// if we got nothing with those mount points for this rpf, mount it
				if (!acc)
				{
					rpf_wrapper.mount_name = default_mount_name;
					rpf->Mount(default_mount_name);

					cb(rpf_wrapper);

					g_pointers->m_fipackfile_unmount(default_mount_name);
				}
			}
			else
			{
				cb(rpf_wrapper);
			}

			if (i % yield_increment == 0)
				script::get_current()->yield();
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
				std::string fn = std::string(parent.c_str()) + std::string("/") + std::string(findData.fileName);

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
